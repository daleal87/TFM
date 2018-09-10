#ifndef _ROS_SERVICE_SendMessage_h
#define _ROS_SERVICE_SendMessage_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace robot_platform
{

static const char SENDMESSAGE[] = "robot_platform/SendMessage";

  class SendMessageRequest : public ros::Msg
  {
    public:
      uint8_t byte1;
      uint8_t byte2;
      uint8_t byte3;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->byte1 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->byte1);
      *(outbuffer + offset + 0) = (this->byte2 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->byte2);
      *(outbuffer + offset + 0) = (this->byte3 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->byte3);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->byte1 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->byte1);
      this->byte2 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->byte2);
      this->byte3 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->byte3);
     return offset;
    }

    const char * getType(){ return SENDMESSAGE; };
    const char * getMD5(){ return "8fbcc54f05abcd91222a2f3ba34fefe7"; };

  };

  class SendMessageResponse : public ros::Msg
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

    const char * getType(){ return SENDMESSAGE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SendMessage {
    public:
    typedef SendMessageRequest Request;
    typedef SendMessageResponse Response;
  };

}
#endif
