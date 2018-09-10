#ifndef _ROS_katana_gripping_msgs_GripObject_h
#define _ROS_katana_gripping_msgs_GripObject_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace katana_gripping_msgs
{

  class GripObject : public ros::Msg
  {
    public:
      const char* name;
      bool feedback;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      memcpy(outbuffer + offset, &length_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      union {
        bool real;
        uint8_t base;
      } u_feedback;
      u_feedback.real = this->feedback;
      *(outbuffer + offset + 0) = (u_feedback.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->feedback);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      memcpy(&length_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      union {
        bool real;
        uint8_t base;
      } u_feedback;
      u_feedback.base = 0;
      u_feedback.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->feedback = u_feedback.real;
      offset += sizeof(this->feedback);
     return offset;
    }

    const char * getType(){ return "katana_gripping_msgs/GripObject"; };
    const char * getMD5(){ return "b1c4a046999d2f8a857263aefbc0f116"; };

  };

}
#endif