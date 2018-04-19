#include "vision/platform_tracking.hpp"

Platform_Tracking::Platform_Tracking() {
	std::string cmd_topic_vel_;  //! Name of the topic where it will be publishing the velocity
    std::string pred_platf_pos_topic_; //topic from which we take the predicted position of the platform
    std::string sonar_height_topic_;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    nh_.param("cmd_topic_vel", cmd_topic_vel_, std::string("/cmd_vel"));
    nh_.param("pred_platf_pos_topic", pred_platf_pos_topic_, std::string("/prediction_kalman_node/future_pos"));
    nh_.param("sonar_height_topic", sonar_height_topic_, std::string("/sonar_height"));

    nh_.param("Kp", Kp, 0.1045);
    nh_.param("Ki", Ki, 0.0015);
    nh_.param("Kd", Kd, 0.008);

    current_status = Status_n::IDLE;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ROS_INFO("Service I/O = [%s]", cmd_topic_vel_.c_str());

  	// PUBLISH through the node handle Twist type messages to the ARDrone_ctrl/command topic
    vel_pub_ = nh_.advertise<geometry_msgs::Twist>(cmd_topic_vel_, 1);
    pred_platform_pos_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("/platform_predicted_position", 1);

	//SUBSCRIBERS
    pred_platform_pos_ = nh_.subscribe(pred_platf_pos_topic_, 1, &Platform_Tracking::tracking, this);
    sonar_subs_ = nh_.subscribe(sonar_height_topic_, 1, &Platform_Tracking::sonar_height, this);
    takeoff_subscriber_ = nh_.subscribe("/ardrone/takeoff", 1, &Platform_Tracking::takeoff, this);
    landing_subscriber_ = nh_.subscribe("/ardrone/land", 1, &Platform_Tracking::landing, this);

    //TIMER
    timer = nh_.createTimer(ros::Duration(0.01), &Platform_Tracking::timerCallback, this);


    t_ref = 0.0;

    // WORLD TO QUADROTOR TRANSFORMATION
    int k = 0;
    tf_listener.waitForTransform("/base_ard2","/centre", ros::Time(0), ros::Duration(3.0));         
    try {
        tf_listener.lookupTransform("/base_ard2","/centre",ros::Time(0), transform_world2quad);
        ROS_INFO("Trying to lookupTransform transform_world2quad (0)");
        k=3;
        t_ref = ros::Time::now().toSec();
    }
    catch (tf::TransformException ex) {
        ROS_ERROR("%s",ex.what());
        ros::Duration(1.0).sleep();
    }

    while(k < 2) {
        ROS_ERROR("%d",k);
        tf_listener.waitForTransform("/base_ard2","/centre", ros::Time(0), ros::Duration(3.0));
        try {
            tf_listener.lookupTransform("/base_ard2","/centre",ros::Time(0), transform_world2quad);
            ROS_INFO("Trying to lookupTransform transform_world2quad (1)");
            k=3;
            t_ref = ros::Time::now().toSec();
        }
        catch (tf::TransformException ex) {
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
            k++;
        }
    }


    // VARIABLE'S INITIALIZATION
    sumatorio_error_x = 0;
    sumatorio_error_y = 0;
    derror_x = 0;
    derror_y = 0;


} // end del constructor


void Platform_Tracking::takeoff(const std_msgs::Int8 &takeoff_signal) {
   current_status = Status_n::TAKINGOFF;
   ROS_INFO("Quadrotor taking off...");  
}


void Platform_Tracking::landing(const std_msgs::Int8 &landing_signal) { 
    current_status = Status_n::LANDING;
    ROS_INFO("Quadrotor landing..."); 
}


void Platform_Tracking::sonar_height(const sensor_msgs::RangeConstPtr& sonar_height_quadrotor) {
    position_z = sonar_height_quadrotor->range;
}

void Platform_Tracking::timerCallback(const ros::TimerEvent& e) {

    if (!current_status == Status_n::IDLE) {
        vel_pub_.publish(vel);
    }

    if (current_status == Status_n::TAKINGOFF) {
        nh_.param("Kp", Kp, 0.1045);
        nh_.param("Ki", Ki, 0.0015);
        nh_.param("Kd", Kd, 0.008);

        sumatorio_error_x = 0;
        sumatorio_error_y = 0;
        position_x0 = 0;
        position_y0 = 0;

        vel.linear.x = 0.0;
        vel.linear.y = 0.0;
        vel.linear.z = 1;
        
        if (position_z > 5.0) {
            vel.linear.x = 0.0;
            vel.linear.y = 0.0;
            vel.linear.z = 0.0;
            current_status = Status_n::TRACKING;
        }
        
        vel_pub_.publish(vel);
        ROS_INFO("Sending Velocity:  (%f,  %f, %f)",vel.linear.x, vel.linear.y, vel.linear.z);
    } 

    if ( (current_status == Status_n::LANDING) && ( std::fabs( ros::Time::now().toSec() - found_time) > 1 ) ) {
        ROS_INFO_STREAM("Aterrizaje fallido! Objetivo perdido! Iniciando maniobra de relocalizacion");
        current_status = Status_n::TAKINGOFF;
        ROS_INFO_STREAM("Quadrotor status: TAKINGOFF");
        sumatorio_error_x = 0;
        sumatorio_error_y = 0;
        position_x0 = 0;
        position_y0 = 0;
    }

    if ( (current_status==Status_n::LANDING) && (position_z < 0.18) ) {
        current_status = Status_n::IDLE;
        ROS_INFO_STREAM("Quadrotor status: IDLE");
        vel.linear.x = 0.0;
        vel.linear.y = 0.0;
        sumatorio_error_x = 0;
        sumatorio_error_y = 0;
        position_x0 = 0;
        position_y0 = 0;

        vel_pub_.publish(vel);
        ROS_INFO("Sending Velocity:  (%f,  %f, %f)",vel.linear.x, vel.linear.y, vel.linear.z);
    }

    // IF WE WERE TRACKING THE PLATFORM, AND SUDDENLY WE LOSE IT, AND A CERTAIN AMOUNT OF TIME PASSES WITHOUT RELOCATING IT: 
    if ( (current_status == Status_n::TRACKING) && ( std::fabs( ros::Time::now().toSec() - found_time) > 1 ) ) {
        ROS_INFO_STREAM("Ojetivo perdido! Iniciando maniobra de relocalizacion");
        current_status = Status_n::SEARCHING;
        ROS_INFO_STREAM("Quadrotor status: SEARCHING");
        sumatorio_error_x = 0;
        sumatorio_error_y = 0;
        position_x0 = 0;
        position_y0 = 0;

    }
}


void  Platform_Tracking::tracking(const geometry_msgs::PoseWithCovarianceStamped& prediction){

    if (current_status == Status_n::SEARCHING) {
        current_status = Status_n::TRACKING;
    }

    found_time = ros::Time::now().toSec();
   
    tf::Vector3 pred_point( prediction.pose.pose.position.x, prediction.pose.pose.position.y, prediction.pose.pose.position.z);
    tf_listener.waitForTransform("/base_ard2","/centre", ros::Time(0), ros::Duration(0.5)); //0.05
    tf_listener.lookupTransform("/base_ard2","/centre",ros::Time(0), transform_world2quad);
    pred_pose_base_link = transform_world2quad * pred_point;

    geometry_msgs::PoseStamped pred_centroid_in_world; //posicion del centroide respecto del mundo
        pred_centroid_in_world.header.stamp= ros::Time::now();
        pred_centroid_in_world.header.seq = ros::Time::now().toSec() - t_ref;
        pred_centroid_in_world.header.frame_id = "/centre";
        pred_centroid_in_world.pose.orientation.w=1;
        pred_centroid_in_world.pose.orientation.x=0;
        pred_centroid_in_world.pose.orientation.y=0;
        pred_centroid_in_world.pose.orientation.z=0;
        pred_centroid_in_world.pose.position.x=pred_point.getX();
        pred_centroid_in_world.pose.position.y=pred_point.getY();
        pred_centroid_in_world.pose.position.z=0.0;
    pred_platform_pos_pub_.publish(pred_centroid_in_world);
    
    ROS_INFO_STREAM("Predected position: " << pred_pose_base_link.getX() << ", " << pred_pose_base_link.getY());


    if (current_status == Status_n::TRACKING) {
        // es decir, si la operación de despegue ha sido completada o si se ha vuelto a encontrar la plataforma:
        
        //REGULADOR PI - proporcional a la integral del error ////////////////////////
        sumatorio_error_x += pred_pose_base_link.getX(); //Sistema simétrico
        sumatorio_error_y += pred_pose_base_link.getY();

        //REGULADOR PID - añadimos proporcionalidad ante la derivada del error ///////
        derror_x = pred_pose_base_link.getX() - position_x0;
        derror_y = pred_pose_base_link.getY() - position_y0;

        //BUENO BUENO BUENO
        vel.linear.x = Kp*pred_pose_base_link.getX() + Ki*sumatorio_error_x + Kd*derror_x;//bien
        vel.linear.y = Kp*pred_pose_base_link.getY() + Ki*sumatorio_error_y + Kd*derror_y;

        position_x0 = pred_pose_base_link.getX();
        position_y0 = pred_pose_base_link.getY();
        
        
        //posicion del centroide respecto del mundo
            pred_centroid_in_world.header.stamp= ros::Time::now();
            pred_centroid_in_world.header.seq = ros::Time::now().toSec() - t_ref;
            pred_centroid_in_world.header.frame_id = "/centre";
            pred_centroid_in_world.pose.orientation.w=1;
            pred_centroid_in_world.pose.orientation.x=0;
            pred_centroid_in_world.pose.orientation.y=0;
            pred_centroid_in_world.pose.orientation.z=0;
            pred_centroid_in_world.pose.position.x=pred_point.getX();
            pred_centroid_in_world.pose.position.y=pred_point.getY();
            pred_centroid_in_world.pose.position.z=0.0;


        ROS_INFO("Sending Velocity:  (%f,  %f, %f)",vel.linear.x, vel.linear.y, vel.linear.z);
        ROS_INFO("Acumulated errors:  (%f,  %f)\n\n",sumatorio_error_x, sumatorio_error_y);   
    }
    else if (current_status == Status_n::LANDING) {
    
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


        //posicion del centroide respecto del mundo
            pred_centroid_in_world.header.stamp= ros::Time::now();
            pred_centroid_in_world.header.seq = ros::Time::now().toSec() - t_ref;
            pred_centroid_in_world.header.frame_id = "/centre";
            pred_centroid_in_world.pose.orientation.w=1;
            pred_centroid_in_world.pose.orientation.x=0;
            pred_centroid_in_world.pose.orientation.y=0;
            pred_centroid_in_world.pose.orientation.z=0;
            pred_centroid_in_world.pose.position.x=pred_point.getX();
            pred_centroid_in_world.pose.position.y=pred_point.getY();
            pred_centroid_in_world.pose.position.z=0.0;        
        

        ROS_INFO("Sending Velocity:  (%f,  %f, %f)",vel.linear.x, vel.linear.y, vel.linear.z);
        ROS_INFO("Acumulated errors:  (%f,  %f)\n\n",sumatorio_error_x, sumatorio_error_y);

        // LANDING STATEMENTS
        if ( (position_z <= 10) && (position_z > 2.0) ) {
            vel.linear.z = -0.4;
        }
        else if ( position_z <= 2.0 ) {
            vel.linear.z = -0.3;
            // Kp = 0.24;
            // Ki = 0.003;
            // Kd = 0.03;
        }

    }
} // end of tracking callback


int main(int argc, char** argv) {
    ros::init(argc, argv, "platform_tracking");
    Platform_Tracking platform_tracking;
    ROS_INFO("Set up completed. Ready to start mission");
    ros::spin();
}

