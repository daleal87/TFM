#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <ardrone_autonomy/Navdata.h>
#include <tf/transform_broadcaster.h>

#include <stdint.h>
#include <vector>
#include <string>


void PublishOdometry(ardrone_autonomy::Navdata);
void navdataCallback(const ardrone_autonomy::Navdata::ConstPtr&);


ardrone_autonomy::Navdata navdata_raw;
ros::Time last_receive_time, navdata_receive_time;
ros::Publisher odo_pub;

double odometry[2];
std::string drone_frame_base = "base_ard2";



int main(int argc, char** argv)
{
    const int PUBLISH_FREQ = 10;

    ros::init(argc, argv, "navdata_a_odometry");

    ros::NodeHandle node;

    ros::Subscriber navdata_sub = node.subscribe("ardrone/navdata", 1, navdataCallback);
    odo_pub = node.advertise<nav_msgs::Odometry>("ardrone/odom", 10);

    last_receive_time = ros::Time::now();

    ros::Rate rate(PUBLISH_FREQ);


    while (node.ok()){

        PublishOdometry(navdata_raw);

        rate.sleep();
        ros::spinOnce();
    }
}


void PublishOdometry(ardrone_autonomy::Navdata navdata_raw)
{
  if (last_receive_time.isValid())
  {
    navdata_receive_time = navdata_raw.header.stamp;
    double delta_t = (navdata_receive_time - last_receive_time).toSec();
    odometry[0] += ((cos((navdata_raw.rotZ / 180000.0) * M_PI) *
                     navdata_raw.vx - sin((navdata_raw.rotZ / 180000.0) * M_PI) *
                     -navdata_raw.vy) * delta_t) / 1000.0;
    odometry[1] += ((sin((navdata_raw.rotZ / 180000.0) * M_PI) *
                     navdata_raw.vx + cos((navdata_raw.rotZ / 180000.0) * M_PI) *
                     -navdata_raw.vy) * delta_t) / 1000.0;
  }
  last_receive_time = navdata_raw.header.stamp;

  nav_msgs::Odometry odo_msg;
  odo_msg.header.stamp = navdata_raw.header.stamp;
  odo_msg.header.frame_id = "odom";
  odo_msg.child_frame_id = drone_frame_base;

  odo_msg.pose.pose.position.x = odometry[0];
  odo_msg.pose.pose.position.y = odometry[1];
  odo_msg.pose.pose.position.z = navdata_raw.altd / 1000.0;
  odo_msg.pose.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(
        navdata_raw.rotX / 180000.0 * M_PI,
        -navdata_raw.rotY / 180000.0 * M_PI,
        -navdata_raw.rotZ / 180000.0 * M_PI);

  odo_msg.twist.twist.linear.x = navdata_raw.vx / 1000.0;
  odo_msg.twist.twist.linear.y = -navdata_raw.vy / 1000.0;
  odo_msg.twist.twist.linear.z = -navdata_raw.vz / 1000.0;

  odo_pub.publish(odo_msg);


  /*
  tf::Vector3 t;
  tf::pointMsgToTF(odo_msg.pose.pose.position, t);
  tf::Quaternion q;
  tf::quaternionMsgToTF(odo_msg.pose.pose.orientation, q);

  tf_odom.stamp_ = navdata_receive_time;
  tf_odom.child_frame_id_ = drone_frame_base;
  tf_odom.setOrigin(t);
  tf_odom.setRotation(q);
  tf_broad.sendTransform(tf_odom);
  */
}

void navdataCallback(const ardrone_autonomy::Navdata::ConstPtr& navdata_msg)
{
  navdata_raw.header.stamp = navdata_msg->header.stamp; // Leemos el valor del topic navadata

  navdata_raw.altd = navdata_msg->altd;

  navdata_raw.vx = navdata_msg->vx;
  navdata_raw.vy = navdata_msg->vy;
  navdata_raw.vz = navdata_msg->vz;

  navdata_raw.rotX = navdata_msg->rotX;
  navdata_raw.rotY = navdata_msg->rotY;
  navdata_raw.rotZ = navdata_msg->rotZ;
}
