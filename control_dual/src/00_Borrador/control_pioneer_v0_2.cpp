#include <ros/ros.h>
#include <tf/transform_datatypes.h>

#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TransformStamped.h>
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

double obj_x, obj_y, obj_z;
double obj_roll, obj_pitch, obj_yaw;
unsigned int accion_p3at; // Acciones que esta realizando el pioneer

void posep3atCallback(const std_msgs::Float64::ConstPtr& pose_p3at)
{
    obj_x = pose_p3at->position.x;
    obj_y = pose_p3at->position.y;

    double quatx,  quaty, quatz, quatw;
    quatx = pose_p3at->oritentation.x;
    quaty = pose_p3at->oritentation.y;
    quatz = pose_p3at->oritentation.z;
    quatw = pose_p3at->oritentation.w;

    tf::Quaternion q(quatx, quaty, quatz, quatw);
    tf::Matrix3x3 m(q);
    m.getRPY(obj_roll, obj_pitch, obj_yaw);
}

void accionp3atCallback(const std_msgs::Int32::ConstPtr& accion_p3at_msg)
{
    accion_p3at = accion_p3at_msg->data;
}

int main(int argc, char **argv)
{
  const int PUBLISH_FREQ = 10;
  double distancia_a_ard2 = 2.0;
  double h_plataforma = 0.4;

  ros::init(argc, argv, "control_pioneer");
  ros::NodeHandle node;

  ros::Subscriber p3at_pose_subs = node.subscribe("guiado/pose_p3at", 1, posep3atCallback);
  ros::Subscriber accion_p3at_subs = node.subscribe("guiado/accion_p3at", 1, accionp3atCallback);

  ros::Publisher p3at_vel = node.advertise<geometry_msgs::Twist>("p3at/cmd_vel", 10);

  ros::Rate rate(PUBLISH_FREQ);

  while (node.ok())
  {
      geometry_msgs::Twist vel_msg;

      if (accion_p3at == P3AT_SEGUIMIENTO)
      {
          // Calculamos cmd_vel
          if (proyeccion_xy > distancia_a_ard2)
          {
              vel_msg.linear.x = 0.2 * proyeccion_xy;
              vel_msg.angular.z = 1.0 * obj_yaw;
          }
          else {
              vel_msg.linear.x = 0.0;
              vel_msg.angular.z = 0.0;
          }
      }
      else if (accion_p3at == P3AT_ESQUIVAOBSTACULO)
      {
          ; // TO_DO: navegacion del pioneer con PID segun trayectoria del planificador
      }
      else if (accion_p3at == P3AT_ESPERAPIONNER)
      {
          vel_msg.linear.x = 0.0;
          vel_msg.angular.z = 0.0;
      }
      else
      {
          ROS_INFO("ERROR: Accion p3at desconocida");
          vel_msg.linear.x = 0.0;
          vel_msg.angular.z = 0.0;
      }

      // Publicamos vel_msg
      p3at_vel.publish(vel_msg);

      rate.sleep();
      ros::spinOnce();
  }
  return 0;
}
