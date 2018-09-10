#ifndef _ROS_ptu_SetPanTilt_h
#define _ROS_ptu_SetPanTilt_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ptu
{

  class SetPanTilt : public ros::Msg
  {
    public:
      float panAngle;
      float tiltAngle;
      bool absolute;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_panAngle;
      u_panAngle.real = this->panAngle;
      *(outbuffer + offset + 0) = (u_panAngle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_panAngle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_panAngle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_panAngle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->panAngle);
      union {
        float real;
        uint32_t base;
      } u_tiltAngle;
      u_tiltAngle.real = this->tiltAngle;
      *(outbuffer + offset + 0) = (u_tiltAngle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_tiltAngle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_tiltAngle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_tiltAngle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->tiltAngle);
      union {
        bool real;
        uint8_t base;
      } u_absolute;
      u_absolute.real = this->absolute;
      *(outbuffer + offset + 0) = (u_absolute.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->absolute);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_panAngle;
      u_panAngle.base = 0;
      u_panAngle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_panAngle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_panAngle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_panAngle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->panAngle = u_panAngle.real;
      offset += sizeof(this->panAngle);
      union {
        float real;
        uint32_t base;
      } u_tiltAngle;
      u_tiltAngle.base = 0;
      u_tiltAngle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_tiltAngle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_tiltAngle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_tiltAngle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->tiltAngle = u_tiltAngle.real;
      offset += sizeof(this->tiltAngle);
      union {
        bool real;
        uint8_t base;
      } u_absolute;
      u_absolute.base = 0;
      u_absolute.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->absolute = u_absolute.real;
      offset += sizeof(this->absolute);
     return offset;
    }

    const char * getType(){ return "ptu/SetPanTilt"; };
    const char * getMD5(){ return "199ecba96acb74f8ac00e91a176d6778"; };

  };

}
#endif