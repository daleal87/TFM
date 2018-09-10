#ifndef _ROS_simple_person_detection_DetectedPerson_h
#define _ROS_simple_person_detection_DetectedPerson_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"
#include "geometry_msgs/Point.h"

namespace simple_person_detection
{

  class DetectedPerson : public ros::Msg
  {
    public:
      ros::Time pcl_time;
      uint8_t poses_length;
      geometry_msgs::Point st_poses;
      geometry_msgs::Point * poses;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->pcl_time.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pcl_time.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->pcl_time.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->pcl_time.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pcl_time.sec);
      *(outbuffer + offset + 0) = (this->pcl_time.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pcl_time.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->pcl_time.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->pcl_time.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pcl_time.nsec);
      *(outbuffer + offset++) = poses_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < poses_length; i++){
      offset += this->poses[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->pcl_time.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->pcl_time.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->pcl_time.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->pcl_time.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->pcl_time.sec);
      this->pcl_time.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->pcl_time.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->pcl_time.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->pcl_time.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->pcl_time.nsec);
      uint8_t poses_lengthT = *(inbuffer + offset++);
      if(poses_lengthT > poses_length)
        this->poses = (geometry_msgs::Point*)realloc(this->poses, poses_lengthT * sizeof(geometry_msgs::Point));
      offset += 3;
      poses_length = poses_lengthT;
      for( uint8_t i = 0; i < poses_length; i++){
      offset += this->st_poses.deserialize(inbuffer + offset);
        memcpy( &(this->poses[i]), &(this->st_poses), sizeof(geometry_msgs::Point));
      }
     return offset;
    }

    const char * getType(){ return "simple_person_detection/DetectedPerson"; };
    const char * getMD5(){ return "2a4f14d4c48d17ed9861189553d58d1e"; };

  };

}
#endif