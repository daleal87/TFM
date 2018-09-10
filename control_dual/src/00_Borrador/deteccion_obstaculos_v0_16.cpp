#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Bool.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>

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

// ___ VARIABLES GLOBALES ___

std_msgs::Int32 accion_ard2_msg, accion_p3at_msg;
std_msgs::Float64 altura_a_suelo_msg;
geometry_msgs::Twist p3at_vel_msg, ard2_vel_msg, joy_p3at_vel_msg, joy_ard2_vel_msg;
geometry_msgs::Pose pose_p3at, pose_ard2, pose_obj_p3at, pose_obj_ard2;

unsigned int accion_ard2, accion_p3at; // Acciones que estan realizando los robots
double proyeccion_xy, orientacion_cable; // Informacion sobre el cable

double dist_centro_plataforma, h_kalman_odom, h_kalman_sonar, h_obstaculo; // Distancia al centro de la plataforma desde el lado en la direccion de la proyeccion del cable
bool obstaculo_detectado, modo_automatico; // Deteccion / No_Deteccion de obstaculo
bool teleop_p3at = false;
bool teleop_ard2 = false;

double distancia_a_ard2 = 2.5;
double altura_vuelo = 1.5;
double distancia_esquiva = 3;

// ___ CALLBACKS SUBSCRIBERS ___

void proyeccionXYCallback(const std_msgs::Float64::ConstPtr& proyeccionXY_msg)
{
  proyeccion_xy = proyeccionXY_msg->data; // Leemos el valor del topic de la proyeccion del cable sobre el plano XY
}

void orientacionCallback(const std_msgs::Float64::ConstPtr& orientacion_cable_msg)
{
  orientacion_cable = orientacion_cable_msg->data; // Leemos el valor del topic que indica la orientacion del cable
}

void ard2kalmanodomCallback(const nav_msgs::Odometry::ConstPtr& ard2_kalman_odom_msg)
{
    pose_ard2 = ard2_kalman_odom_msg->pose.pose;
    h_kalman_odom = ard2_kalman_odom_msg->pose.pose.position.z; // Altura segun el filtro de kalman con todos los sensores
}

void ard2kalmansonarCallback(const nav_msgs::Odometry::ConstPtr& ard2_kalman_sonar_msg)
{
    h_kalman_sonar = ard2_kalman_sonar_msg->pose.pose.position.z; // Altura segun el filtro de kalman con solo el sonar
}

void p3atkalmanodomCallback(const nav_msgs::Odometry::ConstPtr& p3at_kalman_odom_msg)
{
    pose_p3at = p3at_kalman_odom_msg->pose.pose;
}

void modoautomaticoCallback(const std_msgs::Bool::ConstPtr& modo_automatico_msg)
{
    modo_automatico = modo_automatico_msg->data; // Modo automatico activo
}

void joyp3atvelCallback(const geometry_msgs::Twist::ConstPtr& vel_msg)
{
    teleop_p3at = true;
    joy_p3at_vel_msg.linear.x = vel_msg->linear.x;
    joy_p3at_vel_msg.linear.y = vel_msg->linear.y;
    joy_p3at_vel_msg.linear.z = vel_msg->linear.z;
    joy_p3at_vel_msg.angular.x = vel_msg->angular.x;
    joy_p3at_vel_msg.angular.y = vel_msg->angular.y;
    joy_p3at_vel_msg.angular.z = vel_msg->angular.z;
}

void joyard2velCallback(const geometry_msgs::Twist::ConstPtr& vel_msg)
{
    teleop_ard2 = true;
    joy_ard2_vel_msg.linear.x = vel_msg->linear.x;
    joy_ard2_vel_msg.linear.y = vel_msg->linear.y;
    joy_ard2_vel_msg.linear.z = vel_msg->linear.z;
    joy_ard2_vel_msg.angular.x = vel_msg->angular.x;
    joy_ard2_vel_msg.angular.y = vel_msg->angular.y;
    joy_ard2_vel_msg.angular.z = vel_msg->angular.z;
}

// ___ FUNCIONES ___

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
    }

    return std::make_tuple(obstaculo_detectado, h_obstaculo);
    // Devolvemos si se ha detectado un obstaculo y la altura estimada del mismo
}

geometry_msgs::Twist control_ard2(geometry_msgs::Pose p_ard2, geometry_msgs::Pose p_obj_ard2)
{
    geometry_msgs::Twist vel_msg;
    double kp = 0.2;

    tf::Transform tf_ard2, tf_obj_ard2, tf_ruta;

    tf::Vector3 v(p_ard2.position.x, p_ard2.position.y, p_ard2.position.z);
    tf::Vector3 v_obj(p_obj_ard2.position.x, p_obj_ard2.position.y, p_obj_ard2.position.z);

    tf::Quaternion q(p_ard2.orientation.x, p_ard2.orientation.y, p_ard2.orientation.z,
        p_ard2.orientation.w);
    tf::Quaternion q_obj( p_obj_ard2.orientation.x, p_obj_ard2.orientation.y, p_obj_ard2.orientation.z,
        p_obj_ard2.orientation.w);

    tf_ard2.setOrigin(v);
    tf_ard2.setRotation(q);

    tf_obj_ard2.setOrigin(v_obj);
    tf_obj_ard2.setRotation(q_obj);

    tf::Pose diff = tf_ard2.inverse() * tf_obj_ard2;

    vel_msg.linear.x = kp * diff.getOrigin().x();
    vel_msg.linear.y = kp * diff.getOrigin().y();
    vel_msg.linear.z = kp * diff.getOrigin().z();
    vel_msg.angular.z = tf::getYaw(diff.getRotation());

    return vel_msg;
}

geometry_msgs::Quaternion orientar_ard2_hacia_p3at(geometry_msgs::Pose p_ard2, geometry_msgs::Pose p_p3at)
{
    geometry_msgs::Twist vel_msg;
    double kp = 0.2;

    tf::Transform tf_ard2, tf_p3at, tf_ruta;

    tf::Vector3 v(p_ard2.position.x, p_ard2.position.y, p_ard2.position.z);
    tf::Vector3 v_obj(p_p3at.position.x, p_p3at.position.y, p_p3at.position.z);

    tf::Quaternion q(p_ard2.orientation.x, p_ard2.orientation.y, p_ard2.orientation.z,
        p_ard2.orientation.w);
    tf::Quaternion q_obj( p_p3at.orientation.x, p_p3at.orientation.y, p_p3at.orientation.z,
        p_p3at.orientation.w);

    tf_ard2.setOrigin(v);
    tf_ard2.setRotation(q);

    tf_p3at.setOrigin(v_obj);
    tf_p3at.setRotation(q_obj);

    tf::Pose diff = tf_ard2.inverse() * tf_p3at;

    double yaw = atan2(diff.getOrigin().y(), diff.getOrigin().x());
    return tf::createQuaternionMsgFromYaw(yaw);
}

geometry_msgs::Twist modo_seguimiento_p3at(double distancia_pto_obj, double desvio_orient_obj, int accion)
{
    geometry_msgs::Twist vel_msg;

    if (accion == P3AT_SEGUIMIENTO)
    {
        // Calculamos cmd_vel
        if (distancia_pto_obj > distancia_a_ard2)
        {
            vel_msg.linear.x = 0.2 * distancia_pto_obj;
            vel_msg.angular.z = 1.0 * desvio_orient_obj;
        }
        else {
            vel_msg.linear.x = 0.0;
            // TO_DO: funciones:
            //            - Guardar posicion y altura del objeto         vel_msg.angular.z = 0.0;
        }
    }
    else if (accion == P3AT_ESPERAPIONNER)
    {
        vel_msg.linear.x = 0.0;
        vel_msg.angular.z = 0.0;
    }
    else
    {
        vel_msg.linear.x = 0.0;
        vel_msg.angular.z = 0.0;
    }
    return vel_msg;
}

geometry_msgs::Twist control_p3at(geometry_msgs::Pose p_p3at, geometry_msgs::Pose p_obj_p3at)
{
    geometry_msgs::Twist vel_msg;
    double kp = 0.2;

    tf::Transform tf_p3at, tf_obj_p3at;

    tf::Vector3 v(p_p3at.position.x, p_p3at.position.y, p_p3at.position.z);
    tf::Vector3 v_obj(p_obj_p3at.position.x, p_obj_p3at.position.y, 0.0);

    tf::Quaternion q(p_p3at.orientation.x, p_p3at.orientation.y, p_p3at.orientation.z,
        p_p3at.orientation.w);
    tf::Quaternion q_obj( p_obj_p3at.orientation.x, p_obj_p3at.orientation.y, p_obj_p3at.orientation.z,
        p_obj_p3at.orientation.w);

    tf_p3at.setOrigin(v);
    tf_p3at.setRotation(q);

    tf_obj_p3at.setOrigin(v_obj);
    tf_obj_p3at.setRotation(q_obj);

    tf::Pose diff = tf_p3at.inverse() * tf_obj_p3at;

    vel_msg.linear.x = kp * sqrt(pow(diff.getOrigin().x(),2) + pow(diff.getOrigin().y(),2));
    vel_msg.angular.z = atan2(diff.getOrigin().y(), diff.getOrigin().x());

    return vel_msg;
}

geometry_msgs::Twist orientar_p3at(geometry_msgs::Pose p_p3at, geometry_msgs::Pose p_obj_p3at)
{
    geometry_msgs::Twist vel_msg;

    tf::Transform tf_p3at, tf_obj_p3at;

    tf::Vector3 v(p_p3at.position.x, p_p3at.position.y, p_p3at.position.z);
    tf::Vector3 v_obj(p_obj_p3at.position.x, p_obj_p3at.position.y, 0.0);

    tf::Quaternion q(p_p3at.orientation.x, p_p3at.orientation.y, p_p3at.orientation.z,
        p_p3at.orientation.w);
    tf::Quaternion q_obj( p_obj_p3at.orientation.x, p_obj_p3at.orientation.y, p_obj_p3at.orientation.z,
        p_obj_p3at.orientation.w);

    tf_p3at.setOrigin(v);
    tf_p3at.setRotation(q);

    tf_obj_p3at.setOrigin(v_obj);
    tf_obj_p3at.setRotation(q_obj);

    tf::Pose diff = tf_p3at.inverse() * tf_obj_p3at;

    vel_msg.linear.x = 0.0;
    vel_msg.angular.z = tf::getYaw(diff.getRotation());

    return vel_msg;
}

geometry_msgs::Quaternion orientacion_robot(geometry_msgs::Pose pose_robot)
{
    tf::Quaternion q(pose_robot.orientation.x, pose_robot.orientation.y, pose_robot.orientation.z,
        pose_robot.orientation.w);
    double yaw = tf::getYaw(q);
    return tf::createQuaternionMsgFromYaw(yaw);
}


// ___ MAIN ___

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
    double distancia_a_objetivo = 0.0;
    double rotacion_a_objetivo = 0.0;

    accion_ard2 = UNKNOWN_ACTION;
    accion_p3at = UNKNOWN_ACTION;

    // Inicializacion ROS
    ros::init(argc, argv, "detector_obstaculos");
    ros::NodeHandle node;

    // Subcribers
    ros::Subscriber proyeccionXY_cable_subs = node.subscribe("cable/proyeccionXY_gps", 1, proyeccionXYCallback);
    ros::Subscriber orientacion_cable_subs = node.subscribe("cable/orientacion_gps", 1, orientacionCallback);
    //dros::Subscriber kalman_ard2_odom_subs = node.subscribe("ardrone/kalman_odom", 1, ard2kalmanodomCallback);
    ros::Subscriber kalman_ard2_odom_subs = node.subscribe("ground_truth/state", 1, ard2kalmanodomCallback);
    ros::Subscriber kalman_sonar_subs = node.subscribe("ardrone/kalman_sonar", 1, ard2kalmansonarCallback);
    ros::Subscriber kalman_p3at_odom_subs = node.subscribe("p3at/kalman_odom", 1, p3atkalmanodomCallback);
    ros::Subscriber modo_automatico_subs = node.subscribe("guiado/modo_automatico", 1, modoautomaticoCallback);
    ros::Subscriber joy_p3at_vel_subs =  node.subscribe("guiado/joy_p3at_vel", 1,  joyp3atvelCallback);
    ros::Subscriber joy_ard2_vel_subs =  node.subscribe("guiado/joy_ard2_vel", 1, joyard2velCallback);

    // Publishers
    ros::Publisher accion_ard2_pub = node.advertise<std_msgs::Int32>("guiado/accion_ard2", 10);
    ros::Publisher accion_p3at_pub = node.advertise<std_msgs::Int32>("guiado/accion_p3at", 10);
    ros::Publisher altura_a_suelo_pub = node.advertise<std_msgs::Float64>("ardrone/altura_a_suelo", 10);
    ros::Publisher ard2_vel_pub = node.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    ros::Publisher p3at_vel_pub = node.advertise<geometry_msgs::Twist>("p3at/cmd_vel", 1);

    // Mensajes
    p3at_vel_msg.linear.x = p3at_vel_msg.linear.y = p3at_vel_msg.linear.z = 0.0;
    p3at_vel_msg.angular.x =  p3at_vel_msg.angular.y =  p3at_vel_msg.angular.z = 0.0;

    ard2_vel_msg.linear.x = ard2_vel_msg.linear.y = ard2_vel_msg.linear.z = 0.0;
    ard2_vel_msg.angular.x =  ard2_vel_msg.angular.y =  ard2_vel_msg.angular.z = 0.0;

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
          if (proyeccion_xy <= dist_centro_plataforma && accion_ard2 <= ARD2_VUELOSOBRESUELO)
          {
              accion_ard2 = ARD2_VUELOSOBREPLATAFORMA;
              accion_p3at = P3AT_SEGUIMIENTO;

              altura_a_suelo_msg.data = h_kalman_sonar + h_plataforma;
          }
          // CONDICION 2 ||  __OK__
          else if (proyeccion_xy > dist_centro_plataforma && accion_ard2 <= ARD2_VUELOSOBRESUELO && !obstaculo_detectado)
          {
              accion_ard2 = ARD2_VUELOSOBRESUELO;
              accion_p3at = P3AT_SEGUIMIENTO;

              altura_a_suelo_msg.data = h_kalman_sonar;
          }
          // CONDICION 3 ||  ~~ PDTE ~~
          else if (obstaculo_detectado && accion_ard2 == ARD2_VUELOSOBRESUELO)
          {
              accion_ard2 = ARD2_MARCAJEOBSTACULO;
              accion_p3at = P3AT_ESQUIVAOBSTACULO;
              ROS_INFO("P3AT esquivando obstaculo / ARD2 marcando obstaculo");

              altura_a_suelo_msg.data = h_kalman_sonar + h_obstaculo;

              // Drone mantiene la posicion sobre el punto
              pose_obj_ard2 = pose_ard2;
              pose_obj_ard2.orientation = orientar_ard2_hacia_p3at(pose_ard2, pose_p3at);

              // Señalamos la pose objetivo para esquivar el obstaculo
              pose_obj_p3at.position.x = pose_ard2.position.x + distancia_esquiva * sin(orientacion_cable); // TO_DO: esquiva
              pose_obj_p3at.position.y = pose_ard2.position.y + distancia_esquiva * cos(orientacion_cable); // TO_DO: esquiva
              pose_obj_p3at.position.z = 0.0;
              pose_obj_p3at.orientation = tf::createQuaternionMsgFromYaw(orientacion_cable);
              // pose_obj_p3at.orientation = orientacion_robot(pose_ard2);

              /*tf::Quaternion q_ard2(pose_ard2.orientation.x, pose_ard2.orientation.y, pose_ard2.orientation.z,
                  pose_ard2.orientation.w);
              double yaw_ard2 = tf::getYaw(q_ard2);
              pose_obj_p3at.orientation = tf::createQuaternionMsgFromYaw(yaw_ard2); */

              distancia_a_objetivo = sqrt(pow(pose_obj_p3at.position.x - pose_p3at.position.x, 2) +
                                          pow(pose_obj_p3at.position.y - pose_p3at.position.y, 2));
              rotacion_a_objetivo = tf::getYaw(pose_obj_p3at.orientation) - tf::getYaw(pose_p3at.orientation);
          }
          // CONDICION 4 ||  ~~ PDTE ~~
          else if (accion_ard2 == ARD2_MARCAJEOBSTACULO && accion_p3at == P3AT_ESQUIVAOBSTACULO)
          {
              if (obstaculo_detectado == true)
              {
                  altura_a_suelo_msg.data = h_kalman_sonar + h_obstaculo;
              }
              else
              {
                  altura_a_suelo_msg.data = h_kalman_sonar;
              }

              pose_obj_ard2.orientation = orientar_ard2_hacia_p3at(pose_ard2, pose_p3at);

              distancia_a_objetivo = sqrt(pow(pose_obj_p3at.position.x - pose_p3at.position.x, 2) +
                                          pow(pose_obj_p3at.position.y - pose_p3at.position.y, 2));
              rotacion_a_objetivo = tf::getYaw(pose_obj_p3at.orientation) - tf::getYaw(pose_p3at.orientation);

              if (distancia_a_objetivo < 0.2 && rotacion_a_objetivo < 0.05)
              {
                accion_p3at = P3AT_ESPERAPIONNER;
                accion_ard2 = ARD2_APIONEER;
                ROS_INFO("P3AT a la espera / ARD2 hacia Pioneer");

                pose_obj_ard2 = pose_p3at;
                pose_obj_ard2.position.z = altura_vuelo;

                p3at_vel_msg.linear.x = p3at_vel_msg.linear.y = p3at_vel_msg.linear.z = 0.0;
                p3at_vel_msg.angular.x =  p3at_vel_msg.angular.y =  p3at_vel_msg.angular.z = 0.0;
              }


              // TO_DO: funciones:
              //            - Generar trayectoria para esquivar obstaculo
              //            - Hacer navegar el pioneer para que esquive el obstaculo
              //            - Comprobar si el pioneer ha llegado al objetivo. En ese caso, cambiar a estado espera
          }
          // CONDICION 5 ||  ~~ PDTE ~~
          else if (accion_ard2 == ARD2_APIONEER && accion_p3at == P3AT_ESPERAPIONNER && proyeccion_xy > dist_centro_plataforma)
          {
              if (obstaculo_detectado == true)
              {
                  altura_a_suelo_msg.data = h_kalman_sonar + h_obstaculo;
              }
              else
              {
                  altura_a_suelo_msg.data = h_kalman_sonar;
              }

              // TO_DO: funciones:
              //    - Mejorar trayectoria. Tendria que ir mirando hacia adelante hasta que llegue. Luego girar.
          }
          // CONDICION 6 ||  __OK__
          else if (accion_ard2 == ARD2_APIONEER && accion_p3at == P3AT_ESPERAPIONNER && proyeccion_xy <= dist_centro_plataforma)
          {
              accion_ard2 = ARD2_VUELOSOBREPLATAFORMA;
              accion_p3at = P3AT_SEGUIMIENTO;
          }
          // CONDICION 7  ||  __OK__
          /* else {
              accion_ard2 = UNKNOWN_ACTION;
              accion_p3at = UNKNOWN_ACTION;
          } */

          // Caculamos la velocidad de control del Ard2
          if (accion_ard2 >= ARD2_MARCAJEOBSTACULO)
          {
              ard2_vel_msg = control_ard2(pose_ard2, pose_obj_ard2);
          }
          else
          {
              if (modo_automatico == true)
              {
                  // TO_DO: programar modo automatico
              }
              else if (modo_automatico == false && teleop_ard2 == true)
              {
                  ard2_vel_msg = joy_ard2_vel_msg;
              }
              else
              {
                  ard2_vel_msg.linear.x = ard2_vel_msg.linear.y = ard2_vel_msg.linear.z = 0.0;
                  ard2_vel_msg.angular.x =  ard2_vel_msg.angular.y =  ard2_vel_msg.angular.z = 0.0;
              }
          }

          // Calculamos la velocidad de control de Pioneer
          if (accion_p3at == P3AT_ESQUIVAOBSTACULO)
          {
              if (distancia_a_objetivo > 0.2)
              {
                  p3at_vel_msg = control_p3at(pose_p3at, pose_obj_p3at);
              }
              else
              {
                  p3at_vel_msg = orientar_p3at(pose_p3at, pose_obj_p3at);
              }
          }
          else
          {
            if (teleop_p3at == true)
            {
                p3at_vel_msg = joy_p3at_vel_msg;
            }
            else
            {
                p3at_vel_msg = modo_seguimiento_p3at(proyeccion_xy, orientacion_cable, accion_p3at);
            }
          }

          // Publicamos las acciones de los robots
          accion_ard2_msg.data = accion_ard2;
          accion_p3at_msg.data = accion_p3at;
          accion_ard2_pub.publish(accion_ard2_msg);
          accion_p3at_pub.publish(accion_p3at_msg);

          // Publicamos la altura hasta el suelo
          altura_a_suelo_pub.publish(altura_a_suelo_msg);

          // Publicamos las velocidades de control de los robots
          p3at_vel_pub.publish(p3at_vel_msg);
          ard2_vel_pub.publish(ard2_vel_msg);

          teleop_p3at = false;
          teleop_ard2 = false;

          rate.sleep();
          ros::spinOnce();
    }
}
