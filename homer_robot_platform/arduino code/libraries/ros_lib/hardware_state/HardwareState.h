#ifndef _ROS_hardware_state_HardwareState_h
#define _ROS_hardware_state_HardwareState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace hardware_state
{

  class HardwareState : public ros::Msg
  {
    public:
      const char* deviceName;
      bool isOk;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_deviceName = strlen(this->deviceName);
      memcpy(outbuffer + offset, &length_deviceName, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->deviceName, length_deviceName);
      offset += length_deviceName;
      union {
        bool real;
        uint8_t base;
      } u_isOk;
      u_isOk.real = this->isOk;
      *(outbuffer + offset + 0) = (u_isOk.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->isOk);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_deviceName;
      memcpy(&length_deviceName, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_deviceName; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_deviceName-1]=0;
      this->deviceName = (char *)(inbuffer + offset-1);
      offset += length_deviceName;
      union {
        bool real;
        uint8_t base;
      } u_isOk;
      u_isOk.base = 0;
      u_isOk.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->isOk = u_isOk.real;
      offset += sizeof(this->isOk);
     return offset;
    }

    const char * getType(){ return "hardware_state/HardwareState"; };
    const char * getMD5(){ return "eec16308413c602cdbab1f8c74bb22f5"; };

  };

}
#endif