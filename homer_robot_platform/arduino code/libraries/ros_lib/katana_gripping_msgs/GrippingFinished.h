#ifndef _ROS_katana_gripping_msgs_GrippingFinished_h
#define _ROS_katana_gripping_msgs_GrippingFinished_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace katana_gripping_msgs
{

  class GrippingFinished : public ros::Msg
  {
    public:
      const char* object;
      bool error;
      const char* errorMessage;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_object = strlen(this->object);
      memcpy(outbuffer + offset, &length_object, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->object, length_object);
      offset += length_object;
      union {
        bool real;
        uint8_t base;
      } u_error;
      u_error.real = this->error;
      *(outbuffer + offset + 0) = (u_error.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->error);
      uint32_t length_errorMessage = strlen(this->errorMessage);
      memcpy(outbuffer + offset, &length_errorMessage, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->errorMessage, length_errorMessage);
      offset += length_errorMessage;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_object;
      memcpy(&length_object, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_object; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_object-1]=0;
      this->object = (char *)(inbuffer + offset-1);
      offset += length_object;
      union {
        bool real;
        uint8_t base;
      } u_error;
      u_error.base = 0;
      u_error.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->error = u_error.real;
      offset += sizeof(this->error);
      uint32_t length_errorMessage;
      memcpy(&length_errorMessage, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_errorMessage; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_errorMessage-1]=0;
      this->errorMessage = (char *)(inbuffer + offset-1);
      offset += length_errorMessage;
     return offset;
    }

    const char * getType(){ return "katana_gripping_msgs/GrippingFinished"; };
    const char * getMD5(){ return "78f596ee577bc7edcd8c9a0cd4e22050"; };

  };

}
#endif