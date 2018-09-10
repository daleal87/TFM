#ifndef _ROS_speech_rec_msgs_SpeechOutStatusM_h
#define _ROS_speech_rec_msgs_SpeechOutStatusM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace speech_rec_msgs
{

  class SpeechOutStatusM : public ros::Msg
  {
    public:
      int8_t status;
      enum { Finished = 0 };
      enum { Speaking = 1 };

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_status;
      u_status.real = this->status;
      *(outbuffer + offset + 0) = (u_status.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->status);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_status;
      u_status.base = 0;
      u_status.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->status = u_status.real;
      offset += sizeof(this->status);
     return offset;
    }

    const char * getType(){ return "speech_rec_msgs/SpeechOutStatusM"; };
    const char * getMD5(){ return "a22e119748819a06e2b1f7e0c6008751"; };

  };

}
#endif