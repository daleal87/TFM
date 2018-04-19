#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <cvg_sim_msgs/YawrateCommand.h>
#include <cvg_sim_msgs/ThrustCommand.h>
#include <cvg_sim_msgs/AttitudeCommand.h>
#include <std_msgs/Empty.h>
#include <std_srvs/Empty.h>

class ARDrone_Teleop {
private:

    ros::NodeHandle nh_;
  
    ros::Subscriber joy_subscriber_;
    ros::Publisher velocity_publisher_, attitude_publisher_, yawrate_publisher_, thrust_publisher_;

    // VELOCITY COMMANDS //
    geometry_msgs::Twist velocity_;
    //       -----------
    cvg_sim_msgs::AttitudeCommand attitude_;
    cvg_sim_msgs::ThrustCommand thrust_;
    cvg_sim_msgs::YawrateCommand yawrate_;

  
    // COMMON PUBLISHERS //
    ros::Publisher takeoff_pub_;
    ros::Publisher landing_pub_;
    ros::Publisher emergency_pub_;
    ros::Publisher reset_pub_;
    ros::Publisher tracking_pub_;


    // COMMON SERVICES //
    ros::ServiceClient client_togglecam;
    ros::ServiceClient client_flattrim;


    // TASK COMMANDS //
    std_msgs::Empty emptyMsg;
    std_srvs::Empty emptySrv;
  
    
    // AXIS and BUTTONS // 

    struct Axis {
        int axis;
        double max;
    };

    struct Button {
      int button;
    };

    struct {
        Axis x;
        Axis y;
        Axis z;
        Axis yaw;
    } axes_;

    struct {
        Button slow;
      
        Button takeoff_button;
        Button landing_button;
        Button emergency_button;
        Button reset_button;
        Button tracking_button;

        Button togglecam_button;
        Button flattrim_button;
    } buttons_;

    double slow_factor_;

    double duration;


public:
    ARDrone_Teleop();
    void joyTwistCallback(const sensor_msgs::JoyConstPtr &joy);
    void joyAttitudeCallback(const sensor_msgs::JoyConstPtr &joy);
    sensor_msgs::Joy::_axes_type::value_type getAxis(const sensor_msgs::JoyConstPtr &joy, Axis axis);
    sensor_msgs::Joy::_buttons_type::value_type getButton(const sensor_msgs::JoyConstPtr &joy, int button);
};


