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
  float pos_rela_x, pos_rela_y, pos_rela_z;

  ros::init(argc, argv, "longitud_cable");
  ros::NodeHandle node;

  ros::Publisher longitud_cable_pub = node.advertise<std_msgs::Float64>("/cable/longitud_cable", 1);
  ros::Publisher orientacion_cable_pub = node.advertise<std_msgs::Float64>("/cable/orientacion_cable", 1);

  tf::TransformListener listener_p3at, listener_ard2;

  std_msgs::Float64 longitud_cable_msg, orientacion_cable_msg;

  ros::Rate rate(PUBLISH_FREQ);

  while (node.ok()){
     tf::StampedTransform transform_p3at, transform_ard2;
     //tf::Transform transform;
    try{
      listener_p3at.lookupTransform("/odom", "/plataforma", ros::Time(0), transform_p3at);
      listener_ard2.lookupTransform("/nav", "/base_footprint", ros::Time(0), transform_ard2);
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
       ros::Duration(1.0).sleep();
    }
    
    pos_rela_x = transform_p3at.getOrigin().x() - transform_ard2.getOrigin().x();
    pos_rela_y = transform_p3at.getOrigin().y() - transform_ard2.getOrigin().y();
    pos_rela_z = transform_p3at.getOrigin().z() - transform_ard2.getOrigin().z();

    longitud_cable_msg.data = sqrt(pow(pos_rela_x, 2) + pow(pos_rela_y, 2) + pow(pos_rela_z, 2));
    orientacion_cable_msg.data = atan2(pos_rela_y, pos_rela_x);

    longitud_cable_pub.publish(longitud_cable_msg);
    orientacion_cable_pub.publish(orientacion_cable_msg);

    std::cout<<longitud_cable_msg<<std::endl;
    std::cout<<orientacion_cable_msg<<std::endl;

    ros::spinOnce();
    rate.sleep();
  }
  return 0;
}


