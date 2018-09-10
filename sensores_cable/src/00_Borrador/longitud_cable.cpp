#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <tf/transform_listener.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <string>


int main(int argc, char **argv)
{
  const int PUBLISH_FREQ = 1;
  float pos_rel_x, pos_rel_y, pos_rel_z;

  ros::init(argc, argv, "longitud_cable");
  ros::NodeHandle node;
  ros::Publisher longitud_cable_pub = node.advertise<std_msgs::Float64>("/cable/longitud_cable", 1);
  tf::TransformListener listener_p3at, listener_ard2;

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

    std_msgs::Float64 longitud_cable_msg;
    pos_rel_x = transform_p3at.getOrigin().x() - transform_ard2.getOrigin().x();
    pos_rel_y = transform_p3at.getOrigin().y() - transform_ard2.getOrigin().y();
    pos_rel_z = transform_p3at.getOrigin().z() - transform_ard2.getOrigin().z();

    longitud_cable_msg.data = sqrt(pow(pos_rel_x, 2) + pow(pos_rel_y, 2) + pow(pos_rel_z, 2));
    longitud_cable_pub.publish(longitud_cable_msg);
    std::cout<<longitud_cable_msg<<std::endl;

    ros::spinOnce();
    rate.sleep();
  }
  return 0;
}


