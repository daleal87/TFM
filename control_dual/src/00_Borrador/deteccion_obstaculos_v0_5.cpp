#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <nav_msgs/Odometry.h>

#include <stdio.h>
#include <math.h>
#include <tuple>

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
std_msgs::Float64 altura_a_suelo_msg;

unsigned int accion_ard2, accion_p3at; // Acciones que estan realizando los robots
double proyeccion_xy, orientacion_cable; // Informacion sobre el cable

double dist_centro_plataforma, h_kalman_odom, h_kalman_sonar, h_obstaculo; // Distancia al centro de la plataforma desde el lado en la direccion de la proyeccion del cable
bool obstaculo_detectado; // Deteccion / No_Deteccion de obstaculo

void proyeccionXYCallback(const std_msgs::Float64::ConstPtr& proyeccionXY_msg)
{
  proyeccion_xy = proyeccionXY_msg->data; // Leemos el valor del topic de la proyeccion del cable sobre el plano XY
}

void orientacionCallback(const std_msgs::Float64::ConstPtr& orientacion_cable_msg)
{
  orientacion_cable = orientacion_cable_msg->data; // Leemos el valor del topic que indica la orientacion del cable
}

void kalmanodomCallback(const nav_msgs::Odometry::ConstPtr& kalman_odom_msg)
{
    h_kalman_odom = kalman_odom_msg->pose.pose.position.z; // Altura segun el filtro de kalman con todos los sensores
}

void kalmansonarCallback(const nav_msgs::Odometry::ConstPtr& kalman_sonar_msg)
{
    h_kalman_sonar = kalman_sonar_msg->pose.pose.position.z; // Altura segun el filtro de kalman con solo el sonar
}

std::tuple<bool, double> detector_obstaculos(double h_kalman_odom, double h_kalman_sonar, unsigned int accion_ard2)
{   
    if (h_kalman_odom * 0.6 > h_kalman_sonar && h_kalman_odom - h_kalman_sonar > 0.3 && accion_ard2 >= 2) {
        obstaculo_detectado = true;
        h_obstaculo = h_kalman_odom - h_kalman_sonar;

        ROS_INFO("OBSTACULO DETECTADO!!!");
        ROS_INFO("h_obstaculo: %3f", h_obstaculo);
        ROS_INFO("h_kalman_odom: %3f", h_kalman_odom);
        ROS_INFO("h_kalman_sonar: %3f", h_kalman_sonar);

    }
    else {
        obstaculo_detectado = false;
        /*
        ROS_INFO("LIBRE!!");
        ROS_INFO("h_kalman_odom: %3f", h_kalman_odom);
        ROS_INFO("h_kalman_sonar: %3f", h_kalman_sonar);
        ROS_INFO("Estado drone: %i", accion_ard2);
        */
    }

    return std::make_tuple(obstaculo_detectado, h_obstaculo);
    // Devolvemos si se ha detectado un obstaculo y la altura estimada del mismo
}


int main(int argc, char **argv)
{
    // TO_DO: lado plataforma correcto? Ajustar si circulo
    // TO_DO: ajustar a la forma de la plataforma (cuadrada o redonde) y su dimension
    double lado_plataforma = 0.8; // Medida del lado de la plataforma. Nota: ahora es un cuadrado
    double h_plataforma = 0.4; // Altura de la plataforma del AGV
    const int PUBLISH_FREQ = 10;

    int cuenta_obstaculo = 0;
    obstaculo_detectado = false;
    bool deteccion_actual = false;
    bool deteccion_anterior = false;

    accion_ard2 = UNKNOWN_ACTION;
    accion_p3at = UNKNOWN_ACTION;

    ros::init(argc, argv, "detector_obstaculos");
    ros::NodeHandle node;

    // Subcribers a topics
    ros::Subscriber proyeccionXY_cable_subs = node.subscribe("cable/proyeccionXY_gps", 1, proyeccionXYCallback);
    ros::Subscriber orientacion_cable_subs = node.subscribe("cable/orientacion_gps", 1, orientacionCallback);
    ros::Subscriber kalman_odom_subs = node.subscribe("ardrone/kalman_odom", 1, kalmanodomCallback);
    ros::Subscriber kalman_sonar_subs = node.subscribe("ardrone/kalman_sonar", 1, kalmansonarCallback);

    // Publishers
    ros::Publisher accion_ard2_pub = node.advertise<std_msgs::Int32>("guiado/accion_ard2", 10);
    ros::Publisher accion_p3at_pub = node.advertise<std_msgs::Int32>("guiado/accion_p3at", 10);
    ros::Publisher altura_a_suelo_pub = node.advertise<std_msgs::Float64>("ardrone/altura_a_suelo", 10);

    ros::Rate rate(PUBLISH_FREQ);

    while (node.ok()){

          std::tie(deteccion_actual, h_obstaculo) = detector_obstaculos(h_kalman_odom, h_kalman_sonar, accion_ard2);
          if (deteccion_actual != deteccion_anterior && cuenta_obstaculo == 0)
          {
              cuenta_obstaculo++;
              deteccion_anterior = deteccion_actual;
          }
          else if (deteccion_actual == deteccion_anterior && cuenta_obstaculo >= 1 && cuenta_obstaculo < 3)
          {
              cuenta_obstaculo++;
          }
          else if (deteccion_actual == deteccion_anterior && cuenta_obstaculo >= 3)
          {
              obstaculo_detectado = deteccion_actual;
          }
          else if (deteccion_actual != deteccion_anterior && cuenta_obstaculo > 0)
          {
              cuenta_obstaculo = 0;
              deteccion_actual = deteccion_actual;
          }
          // ¿TO_DO?: ¿añadir un filtro para la altura? Ej: calcule la media de las mediciones y que estas tengan
          // que estar dentro un un +/-x%?

          dist_centro_plataforma = lado_plataforma / (2 * std::abs(cos(orientacion_cable)));

          // CONDICION 1 ||  __OK__
          if (proyeccion_xy <= dist_centro_plataforma && accion_ard2 <= ARD2_VUELOSOBRESUELO) {
              accion_ard2 = ARD2_VUELOSOBREPLATAFORMA;
              accion_p3at = P3AT_SEGUIMIENTO;

              altura_a_suelo_msg.data = h_kalman_sonar + h_plataforma;
          }
          // CONDICION 2 ||  __OK__
          else if (proyeccion_xy > dist_centro_plataforma && accion_ard2 <= ARD2_VUELOSOBRESUELO && !obstaculo_detectado) {
              accion_ard2 = ARD2_VUELOSOBRESUELO;
              accion_p3at = P3AT_SEGUIMIENTO;

              altura_a_suelo_msg.data = h_kalman_sonar;
          }
          // CONDICION 3 ||  ~~ PDTE ~~
          else if (obstaculo_detectado && accion_ard2 <= ARD2_VUELOSOBRESUELO) {
              accion_ard2 = ARD2_MARCAJEOBSTACULO;
              accion_p3at = P3AT_ESQUIVAOBSTACULO;

              altura_a_suelo_msg.data = h_kalman_sonar + h_obstaculo;

              // TO_DO: funciones:
              //            - Guardar posicion y altura del objeto
              //            - Hacer que el drone mantenga esta posicion
          }
          // CONDICION 4 ||  ~~ PDTE ~~
          else if (accion_ard2 == ARD2_MARCAJEOBSTACULO && accion_p3at == P3AT_ESQUIVAOBSTACULO) {

              if (obstaculo_detectado == true)
              {
                  altura_a_suelo_msg.data = h_kalman_sonar + h_obstaculo;
                  ROS_INFO("CONDICION 4 - TRUE");
              }
              else
              {
                  altura_a_suelo_msg.data = h_kalman_sonar;
                  ROS_INFO("CONDICION 4 - FALSE");
              }

              // TO_DO: funciones:
              //            - Generar trayectoria para esquivar obstaculo
              //            - Mantener el drone en el punto que señala el obstaculo
              //            - Hacer navegar el pioneer para que esquive el obstaculo
              //            - Comprobar si el pioneer ha llegado al objetivo. En ese caso, cambiar a estado espera
          }
          // CONDICION 5 ||  ~~ PDTE ~~
          else if (accion_ard2 == ARD2_MARCAJEOBSTACULO && accion_p3at == P3AT_ESPERAPIONNER) {
              accion_ard2 = ARD2_APIONEER;

              if (obstaculo_detectado == true)
              {
                  altura_a_suelo_msg.data = h_kalman_sonar + h_obstaculo;
                  ROS_INFO("CONDICION 5 - TRUE");
              }
              else
              {
                  altura_a_suelo_msg.data = h_kalman_sonar;
                  ROS_INFO("CONDICION 5 - FALSE");
              }

              // TO_DO: funciones:
              //            - Generar trayectoria hasta el pioneer
          }
          // CONDICION 6
          else if (proyeccion_xy <= dist_centro_plataforma && accion_ard2 == ARD2_APIONEER) {
              accion_ard2 = ARD2_VUELOSOBREPLATAFORMA;
              accion_p3at = P3AT_SEGUIMIENTO;
              // STATUS -> OK
          }
          // CONDICION 7  ||  __OK__
          else {
              accion_ard2 = UNKNOWN_ACTION;
              accion_p3at = UNKNOWN_ACTION;
          }

          // Publicamos las acciones de los robots
          accion_ard2_msg.data = accion_ard2;
          accion_p3at_msg.data = accion_p3at;
          accion_ard2_pub.publish(accion_ard2_msg);
          accion_p3at_pub.publish(accion_p3at_msg);
          altura_a_suelo_pub.publish(altura_a_suelo_msg);

          rate.sleep();
          ros::spinOnce();
    }
}
