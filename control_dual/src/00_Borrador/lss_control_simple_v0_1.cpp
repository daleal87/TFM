#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Bool.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include "std_msgs/Empty.h"
#include "std_srvs/Empty.h"

#include <stdio.h>
#include <math.h>
#include <tuple>

// Listado de acciones de los robots:
#define EMERGENCIA 0 // Inicio o acción desconocida

// Acciones ARD2:
#define ARD2_VUELOSOBREPLATAFORMA 1 // Drone volando sobre la plataforma
#define ARD2_VUELOSOBRESUELO 2 // Drone volando fuera de la plataforma
#define ARD2_MARCAJEOBSTACULO 3 // Drone estático sobre un obstaculo
#define ARD2_APIONEER 4 // Drone volando hasta el Pionner tras haber esquivado obstaculo
#define ARD2_ATERRIZANDO 5 // Drone efectuando la maniobra de aterrizaje
#define ARD2_ENTIERRA 6 // Drone aterrizado

// Acciones Pioneer
#define P3AT_SEGUIMIENTO 1  // Pioneer siguiendo al drone
#define P3AT_ESQUIVAOBSTACULO 2 // Pioneer esquivando el obstaculo detectado por el drone
#define P3AT_ESPERAPIONNER 3 // Pioneer parado esperando a que el drone vuele sobre el o aterrice
#define P3AT_AFINDEMISION 4 // Pioneer hacia el final de la mision
#define P3AT_MISIONFINALIZADA 5 // Pioneer ha completado la mision

// ___ VARIABLES GLOBALES ___
const int PUBLISH_FREQ = 25;

std_msgs::Int32 accion_ard2_msg, accion_p3at_msg, longitud_cable_msg, joy_cable_vel_msg;
std_msgs::Float64 altura_a_suelo_msg;
geometry_msgs::Twist p3at_vel_msg, ard2_vel_msg, joy_p3at_vel_msg, joy_ard2_vel_msg;
geometry_msgs::Pose pose_p3at, pose_ard2, pose_obj_p3at, pose_obj_ard2;
geometry_msgs::Pose objetivo_mision, objetivo_despegue, objetivo_aterrizaje;
std_msgs::Bool modo_aterrizaje_msg;
geometry_msgs::PoseArray trayectoria_esquiva;
tf::Quaternion q_cable;

ros::Publisher accion_ard2_pub, accion_p3at_pub;

unsigned int accion_ard2, accion_p3at; // Acciones que estan realizando los robots
double proyeccion_xy, orientacion_cable, inclinacion_cable, distancia_entre_robots; // Informacion sobre el cable
double pre_ard2_error_x, pre_ard2_error_y, pre_ard2_error_z;
double pre_p3at_error_x, pre_p3at_error_y, pre_p3at_error_z;
double long_cable_encoder = 0.0;
float longitud_cable_float = 0.0;

double dist_centro_plataforma, h_kalman_odom, h_kalman_sonar, h_obstaculo; // Distancia al centro de la plataforma desde el lado en la direccion de la proyeccion del cable
bool obstaculo_detectado;
bool modo_automatico = false;
bool modo_emergencia = false;
bool teleop_p3at = false;
bool teleop_ard2 = false;
bool teleop_cable = false;
bool fin_mision, fin_despegue, fin_aterrizaje, aproximacion_prima, aproximacion_final;
double misionx, misiony;

double distancia_a_ard2;
double altura_vuelo;
double distancia_esquiva;
double altura_plataforma = 0.4;
double long_cable_max;
bool activar_parada_longitud, activar_deteccion_obstaculos;
int n_ptos_esquiva;

// Velocidades Máximas
double ard2_vmax_linear;
double ard2_vmax_angular;
double p3at_vmax_linear;
double p3at_vmax_angular;

// Valores PID
double kp_ard2, ki_ard2, kd_ard2, kp_p3at, ki_p3at, kd_p3at;
/*double kp_ard2 = 0.5;
double ki_ard2 = 0.0;
double kd_ard2 = 0.0;
double kp_p3at = 0.2;
double ki_p3at = 0.0;
double kd_p3at = 0.0;*/
double k_recogida_cable, k_extension_cable;

double dt = PUBLISH_FREQ / 1000.0;

// Declaracion de funciones
geometry_msgs::Twist parar_robot();

// ___ CALLBACKS SUBSCRIBERS ___

void proyeccionXYCallback(const std_msgs::Float64::ConstPtr& proyeccionXY_msg)
{
    proyeccion_xy = proyeccionXY_msg->data; // Leemos el valor del topic de la proyeccion del cable sobre el plano XY
}

void orientacionCallback(const std_msgs::Float64::ConstPtr& orientacion_cable_msg)
{
    orientacion_cable = orientacion_cable_msg->data; // Leemos el valor del topic que indica la orientacion del cable
}

void inclinacionCallback(const std_msgs::Float64::ConstPtr& inclinacion_cable_msg)
{
    inclinacion_cable = inclinacion_cable_msg->data; // Leemos el valor del topic que indica la inclinacion del cable
}

void distrobotsCallback(const std_msgs::Float64::ConstPtr& msg)
{
    distancia_entre_robots = msg->data; // Leemos el valor del topic que indica la longitud del cable
}

void longitudcableCallback(const std_msgs::Float64::ConstPtr& msg)
{
    /*long_cable_encoder = msg->data; // Leemos el valor del topic que indica la longitud del cable
    if (long_cable_encoder > long_cable_max && activar_parada_longitud && accion_p3at != P3AT_ESPERAPIONNER && accion_ard2 != ARD2_APIONEER) // Comprobamos que no supere la distancia maxima permitida
    {
        accion_p3at = P3AT_ESPERAPIONNER;
        accion_ard2 = ARD2_APIONEER;
        ROS_INFO("ATENCION!! Longitud maxima de cable alcanzada");
        ROS_INFO("ARD2 volviendo sobre el Pioneer");
        pose_obj_ard2 = pose_p3at;
        pose_obj_ard2.position.z = altura_vuelo;

        p3at_vel_msg = parar_robot();
    } */
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

void modoautomaticoCallback(const std_msgs::Bool::ConstPtr& msg)
{   
    if (modo_automatico && msg->data == false)
    {
        fin_despegue = fin_mision = fin_aterrizaje = aproximacion_prima = aproximacion_final = false;

        if (accion_ard2 < ARD2_ATERRIZANDO)
        {
            if (proyeccion_xy <= dist_centro_plataforma) {
                accion_ard2 = ARD2_VUELOSOBREPLATAFORMA; }
            else {
                accion_ard2 = ARD2_VUELOSOBRESUELO; }
            p3at_vel_msg = parar_robot();
            accion_p3at = P3AT_SEGUIMIENTO;
        }

        accion_ard2_msg.data = accion_ard2;
        accion_p3at_msg.data = accion_p3at;
        accion_ard2_pub.publish(accion_ard2_msg);
        accion_p3at_pub.publish(accion_p3at_msg);
    }
    modo_automatico = msg->data; // Modo automatico activo
}

void modoaterrizajeCallback(const std_msgs::Bool::ConstPtr& msg)
{
    if (accion_ard2 != ARD2_ATERRIZANDO && msg->data == true)
    {
        accion_ard2 = ARD2_ATERRIZANDO;

        fin_mision = true;
        fin_despegue = true;
        fin_aterrizaje = false;
    }
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

void joycablevelCallback(const std_msgs::Int32::ConstPtr& vel_msg)
{
    teleop_cable = true;
    joy_cable_vel_msg.data = vel_msg->data;
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

void modoemergenciaCallback(const std_msgs::Bool::ConstPtr& msg)
{
    if (modo_emergencia != msg->data) { modo_emergencia = msg->data; }
    modo_automatico = false;
    fin_despegue = fin_mision = fin_aterrizaje = aproximacion_prima = aproximacion_final = false;

}


// ___ FUNCIONES ___

geometry_msgs::Twist parar_robot()
{
    geometry_msgs::Twist vel_msg;
    vel_msg.linear.x = vel_msg.linear.y = vel_msg.linear.z = 0.0;
    vel_msg.angular.x =  vel_msg.angular.y =  vel_msg.angular.z = 0.0;
    return vel_msg;
}

double limitar_velocidad_lineal(double diferencia, double pre_error, double kp, double ki, double kd, double vmax)
{
    double Pout = kp * diferencia;
    double Iout = ki * diferencia * dt;
    double Dout = kd * (diferencia - pre_error) / dt;

    double vel = Pout + Iout + Dout;

    if (vel > 0 && vel > vmax) { vel = vmax; }
    else if (vel < 0  && vel < -vmax) { vel = -vmax; }

    return vel;
}

double limitar_velocidad_angular(double diferencia, double kp, double vmax)
{
    double vel = kp * diferencia;

    if (vel > 0 && vel > vmax) { vel = vmax; }
    else if (vel < 0  && vel < -vmax) { vel = -vmax; }

    return vel;
}

std::tuple<bool, double> detector_obstaculos(double h_kalman_odom, double h_kalman_sonar, unsigned int accion_ard2)
{   
    if (h_kalman_odom * 0.6 > h_kalman_sonar && h_kalman_odom - h_kalman_sonar > 0.3 && accion_ard2 >= 2) {
        obstaculo_detectado = true;
        h_obstaculo = h_kalman_odom - h_kalman_sonar;
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

    tf::Transform tf_ard2, tf_obj_ard2;

    tf::Vector3 v(p_ard2.position.x, p_ard2.position.y, p_ard2.position.z);
    tf::Vector3 v_obj(p_obj_ard2.position.x, p_obj_ard2.position.y, p_obj_ard2.position.z);

    tf::Quaternion q(p_ard2.orientation.x, p_ard2.orientation.y, p_ard2.orientation.z,
                     p_ard2.orientation.w);
    tf::Quaternion q_obj(p_obj_ard2.orientation.x, p_obj_ard2.orientation.y, p_obj_ard2.orientation.z,
                         p_obj_ard2.orientation.w);

    tf_ard2.setOrigin(v);
    tf_ard2.setRotation(q);

    tf_obj_ard2.setOrigin(v_obj);
    tf_obj_ard2.setRotation(q_obj);

    tf::Pose diff = tf_ard2.inverse() * tf_obj_ard2;

    vel_msg.linear.x = limitar_velocidad_lineal(diff.getOrigin().x(), pre_ard2_error_x, kp_ard2, kd_ard2, ki_ard2,  ard2_vmax_linear);
    vel_msg.linear.y = limitar_velocidad_lineal(diff.getOrigin().y(), pre_ard2_error_y, kp_ard2, kd_ard2, ki_ard2,  ard2_vmax_linear);
    vel_msg.linear.z = limitar_velocidad_lineal(diff.getOrigin().z(), pre_ard2_error_z, kp_ard2, kd_ard2, ki_ard2,  ard2_vmax_linear);
    vel_msg.angular.z = limitar_velocidad_angular(tf::getYaw(diff.getRotation()), 10*kp_ard2, ard2_vmax_angular);

    // Guardamos los errores de la presente iteracion
    pre_ard2_error_x = diff.getOrigin().x();
    pre_ard2_error_y = diff.getOrigin().z();
    pre_ard2_error_z = diff.getOrigin().z();

    return vel_msg;
}

geometry_msgs::Quaternion orientar_a_punto(geometry_msgs::Pose pose, geometry_msgs::Pose pose_obj)
{
    tf::Transform tf_ard2, tf_p3at, tf_final;

    tf::Vector3 v(pose.position.x, pose.position.y, pose.position.z);
    tf::Vector3 v_obj(pose_obj.position.x, pose_obj.position.y, pose_obj.position.z);

    tf::Quaternion q(pose.orientation.x, pose.orientation.y, pose.orientation.z,
                     pose.orientation.w);
    tf::Quaternion q_obj( pose_obj.orientation.x, pose_obj.orientation.y, pose_obj.orientation.z,
                          pose_obj.orientation.w);

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
            vel_msg.linear.x = limitar_velocidad_lineal(distancia_pto_obj, pre_p3at_error_x, kp_p3at, kd_p3at, ki_p3at,  p3at_vmax_linear);
            vel_msg.angular.z = limitar_velocidad_angular(desvio_orient_obj, 1, p3at_vmax_angular);

            pre_p3at_error_x = distancia_pto_obj;
        }
        else {
            vel_msg.linear.x = 0.0;
            pre_p3at_error_x = 0.0;
        }
    }
    else
    {
        vel_msg = parar_robot();
    }
    return vel_msg;
}

geometry_msgs::Twist control_p3at(geometry_msgs::Pose p_p3at, geometry_msgs::Pose p_obj_p3at)
{
    geometry_msgs::Twist vel_msg;
    vel_msg.linear.x = vel_msg.linear.y = vel_msg.linear.z = 0.0;
    vel_msg.angular.x = vel_msg.angular.y = vel_msg.angular.z = 0.0;
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

    double desviacion_orientacion = atan2(diff.getOrigin().y(), diff.getOrigin().x());
    double distancia_objetivo = sqrt(pow(diff.getOrigin().x(), 2) + pow(diff.getOrigin().y(), 2));

    if (std::abs(desviacion_orientacion) < 0.2 ) {
        vel_msg.linear.x = limitar_velocidad_lineal(distancia_objetivo, pre_p3at_error_x, kp_p3at, kd_p3at, ki_p3at,  p3at_vmax_linear);

        pre_p3at_error_x = distancia_objetivo;
    }
    else {
        vel_msg.linear.x = 0.0; }

    vel_msg.angular.z = desviacion_orientacion;
    //vel_msg.angular.z = limitar_velocidad_angular(desviacion_orientacion, 10*kp, p3at_vmax_angular);

    return vel_msg;
}

geometry_msgs::Twist orientar_p3at(geometry_msgs::Pose p_p3at, geometry_msgs::Pose p_obj_p3at)
{
    geometry_msgs::Twist vel_msg;
    double kp = 0.2;

    tf::Transform tf_p3at, tf_obj_p3at;

    tf::Vector3 v(p_p3at.position.x, p_p3at.position.y, p_p3at.position.z);
    tf::Vector3 v_obj(p_obj_p3at.position.x, p_obj_p3at.position.y, p_obj_p3at.position.z);

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
    // vel_msg.angular.z = limitar_velocidad_angular(tf::getYaw(diff.getRotation()), 10*kp, p3at_vmax_angular);

    return vel_msg;
}

geometry_msgs::Quaternion orientacion_robot(geometry_msgs::Pose pose_robot)
{
    tf::Quaternion q(pose_robot.orientation.x, pose_robot.orientation.y, pose_robot.orientation.z,
                     pose_robot.orientation.w);
    double yaw = tf::getYaw(q);
    return tf::createQuaternionMsgFromYaw(yaw);
}

double desviacion_yaw(geometry_msgs::Pose p_p3at, geometry_msgs::Pose p_obj_p3at)
{
    tf::Transform tf_p3at, tf_obj_p3at;

    tf::Vector3 v(p_p3at.position.x, p_p3at.position.y, p_p3at.position.z);
    tf::Vector3 v_obj(p_obj_p3at.position.x, p_obj_p3at.position.y, p_obj_p3at.position.z);

    tf::Quaternion q(p_p3at.orientation.x, p_p3at.orientation.y, p_p3at.orientation.z,
                     p_p3at.orientation.w);
    tf::Quaternion q_obj( p_obj_p3at.orientation.x, p_obj_p3at.orientation.y, p_obj_p3at.orientation.z,
                          p_obj_p3at.orientation.w);

    tf_p3at.setOrigin(v);
    tf_p3at.setRotation(q);

    tf_obj_p3at.setOrigin(v_obj);
    tf_obj_p3at.setRotation(q_obj);

    tf::Pose diff = tf_p3at.inverse() * tf_obj_p3at;

    return tf::getYaw(diff.getRotation());
}

std::tuple<double, double> evaluar_distancias(geometry_msgs::Pose pose, geometry_msgs::Pose pose_objetivo)
{
    double dist_objetivo, dist_altura;
    dist_objetivo = sqrt(pow(pose_objetivo.position.x - pose.position.x, 2) +
                         pow(pose_objetivo.position.y - pose.position.y, 2));
    dist_altura = std::abs(pose_objetivo.position.z - pose.position.z);

    return std::make_tuple(dist_objetivo, dist_altura);
}

geometry_msgs::PoseArray generar_trayectoria_esquiva(geometry_msgs::Pose pose, geometry_msgs::Pose pose_final, int n)
{
    geometry_msgs::PoseArray trayectoria;
    double dif_x = pose_final.position.x - pose.position.x; // Diferencia en x entre posicion inicial y final
    double dif_y = pose_final.position.y - pose.position.y; // Diferencia en y entre posicion inicial y final
    double incre_ang = (M_PI/2) / n; // Incremento del angulo entre cada punto

    if (n > 1)
    {
        for (int i=0; i<n-2; i++)
        {
            geometry_msgs::Pose temp_pose;
            temp_pose.position.x =
                    pose.position.x + (dif_x / n) * cos(orientacion_cable + (M_PI/2) - incre_ang * (i+1));
            temp_pose.position.y =
                    pose.position.y + (dif_y / n) * sin(orientacion_cable + (M_PI/2) - incre_ang * (i+1));
            temp_pose.position.z = 0.0;

            temp_pose.orientation = tf::createQuaternionMsgFromYaw(orientacion_cable - (M_PI/2 + incre_ang * i));

            trayectoria.poses.push_back(temp_pose);
        }
    }
    trayectoria.poses.push_back(pose_final);

    return trayectoria;
}


int control_cable(double orient, double inclin, geometry_msgs::Pose p_ard2, geometry_msgs::Pose p_p3at,
                  geometry_msgs::Twist vel_ard2, geometry_msgs::Twist vel_p3at)
{
    double v_cable_mtrs = 0.0;
    int v_cable_mm = 0;
    double v_rel_x, v_rel_y, v_rel_z;
    double v_cable_x, v_cable_y, v_cable_z;

    tf::Transform tf_ard2, tf_p3at;

    tf::Vector3 pos_ard2(0, 0, 0);
    tf::Vector3 pos_p3at(0, 0, 0);
    //tf::Vector3 pos_ard2(p_ard2.position.x, p_ard2.position.y, p_ard2.position.z);
    //tf::Vector3 pos_p3at(p_p3at.position.x, p_p3at.position.y, p_p3at.position.z);

    tf::Quaternion q_ard2(p_ard2.orientation.x, p_ard2.orientation.y, p_ard2.orientation.z,
                          p_ard2.orientation.w);
    tf::Quaternion q_p3at( p_p3at.orientation.x, p_p3at.orientation.y, p_p3at.orientation.z,
                           p_p3at.orientation.w);

    // Transformamos las poses a la base del cable
    tf_ard2.setOrigin(pos_ard2);
    tf_ard2.setRotation(q_ard2);

    tf_p3at.setOrigin(pos_p3at);
    tf_p3at.setRotation(q_p3at);

    tf::Pose transf_mat_p3at = tf_p3at.inverse() * tf_ard2; // Transformamos la pose del ard2 a la base del cable

    tf::Vector3 v_ard2(vel_ard2.linear.x, vel_ard2.linear.y, vel_ard2.linear.z);

    tf::Vector3 vel_ard2_B_p3at = transf_mat_p3at.operator ()(v_ard2);

    v_rel_x = vel_ard2_B_p3at.x() - vel_p3at.linear.x;
    v_rel_y = vel_ard2_B_p3at.y() - vel_p3at.linear.y;
    v_rel_z = vel_ard2_B_p3at.z() - vel_p3at.linear.z;

    v_cable_x = (v_rel_x * cos(orient) ) * cos(inclin);
    v_cable_y = (v_rel_y * sin(orient) ) * cos(inclin);
    v_cable_z =  v_rel_z * sin(inclin);

    v_cable_mtrs = v_cable_x + v_cable_y + v_cable_z;


    /*v_cable_x = (v_rel_x / cos(orient) ) / cos(inclin);
    v_cable_y = (v_rel_y / sin(orient) ) / cos(inclin);
    v_cable_z =  v_rel_z / sin(inclin);

    v_cable_mtrs = (v_rel_x / cos(orient) ) / cos(inclin) +
            (v_rel_y / sin(orient) ) / cos(inclin) +
            v_rel_z / sin(inclin); // x * arcos() */

    v_cable_mtrs = v_cable_mtrs * 1000;
    v_cable_mm = (int)v_cable_mtrs;

    /* ROS_INFO("------------------------------------------------------------------------");
    ROS_INFO("X: %2f - Y: %2f - Z: %2f", vel_ard2.linear.x, vel_ard2.linear.y, vel_ard2.linear.z);
    ROS_INFO("X: %2f - Y: %2f - Z: %2f", vel_ard2_B_p3at.x(), vel_ard2_B_p3at.y(), vel_ard2_B_p3at.z());
    ROS_INFO("X: %2f - Y: %2f - Z: %2f", vel_p3at.linear.x, vel_p3at.linear.y, vel_p3at.linear.z);
    ROS_INFO("X: %2f - Y: %2f - Z: %2f", v_rel_x, v_rel_y, v_rel_z);
    ROS_INFO("X: %2f - Y: %2f - Z: %2f", v_cable_x, v_cable_y, v_cable_z);
    ROS_INFO("Cable: %i", v_cable_mm);
    ROS_INFO("------------------------------------------------------------------------"); */

    return v_cable_mm;
}

void errores_a_cero()
{
    pre_ard2_error_x = pre_ard2_error_y = pre_ard2_error_z = 0.0;
    pre_p3at_error_x = pre_p3at_error_y = pre_p3at_error_z = 0.0;
}

// ___ MAIN ___

int main(int argc, char **argv)
{
    // TO_DO: ajustar a la forma de la plataforma (cuadrada o redonde) y su dimension
    double lado_plataforma = 0.8; // Medida del lado de la plataforma. Nota: ahora es un cuadrado
    double h_plataforma = 0.4; // Altura de la plataforma del AGV

    int cuenta_obstaculo = 0;
    obstaculo_detectado = false;
    bool deteccion_actual = false;
    bool deteccion_anterior = false;
    double d_objetivo_ard2 = 0.0;
    double d_objetivo_p3at = 0.0;
    double d_pto_esquiva_p3at = 0.0;
    double rot_objetivo_ard2 = 0.0;
    double rot_objetivo_p3at = 0.0;
    double rot_pto_esquiva_p3at = 0.0;
    double d_altura_ard2 = 0.0;
    double d_altura_p3at = 0.0;
    int cnt_esquiva = 0;

    pre_ard2_error_x = pre_ard2_error_y = pre_ard2_error_z = 0.0;
    pre_p3at_error_x = pre_p3at_error_y = pre_p3at_error_z = 0.0;

    accion_ard2 = ARD2_VUELOSOBREPLATAFORMA;
    accion_p3at = P3AT_SEGUIMIENTO;

    fin_despegue = fin_mision = fin_aterrizaje = aproximacion_prima = aproximacion_final = false;

    // Inicializacion ROS
    ros::init(argc, argv, "detector_obstaculos");
    ros::NodeHandle node;

    // Subcribers
    ros::Subscriber proyeccionXY_cable_subs = node.subscribe("cable/proyeccionXY_sim", 1, proyeccionXYCallback);
    ros::Subscriber orientacion_cable_subs = node.subscribe("cable/orientacion_sim", 1, orientacionCallback);
    ros::Subscriber inclinacion_cable_subs = node.subscribe("/cable/inclinacion_sim", 1, inclinacionCallback);
    ros::Subscriber distancia_entre_robots_subs = node.subscribe("/cable/distancia_robots_sim", 1, distrobotsCallback);
    //ros::Subscriber longitud_cable_subs = node.subscribe("/cable/longitud_sim", 1, longitudcableCallback);
    // ros::Subscriber kalman_ard2_odom_subs = node.subscribe("ardrone/kalman_odom", 1, ard2kalmanodomCallback);
    ros::Subscriber kalman_ard2_odom_subs = node.subscribe("ground_truth/state", 1, ard2kalmanodomCallback);
    ros::Subscriber kalman_sonar_subs = node.subscribe("ardrone/kalman_sonar", 1, ard2kalmansonarCallback);
    ros::Subscriber kalman_p3at_odom_subs = node.subscribe("p3at/kalman_odom", 1, p3atkalmanodomCallback);
    ros::Subscriber modo_automatico_subs = node.subscribe("guiado/modo_automatico", 1, modoautomaticoCallback);
    ros::Subscriber modo_aterrizaje_subs = node.subscribe("guiado/modo_aterrizaje", 1, modoaterrizajeCallback);
    ros::Subscriber modo_emergencia_subs = node.subscribe("guiado/modo_emergencia", 1, modoemergenciaCallback);
    ros::Subscriber joy_p3at_vel_subs =  node.subscribe("guiado/joy_p3at_vel", 1,  joyp3atvelCallback);
    ros::Subscriber joy_ard2_vel_subs =  node.subscribe("guiado/joy_ard2_vel", 1, joyard2velCallback);
    ros::Subscriber joy_cable_vel_subs =  node.subscribe("guiado/joy_cable_vel", 1, joycablevelCallback);

    // Publishers
    accion_ard2_pub = node.advertise<std_msgs::Int32>("guiado/accion_ard2", 10);
    accion_p3at_pub = node.advertise<std_msgs::Int32>("guiado/accion_p3at", 10);
    ros::Publisher altura_a_suelo_pub = node.advertise<std_msgs::Float64>("ardrone/altura_a_suelo", 10);
    ros::Publisher ard2_vel_pub = node.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    ros::Publisher p3at_vel_pub = node.advertise<geometry_msgs::Twist>("p3at/cmd_vel", 1);
    ros::Publisher land_pub = node.advertise<std_msgs::Empty>("ardrone/land",1);
    ros::Publisher modo_aterrizaje_pub = node.advertise<std_msgs::Bool>("guiado/modo_aterrizaje", 1);
    ros::Publisher longitud_cable_pub = node.advertise<std_msgs::Int32>("guiado/longitud_cable", 1);

    // Parametros ROS
    // Control Robots
    ros::NodeHandle nh_param("~");
    nh_param.param<double>("kp_ard2", kp_ard2, 0.5);
    nh_param.param<double>("ki_ard2", ki_ard2, 0.0);
    nh_param.param<double>("kd_ard2", kd_ard2, 0.05);
    nh_param.param<double>("kp_p3at", kp_p3at, 0.2);
    nh_param.param<double>("ki_p3at", ki_p3at, 0.0);
    nh_param.param<double>("kd_p3at", kd_p3at, 0.05);
    nh_param.param<double>("ard2_vmax_linear", ard2_vmax_linear, 0.3);
    nh_param.param<double>("ard2_vmax_angular", ard2_vmax_angular, 1.0);
    nh_param.param<double>("p3at_vmax_linear", p3at_vmax_linear, 0.2);
    nh_param.param<double>("p3at_vmax_angular", p3at_vmax_angular, 1.0);

    // Control cable
    nh_param.param<double>("k_extension_cable", k_extension_cable, 1.0);
    nh_param.param<double>("k_recogida_cable", k_recogida_cable, 1.0);

    // Comportamiento Robots
    nh_param.param<double>("distancia_a_ard2", distancia_a_ard2, 2.0);
    nh_param.param<double>("altura_vuelo",altura_vuelo, 1.5);
    nh_param.param<double>("distancia_esquiva", distancia_esquiva, 3.0);
    nh_param.param<double>("long_cable_max", long_cable_max, 20);
    nh_param.param<bool>("activar_parada_longitud", activar_parada_longitud, true);
    nh_param.param<int>("n_ptos_esquiva", n_ptos_esquiva, 5);
    nh_param.param<bool>("activar_deteccion_obstaculos", activar_deteccion_obstaculos, true);

    // Mision
    nh_param.param<double>("misionx", misionx, 6.0);
    nh_param.param<double>("misiony", misiony, 0.0);

    ROS_INFO("--- PARAMETROS CONTROL ROBOTS ---");
    ROS_INFO("PID ARD2 -> Kp = %2f, Ki = %2f, Kd = %2f", kp_ard2, ki_ard2, kd_ard2);
    ROS_INFO("Velocidad maxima ARD2 -> lineal = %2f, angular = %2f", ard2_vmax_linear, ard2_vmax_angular);
    ROS_INFO("PID P3AT -> Kp = %2f, Ki = %2f, Kd = %2f", kp_p3at, ki_p3at, kd_p3at);
    ROS_INFO("Velocidad maxima P3AT -> lineal = %2f, angular = %2f", p3at_vmax_linear, p3at_vmax_angular);

    ROS_INFO("--- PARAMETROS CABLE ---");
    ROS_INFO("K Cable -> K_exten = %2f, K_recog = %2f",k_extension_cable, k_recogida_cable);

    ROS_INFO("--- PARAMETROS COMPORTAMIENTO ROBOTS ---");
    ROS_INFO("Distancia seguimiento P3AT a ARD2: %2f m", distancia_a_ard2);
    ROS_INFO("Altura vuelo del ARD2: %2f m", altura_vuelo);
    ROS_INFO("Distancia a obstaculo de P3AT en la esquiva: %2f m", distancia_esquiva);
    ROS_INFO("Longitud maxima del cable: %2f m", long_cable_max);
    ROS_INFO("Mecanismo parada emergencia por longitud del cable activo?: %d", activar_parada_longitud);
    ROS_INFO("Puntos de la trayectoria de esquiva de obstaculos: %i", n_ptos_esquiva);
    ROS_INFO("Deteccion obstaculos activa?: %d", activar_deteccion_obstaculos);

    ROS_INFO("--- PARAMETROS MISION ---");
    ROS_INFO("Objetivo mision --> X: %2f, Y: %2f", misionx, misiony);

    // Establecemos el objetivo de la mision
    objetivo_mision.position.x = misionx;
    objetivo_mision.position.y = misiony;
    objetivo_mision.position.z = altura_vuelo;

    //objetivo_mision.orientation = tf::createQuaternionMsgFromYaw(atan2(misiony, misionx));
    objetivo_mision.orientation = tf::createQuaternionMsgFromYaw(0.0);

    // Mensajes
    p3at_vel_msg = parar_robot();
    ard2_vel_msg = parar_robot();

    ros::Rate rate(PUBLISH_FREQ);

    while (node.ok()){

        /*if (activar_deteccion_obstaculos)
        {
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
        } */

        dist_centro_plataforma = lado_plataforma / (2 * std::abs(cos(orientacion_cable)));

        // CONDICION 0 || __OK__
        if (modo_emergencia)
        {
            accion_ard2 = EMERGENCIA;
            accion_p3at = EMERGENCIA;
        }
        // CONDICION 1 ||  __OK__
        else if (proyeccion_xy <= dist_centro_plataforma && accion_ard2 <= ARD2_VUELOSOBRESUELO)
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
        // CONDICION 3 ||  __OK__
        else if (obstaculo_detectado && accion_ard2 == ARD2_VUELOSOBRESUELO)
        {
            accion_ard2 = ARD2_MARCAJEOBSTACULO;
            accion_p3at = P3AT_ESQUIVAOBSTACULO;
            cnt_esquiva = 0;
            ROS_INFO("P3AT esquivando obstaculo / ARD2 marcando obstaculo");

            altura_a_suelo_msg.data = h_kalman_sonar + h_obstaculo;

            // Punto final tras esquivar el obstaculo
            pose_obj_p3at.position.x = pose_ard2.position.x + distancia_esquiva * cos(orientacion_cable + (M_PI/2));
            pose_obj_p3at.position.y = pose_ard2.position.y + distancia_esquiva * sin(orientacion_cable + (M_PI/2));
            pose_obj_p3at.position.z = 0.0;

            pose_obj_p3at.orientation = tf::createQuaternionMsgFromYaw(orientacion_cable);

            //Generamos la trayectoria para esquivar el obstaculo
            trayectoria_esquiva = generar_trayectoria_esquiva(pose_p3at, pose_obj_p3at, n_ptos_esquiva);

            // Drone mantiene la posicion sobre el punto y se orienta hacia el punto final de la trayectoria de esquiva
            pose_obj_ard2 = pose_ard2;
            pose_obj_ard2.orientation = orientar_a_punto(pose_ard2, pose_obj_p3at);

            ROS_INFO("Pto esquiva: %i", cnt_esquiva);
            ROS_INFO("Coordenadas - X: %2f / Y: %2f",
                     trayectoria_esquiva.poses[cnt_esquiva].position.x,
                     trayectoria_esquiva.poses[cnt_esquiva].position.y);

        }
        // CONDICION 4 ||  __OK__
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

            // Comprobamos si el Pioneer ha alcanzado en punto final de la esquiva
            std::tie(d_objetivo_p3at, d_altura_p3at) = evaluar_distancias(pose_p3at, pose_obj_p3at);
            rot_objetivo_p3at = std::abs(desviacion_yaw(pose_p3at, pose_obj_p3at));

            if (d_objetivo_p3at < 0.3 && rot_objetivo_p3at < 0.2)
            {
                accion_p3at = P3AT_ESPERAPIONNER;
                accion_ard2 = ARD2_APIONEER;
                ROS_INFO("P3AT a la espera / ARD2 hacia Pioneer");

                pose_obj_ard2 = pose_p3at;
                pose_obj_ard2.position.z = altura_vuelo;

                errores_a_cero();

                p3at_vel_msg = parar_robot();
            }
        }
        // CONDICION 5 ||  __OK__
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
        }
        // CONDICION 6 || __OK__
        else if (accion_ard2 == ARD2_ENTIERRA && accion_p3at == P3AT_MISIONFINALIZADA)
        {
            accion_ard2 = ARD2_VUELOSOBREPLATAFORMA;
            accion_p3at = P3AT_SEGUIMIENTO;
            ROS_INFO("MISION COMPLETA");
            modo_automatico = false;
        }
        // CONDICION 7 ||  __OK__
        else if (accion_ard2 == ARD2_APIONEER && accion_p3at == P3AT_ESPERAPIONNER && proyeccion_xy <= dist_centro_plataforma)
        {
            std::tie(d_objetivo_ard2, d_altura_ard2) = evaluar_distancias(pose_ard2, pose_obj_ard2);
            rot_objetivo_ard2 = std::abs(desviacion_yaw(pose_ard2, pose_obj_ard2));
            if (d_objetivo_ard2 < 0.3 && d_altura_ard2 < 0.2 && rot_objetivo_ard2 < 0.2)
            {
                ROS_INFO("DRONE SOBRE PIONEER");
                accion_ard2 = ARD2_VUELOSOBREPLATAFORMA;
                accion_p3at = P3AT_SEGUIMIENTO;

                errores_a_cero();
            }

            altura_a_suelo_msg.data = h_kalman_sonar + h_plataforma;
        }
        // CONDICION 8 ||  __OK__
        else if ((accion_ard2 == ARD2_ATERRIZANDO || accion_ard2 == ARD2_ENTIERRA) && proyeccion_xy <= dist_centro_plataforma)
        {
            altura_a_suelo_msg.data = h_kalman_sonar + h_plataforma;
        }

        // Caculamos la velocidad de control del Ard2
        if (accion_ard2 ==  EMERGENCIA)
        {
            ard2_vel_msg = joy_ard2_vel_msg;
        }
        else if (accion_ard2 == ARD2_MARCAJEOBSTACULO  || accion_ard2 == ARD2_APIONEER)
        {
            ard2_vel_msg = control_ard2(pose_ard2, pose_obj_ard2);
        }
        else if (accion_ard2 == ARD2_ATERRIZANDO)
        {
            objetivo_aterrizaje = pose_p3at;
            if (!aproximacion_prima)
            {
                objetivo_aterrizaje.position.z = altura_vuelo;

                std::tie(d_objetivo_ard2, d_altura_ard2) = evaluar_distancias(pose_ard2, objetivo_aterrizaje);
                if (d_objetivo_ard2 < 0.3 && d_altura_ard2 < 0.2)
                {
                    aproximacion_prima = true;
                    objetivo_aterrizaje.position.z = altura_plataforma;
                    ROS_INFO("PREAPROXIMACION AL PIONEER");

                    errores_a_cero();
                }
                ard2_vel_msg = control_ard2(pose_ard2, objetivo_aterrizaje);
            }
            else if (aproximacion_prima && !aproximacion_final)
            {
                ard2_vel_msg = parar_robot();
                ard2_vel_msg.linear.z = 0.1;

                if (long_cable_encoder < 0.3 && h_kalman_sonar < 0.2)
                {
                    ROS_INFO("EL DRONE HA ATERRIZADO");
                    fin_aterrizaje = true;
                    if (modo_automatico == true) { accion_ard2 = ARD2_ENTIERRA; }
                    else { accion_ard2 = ARD2_VUELOSOBREPLATAFORMA; }

                    fin_despegue = fin_mision = fin_aterrizaje = aproximacion_prima = aproximacion_final = false;
                    ard2_vel_msg = parar_robot();

                    modo_aterrizaje_msg.data = false;

                    land_pub.publish(std_msgs::Empty());
                    modo_aterrizaje_pub.publish(modo_aterrizaje_msg);

                    errores_a_cero();
                }
            }

            // TO_DO: calcular_velocidad_relativa()
            //      - La funcion tiene que calcular la velocidad relativa del pioneer con respecto al drone
            //      - Depues, sumar ambas velocidades
        }
        else if (accion_ard2 == ARD2_ENTIERRA)
        {
            ard2_vel_msg = parar_robot();
        }
        else
        {
            if (modo_automatico == true)
            {
                if (fin_despegue == false)
                {
                    objetivo_despegue = pose_p3at;
                    objetivo_despegue.position.z = altura_vuelo;
                    ard2_vel_msg = control_ard2(pose_ard2, objetivo_despegue);

                    std::tie(d_objetivo_ard2, d_altura_ard2) = evaluar_distancias(pose_ard2, objetivo_despegue);
                    if (d_objetivo_ard2 < 0.5 && d_altura_ard2 < 0.2)
                    {
                        fin_despegue = true;
                        ard2_vel_msg = control_ard2(pose_ard2, objetivo_mision);
                        ROS_INFO("DESPEGUE COMPLETADO - INICIANDO MISION");

                        errores_a_cero();
                    }
                }
                else if (fin_despegue == true && fin_mision == false)
                {
                    ard2_vel_msg = control_ard2(pose_ard2, objetivo_mision);
                    std::tie(d_objetivo_ard2, d_altura_ard2) = evaluar_distancias(pose_ard2, objetivo_mision);

                    // ROS_INFO("Distancia a objetivo: %2f", d_objetivo_ard2); // DEBUG

                    if (d_objetivo_ard2 < 0.3 && d_altura_ard2 < 0.2)
                    {
                        fin_mision = true;
                        accion_ard2 = ARD2_ATERRIZANDO;
                        accion_p3at = P3AT_AFINDEMISION;
                        objetivo_mision.position.z = 0.0;
                        ROS_INFO("EL DRONE HA COMPLETADO SU MISION - ATERRIZANDO");

                        errores_a_cero();
                    }
                }
            }
            else if (modo_automatico == false && teleop_ard2 == true)
            {
                ard2_vel_msg = joy_ard2_vel_msg;
            }
            else
            {
                ard2_vel_msg = parar_robot();
            }
        }

        // Calculamos la velocidad de control de Pioneer
        if (accion_p3at ==  EMERGENCIA)
        {
            p3at_vel_msg = parar_robot();
        }
        else if (accion_p3at == P3AT_ESQUIVAOBSTACULO)
        {
            if (cnt_esquiva < n_ptos_esquiva)
            {
                std::tie(d_pto_esquiva_p3at, d_altura_p3at) = evaluar_distancias(pose_p3at, trayectoria_esquiva.poses[cnt_esquiva]);

                geometry_msgs::Pose temp_pose_esquiva = trayectoria_esquiva.poses[cnt_esquiva];
                temp_pose_esquiva.orientation =  orientar_a_punto(pose_p3at, temp_pose_esquiva);
                rot_pto_esquiva_p3at = std::abs(desviacion_yaw(pose_p3at, temp_pose_esquiva));

                if (d_pto_esquiva_p3at < 0.5 && rot_pto_esquiva_p3at < 0.3)
                {
                    ROS_INFO("Pto esquiva: %i", cnt_esquiva);
                    ROS_INFO("Coordenadas - X: %2f / Y: %2f",
                             trayectoria_esquiva.poses[cnt_esquiva].position.x,
                             trayectoria_esquiva.poses[cnt_esquiva].position.y);
                    cnt_esquiva++;
                }
                else if (d_pto_esquiva_p3at > 0.2)
                {
                    p3at_vel_msg = control_p3at(pose_p3at, trayectoria_esquiva.poses[cnt_esquiva]);
                }
                else if (d_pto_esquiva_p3at < 0.2 && rot_pto_esquiva_p3at > 0.1)
                {
                    p3at_vel_msg = orientar_p3at(pose_p3at, trayectoria_esquiva.poses[cnt_esquiva]);
                }
            }
        }
        else if (accion_p3at == P3AT_AFINDEMISION)
        {
            p3at_vel_msg = control_p3at(pose_p3at, objetivo_mision);

            std::tie(d_objetivo_p3at, d_altura_p3at) = evaluar_distancias(pose_p3at, objetivo_mision);
            rot_objetivo_p3at = std::abs(desviacion_yaw(pose_p3at, pose_obj_p3at));

            if (d_objetivo_p3at < 0.3 && rot_objetivo_p3at < 0.2)
            {
                accion_p3at = P3AT_MISIONFINALIZADA;
                ROS_INFO("EL PIONEER HA COMPLETADO SU MISION");

                p3at_vel_msg = parar_robot();
            }
        }
        else if(accion_p3at == P3AT_ESPERAPIONNER)
        {
            p3at_vel_msg = parar_robot();
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

        // TO_DO: calcular la velocidad del cable
        q_cable = tf::createQuaternionFromRPY(0.0, inclinacion_cable, orientacion_cable);



        if (accion_ard2 == ARD2_ATERRIZANDO && (aproximacion_final || aproximacion_prima))
        {
            longitud_cable_float = (long_cable_encoder - k_recogida_cable/5 * (PUBLISH_FREQ / 1000.0));

            if (longitud_cable_float < 0.3) { longitud_cable_float = 0.3; }

            longitud_cable_msg.data = (int)(longitud_cable_float * 1000);
            long_cable_encoder = longitud_cable_float;
        }
        else
        {
            longitud_cable_float = k_extension_cable * distancia_entre_robots * 1000;
            longitud_cable_msg.data = (int)longitud_cable_float;
            long_cable_encoder = k_extension_cable * distancia_entre_robots;
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

        if (accion_ard2 != EMERGENCIA || accion_p3at != EMERGENCIA)
        {
            longitud_cable_pub.publish(longitud_cable_msg);
        }

        teleop_p3at = false;
        teleop_ard2 = false;
        teleop_cable = false;

        rate.sleep();
        ros::spinOnce();
    }
}
