#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <ardrone_autonomy/Navdata.h>

#include <stdint.h>
#include <vector>
#include <string>






ardrone_autonomy::Navdata navdata;
nav_msgs::Odometry odo_msg;


void navdataCallback(const ardrone_autonomy::Navdata::ConstPtr& navdata_msg)
{
  navdata.data = navdata_msg->data; // Leemos el valor del topic navadata
}



int main(int argc, char** argv)
{
    ros::init(argc, argv, "navdata_a_odometry");
    ros::NodeHandle node;

    ros::Subscriber navdata_sub = node.subscribe("ardrone/navdata", 1, navdataCallback);
    ros::Publisher odo_pub = node.advertise<geometry_msgs::Twist>("ardrone/odom", 10);

    while (node.ok()){






        odo_msg.header.stamp = navdata_receive_time;
        odo_msg.header.frame_id = "odom";
        odo_msg.child_frame_id = drone_frame_base;

        odo_msg.pose.pose.position.x = odometry[0];
        odo_msg.pose.pose.position.y = odometry[1];
        odo_msg.pose.pose.position.z = navdata_raw.navdata_demo.altitude / 1000.0;
        odo_msg.pose.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(
              navdata_raw.navdata_demo.phi / 180000.0 * M_PI,
              -navdata_raw.navdata_demo.theta / 180000.0 * M_PI,
              -navdata_raw.navdata_demo.psi / 180000.0 * M_PI);

        odo_msg.twist.twist.linear.x = navdata_raw.navdata_demo.vx / 1000.0;
        odo_msg.twist.twist.linear.y = -navdata_raw.navdata_demo.vy / 1000.0;
        odo_msg.twist.twist.linear.z = -navdata_raw.navdata_demo.vz / 1000.0;


        odo_pub.publish(odo_msg);
        ros::spinOnce();
    }
}
