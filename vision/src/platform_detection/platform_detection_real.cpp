#include <vision/platform_detection/platform_detection_real.hpp>

Platform_Detection::Platform_Detection() {
    ROS_INFO("Init Class: Platform_Detection");
    
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_(nh_);
    

    std::string platform_position_topic_;
    std::string image_topic_;
    std::string camera_info_topic_;
    std::string navdata_topic_;
    std::string imu_topic_;


    // GETTING ROS PARAMETERS
    nh_.param("platform_position_topic", platform_position_topic_, std::string("/platform/estimated_position"));    
    nh_.param("image_topic", image_topic_, std::string("/ardrone/bottom/image_raw"));
    nh_.param("navdata_topic", navdata_topic_, std::string("/ardrone/navdata"));
    nh_.param("imu_topic", imu_topic_, std::string("/ardrone/imu"));
    nh_.param("cam_info_topic", camera_info_topic_, std::string("/ardrone/bottom/camera_info"));

    nh_.param<int>("H_min", H_min, 0);
    nh_.param<int>("H_max", H_max, 179);
    nh_.param<int>("S_min", S_min, 0);
    nh_.param<int>("S_max", S_max, 156);
    nh_.param<int>("V_min", V_min, 0);
    nh_.param<int>("V_max", V_max, 164);

    nh_.param<float>("target_size", target_size, DEFAULT_SIZE);
    nh_.param<float>("altura_platform", altura_platform, 0.392);

    nh_.param<int>("min_num_sides", min_num_sides, 3);
    nh_.param<int>("max_num_sides", max_num_sides, 12);

    nh_.param<int>("iterations", iterations, 2);

    //////////////////////////////////// PUBLISHERS /////////////////////////////////////////////
    //We publish on the platform_POSITION_TOPIC 
    platform_position_pub_ = nh_.advertise<geometry_msgs::PoseStamped>(platform_position_topic_, 1);
   
    //////////////////////////////////// SUBSCRIBERS /////////////////////////////////////////////
    //Subscribe to input video feed and publish output video feed
    image_sub_ = it_.subscribe(image_topic_, 1, &Platform_Detection::colorDetectionCallback, this);
    image_pub_ = it_.advertise("/image_converter/output_video", 1);

    //We subscribe to the ALTITUDE_TOPIC of the quadrotor
    navdata_subs_ = nh_.subscribe(navdata_topic_, 1, &Platform_Detection::navdata, this);
    
    //We subscribe to the IMU_TOPIC of the quadrotor
    imu_subs_ = nh_.subscribe(imu_topic_, 1, &Platform_Detection::angle, this);

    //We subscribe to the CAMERA_INFO_TOPIC of the quadrotor
    cam_info_subs_ = nh_.subscribe(camera_info_topic_, 1, &Platform_Detection::cam_info, this);

   
    // --TRACKBARS-- //
    cv::namedWindow("BallPlatform");
    cv::createTrackbar("H_min","BallPlatform",&H_min,179,NULL);
    cv::createTrackbar("H_max","BallPlatform",&H_max,179,NULL);
    cv::createTrackbar("S_min","BallPlatform",&S_min,255,NULL);
    cv::createTrackbar("S_max","BallPlatform",&S_max,255,NULL);
    cv::createTrackbar("V_min","BallPlatform",&V_min,255,NULL);
    cv::createTrackbar("V_max","BallPlatform",&V_max,255,NULL);


    erosion_elem = 1;
    erosion_size = 4;
    dilation_elem = 2;
    dilation_size = 4;
    int const max_elem = 2;
    int const max_kernel_size = 21;
    
    /// Create windows
    namedWindow( "Erosion Dilation Demo", CV_WINDOW_AUTOSIZE );
    //cvMoveWindow( "Dilation Demo", img_mask.cols, 0 );

    /// Create Erosion Trackbar
    createTrackbar( "E Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Dilation Demo",
                  &erosion_elem, max_elem,
                  NULL );

    createTrackbar( "E Kernel size:\n 2n +1", "Erosion Dilation Demo",
                  &erosion_size, max_kernel_size,
                  NULL );

    /// Create Dilation Trackbar
    createTrackbar( "D Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Dilation Demo",
                  &dilation_elem, max_elem,
                  NULL );

    createTrackbar( "D Kernel size:\n 2n +1", "Erosion Dilation Demo",
                  &dilation_size, max_kernel_size,
                  NULL );

    
    ROS_INFO("Setup completed");
}
   
void Platform_Detection::navdata(const ardrone_autonomy::NavdataConstPtr& nav_msg_in) {
    altitude = (double)((nav_msg_in -> altd) / pow(10,3));
    ROS_INFO_STREAM(altitude);
}


void Platform_Detection::angle(const sensor_msgs::ImuConstPtr& ardrone_imu) {
    angle_x               = ardrone_imu->orientation.x;
    angular_velocity_x    = ardrone_imu->angular_velocity.x;
 
    angle_y               = ardrone_imu->orientation.y;
    angular_velocity_y    = ardrone_imu->angular_velocity.y;
 
    linear_acceleration_x = ardrone_imu->linear_acceleration.x;
    linear_acceleration_y = ardrone_imu->linear_acceleration.y;
}


void Platform_Detection::cam_info(const sensor_msgs::CameraInfo& cam_parameters) {
    //ROS_INFO("Parameters from the pinhole model");
    fx = cam_parameters.K.at(0);
    fy = cam_parameters.K.at(4);
    cx = cam_parameters.K.at(2);
    cy = cam_parameters.K.at(5);
    T  = cam_parameters.K.at(1);
    //ROS_INFO("Los parametros son  (fx,fy)=(%f , %f)", fx, fy);
}


void Platform_Detection::erosion( int, void*, Mat src ) {
    int erosion_type;
    if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
    else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
    else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

    Mat element = getStructuringElement( erosion_type,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) );

    /// Apply the erosion operation
    erode( src, erosion_dst, element );
}

void Platform_Detection::dilation( int, void* ) {
    int dilation_type;
    if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
    else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
    else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

    Mat element = getStructuringElement( dilation_type,
                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       Point( dilation_size, dilation_size ) );
    /// Apply the dilation operation
    dilate( erosion_dst, dilation_dst, element );
}


void Platform_Detection::colorDetectionCallback(const sensor_msgs::ImageConstPtr& original_image) {
    //Convert from the ROS image message to a CvImage suitable for working with OpenCV for processing
    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(original_image, enc::BGR8);
        image = cv_ptr->image;
        //images_read++;
    }
    catch (cv_bridge::Exception& e) {
        ROS_ERROR("Failed to convert image: %s", e.what());
        return;
    }

    //imshow("original",cv_ptr->image);

    cv::cvtColor( cv_ptr->image, img_hsv, CV_BGR2HSV );
    // vector<Mat> channels;

    // split(img_hsv, channels);
    
    // cv::namedWindow( "hsv", CV_WINDOW_AUTOSIZE );
    // cv::imshow( "hsv", img_hsv );
    
    cv::inRange( img_hsv, cv::Scalar(H_min, S_min, V_min), cv::Scalar(H_max, S_max, V_max), img_mask ); 
    
    // cv::namedWindow( "mask", CV_WINDOW_AUTOSIZE );
    // cv::imshow( "mask", img_mask );

    erosion(0,0, img_mask);
    //imshow("erosion", erosion_dst);
    dilation(0,0);
    //imshow("dilation", dilation_dst); 

    for (int i = 0; i < iterations; ++i) {
        erosion(0,0, dilation_dst);
        dilation(0,0);    
    }
    
    //imshow( "Erosion Dilation Demo", dilation_dst );

    img_dilated = dilation_dst;

    cv::medianBlur(img_dilated, img_median, 15);
    
    // cv::namedWindow( "median", CV_WINDOW_AUTOSIZE );
    // cv::imshow( "median", img_median );
   
   
    
    // --CENTROID-- //

    //Find countours on the image
    cv::findContours(img_median, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
    //ROS_INFO("Find contours");
    //this function modifies the image
    //ros::Rate loop_rate(0.1);
    //---------------------------------------------------------
    // cv::namedWindow( "contours", CV_WINDOW_AUTOSIZE );
    // cv::imshow( "contours", img_median );

    target_size = 0.25;
    for (int i = 0; i < contours.size(); i++) {
        
        cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)* 0.02, true);

        if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx)) 
        continue;

        
        if (    approx.size() >= min_num_sides                              && approx.size() <= max_num_sides
                && fabs(angle_x)                                     <= 0.5 && fabs(angular_velocity_x) <= 0.4 //angles limit 0.5
                && fabs(angular_velocity_y)                          <= 0.4 && fabs(angle_y) <= 0.5
                && fabs(linear_acceleration_x)                       <= 1   && fabs(linear_acceleration_y) <= 1
                && fabs(linear_acceleration_x*linear_acceleration_y) <= 0.7
                && fabs(angular_velocity_x)*fabs(angular_velocity_y) <= 0.25 //variation angular_velocity limit
                && cv::isContourConvex(cv::Mat(approx)))  {
        
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

            // Centroid extraction----------------------------------------------------------------
            /// 1º Get the moments
            cv::Moments m;
            m = cv::moments( approx, false );

            /// 2º Get the mass centers: (centroid)
            cv::Point2f mc;
            mc = cv::Point2f( m.m10/m.m00 , m.m01/m.m00 );
            cv::line(image, mc, mc, cv::Scalar(0,255,255), 8); // we draw a yellow point for that mc

            /// PINHOLE inverse transformation ==> (x,y,z)= f(u,v) without distortion, (u,v)=mc ---------------------
            ROS_INFO("Centroid location");
            geometry_msgs::PoseStamped centroid;
                centroid.header.stamp= ros::Time::now();
                centroid.header.seq = ros::Time::now().toSec();
                centroid.header.frame_id = "/ardrone_base_bottomcam";
                centroid.pose.orientation.w=1;
                centroid.pose.orientation.x=0;
                centroid.pose.orientation.y=0;
                centroid.pose.orientation.z=0;
                
                //Centroide corregido
                centroid.pose.position.x= - ((mc.x - cx)*altitude - (T*(mc.y - cy)*altitude)/fy)/fx;
                centroid.pose.position.y= - (((mc.y - cy)*altitude)/fy);            
                centroid.pose.position.z= altitude - altura_platform;    
            
            ROS_INFO("Centro de masas en pixels del objetivo: (%f , %f)", mc.x, mc.y);
            ROS_INFO("La posicion del objetivo es: (%f , %f, %f) en metros respecto a la camara", centroid.pose.position.x, centroid.pose.position.y, centroid.pose.position.z);

            platform_position_pub_.publish(centroid);
        }
    }
    

    


    /// Show in a window
    cv::namedWindow( "platform_DETECTED", CV_WINDOW_AUTOSIZE );
    cv::imshow( "platform_DETECTED", image );
    cv::waitKey(3);

    image_pub_.publish(cv_ptr->toImageMsg());                                      
}
   

int main(int argc, char** argv) {
    ros::init(argc, argv, "platform_detection_real");

    Platform_Detection platform_detection;
    ros::spin();
    ROS_INFO("platform_detection::main.cpp::No error.");
    cv::destroyWindow("platform_DETECTED");
    return 0;
}
