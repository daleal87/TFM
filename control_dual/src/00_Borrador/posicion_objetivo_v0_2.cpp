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

  tf::TransformListener listener;

  std_msgs::Float64 longitud_cable_msg, orientacion_cable_msg;

  ros::Rate rate(PUBLISH_FREQ);

  while (node.ok()){
     tf::StampedTransform transform;
    try{
      listener.lookupTransform("/plataforma", "/base_ard2", ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
       ros::Duration(1.0).sleep();
    }

    geometry_msgs::Twist vel_msg;

    vel_msg.angular.z = 1.0 * atan2(transform.getOrigin().y(),
                                   transform.getOrigin().x());
    vel_msg.linear.x = 0.1 * sqrt(pow(transform.getOrigin().y(), 2) +
                                  pow(transform.getOrigin().x(), 2));
    p3at_vel.publish(vel_msg);

    rate.sleep();
  }
  return 0;
}
