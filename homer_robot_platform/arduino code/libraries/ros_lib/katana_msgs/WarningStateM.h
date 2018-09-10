#ifndef _ROS_katana_msgs_WarningStateM_h
#define _ROS_katana_msgs_WarningStateM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace katana_msgs
{

  class WarningStateM : public ros::Msg
  {
    public:
      const char* m_Id;
      bool m_Warn;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_m_Id = strlen(this->m_Id);
      memcpy(outbuffer + offset, &length_m_Id, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->m_Id, length_m_Id);
      offset += length_m_Id;
      union {
        bool real;
        uint8_t base;
      } u_m_Warn;
      u_m_Warn.real = this->m_Warn;
      *(outbuffer + offset + 0) = (u_m_Warn.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_Warn);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_m_Id;
      memcpy(&length_m_Id, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_m_Id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_m_Id-1]=0;
      this->m_Id = (char *)(inbuffer + offset-1);
      offset += length_m_Id;
      union {
        bool real;
        uint8_t base;
      } u_m_Warn;
      u_m_Warn.base = 0;
      u_m_Warn.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_Warn = u_m_Warn.real;
      offset += sizeof(this->m_Warn);
     return offset;
    }

    const char * getType(){ return "katana_msgs/WarningStateM"; };
    const char * getMD5(){ return "b928563373488b482a8b7042d3c19323"; };

  };

}
#endif