#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv/cv.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Range.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Imu.h>
#include <cvg_sim_msgs/Altimeter.h>

#include <tf/transform_listener.h>

#define DEFAULT_SIZE 0.64

namespace enc = sensor_msgs::image_encodings;
using namespace cv;
using namespace std;

static const char WINDOW[] = "Image Processed";
static const char WINDOW_NAME_BLUR[] = "window_image_blur";
static const char WINDOW_NAME_FINAL[] = "window_image_final";


cv::Mat image;




int H_min_g;
int H_max_g;
int S_min_g;
int S_max_g;
int V_min_g;
int V_max_g;

int images_read = 0;
int times_detected = 0;
int false_positives = 0;
int obj_detected = 0;

// image Subscriber and Publisher
image_transport::Subscriber image_sub_;
image_transport::Publisher image_pub_;

class Indicator_Detection
{
  
    // ROS PUBLISHERS
    ros::Publisher indicator_position_;

    // ROS SUBSCRIBERS
    ros::Subscriber camera_info_;
    ros::Subscriber altitude_;
    ros::Subscriber cam_info_;
    ros::Subscriber imu_info_;

    double fx;
    double fy;
    double cx;
    double cy;
    double T;
    
    double altitude_quadrotor;
    
    geometry_msgs::Twist vel;
    
    double angle_x;
    double angular_velocity_x;
    
    double angle_y;
    double angular_velocity_y;
    
    double linear_acceleration_x;
    double linear_acceleration_y;

    double teoric_size;

    double altura_platform;

    //VARIABLES FOR DRAWING THE LANDING_PLATFORM SHAPE
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<cv::Point> approx;

public:
    Indicator_Detection();
    void height(const cvg_sim_msgs::AltimeterPtr& hector_height);
    void cam_info(const sensor_msgs::CameraInfo& cam_parameters);
    void angle(const sensor_msgs::ImuConstPtr& hector_imu);
    void indicatorDetectionCallback(const sensor_msgs::ImageConstPtr& original_image);

    
    
}; //end of class Indicator_Detection


Indicator_Detection::Indicator_Detection()
{
    ROS_INFO("Init Class: Indicator_Detection");
    
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_(nh_);
    

    std::string image_topic;
    std::string indicator_position_topic;
    std::string altitude_topic;
    std::string camera_info_topic;
    std::string imu_topic;
    std::string cmd_topic_vel_;

    
    
    

    // GETTING ROS PARAMETERS
    nh_.param("image_topic", image_topic, std::string("/ardrone/bottom/image_raw"));
    nh_.param("cam_info_topic", camera_info_topic, std::string("/ardrone/bottom/camera_info"));
    nh_.param("indicator_position_topic", indicator_position_topic, std::string("/platform/indicator_position"));
    nh_.param("altitude_topic", altitude_topic, std::string("/altimeter")); // /quadrotor/altimeter has less limitations
    nh_.param("imu_topic", imu_topic, std::string("/ardrone/imu"));

    nh_.param("H_min_g", H_min_g, 0);
    nh_.param("H_max_g", H_max_g, 179);
    nh_.param("S_min_g", S_min_g, 0);
    nh_.param("S_max_g", S_max_g, 156);
    nh_.param("V_min_g", V_min_g, 0);
    nh_.param("V_max_g", V_max_g, 164);

    nh_.param("teoric_size", teoric_size, DEFAULT_SIZE);
    nh_.param("altura_platform", altura_platform, 0.392);



    //TOPICS

    //Subscribe to input video feed and publish output video feed
    image_sub_ = it_.subscribe(image_topic, 1, &Indicator_Detection::indicatorDetectionCallback, this);
    image_pub_ = it_.advertise("/image_converter/output_video", 1);

    //We subscribe to the ALTITUDE_TOPIC of the quadrotor
    altitude_ = nh_.subscribe(altitude_topic, 1, &Indicator_Detection::height, this);
    
    //We subscribe to the IMU_TOPIC of the quadrotor
    imu_info_ = nh_.subscribe(imu_topic, 1, &Indicator_Detection::angle, this);

    //We subscribe to the CAMERA_INFO_TOPIC of the quadrotor
    cam_info_ = nh_.subscribe(camera_info_topic, 1, &Indicator_Detection::cam_info, this);

    //We publish on the indicator_POSITION_TOPIC 
    indicator_position_ = nh_.advertise<geometry_msgs::PoseStamped>(indicator_position_topic, 1);



    //TRACKBAR

    cv::namedWindow("BallIndicator");
    cv::createTrackbar("H_min","BallIndicator",&H_min_g,179,NULL);
    cv::createTrackbar("H_max","BallIndicator",&H_max_g,179,NULL);
    cv::createTrackbar("S_min","BallIndicator",&S_min_g,255,NULL);
    cv::createTrackbar("S_max","BallIndicator",&S_max_g,255,NULL);
    cv::createTrackbar("V_min","BallIndicator",&V_min_g,255,NULL);
    cv::createTrackbar("V_max","BallIndicator",&V_max_g,255,NULL);



    ROS_INFO("Setup completed");




}
   
void Indicator_Detection::height(const cvg_sim_msgs::AltimeterPtr& hector_height)
{
    altitude_quadrotor = hector_height->altitude;

    
}


void Indicator_Detection::angle(const sensor_msgs::ImuConstPtr& hector_imu)
{

  angle_x               = hector_imu->orientation.x;
  angular_velocity_x    = hector_imu->angular_velocity.x;
 
  angle_y               = hector_imu->orientation.y;
  angular_velocity_y    = hector_imu->angular_velocity.y;
 
  linear_acceleration_x = hector_imu->linear_acceleration.x;
  linear_acceleration_y = hector_imu->linear_acceleration.y;

}


void Indicator_Detection::cam_info(const sensor_msgs::CameraInfo& cam_parameters){
    //ROS_INFO("Parameters from the pinhole model");
    fx = cam_parameters.K.at(0);
    fy = cam_parameters.K.at(4);
    cx = cam_parameters.K.at(2);
    cy = cam_parameters.K.at(5);
    T  = cam_parameters.K.at(1);
    //ROS_INFO("Los parametros son  (fx,fy)=(%f , %f)", fx, fy);
}


void Indicator_Detection::indicatorDetectionCallback(const sensor_msgs::ImageConstPtr& original_image)
{
    //Convert from the ROS image message to a CvImage suitable for working with OpenCV for processing
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(original_image, enc::BGR8);
        image = cv_ptr->image;
        images_read++;
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Failed to convert image: %s", e.what());
        return;
    }

    cv::Mat img_mask, img_hsv; 
    cv::cvtColor(cv_ptr->image,img_hsv,CV_BGR2HSV);
    cv::inRange(img_hsv,cv::Scalar(H_min_g,S_min_g,V_min_g),cv::Scalar(H_max_g,S_max_g,V_max_g),img_mask); 
    //cv::imshow(WINDOW, img_mask);
    cv::waitKey(3);

    //We negate the image
    cv::Mat img_negated;
    cv::bitwise_not ( img_mask, img_negated );
   
   
    //Find countours on the image
    cv::findContours(img_negated, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));

    for (int i = 0; i < contours.size(); i++)
    {
        cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)* 0.02, true);

        cv::Point pt;
        for(int j=0;j<approx.size();j++)
        {
            //cv::Point point = approx[i];
            //ROS_INFO("extracting points X %d Y %d",point.x, point.y);

            if (j == approx.size()-1)
            {
                cv::line(image, approx.at(j), approx.at(0), cv::Scalar(0,255,0), 4);
            }
            else
            {
                cv::line(image, approx.at(j), approx.at(j+1), cv::Scalar(0,255,0), 4);
            }
        }

        // indicator extraction----------------------------------------------------------------
        /// 1º Get the moments
        cv::Moments m;
        m = cv::moments( approx, false );

        /// 2º Get the mass centers: (indicator)
        cv::Point2f mc;
        mc = cv::Point2f( m.m10/m.m00 , m.m01/m.m00 );
        cv::line(image, mc, mc, cv::Scalar(0,255,255), 8); // we draw a yellow point for that mc

        /// PINHOLE inverse transformation ==> (x,y,z)= f(u,v) without distortion, (u,v)=mc ---------------------
        ROS_INFO("indicator location");
        geometry_msgs::PoseStamped indicator;
            indicator.header.stamp= ros::Time::now();
            indicator.header.seq = ros::Time::now().toSec();
            indicator.header.frame_id = "/image_plane";
            indicator.pose.orientation.w=1;
            indicator.pose.orientation.x=0;
            indicator.pose.orientation.y=0;
            indicator.pose.orientation.z=0;
            
            //indicatore corregido
            indicator.pose.position.x=((mc.x - cx)*altitude_quadrotor - (T*(mc.y - cy)*altitude_quadrotor)/fy)/fx;
            indicator.pose.position.y=(((mc.y - cy)*altitude_quadrotor)/fy);            
            indicator.pose.position.z=altitude_quadrotor - altura_platform;          
        
        ROS_INFO("Centro de masas en pixels del objetivo: (%f , %f)", mc.x, mc.y);
        ROS_INFO("La posicion del objetivo es: (%f , %f, %f) en metros respecto a la camara", indicator.pose.position.x, indicator.pose.position.y, indicator.pose.position.z);

        indicator_position_.publish(indicator);

    }

    /// Show in a window
    //namedWindow( "platform_DETECTED", CV_WINDOW_AUTOSIZE );
    imshow( "Indicator_DETECTED", image );
    cv::waitKey(3);


    image_pub_.publish(cv_ptr->toImageMsg());
                                         
}
   

int main(int argc, char** argv)
{
    ros::init(argc, argv, "indicator_detection");
    
    Indicator_Detection indicator_detection;
    ros::spin();
    ROS_INFO("Indicator_Detection::main.cpp::No error.");
    cv::destroyWindow(WINDOW);
    return 0;
}
