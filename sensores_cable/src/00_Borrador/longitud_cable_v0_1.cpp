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
  float longitud;

  ros::init(argc, argv, "longitud_cable");
  ros::NodeHandle node;
  ros::Publisher longitud_cable_pub = node.advertise<std_msgs::Float64>("/cable/longitud_cable", 1);
  tf::TransformListener listener;

  ros::Rate rate(PUBLISH_FREQ);

  while (node.ok()){
     tf::StampedTransform transform;
     //tf::Transform transform;
    try{
      listener.lookupTransform("/base_link", "/sphere_20_y", ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
       ros::Duration(1.0).sleep();
    }

    std_msgs::Float64 longitud_cable_msg;
    longitud_cable_msg.data = sqrt(pow(transform.getOrigin().x(), 2) +
                                pow(transform.getOrigin().y(), 2));
    longitud_cable_pub.publish(longitud_cable_msg);
    std::cout<<longitud_cable_msg<<std::endl;

    ros::spinOnce();
    rate.sleep();
  }
  return 0;
}


