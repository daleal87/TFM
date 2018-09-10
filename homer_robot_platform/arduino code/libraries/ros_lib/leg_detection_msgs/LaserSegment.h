#ifndef _ROS_leg_detection_msgs_LaserSegment_h
#define _ROS_leg_detection_msgs_LaserSegment_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Pose2D.h"

namespace leg_detection_msgs
{

  class LaserSegment : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t segmentPoints_length;
      geometry_msgs::Pose2D st_segmentPoints;
      geometry_msgs::Pose2D * segmentPoints;
      geometry_msgs::Pose2D m_Centroid;
      bool m_IsValid;
      bool m_LeftShadow;
      bool m_RightShadow;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = segmentPoints_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < segmentPoints_length; i++){
      offset += this->segmentPoints[i].serialize(outbuffer + offset);
      }
      offset += this->m_Centroid.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_m_IsValid;
      u_m_IsValid.real = this->m_IsValid;
      *(outbuffer + offset + 0) = (u_m_IsValid.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_IsValid);
      union {
        bool real;
        uint8_t base;
      } u_m_LeftShadow;
      u_m_LeftShadow.real = this->m_LeftShadow;
      *(outbuffer + offset + 0) = (u_m_LeftShadow.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_LeftShadow);
      union {
        bool real;
        uint8_t base;
      } u_m_RightShadow;
      u_m_RightShadow.real = this->m_RightShadow;
      *(outbuffer + offset + 0) = (u_m_RightShadow.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_RightShadow);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t segmentPoints_lengthT = *(inbuffer + offset++);
      if(segmentPoints_lengthT > segmentPoints_length)
        this->segmentPoints = (geometry_msgs::Pose2D*)realloc(this->segmentPoints, segmentPoints_lengthT * sizeof(geometry_msgs::Pose2D));
      offset += 3;
      segmentPoints_length = segmentPoints_lengthT;
      for( uint8_t i = 0; i < segmentPoints_length; i++){
      offset += this->st_segmentPoints.deserialize(inbuffer + offset);
        memcpy( &(this->segmentPoints[i]), &(this->st_segmentPoints), sizeof(geometry_msgs::Pose2D));
      }
      offset += this->m_Centroid.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_m_IsValid;
      u_m_IsValid.base = 0;
      u_m_IsValid.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_IsValid = u_m_IsValid.real;
      offset += sizeof(this->m_IsValid);
      union {
        bool real;
        uint8_t base;
      } u_m_LeftShadow;
      u_m_LeftShadow.base = 0;
      u_m_LeftShadow.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_LeftShadow = u_m_LeftShadow.real;
      offset += sizeof(this->m_LeftShadow);
      union {
        bool real;
        uint8_t base;
      } u_m_RightShadow;
      u_m_RightShadow.base = 0;
      u_m_RightShadow.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_RightShadow = u_m_RightShadow.real;
      offset += sizeof(this->m_RightShadow);
     return offset;
    }

    const char * getType(){ return "leg_detection_msgs/LaserSegment"; };
    const char * getMD5(){ return "3ea788ea34c3695ec97cf559f35fb5d9"; };

  };

}
#endif