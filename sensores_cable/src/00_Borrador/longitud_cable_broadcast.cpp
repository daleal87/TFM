#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <tf/transform_broadcaster.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <string>


void poseCallback(const turtlesim::PoseConstPtr& msg){
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  transform.setOrigin( tf::Vector3(msg->x, msg->y, msg->z) );
  tf::Quaternion q;
  q.setRPY(0, 0, msg->theta);
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", turtle_name));
}

int main(int argc, char** argv){
  ros::init(argc, argv, "longitud_cable_broadcaster");
  if (argc != 2){
  	ROS_ERROR("need turtle name as argument");
  	return -1;
  }
  turtle_name = argv[1];

  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("/base_link", 10, &poseCallback);

  ros::spin();
  return 0;
};


















int main(int argc, char **argv)
{
  const int PUBLISH_FREQ = 1000;
  float longitud;

  ros::init(argc, argv, "longitud_cable");
  ros::NodeHandle node;
  ros::Publisher longitud_cable_pub = node.advertise<std_msgs::Float64>("/cable/longitud_cable", 1);
  tf::TransformListener listener;

  ros::Rate rate(PUBLISH_FREQ);

  while (node.ok()){
     tf::StampedTransform transform;
    try{
      listener.lookupTransform("/sphere_0_x", "/sphere_20_y", ros::Time(0), transform);
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


