#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv/cv.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "highgui.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Range.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Imu.h>
#include <ardrone_autonomy/Navdata.h>


#include <tf/transform_listener.h>

#define DEFAULT_SIZE 1.5
#define MIN_NUM_SIDES 3
#define MAX_NUM_SIDES 12

namespace enc = sensor_msgs::image_encodings;
using namespace cv;
using namespace std;

class Platform_Detection {
public:
    Platform_Detection();
    void navdata(const ardrone_autonomy::NavdataConstPtr& nav_msg_in);
    void cam_info(const sensor_msgs::CameraInfo& cam_parameters);
    void angle(const sensor_msgs::ImuConstPtr& ardrone_imu);
    void colorDetectionCallback(const sensor_msgs::ImageConstPtr& original_image);
    void erosion( int, void*, Mat src );
    void dilation( int, void* );
    

private:
    //ROS PUBLISHERS
    ros::Publisher platform_position_pub_;

    // ROS SUBSCRIBERS
    ros::Subscriber navdata_subs_;
    ros::Subscriber imu_subs_;
    ros::Subscriber cam_info_subs_;

    // IMAGE SUBSCRIBER AND PUBLISHER
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;

    double fx;
    double fy;
    double cx;
    double cy;
    double T;
    
    double altitude;
    
    geometry_msgs::Twist vel;
    
    double angle_x;
    double angular_velocity_x;
    
    double angle_y;
    double angular_velocity_y;
    
    double linear_acceleration_x;
    double linear_acceleration_y;

    float target_size;

    float altura_platform;

    int min_num_sides;
    int max_num_sides;

    int iterations;

    //VARIABLES FOR DRAWING THE LANDING_PLATFORM SHAPE
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<cv::Point> approx;


    //VARIABLE FOR STORING THE RECEIVED IMAGE
    Mat image;
    Mat img_mask, img_hsv, img_dilated, img_median; 
    Mat erosion_dst, dilation_dst;


    //VARIABLES FOR THE IMAGE FILTER
    
    // int H_min = 0;
    // int H_max = 179;
    // int S_min = 0;
    // int S_max = 196;
    // int V_min = 0;
    // int V_max = 170;

    int H_min;
    int H_max;
    int S_min;
    int S_max;
    int V_min;
    int V_max;

    int erosion_elem;
    int erosion_size;
    int dilation_elem;
    int dilation_size;
   

    //STATISTIC VARIABLES
    // int images_read = 0;
    // int times_detected = 0;
    // int false_positives = 0;
    // int obj_detected = 0;
     
}; //end of class platform_Detection
