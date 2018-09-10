#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TransformStamped.h>
#include <sensor_msgs/Range.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <math.h>
#include <sstream>

std_msgs::Float64 longitud_cable_msg, orientacion_cable_msg, inclinacion_cable_msg;
double proyeccion_xy;

void longitudCallback(const std_msgs::Float64::ConstPtr& longitud)
{
  longitud_cable_msg.data = longitud->data;
  // ROS_INFO("Longitud: [%.3f]", longitud->data);
}

void orientacionCallback(const std_msgs::Float64::ConstPtr& orientacion)
{
  orientacion_cable_msg.data = orientacion->data;
  // ROS_INFO("Orientacion: [%.3f]", orientacion->data);
}

void inclinacionCallback(const std_msgs::Float64::ConstPtr& inclinacion)
{
  inclinacion_cable_msg.data = inclinacion->data;
  // ROS_INFO("Inclinacion: [%.3f]", inclinacion->data);
}


int main(int argc, char **argv)
{
  const int PUBLISH_FREQ = 10;

  double h_plataforma = 0.4;

  ros::init(argc, argv, "posicion_objetivo");
  ros::NodeHandle node;

  ros::Subscriber longitud_cable_subs = node.subscribe("cable/longitud_gps", 1, longitudCallback);
  ros::Subscriber orientacion_cable_subs = node.subscribe("cable/orientacion_gps", 1, orientacionCallback);
  ros::Subscriber inclinacion_cable_subs = node.subscribe("cable/inclinacion_gps", 1, inclinacionCallback);
  ros::Publisher p3at_vel = node.advertise<geometry_msgs::Twist>("p3at/cmd_vel", 10);

  ros::Rate rate(PUBLISH_FREQ);

  while (node.ok()){

    geometry_msgs::Twist vel_msg;

    proyeccion_xy = longitud_cable_msg.data * cos(inclinacion_cable_msg.data);

    // Calculamos cmd_vel
    if (proyeccion_xy > 1.5) {
      vel_msg.angular.z = 1.0 * orientacion_cable_msg.data;
      vel_msg.linear.x = 0.2 * proyeccion_xy;
    }
    else {
      vel_msg.angular.z = 0.0;
      vel_msg.linear.x = 0.0;
    }

    // Publicamos vel_msg
    p3at_vel.publish(vel_msg);
    ROS_INFO("Proyeccion XY: [%.3f]", proyeccion_xy);

    rate.sleep();
    ros::spinOnce();
  }
  return 0;
}
