#ifndef _ROS_katana_msgs_testmessage1_h
#define _ROS_katana_msgs_testmessage1_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace katana_msgs
{

  class testmessage1 : public ros::Msg
  {
    public:
      int16_t num;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_num;
      u_num.real = this->num;
      *(outbuffer + offset + 0) = (u_num.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_num.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->num);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_num;
      u_num.base = 0;
      u_num.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_num.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->num = u_num.real;
      offset += sizeof(this->num);
     return offset;
    }

    const char * getType(){ return "katana_msgs/testmessage1"; };
    const char * getMD5(){ return "79e2a05b252e69632375170571b25d3d"; };

  };

}
#endif