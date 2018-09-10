#include <ros/ros.h>
#include <sensor_msgs/Range.h>
#include <nav_msgs/Odometry.h>
#include <ardrone_autonomy/Navdata.h>
#include <tf/transform_broadcaster.h>

#include <stdint.h>
#include <vector>
#include <string>


void PublishOdometry(sensor_msgs::Range);
void sonarheigthCallback(const sensor_msgs::Range::ConstPtr&);

sensor_msgs::Range sonar_height;
ros::Publisher odo_pub;
std::string drone_frame_base;


int main(int argc, char** argv)
{
    const int PUBLISH_FREQ = 50;

    ros::init(argc, argv, "sonar_height_a_odometry");

    ros::NodeHandle node;

    ros::Subscriber sonar_height_sub = node.subscribe("sonar_height", 1, sonarheigthCallback);
    odo_pub = node.advertise<nav_msgs::Odometry>("ardrone/odom_sonar_height", 10);


    ros::NodeHandle nh_param("~");
    nh_param.param<std::string>("drone_frame_base", drone_frame_base, "base_ard2");

    ros::Rate rate(PUBLISH_FREQ);

    while (node.ok()){

        PublishOdometry(sonar_height);

        rate.sleep();
        ros::spinOnce();
    }
}


void PublishOdometry(sensor_msgs::Range sonar_height)
{
  nav_msgs::Odometry odo_msg;

  odo_msg.header.stamp = sonar_height.header.stamp;
  odo_msg.header.frame_id = "odom";
  odo_msg.child_frame_id = drone_frame_base;

  odo_msg.pose.pose.position.x = 0;
  odo_msg.pose.pose.position.y = 0;
  odo_msg.pose.pose.position.z = sonar_height.range;
  odo_msg.pose.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, 0);

  odo_msg.twist.twist.linear.x = 0;
  odo_msg.twist.twist.linear.y = 0;
  odo_msg.twist.twist.linear.z = 0;

  odo_pub.publish(odo_msg);
}

void sonarheigthCallback(const sensor_msgs::Range::ConstPtr& sonar_height_msg)
{
  sonar_height.range = sonar_height_msg->range; // Leemos el valor del topic navadata
}
