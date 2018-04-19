
#include "vision/ardrone_teleop.hpp"

ARDrone_Teleop::ARDrone_Teleop() {
    
    ros::NodeHandle params("~");

    std::string cmd_vel_topic_;
    std::string takeoff_topic_;
    std::string landing_topic_;
    std::string emergency_topic_;    
    std::string reset_topic_;
    std::string tracking_topic_;


    // VELOCITY BUTTONS //
    params.param<int>("x_axis", axes_.x.axis, 2);
    params.param<int>("y_axis", axes_.y.axis, 1);
    params.param<int>("z_axis", axes_.z.axis, 4);
    params.param<int>("yaw_axis", axes_.yaw.axis, 3);

    params.param<double>("yaw_velocity_max", axes_.yaw.max, 90.0 * M_PI / 180.0);
    params.param<int>("slow_button", buttons_.slow.button, 6);
    params.param<double>("slow_factor", slow_factor_, 0.2);

    // TASK BUTTONS //
    params.param<int>("takeoff_button", buttons_.takeoff_button.button, 13);
    params.param<int>("landing_button", buttons_.landing_button.button, 15);
    params.param<int>("emergency_button", buttons_.emergency_button.button, 14);    
    params.param<int>("reset_button", buttons_.reset_button.button, 4);
    params.param<int>("tracking_button", buttons_.tracking_button.button, 16);    

    params.param<int>("togglecam_button", buttons_.togglecam_button.button, 17);
    params.param<int>("flattrim_button", buttons_.flattrim_button.button, 1);

    // TOPICS //
    params.param("cmd_vel_topic", cmd_vel_topic_, std::string("/cmd_vel"));

    params.param("takeoff_topic", takeoff_topic_, std::string("/ardrone/takeoff"));
    params.param("landing_topic", landing_topic_, std::string("/ardrone/land"));
    params.param("emergency_topic", emergency_topic_, std::string("/ardrone/emergency_topic"));    
    params.param("reset_topic", reset_topic_, std::string("/ardrone/reset"));
    params.param("tracking_topic", tracking_topic_, std::string("/ardrone/tracking_topic"));

    params.param<double>("duration", duration, 1.0);

    // CONTROL MODE //
    std::string control_mode_str;
    params.param<std::string>("control_mode", control_mode_str, "twist");
    if (control_mode_str == "twist") {
        params.param<double>("x_velocity_max", axes_.x.max, 2.0);
        params.param<double>("y_velocity_max", axes_.y.max, 2.0);
        params.param<double>("z_velocity_max", axes_.z.max, 2.0);

        joy_subscriber_     = nh_.subscribe<sensor_msgs::Joy>("joy", 1, boost::bind(&ARDrone_Teleop::joyTwistCallback, this, _1));

        velocity_publisher_ = nh_.advertise<geometry_msgs::Twist>(cmd_vel_topic_, 10);    
    }
    else if (control_mode_str == "attitude") {
        params.param<double>("x_roll_max", axes_.x.max, 0.35);
        params.param<double>("y_pitch_max", axes_.y.max, 0.35);
        params.param<double>("z_thrust_max", axes_.z.max, 25.0);
        
        joy_subscriber_ = nh_.subscribe<sensor_msgs::Joy>("joy", 1, boost::bind(&ARDrone_Teleop::joyAttitudeCallback, this, _1));

        attitude_publisher_ = nh_.advertise<cvg_sim_msgs::AttitudeCommand>("command/attitude", 10);
        yawrate_publisher_  = nh_.advertise<cvg_sim_msgs::YawrateCommand>("command/yawrate", 10);
        thrust_publisher_   = nh_.advertise<cvg_sim_msgs::ThrustCommand>("command/thrust", 10);
    }

    // COMMON PUBLISHERS
    takeoff_pub_   = nh_.advertise<std_msgs::Empty>(takeoff_topic_, 1);
    landing_pub_   = nh_.advertise<std_msgs::Empty>(landing_topic_, 1);
    emergency_pub_ = nh_.advertise<std_msgs::Empty>(emergency_topic_, 1);
    reset_pub_     = nh_.advertise<std_msgs::Empty>(reset_topic_, 1);
    tracking_pub_  = nh_.advertise<std_msgs::Empty>(tracking_topic_, 1);

    // COMMON SERVICES
    client_togglecam = nh_.serviceClient<std_srvs::Empty>("/ardrone/togglecam");
    client_flattrim  = nh_.serviceClient<std_srvs::Empty>("/ardrone/flattrim");

} // end del constructor

void ARDrone_Teleop::joyTwistCallback(const sensor_msgs::JoyConstPtr &joy) {
    
    velocity_.linear.x = ARDrone_Teleop::getAxis(joy, axes_.x);   // 2
    velocity_.linear.y = getAxis(joy, axes_.y);   // 1
    velocity_.linear.z = getAxis(joy, axes_.z);   // 4
    velocity_.angular.z = getAxis(joy, axes_.yaw);// 3

    velocity_publisher_.publish(velocity_);
    
    ////////////////////// SLOW BUTTON //////////////////////////////
    if (getButton(joy, buttons_.slow.button)) {
        velocity_.linear.x *= slow_factor_;
        velocity_.linear.y *= slow_factor_;
        velocity_.linear.z *= slow_factor_;
        velocity_.angular.z *= slow_factor_;
    }
    
    ////////////////////// TAKEOFF //////////////////////////////
    if (getButton(joy, buttons_.takeoff_button.button)) {
        takeoff_pub_.publish(emptyMsg);
        ROS_INFO("takeoff_button pressed");
        ros::Duration(duration).sleep();
    }
    
    ////////////////////// LANDING //////////////////////////////
    if (getButton(joy, buttons_.landing_button.button)) {
        landing_pub_.publish(emptyMsg);
        ROS_INFO("landing_button pressed");
        ros::Duration(duration).sleep();
    }

    ////////////////////// EMERGENCY //////////////////////////////
    if (getButton(joy, buttons_.emergency_button.button)) {
        emergency_pub_.publish(emptyMsg);
        ROS_INFO("emergency_button pressed");
        ros::Duration(duration).sleep();
    }
    
    ////////////////////// RESET //////////////////////////////
    if (getButton(joy, buttons_.reset_button.button)) {
        reset_pub_.publish(emptyMsg);
        ROS_INFO("reset_button pressed");
        ros::Duration(duration).sleep();
    }
    
    ////////////////////// TRACKING //////////////////////////////
    if (getButton(joy, buttons_.tracking_button.button)) {
        tracking_pub_.publish(emptyMsg);
        ROS_INFO("tracking_button pressed");
        ros::Duration(duration).sleep();
    }
    
    ////////////////////// TOGGLECAM //////////////////////////////
    if (getButton(joy, buttons_.togglecam_button.button)) {
        client_togglecam.call(emptySrv);
        ROS_INFO("togglecam_button pressed");
        ros::Duration(duration).sleep();
    }

    ////////////////////// FLATTRIM //////////////////////////////
    if (getButton(joy, buttons_.flattrim_button.button)) {
        client_flattrim.call(emptySrv);
        ROS_INFO("flattrim_button pressed");
        ros::Duration(duration).sleep();
    }
}

void ARDrone_Teleop::joyAttitudeCallback(const sensor_msgs::JoyConstPtr &joy) {
    
    attitude_.roll = getAxis(joy, axes_.x);
    attitude_.pitch = getAxis(joy, axes_.y);
    attitude_publisher_.publish(attitude_);

    thrust_.thrust = getAxis(joy, axes_.z);
    thrust_publisher_.publish(thrust_);

    yawrate_.turnrate = getAxis(joy, axes_.yaw);
    if (getButton(joy, buttons_.slow.button))
    {
      yawrate_.turnrate *= slow_factor_;
    }
    yawrate_publisher_.publish(yawrate_);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
                                            //getAxis//
///////////////////////////////////////////////////////////////////////////////////////////////////////
sensor_msgs::Joy::_axes_type::value_type ARDrone_Teleop::getAxis(const sensor_msgs::JoyConstPtr &joy, Axis axis) {
    
    if (axis.axis == 0) {
        return 0;
    }

    sensor_msgs::Joy::_axes_type::value_type sign = 1.0;
    
    if (axis.axis < 0) {
      sign = -1.0;
      axis.axis = -axis.axis;
    }

    if ((size_t) axis.axis > joy->axes.size()) {
        return 0;
    }

    return sign * joy->axes[axis.axis - 1] * axis.max;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////
                                            //getButton//
///////////////////////////////////////////////////////////////////////////////////////////////////////
sensor_msgs::Joy::_buttons_type::value_type ARDrone_Teleop::getButton(const sensor_msgs::JoyConstPtr &joy, int button) {
    
    if (button <= 0) {
        return 0;
    }
    if ((size_t) button > joy->buttons.size()) {
        return 0;
    }
    return joy->buttons[button - 1];
} 
///////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
    
    ros::init(argc, argv, "ardrone_teleop");

    ARDrone_Teleop ardrone_teleop;
    ros::spin();

    return 0;
}
