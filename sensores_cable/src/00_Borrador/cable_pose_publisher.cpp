
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <ros/ros.h>
#include <tf/transform_listener.h>

/*!
 * Creates and runs the robot_pose_publisher node.
 *
 * \param argc argument count that is passed to ros::init
 * \param argv arguments that are passed to ros::init
 * \return EXIT_SUCCESS if the node runs correctly
 */
int main(int argc, char ** argv)
{
  // initialize ROS and the node
  ros::init(argc, argv, "cable_pose_publisher");
  ros::NodeHandle nh;
  ros::NodeHandle nh_priv("~");

  // configuring parameters
  std::string zero_frame, objective_frame;
  double publish_frequency;
  bool is_stamped;
  ros::Publisher p_pub;

  nh_priv.param<std::string>("objective_frame",zero_frame,"/base_link");
  nh_priv.param<std::string>("sphere_20_frame",objective_frame,"/sphere_20_x");
  nh_priv.param<double>("publish_frequency",publish_frequency,1);
  nh_priv.param<bool>("is_stamped", is_stamped, false);

  if(is_stamped)
    p_pub = nh.advertise<geometry_msgs::PoseStamped>("cable_pose", 1);
  else 
    p_pub = nh.advertise<geometry_msgs::Pose>("cable_pose", 1);

  // create the listener
  tf::TransformListener listener;
  

  ros::Rate rate(publish_frequency);
  while (nh.ok())
  {
    tf::StampedTransform transform;
    //tf::Transform transform;
    try
    {
      listener.waitForTransform(zero_frame, objective_frame, ros::Time::now(), ros::Duration(3.0));
      //listener.lookupTransform(zero_frame, objective_frame, ros::Time(0), transform);
      listener.lookupTransform(zero_frame, objective_frame, ros::Time::now(), transform);

      // construct a pose message
      geometry_msgs::PoseStamped pose_stamped;
      pose_stamped.header.frame_id = zero_frame;
      pose_stamped.header.stamp = ros::Time::now();

      pose_stamped.pose.orientation.x = transform.getRotation().getX();
      pose_stamped.pose.orientation.y = transform.getRotation().getY();
      pose_stamped.pose.orientation.z = transform.getRotation().getZ();
      pose_stamped.pose.orientation.w = transform.getRotation().getW();

      pose_stamped.pose.position.x = transform.getOrigin().getX();
      pose_stamped.pose.position.y = transform.getOrigin().getY();
      pose_stamped.pose.position.z = transform.getOrigin().getZ();

      if(is_stamped)
        p_pub.publish(pose_stamped);
      else
        p_pub.publish(pose_stamped.pose);
    }
    catch (tf::TransformException &ex)
    {
      // just continue on
    }

    rate.sleep();
  }

  return EXIT_SUCCESS;
}
