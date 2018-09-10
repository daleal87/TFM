#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <tf/transform_listener.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
  const int PUBLISH_FREQ = 10;

  ros::init(argc, argv, "longitud_cable");
  ros::NodeHandle node;

  ros::Publisher longitud_cable_pub = node.advertise<std_msgs::Float64>("/cable/longitud", 1);
  ros::Publisher orientacion_cable_pub = node.advertise<std_msgs::Float64>("/cable/orientacion", 1);

  tf::TransformListener listener;

  std_msgs::Float64 longitud_cable_msg, orientacion_cable_msg;

  ros::Rate rate(PUBLISH_FREQ);

  while (node.ok()){
     tf::StampedTransform transform;
    try{
      listener.lookupTransform("/plataforma", "/base_ard2", ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
       ros::Duration(1.0).sleep();
    }

    longitud_cable_msg.data = sqrt(pow(transform.getOrigin().x(), 2) + pow(transform.getOrigin().y(), 2) + pow(transform.getOrigin().z(), 2));
    orientacion_cable_msg.data = atan2(transform.getOrigin().y(), transform.getOrigin().x());

    longitud_cable_pub.publish(longitud_cable_msg);
    orientacion_cable_pub.publish(orientacion_cable_msg);

    // std::cout<<"Longitud: "<<longitud_cable_msg<<std::endl;
    // std::cout<<"Orientacion: "<<orientacion_cable_msg<<std::endl;

    ros::spinOnce();
    rate.sleep();
  }
  return 0;





	int id = 50;
        try
        {
            listener->waitForTransform("/map", "/laser", scan_msg->header.stamp, ros::Duration(10.0));
            listener->lookupTransform("/map", "/laser",  scan_msg->header.stamp, transform);
        }
        catch (tf::TransformException& ex)
        {
            ROS_ERROR("Received an exception trying to transform a point from \"laser\" to \"map\": %s", ex.what());
        }

        float angle = scan_msg->angle_min + id * scan_msg->angle_increment;
        pt.x = ra * cos(angle);
        pt.y = ra * sin(angle);

        position_in.header = scan_msg->header;
        position_in.point.x = pt.x;
        position_in.point.y = pt.y;
        listener->transformPoint("map", position_in, position_out);


        // header
        new_goal.header.frame_id = "map";
        new_goal.header.stamp = ros::Time::now();
        // position
        new_goal.pose.position.x = position_out.point.x;
        new_goal.pose.position.y = position_out.point.y;
        new_goal.pose.position.z = 0.0;

        tf::Quaternion q = transform.getRotation();
        double yaw = tf::getYaw(q);
        double angle_goal = yaw + angle_orientation;

        geometry_msgs::Quaternion goal_quat = tf::createQuaternionMsgFromYaw(angle_goal);
        new_goal.pose.orientation = goal_quat;
        p_pub.publish(new_goal);

























}
