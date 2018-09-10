#ifndef _ROS_katana_gripping_msgs_GrippingState_h
#define _ROS_katana_gripping_msgs_GrippingState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace katana_gripping_msgs
{

  class GrippingState : public ros::Msg
  {
    public:
      const char* objectName;
      bool carryingObject;
      const char* currentState;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_objectName = strlen(this->objectName);
      memcpy(outbuffer + offset, &length_objectName, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->objectName, length_objectName);
      offset += length_objectName;
      union {
        bool real;
        uint8_t base;
      } u_carryingObject;
      u_carryingObject.real = this->carryingObject;
      *(outbuffer + offset + 0) = (u_carryingObject.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->carryingObject);
      uint32_t length_currentState = strlen(this->currentState);
      memcpy(outbuffer + offset, &length_currentState, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->currentState, length_currentState);
      offset += length_currentState;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_objectName;
      memcpy(&length_objectName, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_objectName; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_objectName-1]=0;
      this->objectName = (char *)(inbuffer + offset-1);
      offset += length_objectName;
      union {
        bool real;
        uint8_t base;
      } u_carryingObject;
      u_carryingObject.base = 0;
      u_carryingObject.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->carryingObject = u_carryingObject.real;
      offset += sizeof(this->carryingObject);
      uint32_t length_currentState;
      memcpy(&length_currentState, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_currentState; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_currentState-1]=0;
      this->currentState = (char *)(inbuffer + offset-1);
      offset += length_currentState;
     return offset;
    }

    const char * getType(){ return "katana_gripping_msgs/GrippingState"; };
    const char * getMD5(){ return "ad6237611e0992d4921a4b217498fe8f"; };

  };

}
#endif