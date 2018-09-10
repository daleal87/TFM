#ifndef _ROS_katana_msgs_RobotArmMoveFinishedM_h
#define _ROS_katana_msgs_RobotArmMoveFinishedM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace katana_msgs
{

  class RobotArmMoveFinishedM : public ros::Msg
  {
    public:
      int32_t m_RequestId;
      bool m_Success;
      bool m_Timeout;
      bool m_Exception;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_m_RequestId;
      u_m_RequestId.real = this->m_RequestId;
      *(outbuffer + offset + 0) = (u_m_RequestId.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_m_RequestId.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_m_RequestId.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_m_RequestId.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->m_RequestId);
      union {
        bool real;
        uint8_t base;
      } u_m_Success;
      u_m_Success.real = this->m_Success;
      *(outbuffer + offset + 0) = (u_m_Success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_Success);
      union {
        bool real;
        uint8_t base;
      } u_m_Timeout;
      u_m_Timeout.real = this->m_Timeout;
      *(outbuffer + offset + 0) = (u_m_Timeout.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_Timeout);
      union {
        bool real;
        uint8_t base;
      } u_m_Exception;
      u_m_Exception.real = this->m_Exception;
      *(outbuffer + offset + 0) = (u_m_Exception.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_Exception);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_m_RequestId;
      u_m_RequestId.base = 0;
      u_m_RequestId.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_m_RequestId.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_m_RequestId.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_m_RequestId.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->m_RequestId = u_m_RequestId.real;
      offset += sizeof(this->m_RequestId);
      union {
        bool real;
        uint8_t base;
      } u_m_Success;
      u_m_Success.base = 0;
      u_m_Success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_Success = u_m_Success.real;
      offset += sizeof(this->m_Success);
      union {
        bool real;
        uint8_t base;
      } u_m_Timeout;
      u_m_Timeout.base = 0;
      u_m_Timeout.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_Timeout = u_m_Timeout.real;
      offset += sizeof(this->m_Timeout);
      union {
        bool real;
        uint8_t base;
      } u_m_Exception;
      u_m_Exception.base = 0;
      u_m_Exception.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_Exception = u_m_Exception.real;
      offset += sizeof(this->m_Exception);
     return offset;
    }

    const char * getType(){ return "katana_msgs/RobotArmMoveFinishedM"; };
    const char * getMD5(){ return "9c8415f7c262db7dc39bd13cab0cc602"; };

  };

}
#endif