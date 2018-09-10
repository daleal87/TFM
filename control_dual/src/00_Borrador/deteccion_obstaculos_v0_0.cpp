#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <stdio.h>
#include <math.h>

// Listado de acciones de los robots:
#define UNKNOWN_ACTION 0 // Inicio o acción desconocida

// Acciones ARD2:
#define ARD2_VUELOSOBREPLATAFORMA 1 // Drone volando sobre la plataforma
#define ARD2_VUELOSOBRESUELO 2 // Drone volando fuera de la plataforma
#define ARD2_MARCAJEOBSTACULO 3 // Drone estático sobre un obstaculo
#define ARD2_APIONEER 4 // Drone volando hasta el Pionner tras haber esquivado obstaculo

// Acciones Pioneer
#define P3AT_SEGUIMIENTO 1  // Pioneer siguiendo al drone
#define P3AT_ESQUIVAOBSTACULO 2 // Pioneer esquivando el obstaculo detectado por el drone
#define P3AT_ESPERAPIONNER 3 // Pioneer parado esperando a que el drone vuele sobre el

std_msgs::Int32 accion_ard2_msg, accion_p3at_msg;
unsigned int accion_ard2, accion_p3at; // Acciones que estan realizando los robots
double proyeccion_xy, orientacion_cable; // Informacion sobre el cable
double lado_plataforma = 0.8; // Medida del lado de la plataforma. Nota: ahora es un cuadrado
double dist_centro_plataforma; // Distancia al centro de la plataforma desde el lado en la direccion de la proyeccion del cable
bool obstaculo_detectado; // Deteccion / No_Deteccion de obstaculo

void proyeccionXYCallback(const std_msgs::Float64::ConstPtr& proyeccionXY_msg)
{
  proyeccion_xy = proyeccionXY_msg->data; // Leemos el valor del topic de la proyeccion del cable sobre el plano XY
}

void orientacionCallback(const std_msgs::Float64::ConstPtr& orientacion_cable_msg)
{
  orientacion_cable = orientacion_cable_msg->data; // Leemos el valor del topic que indica la orientacion del cable
}


// PDTE: deteccion de obstaculos



int main(int argc, char **argv)
{
  const int PUBLISH_FREQ = 10;
  accion_ard2 = UNKNOWN_ACTION;
  accion_p3at = UNKNOWN_ACTION;
  obstaculo_detectado = false;

  ros::init(argc, argv, "detector_obstaculos");
  ros::NodeHandle node;

  ros::Subscriber proyeccionXY_cable_subs = node.subscribe("cable/proyeccionXY_gps", 1, proyeccionXYCallback);
  ros::Subscriber orientacion_cable_subs = node.subscribe("cable/orientacion_gps", 1, orientacionCallback);
  ros::Publisher accion_ard2_pub = node.advertise<std_msgs::Int32>("guiado/accion_ard2", 10);
  ros::Publisher accion_p3at_pub = node.advertise<std_msgs::Int32>("guiado/accion_p3at", 10);

  ros::Rate rate(PUBLISH_FREQ);

   while (node.ok()){

      dist_centro_plataforma = lado_plataforma / (2 * std::abs(cos(orientacion_cable)));

      if (proyeccion_xy <= dist_centro_plataforma && accion_ard2 <= ARD2_VUELOSOBRESUELO) {
          accion_ard2 = ARD2_VUELOSOBREPLATAFORMA;
          accion_p3at = P3AT_SEGUIMIENTO;
          // TO_DO: funciones
      }
      else if (proyeccion_xy > dist_centro_plataforma && accion_ard2 <= ARD2_VUELOSOBRESUELO) {
          accion_ard2 = ARD2_VUELOSOBRESUELO;
          accion_p3at = P3AT_SEGUIMIENTO;
          // TO_DO: funciones
      }
      else if (obstaculo_detectado && accion_ard2 <= ARD2_VUELOSOBRESUELO) {
          accion_ard2 = ARD2_MARCAJEOBSTACULO;
          accion_p3at = P3AT_ESQUIVAOBSTACULO;
          // TO_DO: funciones
      }
      else if (accion_ard2 == ARD2_MARCAJEOBSTACULO && accion_p3at == P3AT_ESQUIVAOBSTACULO) {
          // TO_DO: funciones
          // TO_DO: condicion de cambio de estados
      }
      else if (accion_ard2 == ARD2_MARCAJEOBSTACULO && accion_p3at == P3AT_ESPERAPIONNER) {
          accion_ard2 = ARD2_APIONEER;
          // TO_DO: funciones
      }
      else if (proyeccion_xy <= dist_centro_plataforma && accion_ard2 == ARD2_APIONEER) {
          accion_ard2 = ARD2_VUELOSOBREPLATAFORMA;
          accion_p3at = P3AT_SEGUIMIENTO;
      }
      else {
          accion_ard2 = UNKNOWN_ACTION;
          accion_p3at = UNKNOWN_ACTION;
      }

      // Publicamos las acciones de los robots
      accion_ard2_msg.data = accion_ard2;
      accion_p3at_msg.data = accion_p3at;
      accion_ard2_pub.publish(accion_ard2_msg);
      accion_p3at_pub.publish(accion_p3at_msg);

      rate.sleep();
      ros::spinOnce();

    }
}
