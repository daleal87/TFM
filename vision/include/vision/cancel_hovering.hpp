#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <std_srvs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PointStamped.h>
#include <string>
#include <std_msgs/Int32.h>
#include <boost/function.hpp>
#include <sensor_msgs/Range.h>
#include <ardrone_autonomy/Navdata.h>



class Cancel_Hovering {
public:
    Cancel_Hovering();

    void nav_callback(const ardrone_autonomy::NavdataConstPtr& nav_msg_in);
    void getCurrentStatus(const std_msgs::Int32& current_status_msg);

    void timerCallback(const ros::TimerEvent& e);
    void printArdroneState();
    void printCurrentStatus();
  
private:
	ros::NodeHandle nh_;

    int32_t current_status;
    int ardrone_state;
    float position_z;

    geometry_msgs::Twist vel;

    // PUBLISHER
    ros::Publisher vel_pub_;

    //SUBSCRIBERS
    ros::Subscriber navdata_subs_;
    ros::Subscriber current_status_subs_;

    // TIMER
    ros::Timer timer;
};
