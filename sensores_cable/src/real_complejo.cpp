#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <tf/transform_listener.h>

#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <math.h>
#include <string>


float inclinacion, orientacion, longitud;
//geometry_msgs::Pose pose_p3at;
float posX, posY, posZ;

void imucableCallback(const geometry_msgs::Vector3Stamped::ConstPtr& msg) // TO_DO: tipo mensaje
{
    inclinacion = msg->vector.y;
    orientacion = msg->vector.z;
}

void longitudCallback(const std_msgs::Int32::ConstPtr& msg)  // TO_DO: tipo mensaje
{
    inclinacion = msg->data / 1000.0;
}

void p3atkalmanodomCallback(const nav_msgs::Odometry::ConstPtr& p3at_kalman_odom_msg)
{
    //pose_p3at = p3at_kalman_odom_msg->pose.pose;
    posX =  p3at_kalman_odom_msg->pose.pose.position.x;
    posY =  p3at_kalman_odom_msg->pose.pose.position.y;
    posZ =  p3at_kalman_odom_msg->pose.pose.position.z;
}

int main(int argc, char **argv)
{
  const int PUBLISH_FREQ = 50;

  ros::init(argc, argv, "sensores_cable");
  ros::NodeHandle node;

  // Subscribers
  ros::Subscriber longitud_cable_sub =  node.subscribe("/cable/longitud_real", 1, longitudCallback);
  ros::Subscriber imu_cable_subs =  node.subscribe("/imu/rpy/filtered", 1, imucableCallback);
  ros::Subscriber kalman_p3at_odom_subs = node.subscribe("p3at/kalman_odom", 1, p3atkalmanodomCallback);


  // Publishers
  ros::Publisher proyeccionXY_cable_pub = node.advertise<std_msgs::Float64>("/cable/proyeccionXY", 1);
  ros::Publisher orientacion_cable_pub = node.advertise<std_msgs::Float64>("/cable/orientacion", 1);
  ros::Publisher inclinacion_cable_pub = node.advertise<std_msgs::Float64>("/cable/inclinacion", 1);
  ros::Publisher ard2_cable_pos_pub = node.advertise<nav_msgs::Odometry>("/cable/drone_pos", 1);

  // Mensajes ROS
  std_msgs::Float64 proyeccionXY_cable_msg, orientacion_cable_msg, inclinacion_cable_msg;
  nav_msgs::Odometry ard2_odo_msg;

  float h_plataforma = 0.4;
  std::string drone_frame_base = "ardrone_base_link";

  ros::Rate rate(PUBLISH_FREQ);

  while (node.ok()){
    
    proyeccionXY_cable_msg.data = longitud * cos(inclinacion);

    // TO_DO: modificar las formulas de manera que a la posicion del pioneer le sumemos la informacion del cable
    ard2_odo_msg.header.stamp = ros::Time::now();
    ard2_odo_msg.header.frame_id = "odom";
    ard2_odo_msg.child_frame_id = drone_frame_base;

    ard2_odo_msg.pose.pose.position.x = posX;
    ard2_odo_msg.pose.pose.position.y = posY;
    ard2_odo_msg.pose.pose.position.z = posZ + h_plataforma;
    ard2_odo_msg.pose.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, 0);

    // Publicamos los topics
    proyeccionXY_cable_pub.publish(proyeccionXY_cable_msg);
    orientacion_cable_pub.publish(orientacion_cable_msg);
    inclinacion_cable_pub.publish(inclinacion_cable_msg);
    ard2_cable_pos_pub.publish(ard2_odo_msg);

    ros::spinOnce();
    rate.sleep();
  }
  return 0;
}


