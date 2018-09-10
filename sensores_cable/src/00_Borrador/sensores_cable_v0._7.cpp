#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <tf/transform_listener.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
  const int PUBLISH_FREQ = 10;

  ros::init(argc, argv, "sensores_cable");
  ros::NodeHandle node;

  ros::Publisher longitud_cable_pub = node.advertise<std_msgs::Float64>("/cable/longitud_gps", 1);
  ros::Publisher orientacion_cable_pub = node.advertise<std_msgs::Float64>("/cable/orientacion_gps", 1);
  ros::Publisher inclinacion_cable_pub = node.advertise<std_msgs::Float64>("/cable/inclinacion_gps", 1);
  ros::Publisher proyeccionXY_cable_pub = node.advertise<std_msgs::Float64>("/cable/proyeccionXY_gps", 1);

  tf::TransformListener listener;

  std_msgs::Float64 longitud_cable_msg, orientacion_cable_msg, inclinacion_cable_msg, proyeccionXY_cable_msg;

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

    longitud_cable_msg.data = sqrt(pow(transform.getOrigin().x(), 2) + pow(transform.getOrigin().y(), 2) + pow(transform.getOrigin().z(), 2));
    orientacion_cable_msg.data = atan2(transform.getOrigin().y(), transform.getOrigin().x());
    inclinacion_cable_msg.data = asin(transform.getOrigin().z() / longitud_cable_msg.data);
    proyeccionXY_cable_msg.data = longitud_cable_msg.data * cos(inclinacion_cable_msg.data);

    longitud_cable_pub.publish(longitud_cable_msg);
    orientacion_cable_pub.publish(orientacion_cable_msg);
    inclinacion_cable_pub.publish(inclinacion_cable_msg);
    proyeccionXY_cable_pub.publish(proyeccionXY_cable_msg);

    ros::spinOnce();
    rate.sleep();
  }
  return 0;
}


