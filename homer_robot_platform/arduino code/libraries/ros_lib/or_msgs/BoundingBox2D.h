#ifndef _ROS_or_msgs_BoundingBox2D_h
#define _ROS_or_msgs_BoundingBox2D_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace or_msgs
{

  class BoundingBox2D : public ros::Msg
  {
    public:
      float minX;
      float minY;
      float maxX;
      float maxY;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_minX;
      u_minX.real = this->minX;
      *(outbuffer + offset + 0) = (u_minX.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_minX.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_minX.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_minX.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->minX);
      union {
        float real;
        uint32_t base;
      } u_minY;
      u_minY.real = this->minY;
      *(outbuffer + offset + 0) = (u_minY.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_minY.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_minY.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_minY.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->minY);
      union {
        float real;
        uint32_t base;
      } u_maxX;
      u_maxX.real = this->maxX;
      *(outbuffer + offset + 0) = (u_maxX.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_maxX.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_maxX.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_maxX.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->maxX);
      union {
        float real;
        uint32_t base;
      } u_maxY;
      u_maxY.real = this->maxY;
      *(outbuffer + offset + 0) = (u_maxY.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_maxY.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_maxY.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_maxY.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->maxY);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_minX;
      u_minX.base = 0;
      u_minX.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_minX.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_minX.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_minX.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->minX = u_minX.real;
      offset += sizeof(this->minX);
      union {
        float real;
        uint32_t base;
      } u_minY;
      u_minY.base = 0;
      u_minY.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_minY.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_minY.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_minY.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->minY = u_minY.real;
      offset += sizeof(this->minY);
      union {
        float real;
        uint32_t base;
      } u_maxX;
      u_maxX.base = 0;
      u_maxX.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_maxX.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_maxX.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_maxX.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->maxX = u_maxX.real;
      offset += sizeof(this->maxX);
      union {
        float real;
        uint32_t base;
      } u_maxY;
      u_maxY.base = 0;
      u_maxY.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_maxY.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_maxY.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_maxY.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->maxY = u_maxY.real;
      offset += sizeof(this->maxY);
     return offset;
    }

    const char * getType(){ return "or_msgs/BoundingBox2D"; };
    const char * getMD5(){ return "e5c096841db08a95192d2e9b57b16743"; };

  };

}
#endif