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

#include <dynamic_reconfigure/server.h>
#include <vision/TrackingRealConfig.h>

using vision::TrackingRealConfig;

#define IDLE 0
#define TAKINGOFF 1
#define TRACKING 2
#define LANDING 3
#define SEARCHING 4
#define EMERGENCY 5


class Platform_Tracking {
public:
    Platform_Tracking();

    void nav_callback(const ardrone_autonomy::NavdataConstPtr& nav_msg_in);
    
    void takeoff(const std_msgs::EmptyConstPtr& emptyMsg);
    void landing(const std_msgs::EmptyConstPtr& emptyMsg);
    void emergency(const std_msgs::EmptyConstPtr& emptyMsg);
    void tracking(const std_msgs::EmptyConstPtr& emptyMsg);

    void timerCallback(const ros::TimerEvent& e);
    void followThatPlatform(const geometry_msgs::PoseWithCovarianceStamped& prediction);

    virtual void dynamicReconfigureCallback(TrackingRealConfig &config, uint32_t level);



private:
    ros::NodeHandle nh_;

    std_msgs::Int32 current_status;
    int ardrone_state;

    double sumatorio_error_x;
    double sumatorio_error_y;

    double derror_x;
    double derror_y;

    double position_x0;
    double position_y0;

    //MESSAGES AND SERVICES
    geometry_msgs::Twist        vel;
    std_msgs::Empty             emptyMsg;
    std_srvs::Empty             emptySrv;

    double position_x;
    double position_y;
    double position_z;
  

    double Kp;
    double Ki;
    double Kd;

    double found_time;

    float searching_altitude;
    float takeoff_sleep_duration;
    float takeoff_vel_z;


    // PUBLISHERS
    ros::Publisher vel_pub_;

    ros::Publisher takeoff_pub_;
    ros::Publisher land_pub_;
    ros::Publisher reset_pub_;
    ros::Publisher current_status_pub_;

    //SUBSCRIBERS
    ros::Subscriber pred_platform_position_subs_; //subscriber al topic en el que el algoritmo de predicción publica la posición futura
    ros::Subscriber navdata_subs_;
    
    ros::Subscriber takeoff_subs_;
    ros::Subscriber landing_subs_;
    ros::Subscriber emergency_subs_;
    ros::Subscriber tracking_subs_;

    // TIMER
    ros::Timer timer;

    // SERVICES
    ros::ServiceClient client_1;//!togglecam
    ros::ServiceClient client_2;//!flattrim
  
    //TRANSFORMATION VARIABLES
    float t_ref;
    tf::TransformListener tf_listener;
    tf::StampedTransform  transform;

    dynamic_reconfigure::Server<TrackingRealConfig> server;
    dynamic_reconfigure::Server<TrackingRealConfig>::CallbackType f;
};
