#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <std_msgs/Float64.h>
#include <tf/transform_listener.h>
#include <ardrone_autonomy/Navdata.h>

#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <math.h>
#include <string>

const int PUBLISH_FREQ = 50;

double inclinacion, orientacion, k_correccion_orient;
double correcion_orient = 0.0;
double timer_trigger = 0.1;
double longitud_cable = 0.0;

std::string drone_frame_base, pioneer_frame_base, drone_frame_full, pioneer_frame_full;
std_msgs::Int32 navdata_altd_msg;

void imucableCallback(const geometry_msgs::Vector3Stamped::ConstPtr& msg) // TO_DO: tipo mensaje
{
    inclinacion = msg->vector.y;
    orientacion = msg->vector.z - correcion_orient;
}

void longitudCallback(const std_msgs::Int32::ConstPtr& msg) // TO_DO: tipo mensaje
{
    longitud_cable = msg->data / 1000.0;
}

void correcionCallback(const ros::TimerEvent&)
{
  correcion_orient += k_correccion_orient * timer_trigger;
}

void navdataCallback(const ardrone_autonomy::Navdata::ConstPtr& navdata_msg)
{
  navdata_altd_msg.data = navdata_msg->altd;
}


int main(int argc, char **argv)
{  
  ros::init(argc, argv, "sensores_cable");
  ros::NodeHandle node;


  ros::Subscriber longitud_cable_subs =  node.subscribe("/cable/longitud", 1, longitudCallback);
  ros::Subscriber navdata_sub = node.subscribe("ardrone/navdata", 1, navdataCallback);

  ros::Publisher dist_robots_pub = node.advertise<std_msgs::Float64>("/cable/distancia_robots", 1);
  ros::Publisher orientacion_cable_pub = node.advertise<std_msgs::Float64>("/cable/orientacion", 1);
  ros::Publisher inclinacion_cable_pub = node.advertise<std_msgs::Float64>("/cable/inclinacion", 1);
  ros::Publisher proyeccionXY_cable_pub = node.advertise<std_msgs::Float64>("/cable/proyeccionXY", 1);
  ros::Publisher cable_drone_pos_pub = node.advertise<nav_msgs::Odometry>("/cable/drone_pos", 1);
  ros::Publisher navdata_altd_pub = node.advertise<std_msgs::Int32>("/ardrone/navdata_altitude", 1);

  ros::NodeHandle nh_param("~");
  nh_param.param<std::string>("pioneer_frame_base", pioneer_frame_base, "base_link");
  nh_param.param<std::string>("drone_frame_base", drone_frame_base, "ardrone_base_link");

  tf::TransformListener listener;

  std_msgs::Float64 dist_robots_msg, orientacion_cable_msg, inclinacion_cable_msg, proyeccionXY_cable_msg;

  double posX, posY, posZ;
  double h_plataforma = 0.4;

  drone_frame_full = "/";
  pioneer_frame_full = "/";

  drone_frame_full.append(drone_frame_base);
  pioneer_frame_full.append(pioneer_frame_base);

  ROS_INFO("--- CORRECCION ---");
  ROS_INFO("k correccion orientacion = %2f", k_correccion_orient);

  ROS_INFO("--- FRAMES ---");
  ROS_INFO("pioneer_frame_base = %s", drone_frame_full.c_str());
  ROS_INFO("drone_frame_base = %s", pioneer_frame_full.c_str());

  ros::Rate rate(PUBLISH_FREQ);

  while (node.ok()){
     tf::StampedTransform transform;
    try{
      listener.lookupTransform(pioneer_frame_full, drone_frame_full, ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
       ros::Duration(1.0).sleep();
    }

    posX = transform.getOrigin().x();
    posY = transform.getOrigin().y();
    posZ = transform.getOrigin().z();

    dist_robots_msg.data = sqrt(pow(transform.getOrigin().x(), 2) + pow(transform.getOrigin().y(), 2) + pow(transform.getOrigin().z(), 2));
    orientacion_cable_msg.data = atan2(transform.getOrigin().y(), transform.getOrigin().x());
    inclinacion_cable_msg.data = asin(transform.getOrigin().z() / dist_robots_msg.data);
    proyeccionXY_cable_msg.data = dist_robots_msg.data * cos(inclinacion_cable_msg.data);

    // Cremos el topic con la odometria deducida de la informacion del cable
    nav_msgs::Odometry odo_msg;

    odo_msg.header.stamp = ros::Time::now();
    odo_msg.header.frame_id = "odom";
    odo_msg.child_frame_id = drone_frame_base;

    odo_msg.pose.pose.position.x = posX;
    odo_msg.pose.pose.position.y = posY;
    odo_msg.pose.pose.position.z = posZ + h_plataforma;
    odo_msg.pose.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, 0);

    //odo_msg.twist.twist.linear.x = 0;
    //odo_msg.twist.twist.linear.y = 0;
    //odo_msg.twist.twist.linear.z = 0;

    // Publicamos los topics
    dist_robots_pub.publish(dist_robots_msg);
    orientacion_cable_pub.publish(orientacion_cable_msg);
    inclinacion_cable_pub.publish(inclinacion_cable_msg);
    proyeccionXY_cable_pub.publish(proyeccionXY_cable_msg);
    cable_drone_pos_pub.publish(odo_msg);
    navdata_altd_pub.publish(navdata_altd_msg);

    ros::spinOnce();
    rate.sleep();
  }
  return 0;
}


