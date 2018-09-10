#ifndef _ROS_katana_msgs_EmergencyStopM_h
#define _ROS_katana_msgs_EmergencyStopM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace katana_msgs
{

  class EmergencyStopM : public ros::Msg
  {
    public:
      int8_t m_state;
      enum { PUSHED = 0 };
      enum { RELEASED = 1 };

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_m_state;
      u_m_state.real = this->m_state;
      *(outbuffer + offset + 0) = (u_m_state.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_m_state;
      u_m_state.base = 0;
      u_m_state.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_state = u_m_state.real;
      offset += sizeof(this->m_state);
     return offset;
    }

    const char * getType(){ return "katana_msgs/EmergencyStopM"; };
    const char * getMD5(){ return "f9ffb93bff08f918d881be805490e3bd"; };

  };

}
#endif