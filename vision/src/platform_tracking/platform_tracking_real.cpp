#include "vision/platform_tracking/platform_tracking_real.hpp"

Platform_Tracking::Platform_Tracking() {
	std::string cmd_topic_vel_;  //! Name of the topic where it will be publishing the velocity
    std::string pred_platf_pos_topic_; //topic from which we take the predicted position of the platform
    std::string platform_position_topic_;
    
    std::string ardrone_navdata_topic_;
    std::string takeoff_topic_;
    std::string landing_topic_;
    std::string emergency_topic_;
    std::string tracking_topic_;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    nh_.param("cmd_topic_vel", cmd_topic_vel_, std::string("/cmd_vel"));
    nh_.param("platform_position_topic", platform_position_topic_, std::string("/aruco_single/pose"));
    nh_.param("pred_platf_pos_topic", pred_platf_pos_topic_, std::string("/prediction_kalman_node/future_pos"));
    
    nh_.param("ardrone_navdata", ardrone_navdata_topic_, std::string("/ardrone/navdata"));
    nh_.param("takeoff_topic", takeoff_topic_, std::string("/ardrone/takeoff"));
    nh_.param("landing_topic", landing_topic_, std::string("/ardrone/land"));
    nh_.param("emergency_topic", emergency_topic_, std::string("/ardrone/emergency_topic"));    
    nh_.param("tracking_topic", tracking_topic_, std::string("/ardrone/tracking_topic"));    

    nh_.param("Kp", Kp, 0.1045);
    nh_.param("Ki", Ki, 0.0015);
    nh_.param("Kd", Kd, 0.008);

    nh_.param<float>("searching_altitude", searching_altitude, 1.5); // measured in m
    nh_.param<float>("takeoff_sleep_duration", takeoff_sleep_duration, 4); // measured in s
    nh_.param<float>("takeoff_vel_z", takeoff_vel_z, 0.8); // measured in m/s

    // Dynamic reconfiguration
    f = boost::bind(&Platform_Tracking::dynamicReconfigureCallback, this, _1, _2);
    server.setCallback(f);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ROS_INFO("Service I/O = [%s]", cmd_topic_vel_.c_str());

  	// Publishers
    vel_pub_     = nh_.advertise<geometry_msgs::Twist>(cmd_topic_vel_, 1);
    takeoff_pub_ = nh_.advertise<std_msgs::Empty>("ardrone/takeoff", 1);
    land_pub_    = nh_.advertise<std_msgs::Empty>("ardrone/land", 1);
    reset_pub_   = nh_.advertise<std_msgs::Empty>("ardrone/reset", 1);
    current_status_pub_ = nh_.advertise<std_msgs::Int32>("/cancel_hovering/current_status",1);

    //Subscribers
    pred_platform_position_subs_  = nh_.subscribe(platform_position_topic_, 1, &Platform_Tracking::followThatPlatform, this);

    navdata_subs_            = nh_.subscribe(ardrone_navdata_topic_, 1, &Platform_Tracking::nav_callback, this);
    takeoff_subs_            = nh_.subscribe(takeoff_topic_, 1, &Platform_Tracking::takeoff, this);
    landing_subs_            = nh_.subscribe(landing_topic_, 1, &Platform_Tracking::landing, this);
    emergency_subs_          = nh_.subscribe(emergency_topic_, 1, &Platform_Tracking::emergency, this);
    tracking_subs_           = nh_.subscribe(tracking_topic_, 1, &Platform_Tracking::tracking, this);


    //Timer
    timer = nh_.createTimer(ros::Duration(0.0025), &Platform_Tracking::timerCallback, this);

    // ----------------------------- SERVICES --------------------------------- //
    //Ask for services
    client_1 = nh_.serviceClient<std_srvs::Empty>("/ardrone/togglecam");
    client_2 = nh_.serviceClient<std_srvs::Empty>("/ardrone/flattrim");

    std_srvs::Empty::Request req;
    std_srvs::Empty::Response resp;


    t_ref = 0.0;

    // ------------------ TRANSFORMATIONS FROM CAM TO BODY OF QUADROTOR --------- //
    int i = 0;
    tf_listener.waitForTransform("/base_ard2","/odom", ros::Time(0), ros::Duration(3.0));         
    try{
        tf_listener.lookupTransform("/base_ard2","/odom",ros::Time(0), transform);
        ROS_INFO("Trying to lookupTransform transform (0)");
        i=3;
        t_ref = ros::Time::now().toSec();
    }
    catch (tf::TransformException ex){
        ROS_ERROR("%s",ex.what());
        ros::Duration(1.0).sleep();
    }

    while(i < 2)
    {
        ROS_ERROR("%d",i);
        tf_listener.waitForTransform("/base_ard2","/odom", ros::Time(0), ros::Duration(3.0));
        try{
            tf_listener.lookupTransform("/base_ard2","/odom",ros::Time(0), transform);
            ROS_INFO("Trying to lookupTransform transform (1)");
            i=3;
            t_ref = ros::Time::now().toSec();
        }
        catch (tf::TransformException ex){
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
            i++;
        }
    }


    // VARIABLE'S INITIALIZATION
    sumatorio_error_x = 0;
    sumatorio_error_y = 0;
    derror_x = 0;
    derror_y = 0;

    current_status.data = IDLE;

} // end del constructor

void Platform_Tracking::dynamicReconfigureCallback(TrackingRealConfig &config, uint32_t level) {
    // ROS_INFO("Reconfigure Request: %d %f %s %s %d", 
    //          config.int_param, 
    //          config.double_param, 
    //          config.str_param.c_str(), 
    //          config.bool_param?"True":"False", 
    //          config.size);
    Kp = config.Kp;
    Ki = config.Ki;
    Kd = config.Kd;
}

void Platform_Tracking::nav_callback(const ardrone_autonomy::NavdataConstPtr& nav_msg_in) {
    position_z = (double)((nav_msg_in -> altd) / pow(10,3));
    ardrone_state = nav_msg_in -> state;
}

void Platform_Tracking::takeoff(const std_msgs::EmptyConstPtr& emptyMsg) {
   current_status.data = TAKINGOFF;
   ROS_INFO("Quadrotor taking off...");
   takeoff_pub_.publish(emptyMsg);
   ros::Duration(takeoff_sleep_duration).sleep();
}

void Platform_Tracking::landing(const std_msgs::EmptyConstPtr& emptyMsg) { 
    current_status.data = LANDING;
    ROS_INFO("Quadrotor landing..."); 
}

void Platform_Tracking::emergency(const std_msgs::EmptyConstPtr& emptyMsg) {
    current_status.data = EMERGENCY;
    ROS_INFO("EMERGENCY! Landing quadrotor!");
    land_pub_.publish(emptyMsg);
}

void Platform_Tracking::tracking(const std_msgs::EmptyConstPtr& emptyMsg) {
    current_status.data = TRACKING;
    ROS_INFO("Let's follow that platform");
    
    vel.linear.z = 0.0;
    
    vel.angular.x = 0.8;
    vel.angular.y = 0.8;

    vel_pub_.publish(vel);

}

void Platform_Tracking::timerCallback(const ros::TimerEvent& e) {

    if (current_status.data == TAKINGOFF) {

       
        ROS_INFO("Taking off...");
        vel.angular.x = 0.8;
        vel.angular.y = 0.8;
        vel.linear.z = takeoff_vel_z;       

        if (position_z > searching_altitude) {
            vel.angular.x = 0.8;
            vel.angular.y = 0.8;
            vel.linear.z = 0;
            //current_status.data = TRACKING;    
        } 

        vel_pub_.publish(vel);
    } 

    if ( (current_status.data == LANDING) && ( std::fabs( ros::Time::now().toSec() - found_time) > 1 ) ) {
        ROS_INFO_STREAM("Ojetivo perdido! Iniciando maniobra de relocalizacion");
        current_status.data = TAKINGOFF;
        ROS_INFO_STREAM("Quadrotor status: TAKINGOFF");
        sumatorio_error_x = 0;
        sumatorio_error_y = 0;
        derror_x = 0;
        derror_y = 0;
    }


    if ( (current_status.data == TRACKING) && ( std::fabs( ros::Time::now().toSec() - found_time) > 3.0 ) ) {
        ROS_INFO_STREAM("Ojetivo perdido! Iniciando maniobra de relocalizacion");
        current_status.data = SEARCHING;
        ROS_INFO_STREAM("Quadrotor status: SEARCHING");
        

        vel.linear.x = Kp*position_x0;
        vel.linear.y = Kp*position_y0;

        vel_pub_.publish(vel);
    }

    if (current_status.data == TRACKING) {
        vel.angular.x = 0.8;
        vel.angular.y = 0.8;
        vel_pub_.publish(vel);
    }

    current_status_pub_.publish(current_status);
}


void  Platform_Tracking::followThatPlatform(const geometry_msgs::PoseWithCovarianceStamped& prediction){

    found_time = ros::Time::now().toSec();
    ROS_INFO("OBJETIVO LOCALIZADO");

    tf::Vector3 pred_point( prediction.pose.pose.position.x, prediction.pose.pose.position.y, prediction.pose.pose.position.z);
    
    tf_listener.waitForTransform("/base_ard2","/odom", ros::Time(0), ros::Duration(0.5)); //0.05
    tf_listener.lookupTransform("/base_ard2","/odom",ros::Time(0), transform);
    tf::Vector3 pred_pose_base_link = transform * pred_point;
    
    ROS_INFO_STREAM("Actual position: " << pred_pose_base_link.getX() << ", " << pred_pose_base_link.getY());

    if (current_status.data == SEARCHING) {
        current_status.data = TRACKING;
    }

    if (current_status.data == TRACKING) {
        //REGULADOR PI - proporcional a la integral del error ////////////////////////
        sumatorio_error_x += pred_pose_base_link.getX(); //Sistema simétrico
        sumatorio_error_y += pred_pose_base_link.getY();

        //REGULADOR PID - añadimos proporcionalidad ante la derivada del error ///////
        derror_x = pred_pose_base_link.getX() - position_x0;
        derror_y = pred_pose_base_link.getY() - position_y0;

        //BUENO BUENO BUENO
        vel.linear.x = Kp*pred_pose_base_link.getX() + Ki*sumatorio_error_x + Kd*derror_x;//bien
        vel.linear.y = Kp*pred_pose_base_link.getY() + Ki*sumatorio_error_y + Kd*derror_y;

        vel_pub_.publish(vel);

        position_x0 = pred_pose_base_link.getX();
        position_y0 = pred_pose_base_link.getY();

        ROS_INFO("Sending Velocity:  (%f,  %f, %f)",vel.linear.x, vel.linear.y, vel.linear.z);
        ROS_INFO("Acumulated errors:  (%f,  %f)\n\n",sumatorio_error_x, sumatorio_error_y);    
    }
    else if (current_status.data == LANDING) {
        //REGULADOR PI - proporcional a la integral del error ////////////////////////
        sumatorio_error_x += pred_pose_base_link.getX(); //Sistema simétrico
        sumatorio_error_y += pred_pose_base_link.getY();

        //REGULADOR PID - añadimos proporcionalidad ante la derivada del error ///////
        derror_x = pred_pose_base_link.getX() - position_x0;
        derror_y = pred_pose_base_link.getY() - position_y0;

        //TODO poner a cero el sumatorio_error!!!!!!!

        //BUENO BUENO BUENO
        vel.linear.x = Kp*pred_pose_base_link.getX() + Ki*sumatorio_error_x + Kd*derror_x;//bien
        vel.linear.y = Kp*pred_pose_base_link.getY() + Ki*sumatorio_error_y + Kd*derror_y;

        position_x0 = pred_pose_base_link.getX();
        position_y0 = pred_pose_base_link.getY();

        
        ROS_INFO("Sending Velocity:  (%f,  %f, %f)",vel.linear.x, vel.linear.y, vel.linear.z);
        ROS_INFO("Acumulated errors:  (%f,  %f)\n\n",sumatorio_error_x, sumatorio_error_y);

        // LANDING STATEMENTS
        if ( (position_z <= 2.5) && (position_z > 0.5) ) {
            vel.linear.z = -0.4;
        }
        else if ( position_z <= 0.5 ) {
            land_pub_.publish(emptyMsg);
        }
    }
} // end of tracking callback


int main(int argc, char** argv) {
    ros::init(argc, argv, "platform_tracking");
    Platform_Tracking platform_tracking;
    ROS_INFO("Set up completed. Ready to start mission");
    ros::spin();
}

