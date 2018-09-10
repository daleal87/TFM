#ifndef _ROS_katana_msgs_RobotArmMoveM_h
#define _ROS_katana_msgs_RobotArmMoveM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace katana_msgs
{

  class RobotArmMoveM : public ros::Msg
  {
    public:
      uint8_t m_Axes_length;
      float st_m_Axes;
      float * m_Axes;
      bool m_ChangePowerState;
      bool m_NewPowerState;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = m_Axes_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < m_Axes_length; i++){
      int32_t * val_m_Axesi = (int32_t *) &(this->m_Axes[i]);
      int32_t exp_m_Axesi = (((*val_m_Axesi)>>23)&255);
      if(exp_m_Axesi != 0)
        exp_m_Axesi += 1023-127;
      int32_t sig_m_Axesi = *val_m_Axesi;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_Axesi<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_Axesi>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_Axesi>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_Axesi<<4) & 0xF0) | ((sig_m_Axesi>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_Axesi>>4) & 0x7F;
      if(this->m_Axes[i] < 0) *(outbuffer + offset -1) |= 0x80;
      }
      union {
        bool real;
        uint8_t base;
      } u_m_ChangePowerState;
      u_m_ChangePowerState.real = this->m_ChangePowerState;
      *(outbuffer + offset + 0) = (u_m_ChangePowerState.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_ChangePowerState);
      union {
        bool real;
        uint8_t base;
      } u_m_NewPowerState;
      u_m_NewPowerState.real = this->m_NewPowerState;
      *(outbuffer + offset + 0) = (u_m_NewPowerState.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_NewPowerState);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t m_Axes_lengthT = *(inbuffer + offset++);
      if(m_Axes_lengthT > m_Axes_length)
        this->m_Axes = (float*)realloc(this->m_Axes, m_Axes_lengthT * sizeof(float));
      offset += 3;
      m_Axes_length = m_Axes_lengthT;
      for( uint8_t i = 0; i < m_Axes_length; i++){
      uint32_t * val_st_m_Axes = (uint32_t*) &(this->st_m_Axes);
      offset += 3;
      *val_st_m_Axes = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_st_m_Axes |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_st_m_Axes |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_st_m_Axes |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_st_m_Axes = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_st_m_Axes |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_st_m_Axes !=0)
        *val_st_m_Axes |= ((exp_st_m_Axes)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->st_m_Axes = -this->st_m_Axes;
        memcpy( &(this->m_Axes[i]), &(this->st_m_Axes), sizeof(float));
      }
      union {
        bool real;
        uint8_t base;
      } u_m_ChangePowerState;
      u_m_ChangePowerState.base = 0;
      u_m_ChangePowerState.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_ChangePowerState = u_m_ChangePowerState.real;
      offset += sizeof(this->m_ChangePowerState);
      union {
        bool real;
        uint8_t base;
      } u_m_NewPowerState;
      u_m_NewPowerState.base = 0;
      u_m_NewPowerState.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_NewPowerState = u_m_NewPowerState.real;
      offset += sizeof(this->m_NewPowerState);
     return offset;
    }

    const char * getType(){ return "katana_msgs/RobotArmMoveM"; };
    const char * getMD5(){ return "4d1bf017d0847a8249ee79eab0292295"; };

  };

}
#endif