#include "vision/pos_transformer/pos_transformer_real.hpp"

Pos_Transformer::Pos_Transformer()
{
    ros::NodeHandle nh_; 

    std::string platform_position_topic_; //topic donde el nodo de detección publica la posición de la plataforma respecto de la cámara del dron.
    std::string world_estimated_position_topic_; //topic donde se va a publicar la posición estimada de la plataforma en el mundo.


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    nh_.param("platform_position_topic", platform_position_topic_, std::string("/platform/estimated_position"));
    nh_.param("world_estimated_position_topic", world_estimated_position_topic_, std::string("/world_estimated_position"));
    nh_.param("pub_rate", pub_rate, 10.0);    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Subscribers
    platform_position_subs_ = nh_.subscribe(platform_position_topic_, 1, &Pos_Transformer::transformation, this);

    //Publishers
    pose_in_world_pub_ = nh_.advertise<geometry_msgs::PoseStamped>(world_estimated_position_topic_, 1);

    //Timer
    timer = nh_.createTimer(ros::Duration(1.0/pub_rate), &Pos_Transformer::timerCallback, this);


    // VARIABLES' INITIALIZATION
    t_ref = 0;
    found = false;
    found_time = 0.0;

    // CAM to QUADROTOR TRANSFORMATI
    int i = 0;
    tf_listener.waitForTransform("/centre","/downward_cam_optical_frame", ros::Time(0), ros::Duration(3.0));         
    try{
        tf_listener.lookupTransform("/centre","/downward_cam_optical_frame",ros::Time(0), transform);
        ROS_INFO("Trying to lookupTransform transform (0)");
        i=3;
        t_ref = ros::Time::now().toSec();
    }
    catch (tf::TransformException ex){
        ROS_ERROR("%s",ex.what());
        ros::Duration(1.0).sleep();
    }

    while(i < 2)
    {
        ROS_ERROR("%d",i);
        tf_listener.waitForTransform("/centre","/downward_cam_optical_frame", ros::Time(0), ros::Duration(3.0));
        try{
            tf_listener.lookupTransform("/centre","/downward_cam_optical_frame",ros::Time(0), transform);
            ROS_INFO("Trying to lookupTransform transform (1)");
            i=3;
            t_ref = ros::Time::now().toSec();
        }
        catch (tf::TransformException ex){
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
            i++;
        }
    }
    
} // end del constructor

void Pos_Transformer::timerCallback(const ros::TimerEvent& e){
    if (found) {
        pose_in_world_pub_.publish(estimated_centroid_in_world); 
    }

    if ( found && (std::fabs( ros::Time::now().toSec() - found_time) > 1)  ) {
        ROS_INFO_STREAM("Ojetivo perdido! Iniciando maniobra de relocalizacion");
        found = false;        
    }
}

void  Pos_Transformer::transformation(const geometry_msgs::PoseStamped &centroid){

    found = true;
    found_time = ros::Time::now().toSec();

    // Transformation from the quadrotor Cam to the world, which is called /centre
    tf::Vector3 point( centroid.pose.position.x, centroid.pose.position.y, centroid.pose.position.z );
    
    tf_listener.waitForTransform("/centre","/downward_cam_optical_frame", ros::Time(0), ros::Duration(0.5)); //0.05
    tf_listener.lookupTransform("/centre","/downward_cam_optical_frame",ros::Time(0), transform);
    
    pose_in_world_ = transform * point;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    

    //posicin del centride de la etimacion en el mundo
    estimated_centroid_in_world.header.stamp= ros::Time::now();
    estimated_centroid_in_world.header.seq = ros::Time::now().toSec() - t_ref;
    estimated_centroid_in_world.header.frame_id = "/centre";
    estimated_centroid_in_world.pose.orientation.w=1;
    estimated_centroid_in_world.pose.orientation.x=0;
    estimated_centroid_in_world.pose.orientation.y=0;
    estimated_centroid_in_world.pose.orientation.z=0;
    estimated_centroid_in_world.pose.position.x=pose_in_world_.getX();
    estimated_centroid_in_world.pose.position.y=pose_in_world_.getY();
    estimated_centroid_in_world.pose.position.z=1.4;
     
} // end of tracking callback


int main(int argc, char** argv)
{
    ros::init(argc, argv, "pos_transformer");
    Pos_Transformer pos_transformer;
    ROS_INFO("quadrotorCam_to_world transformation done");
    ros::spin();
}

