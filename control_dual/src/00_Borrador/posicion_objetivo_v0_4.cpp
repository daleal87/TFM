#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TransformStamped.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <math.h>
#include <sstream>

std_msgs::Float64 longitud_cable_msg, orientacion_cable_msg;

void longitudCallback(const std_msgs::Float64::ConstPtr& longitud)
{
  longitud_cable_msg.data = longitud->data;
  ROS_INFO("Longitud: [%.3f]", longitud->data);
}

void orientacionCallback(const std_msgs::Float64::ConstPtr& orientacion)
{
  orientacion_cable_msg.data = orientacion->data;
  ROS_INFO("Orientacion: [%.3f]", orientacion->data);
}

/* void alturasonarCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
  //you can get readings with scan->ranges[]
} */

int main(int argc, char **argv)
{
  const int PUBLISH_FREQ = 10;

  ros::init(argc, argv, "posicion_objetivo");
  ros::NodeHandle node;

  ros::Subscriber longitud_cable = node.subscribe("cable/longitud", 1, longitudCallback);
  ros::Subscriber orientacion_cable = node.subscribe("cable/orientacion", 1, orientacionCallback);
  //ros::Subscriber altura_sonar = node.subscribe("sonar_height", 10, alturasonarCallback);
  ros::Publisher p3at_vel = node.advertise<geometry_msgs::Twist>("p3at/cmd_vel", 10);

  ros::Rate rate(PUBLISH_FREQ);

  while (node.ok()){

    
    geometry_msgs::Twist vel_msg;

    vel_msg.angular.z = 1.0 * orientacion_cable_msg.data;
    vel_msg.linear.x = 0.1 * longitud_cable_msg.data;
    // vel_msg.linear.x = 0.1 * sqrt(pow(longitud.data, 2) + pow(altura_sonar, 2));
    p3at_vel.publish(vel_msg);
    ROS_INFO("Velocidad: [%.3f]", orientacion_cable_msg.data);

    rate.sleep();
    ros::spinOnce();
  }
  return 0;
}
