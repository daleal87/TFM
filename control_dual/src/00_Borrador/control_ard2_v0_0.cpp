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

std_msgs::Float64 orientacion_cable_msg;
double proyeccion_xy;

void proyeccionXYCallback(const std_msgs::Float64::ConstPtr& proyeccionXY_msg)
{
  proyeccion_xy = proyeccionXY_msg->data;
}

void orientacionCallback(const std_msgs::Float64::ConstPtr& orientacion)
{
  orientacion_cable_msg.data = orientacion->data;
}


int main(int argc, char **argv)
{
  const int PUBLISH_FREQ = 10;

  double h_plataforma = 0.4;

  ros::init(argc, argv, "posicion_objetivo");
  ros::NodeHandle node;

  ros::Subscriber proyeccionXY_cable_subs = node.subscribe("cable/proyeccionXY_gps", 1, proyeccionXYCallback);
  ros::Subscriber orientacion_cable_subs = node.subscribe("cable/orientacion_gps", 1, orientacionCallback);
  ros::Publisher p3at_vel = node.advertise<geometry_msgs::Twist>("p3at/cmd_vel", 10);

  ros::Rate rate(PUBLISH_FREQ);

  while (node.ok()){

    geometry_msgs::Twist vel_msg;

    // Calculamos cmd_vel
    if (proyeccion_xy > 2) {
      vel_msg.angular.z = 1.0 * orientacion_cable_msg.data;
      vel_msg.linear.x = 0.2 * proyeccion_xy;
    }
    else {
      vel_msg.angular.z = 0.0;
      vel_msg.linear.x = 0.0;
    }

    // Publicamos vel_msg
    p3at_vel.publish(vel_msg);

    rate.sleep();
    ros::spinOnce();
  }
  return 0;
}
