#ifndef _ROS_SERVICE_SetTaskSpeedMiddle_h
#define _ROS_SERVICE_SetTaskSpeedMiddle_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace robot_platform
{

static const char SETTASKSPEEDMIDDLE[] = "robot_platform/SetTaskSpeedMiddle";

  class SetTaskSpeedMiddleRequest : public ros::Msg
  {
    public:
      uint8_t speed;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->speed >> (8 * 0)) & 0xFF;
      offset += sizeof(this->speed);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->speed =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->speed);
     return offset;
    }

    const char * getType(){ return SETTASKSPEEDMIDDLE; };
    const char * getMD5(){ return "a29fd828fef714caa1fd63db675216db"; };

  };

  class SetTaskSpeedMiddleResponse : public ros::Msg
  {
    public:

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return SETTASKSPEEDMIDDLE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SetTaskSpeedMiddle {
    public:
    typedef SetTaskSpeedMiddleRequest Request;
    typedef SetTaskSpeedMiddleResponse Response;
  };

}
#endif
