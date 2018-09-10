#ifndef _ROS_robot_platform_StopRobot_h
#define _ROS_robot_platform_StopRobot_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace robot_platform
{

  class StopRobot : public ros::Msg
  {
    public:
      bool m_EmergencyStop;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_m_EmergencyStop;
      u_m_EmergencyStop.real = this->m_EmergencyStop;
      *(outbuffer + offset + 0) = (u_m_EmergencyStop.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_EmergencyStop);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_m_EmergencyStop;
      u_m_EmergencyStop.base = 0;
      u_m_EmergencyStop.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_EmergencyStop = u_m_EmergencyStop.real;
      offset += sizeof(this->m_EmergencyStop);
     return offset;
    }

    const char * getType(){ return "robot_platform/StopRobot"; };
    const char * getMD5(){ return "b5a9a22af23798117066172383e3b1e9"; };

  };

}
#endif