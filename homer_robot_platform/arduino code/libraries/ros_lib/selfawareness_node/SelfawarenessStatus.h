#ifndef _ROS_selfawareness_node_SelfawarenessStatus_h
#define _ROS_selfawareness_node_SelfawarenessStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace selfawareness_node
{

  class SelfawarenessStatus : public ros::Msg
  {
    public:
      bool hasObject;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_hasObject;
      u_hasObject.real = this->hasObject;
      *(outbuffer + offset + 0) = (u_hasObject.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->hasObject);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_hasObject;
      u_hasObject.base = 0;
      u_hasObject.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->hasObject = u_hasObject.real;
      offset += sizeof(this->hasObject);
     return offset;
    }

    const char * getType(){ return "selfawareness_node/SelfawarenessStatus"; };
    const char * getMD5(){ return "9a629b82e0145c6d8f9a1c728dd4faa2"; };

  };

}
#endif