/*
* ardrone_joystick:
*
* This software provides a connection between a PS3-Joystick and the ardrone_brown - drone-driver
*
* It receives the joystick state from the joy-node and publishes the corresponding commands to the driver
*
* Author: Nikolas Engelhard
*
*
*/


#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Empty.h"
#include "std_srvs/Empty.h"
#include <math.h>

const int PUBLISH_FREQ = 50;

using namespace std;

struct TeleopArDrone
{
  ros::Subscriber joy_sub;
  ros::Publisher pub_takeoff, pub_land, pub_toggle_state, pub_vel, pub_vel_p3at;

  bool got_first_joy_msg;

  bool is_flying;
  bool toggle_pressed_in_last_msg;
  bool cam_toggle_pressed_in_last_msg;
  bool control_ard2, control_p3at;
  std_srvs::Empty srv_empty;

	ros::NodeHandle nh_;
  geometry_msgs::Twist twist, twist_p3at;
	ros::ServiceClient srv_cl_cam;


	void joyCb(const sensor_msgs::JoyConstPtr joy_msg){  

	 if (!got_first_joy_msg){
    ROS_INFO("Found joystick with %zu buttons and %zu axes", joy_msg->buttons.size(), joy_msg->axes.size());
	  got_first_joy_msg = true;
	 }

	 // mapping from joystick to velocity
	 float scale = 1;
   float scale_p3at = 0.5;

   twist.linear.x = scale*joy_msg->axes[1]; // forward, backward
   twist.linear.y = scale*joy_msg->axes[0]; // left right
   twist.linear.z = scale*joy_msg->axes[5]; // up down
   twist.angular.z = scale*joy_msg->axes[2]; // yaw

   twist_p3at.linear.x = scale_p3at*sqrt(pow(joy_msg->axes[1],2) + pow(joy_msg->axes[0],2)); // forward, backward
   if (joy_msg->axes[1] < 0){
     twist_p3at.linear.x = - twist_p3at.linear.x;
   }
   twist_p3at.angular.z = scale_p3at*joy_msg->axes[0]; // yaw
   if (twist_p3at.linear.x == 0) {
     twist_p3at.angular.z = 2*scale_p3at*joy_msg->axes[2]; // yaw
   }

/*
   twist_p3at.linear.x = scale_p3at*joy_msg->axes[1]; // forward, backward
   twist_p3at.angular.z = scale_p3at*joy_msg->axes[2]; // yaw
*/
   // button 5 (L1): dead man switch
	 bool dead_man_pressed = joy_msg->buttons.at(4);

   // button 6 (L2): switch emergeny state
   bool emergency_toggle_pressed = joy_msg->buttons.at(6);

	 // button 0 (select): switch camera mode
   bool cam_toggle_pressed = joy_msg->buttons.at(1);

   // button 8 (R2): control del Pioneer
   bool boton_control_p3at = joy_msg->buttons.at(7);


	 if (!is_flying && dead_man_pressed){
	  ROS_INFO("L1 was pressed, Taking off!");
	  pub_takeoff.publish(std_msgs::Empty());
	  is_flying = true;
    control_ard2 = true;
    control_p3at = false;
	 }

	 if (is_flying && !dead_man_pressed){
	  ROS_INFO("L1 was released, landing");
	  pub_land.publish(std_msgs::Empty());
	  is_flying = false;
	 }

	 // toggle only once!
	 if (!toggle_pressed_in_last_msg && emergency_toggle_pressed){
	  ROS_INFO("Changing emergency status");
	  pub_toggle_state.publish(std_msgs::Empty());
	 }
	 toggle_pressed_in_last_msg = emergency_toggle_pressed;


	 if (!cam_toggle_pressed_in_last_msg && cam_toggle_pressed){
	  ROS_INFO("Changing Camera");
	  if (!srv_cl_cam.call(srv_empty))  ROS_INFO("Failed to toggle Camera");
	 }
	 cam_toggle_pressed_in_last_msg = cam_toggle_pressed;


   if (boton_control_p3at && !dead_man_pressed && !control_p3at){
    ROS_INFO("R2 pulsado. Controlando el p3at");
    control_ard2 = false;
    control_p3at = true;
   }

   if (!boton_control_p3at && control_p3at){
    ROS_INFO("R2 liberado. Control del p3at finalizado");
    control_p3at = false;
   }
  }


	TeleopArDrone(){

	 twist.linear.x = twist.linear.y = twist.linear.z = 0;
	 twist.angular.x = twist.angular.y = twist.angular.z = 0;


   twist_p3at.linear.x = twist_p3at.linear.y = twist_p3at.linear.z = 0;
   twist_p3at.angular.x = twist_p3at.angular.y = twist_p3at.angular.z = 0;

	 is_flying = false;
	 got_first_joy_msg = false;
   control_ard2 = false;
   control_p3at = false;

	 joy_sub = nh_.subscribe("/joy", 1,&TeleopArDrone::joyCb, this);
	 toggle_pressed_in_last_msg = cam_toggle_pressed_in_last_msg = false;

   pub_takeoff       = nh_.advertise<std_msgs::Empty>("ardrone/takeoff",1);
   pub_land          = nh_.advertise<std_msgs::Empty>("ardrone/land",1);
   pub_toggle_state  = nh_.advertise<std_msgs::Empty>("ardrone/reset",1);
   pub_vel           = nh_.advertise<geometry_msgs::Twist>("cmd_vel",1);
   srv_cl_cam        = nh_.serviceClient<std_srvs::Empty>("ardrone/togglecam",1);
   pub_vel_p3at      = nh_.advertise<geometry_msgs::Twist>("p3at/cmd_vel", 10);
  }

	void send_cmd_vel(){
    pub_vel.publish(twist);
  }

  void send_cmd_vel_p3at(){
    pub_vel_p3at.publish(twist_p3at);
  }
};


int main(int argc, char **argv)
{
  ros::init(argc, argv, "ardrone_teleop");

  ROS_INFO("Started ArDrone joystick-Teleop");
  ROS_INFO("Press L1 to toggle emergency-state");
  ROS_INFO("Press and hold L2 for takeoff");
  ROS_INFO("Press 'select' to choose camera");

  TeleopArDrone teleop;
  ros::Rate pub_rate(PUBLISH_FREQ);

  while (teleop.nh_.ok())
  {
    ros::spinOnce();
    if (teleop.control_ard2 == true) {
      teleop.send_cmd_vel();
    }
    else if (teleop.control_p3at == true) {
      teleop.send_cmd_vel_p3at();
    }
    pub_rate.sleep();
  }

  return 0;
}
