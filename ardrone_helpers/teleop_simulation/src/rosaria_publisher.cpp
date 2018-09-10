#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>

geometry_msgs::Twist twist_rosaria;

void p3at_cmd_vel_Callback(const geometry_msgs::Twist::ConstPtr& p3at_cmd_vel)
{
  twist_rosaria.angular = p3at_cmd_vel->angular;
  twist_rosaria.linear = p3at_cmd_vel->linear;
}

int main(int argc, char **argv)
{
  const int PUBLISH_FREQ = 10;

  ros::init(argc, argv, "rosaria_publisher");
  ros::NodeHandle node;

  ros::Subscriber longitud_cable_subs = node.subscribe("p3at/cmd_vel", 1, p3at_cmd_vel_Callback);
  ros::Publisher twist_rosaria_pub = node.advertise<geometry_msgs::Twist>("RosAria/cmd_vel", 1);

  ros::Rate rate(PUBLISH_FREQ);

  while (node.ok()){

    twist_rosaria_pub.publish(twist_rosaria);

    rate.sleep();
    ros::spinOnce();
  }
}


