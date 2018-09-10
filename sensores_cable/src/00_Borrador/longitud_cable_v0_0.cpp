#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_listener.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <string>


int main(int argc, char **argv)
{
  const int PUBLISH_FREQ = 1;
  float longitud;

  ros::init(argc, argv, "longitud_cable");
  ros::NodeHandle node;
  ros::Publisher longitud_cable_pub = n.advertise<sensor_msgs::JointState>("/cable/longitud_cable", 1);
  tf::TransformListener listener;

  ros::Rate loop_rate(PUBLISH_FREQ);

  sensor_msgs::JointState joint_state;

  joint_state.name.resize(25);
  joint_state.position.resize(25);

  joint_state.name[0] = "tensor_1";
  joint_state.name[1] = "tensor_2";
  joint_state.name[2] = "tensor_3";
  joint_state.name[3] = "tensor_4";  
  joint_state.name[4] = "tensor_5";
  joint_state.name[5] = "tensor_6";
  joint_state.name[6] = "tensor_7";
  joint_state.name[7] = "tensor_8";
  joint_state.name[8] = "tensor_9";
  joint_state.name[9] = "tensor_10";
  joint_state.name[10] = "tensor_11";
  joint_state.name[11] = "tensor_12";  
  joint_state.name[12] = "tensor_13";
  joint_state.name[13] = "tensor_14";
  joint_state.name[14] = "tensor_15";
  joint_state.name[15] = "tensor_16";
  joint_state.name[16] = "tensor_17";
  joint_state.name[17] = "tensor_18";
  joint_state.name[18] = "tensor_19";
  joint_state.name[19] = "tensor_20";  
  joint_state.name[20] = "tensor_21";
  joint_state.name[21] = "tensor_22";
  joint_state.name[22] = "tensor_23";
  joint_state.name[23] = "tensor_24";
  joint_state.name[24] = "tensor_25";

// set your calculated velocities  
  for(size_t i = 0; i < joint_state.name.size(); i++)
	//joint_state.name[i] = "tensor_" + std::to_string(i);
  	joint_state.position[i] = 0.0;
  std::cout<<joint_state<<std::endl;


  while(ros::ok()){
    //update joint_state.command commands here
    longitud_cable_pub.publish(joint_state);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}


