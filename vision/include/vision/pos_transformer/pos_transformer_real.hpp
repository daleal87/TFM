/*
NODO QUE RECIBE UN PUNTO REFERENCIADO AL QUADROTOR,
LO CAMBIA PARA REFERENCIARLO AL MUNDO Y,
FINALMENTE, LO PUBLICA
*/


#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <std_srvs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PointStamped.h>
#include <cvg_sim_msgs/Altimeter.h>
#include <string>
#include <std_msgs/Int8.h>
#include <boost/function.hpp>
#include <sensor_msgs/Range.h>

class Pos_Transformer {
public:
    Pos_Transformer();
    
    void transformation(const geometry_msgs::PoseStamped& centroid);
    void timerCallback(const ros::TimerEvent& e);

private:
    ros::Subscriber platform_position_subs_;
    ros::Publisher  pose_in_world_pub_;

    geometry_msgs::PoseStamped estimated_centroid_in_world; // posición del centroide respecto del mundo
    geometry_msgs::PoseStamped prev_estimated_centroid_in_world;

    //Transformations
    tf::TransformListener tf_listener;
    tf::StampedTransform transform, transform_cam2world;

    ros::Timer timer;
    float t_ref;

    double pub_rate;

    bool found;
    double found_time;

    tf::Vector3 pose_in_world_;
    tf::Vector3 prev_pose_in_world_;
    
};
