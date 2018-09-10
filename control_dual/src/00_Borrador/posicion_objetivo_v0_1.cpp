#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/transform_listener.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
  const int PUBLISH_FREQ = 10;

  ros::init(argc, argv, "posicion_objetivo");
  ros::NodeHandle node;

  ros::Publisher p3at_vel = node.advertise<geometry_msgs::Twist>("p3at/cmd_vel", 10);

  tf2_ros::Buffer tfBuffer;
  tf::TransformListener listener;

  std_msgs::Float64 longitud_cable_msg, orientacion_cable_msg;

  ros::Rate rate(PUBLISH_FREQ);

  while (node.ok()){
     geometry_msgs::TransformStamped transformStamped;
     tf::StampedTransform transform;
    try{
       transformStamped = tfBuffer.lookupTransform("plataforma", "base_ard2", ros::Time(0));
    }
    catch (tf2::TransformException &ex) {
       ROS_WARN("%s",ex.what());
       ros::Duration(1.0).sleep();
       continue;
    }

    geometry_msgs::Twist vel_msg;

    vel_msg.angular.z = 4.0 * atan2(transformStamped.transform.translation.y,
                                   transformStamped.transform.translation.x);
    vel_msg.linear.x = 0.5 * sqrt(pow(transformStamped.transform.translation.x, 2) +
                                  pow(transformStamped.transform.translation.y, 2));
    p3at_vel.publish(vel_msg);

    rate.sleep();
  }
  return 0;
}
