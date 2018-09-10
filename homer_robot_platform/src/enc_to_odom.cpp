#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include "homer_robot_platform/EncoderValues.h"
#include "math.h"
#include "ros/ros.h"

double m_distance_per_tick = 0.00039027974;
double m_wheel_diff = 0.41;
double m_x;
double m_y;
double m_theta;

double fl;
double fr;
double delta_s;
double delta_theta;
double delta_x;
double delta_y;

ros::Publisher m_odom_pub;

void encCallback(const homer_robot_platform::EncoderValues::ConstPtr& msg)
{
  fl = msg->left * m_distance_per_tick;
  fr = msg->right * m_distance_per_tick;

  delta_s = (fl + fr) / 2.0;
  delta_theta = (fr - fl) / m_wheel_diff;

  delta_x = delta_s * cos(m_theta + delta_theta / 2.0);
  delta_y = delta_s * sin(m_theta + delta_theta / 2.0);

  m_x += delta_x;
  m_y += delta_y;
  m_theta += delta_theta;

  nav_msgs::Odometry odom;

  odom.header.frame_id = "map";
  odom.header.stamp = ros::Time::now();
  odom.child_frame_id = "base_link";

  odom.twist.twist.linear.x = delta_x;
  odom.twist.twist.linear.y = delta_y;
  odom.twist.twist.angular.z = delta_theta;

  odom.pose.pose.position.x = m_x;
  odom.pose.pose.position.y = m_y;
  odom.pose.pose.orientation = tf::createQuaternionMsgFromYaw(m_theta);

  m_odom_pub.publish(odom);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "encoder_to_odom");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("/robot_platform/encoder", 10, encCallback);
  m_odom_pub = nh.advertise<nav_msgs::Odometry>("odom", 10);

  double tmp;

  if (nh.getParam("robot_platform/wheelDiff", tmp))
  {
    m_wheel_diff = tmp;
  }
  if (nh.getParam("robot_platform/distancePerTick", tmp))
  {
    m_distance_per_tick = tmp;
  }

  ROS_INFO_STREAM("encoder to odom node loaded");

  ros::spin();
  return 0;
}
