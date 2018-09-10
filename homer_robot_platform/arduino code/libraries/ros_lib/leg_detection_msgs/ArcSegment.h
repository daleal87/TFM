#ifndef _ROS_leg_detection_msgs_ArcSegment_h
#define _ROS_leg_detection_msgs_ArcSegment_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Pose2D.h"

namespace leg_detection_msgs
{

  class ArcSegment : public ros::Msg
  {
    public:
      std_msgs::Header header;
      geometry_msgs::Pose2D arcCenter;
      uint8_t segmentPoints_length;
      geometry_msgs::Pose2D st_segmentPoints;
      geometry_msgs::Pose2D * segmentPoints;
      float arcRadius;
      float standardDeviation;
      float meanAngle;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->arcCenter.serialize(outbuffer + offset);
      *(outbuffer + offset++) = segmentPoints_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < segmentPoints_length; i++){
      offset += this->segmentPoints[i].serialize(outbuffer + offset);
      }
      union {
        float real;
        uint32_t base;
      } u_arcRadius;
      u_arcRadius.real = this->arcRadius;
      *(outbuffer + offset + 0) = (u_arcRadius.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_arcRadius.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_arcRadius.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_arcRadius.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->arcRadius);
      union {
        float real;
        uint32_t base;
      } u_standardDeviation;
      u_standardDeviation.real = this->standardDeviation;
      *(outbuffer + offset + 0) = (u_standardDeviation.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_standardDeviation.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_standardDeviation.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_standardDeviation.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->standardDeviation);
      union {
        float real;
        uint32_t base;
      } u_meanAngle;
      u_meanAngle.real = this->meanAngle;
      *(outbuffer + offset + 0) = (u_meanAngle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_meanAngle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_meanAngle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_meanAngle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->meanAngle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->arcCenter.deserialize(inbuffer + offset);
      uint8_t segmentPoints_lengthT = *(inbuffer + offset++);
      if(segmentPoints_lengthT > segmentPoints_length)
        this->segmentPoints = (geometry_msgs::Pose2D*)realloc(this->segmentPoints, segmentPoints_lengthT * sizeof(geometry_msgs::Pose2D));
      offset += 3;
      segmentPoints_length = segmentPoints_lengthT;
      for( uint8_t i = 0; i < segmentPoints_length; i++){
      offset += this->st_segmentPoints.deserialize(inbuffer + offset);
        memcpy( &(this->segmentPoints[i]), &(this->st_segmentPoints), sizeof(geometry_msgs::Pose2D));
      }
      union {
        float real;
        uint32_t base;
      } u_arcRadius;
      u_arcRadius.base = 0;
      u_arcRadius.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_arcRadius.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_arcRadius.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_arcRadius.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->arcRadius = u_arcRadius.real;
      offset += sizeof(this->arcRadius);
      union {
        float real;
        uint32_t base;
      } u_standardDeviation;
      u_standardDeviation.base = 0;
      u_standardDeviation.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_standardDeviation.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_standardDeviation.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_standardDeviation.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->standardDeviation = u_standardDeviation.real;
      offset += sizeof(this->standardDeviation);
      union {
        float real;
        uint32_t base;
      } u_meanAngle;
      u_meanAngle.base = 0;
      u_meanAngle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_meanAngle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_meanAngle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_meanAngle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->meanAngle = u_meanAngle.real;
      offset += sizeof(this->meanAngle);
     return offset;
    }

    const char * getType(){ return "leg_detection_msgs/ArcSegment"; };
    const char * getMD5(){ return "22715e86a75009944875439fccf06466"; };

  };

}
#endif