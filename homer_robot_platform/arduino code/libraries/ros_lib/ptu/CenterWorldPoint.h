#ifndef _ROS_ptu_CenterWorldPoint_h
#define _ROS_ptu_CenterWorldPoint_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Vector3.h"

namespace ptu
{

  class CenterWorldPoint : public ros::Msg
  {
    public:
      geometry_msgs::Vector3 point;
      bool permanent;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->point.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_permanent;
      u_permanent.real = this->permanent;
      *(outbuffer + offset + 0) = (u_permanent.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->permanent);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->point.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_permanent;
      u_permanent.base = 0;
      u_permanent.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->permanent = u_permanent.real;
      offset += sizeof(this->permanent);
     return offset;
    }

    const char * getType(){ return "ptu/CenterWorldPoint"; };
    const char * getMD5(){ return "e1fa339fee670c931df39a6cf3349616"; };

  };

}
#endif