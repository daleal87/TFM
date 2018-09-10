#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Range.h>

#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <math.h>
#include <sstream>

// Acciones Pioneer
#define P3AT_SEGUIMIENTO 1  // Pioneer siguiendo al drone
#define P3AT_ESQUIVAOBSTACULO 2 // Pioneer esquivando el obstaculo detectado por el drone
#define P3AT_ESPERAPIONNER 3 // Pioneer parado esperando a que el drone vuele sobre el

std_msgs::Float64 distancia_objetivo_msg, orientacion_objetivo_msg;
double proyeccion_xy, orientacion_cable;
unsigned int accion_p3at; // Acciones que esta realizando el pioneer

void proyeccionXYCallback(const std_msgs::Float64::ConstPtr& proyeccionXY_msg)
{
  proyeccion_xy = proyeccionXY_msg->data;
}

void orientacionCallback(const std_msgs::Float64::ConstPtr& orientacion)
{
  orientacion_cable = orientacion->data;
}

void accionp3atCallback(const std_msgs::Int32::ConstPtr& accion_p3at_msg)
{
    accion_p3at = accion_p3at_msg->data;
}

int main(int argc, char **argv)
{
  const int PUBLISH_FREQ = 10;
  double distancia_hasta_ard2 = 2.0;
  double h_plataforma = 0.4;

  ros::init(argc, argv, "posicion_objetivo");
  ros::NodeHandle node;

  // Subscribers
  ros::Subscriber proyeccionXY_cable_subs = node.subscribe("cable/proyeccionXY_gps", 1, proyeccionXYCallback);
  ros::Subscriber orientacion_cable_subs = node.subscribe("cable/orientacion_gps", 1, orientacionCallback);
  ros::Subscriber accion_p3at_subs = node.subscribe("guiado/accion_p3at", 1, accionp3atCallback);

  // Publisher
  ros::Publisher p3at_vel_pub = node.advertise<geometry_msgs::Twist>("p3at/cmd_vel", 10);
  ros::Publisher distancia_objetivo_pub = node.advertise<std_msgs::Float64>("p3at/posicion_objetivo", 10);
  ros::Publisher orientacion_objetivo_pub = node.advertise<std_msgs::Float64>("p3at/orientacion_objetivo", 10);

  ros::Rate rate(PUBLISH_FREQ);

  while (node.ok())
  {
      geometry_msgs::Twist p3at_vel_msg;

      if (accion_p3at == P3AT_SEGUIMIENTO)
      {
          // Calculamos cmd_vel
          if (proyeccion_xy > distancia_hasta_ard2)
          {
              distancia_objetivo_msg.data = proyeccion_xy - distancia_hasta_ard2;
              orientacion_objetivo_msg.data = 1.0 * orientacion_cable;
          }
          else {
              distancia_objetivo_msg.data = 0.0;
              orientacion_objetivo_msg.data = 0.0;
          }
      }
      else if (accion_p3at == P3AT_ESQUIVAOBSTACULO)
      {
          ; // TO_DO: navegacion del pioneer con PID segun trayectoria del planificador
      }
      else if (accion_p3at == P3AT_ESPERAPIONNER)
      {
          distancia_objetivo_msg.data = 0.0;
          orientacion_objetivo_msg.data = 0.0;
      }
      else
      {
          ROS_INFO("ERROR: Accion p3at desconocida");
          distancia_objetivo_msg.data = 0.0;
          orientacion_objetivo_msg.data = 0.0;
      }

      // TO_DO: leer los mensajes de los PID y pasarlos al mensaje de velocidad


      // Publicamos la distancia y orientacion objetivos
      distancia_objetivo_pub.publish(distancia_objetivo_msg);
      orientacion_objetivo_pub.publish(orientacion_objetivo_msg);

      // Publicamos la velocidad el Pioneer
      p3at_vel_pub.publish(p3at_vel_msg);

      rate.sleep();
      ros::spinOnce();
  }
  return 0;
}
