#include "vision/cancel_hovering.hpp"

Cancel_Hovering::Cancel_Hovering() {


    std::string cmd_topic_vel_;  //! Name of the topic where it will be publishing the velocity
    std::string ardrone_navdata_topic_;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    nh_.param("cmd_topic_vel", cmd_topic_vel_, std::string("/cmd_vel"));
    nh_.param("ardrone_navdata", ardrone_navdata_topic_, std::string("/ardrone/navdata"));


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Publishers
    vel_pub_ = nh_.advertise<geometry_msgs::Twist>(cmd_topic_vel_, 1);

    // Subscribers
    navdata_subs_ = nh_.subscribe(ardrone_navdata_topic_, 1, &Cancel_Hovering::nav_callback, this);
    current_status_subs_ = nh_.subscribe("cancel_hovering/current_status", 1, &Cancel_Hovering::getCurrentStatus, this);

    //Timer
    timer = nh_.createTimer(ros::Duration(0.0025), &Cancel_Hovering::timerCallback, this);

   
    vel.angular.x = 0.8;
    vel.angular.y = 0.8;

}//end of constructor

void Cancel_Hovering::nav_callback(const ardrone_autonomy::NavdataConstPtr& nav_msg_in) {
    position_z = (double)((nav_msg_in -> altd) / pow(10,3));
    ardrone_state = nav_msg_in -> state;
}



void Cancel_Hovering::timerCallback(const ros::TimerEvent& e) {
    vel.angular.x = 0.8;
    vel.angular.y = 0.8;

    switch (ardrone_state) {
        case 0:
            ROS_INFO_STREAM("ARDRONE STATE: Unknonw");
            break;
        case 1:
            ROS_INFO_STREAM("ARDRONE STATE: Inited");
            break;
        case 2:
            ROS_INFO_STREAM("ARDRONE STATE: Landed");
            break;
        case 3:
            ROS_INFO_STREAM("ARDRONE STATE: FLying");
            break;
        case 4:
            ROS_INFO_STREAM("ARDRONE STATE: Hovering");
            break;
        case 5:
            ROS_INFO_STREAM("ARDRONE STATE: Test");
            break;
        case 6:
            ROS_INFO_STREAM("ARDRONE STATE: Taking off");
            break;
        case 7:
            ROS_INFO_STREAM("ARDRONE STATE: Flying");
            break;
        case 8:
            ROS_INFO_STREAM("ARDRONE STATE: Landing");
            break;
        case 9:
            ROS_INFO_STREAM("ARDRONE STATE: Looping");
            break;
    }
    switch (current_status) {
        case 0:
            ROS_INFO_STREAM("current_status: IDLE");
            break;
        case 1:
            ROS_INFO_STREAM("current_status: TAKINGOFF");
            break;
        case 2:
            ROS_INFO_STREAM("current_status: TRACKING");
            break;
        case 3:
            ROS_INFO_STREAM("current_status: LANDING");
            break;
        case 4:
            ROS_INFO_STREAM("current_status: SEARCHING");
            break;
        case 5:
            ROS_INFO_STREAM("current_status: EMERGENCY");
            break;
    }


    //vel_pub_.publish(vel);
    //Cancel_Hovering::printArdroneState();
    //Cancel_Hovering::printCurrentStatus();
    ROS_INFO_STREAM("Altitude: " << position_z << "\n");
}

void Cancel_Hovering::printArdroneState() {
    switch (ardrone_state) {
        case 0:
            ROS_INFO_STREAM("ARDRONE STATE: Unknonw");
            break;
        case 1:
            ROS_INFO_STREAM("ARDRONE STATE: Inited");
            break;
        case 2:
            ROS_INFO_STREAM("ARDRONE STATE: Landed");
            break;
        case 3:
            ROS_INFO_STREAM("ARDRONE STATE: FLying");
            break;
        case 4:
            ROS_INFO_STREAM("ARDRONE STATE: Hovering");
            break;
        case 5:
            ROS_INFO_STREAM("ARDRONE STATE: Test");
            break;
        case 6:
            ROS_INFO_STREAM("ARDRONE STATE: Taking off");
            break;
        case 7:
            ROS_INFO_STREAM("ARDRONE STATE: Flying");
            break;
        case 8:
            ROS_INFO_STREAM("ARDRONE STATE: Landing");
            break;
        case 9:
            ROS_INFO_STREAM("ARDRONE STATE: Looping");
            break;
    }
}


void Cancel_Hovering::printCurrentStatus() {
    switch (current_status) {
        case 0:
            ROS_INFO_STREAM("current_status: IDLE");
            break;
        case 1:
            ROS_INFO_STREAM("current_status: TAKINGOFF");
            break;
        case 2:
            ROS_INFO_STREAM("current_status: TRACKING");
            break;
        case 3:
            ROS_INFO_STREAM("current_status: LANDING");
            break;
        case 4:
            ROS_INFO_STREAM("current_status: SEARCHING");
            break;
        case 5:
            ROS_INFO_STREAM("current_status: EMERGENCY");
            break;
    }
}

void Cancel_Hovering::getCurrentStatus(const std_msgs::Int32& current_status_msg) {
    current_status = current_status_msg.data;
}



int main(int argc, char** argv) {
    ros::init(argc, argv, "cancel_hovering");
    Cancel_Hovering cancel_hovering;

    ROS_INFO("Set up completed. About to start mission");

    ros::spin();
}

