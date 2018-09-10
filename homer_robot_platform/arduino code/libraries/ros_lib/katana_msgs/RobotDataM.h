#ifndef _ROS_katana_msgs_RobotDataM_h
#define _ROS_katana_msgs_RobotDataM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace katana_msgs
{

  class RobotDataM : public ros::Msg
  {
    public:
      float m_BatteryVoltage;
      float m_Speed;
      float m_RotationalSpeed;
      bool m_Turning;
      bool m_Moving;
      bool m_Connected;
      float m_XCoord;
      float m_YCoord;
      float m_Heading;
      bool m_Stalled;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      int32_t * val_m_BatteryVoltage = (int32_t *) &(this->m_BatteryVoltage);
      int32_t exp_m_BatteryVoltage = (((*val_m_BatteryVoltage)>>23)&255);
      if(exp_m_BatteryVoltage != 0)
        exp_m_BatteryVoltage += 1023-127;
      int32_t sig_m_BatteryVoltage = *val_m_BatteryVoltage;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_BatteryVoltage<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_BatteryVoltage>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_BatteryVoltage>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_BatteryVoltage<<4) & 0xF0) | ((sig_m_BatteryVoltage>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_BatteryVoltage>>4) & 0x7F;
      if(this->m_BatteryVoltage < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_m_Speed = (int32_t *) &(this->m_Speed);
      int32_t exp_m_Speed = (((*val_m_Speed)>>23)&255);
      if(exp_m_Speed != 0)
        exp_m_Speed += 1023-127;
      int32_t sig_m_Speed = *val_m_Speed;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_Speed<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_Speed>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_Speed>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_Speed<<4) & 0xF0) | ((sig_m_Speed>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_Speed>>4) & 0x7F;
      if(this->m_Speed < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_m_RotationalSpeed = (int32_t *) &(this->m_RotationalSpeed);
      int32_t exp_m_RotationalSpeed = (((*val_m_RotationalSpeed)>>23)&255);
      if(exp_m_RotationalSpeed != 0)
        exp_m_RotationalSpeed += 1023-127;
      int32_t sig_m_RotationalSpeed = *val_m_RotationalSpeed;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_RotationalSpeed<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_RotationalSpeed>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_RotationalSpeed>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_RotationalSpeed<<4) & 0xF0) | ((sig_m_RotationalSpeed>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_RotationalSpeed>>4) & 0x7F;
      if(this->m_RotationalSpeed < 0) *(outbuffer + offset -1) |= 0x80;
      union {
        bool real;
        uint8_t base;
      } u_m_Turning;
      u_m_Turning.real = this->m_Turning;
      *(outbuffer + offset + 0) = (u_m_Turning.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_Turning);
      union {
        bool real;
        uint8_t base;
      } u_m_Moving;
      u_m_Moving.real = this->m_Moving;
      *(outbuffer + offset + 0) = (u_m_Moving.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_Moving);
      union {
        bool real;
        uint8_t base;
      } u_m_Connected;
      u_m_Connected.real = this->m_Connected;
      *(outbuffer + offset + 0) = (u_m_Connected.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_Connected);
      int32_t * val_m_XCoord = (int32_t *) &(this->m_XCoord);
      int32_t exp_m_XCoord = (((*val_m_XCoord)>>23)&255);
      if(exp_m_XCoord != 0)
        exp_m_XCoord += 1023-127;
      int32_t sig_m_XCoord = *val_m_XCoord;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_XCoord<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_XCoord>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_XCoord>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_XCoord<<4) & 0xF0) | ((sig_m_XCoord>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_XCoord>>4) & 0x7F;
      if(this->m_XCoord < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_m_YCoord = (int32_t *) &(this->m_YCoord);
      int32_t exp_m_YCoord = (((*val_m_YCoord)>>23)&255);
      if(exp_m_YCoord != 0)
        exp_m_YCoord += 1023-127;
      int32_t sig_m_YCoord = *val_m_YCoord;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_YCoord<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_YCoord>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_YCoord>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_YCoord<<4) & 0xF0) | ((sig_m_YCoord>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_YCoord>>4) & 0x7F;
      if(this->m_YCoord < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_m_Heading = (int32_t *) &(this->m_Heading);
      int32_t exp_m_Heading = (((*val_m_Heading)>>23)&255);
      if(exp_m_Heading != 0)
        exp_m_Heading += 1023-127;
      int32_t sig_m_Heading = *val_m_Heading;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_Heading<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_Heading>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_Heading>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_Heading<<4) & 0xF0) | ((sig_m_Heading>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_Heading>>4) & 0x7F;
      if(this->m_Heading < 0) *(outbuffer + offset -1) |= 0x80;
      union {
        bool real;
        uint8_t base;
      } u_m_Stalled;
      u_m_Stalled.real = this->m_Stalled;
      *(outbuffer + offset + 0) = (u_m_Stalled.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->m_Stalled);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t * val_m_BatteryVoltage = (uint32_t*) &(this->m_BatteryVoltage);
      offset += 3;
      *val_m_BatteryVoltage = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_m_BatteryVoltage |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_m_BatteryVoltage |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_m_BatteryVoltage |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_m_BatteryVoltage = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_m_BatteryVoltage |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_m_BatteryVoltage !=0)
        *val_m_BatteryVoltage |= ((exp_m_BatteryVoltage)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->m_BatteryVoltage = -this->m_BatteryVoltage;
      uint32_t * val_m_Speed = (uint32_t*) &(this->m_Speed);
      offset += 3;
      *val_m_Speed = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_m_Speed |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_m_Speed |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_m_Speed |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_m_Speed = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_m_Speed |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_m_Speed !=0)
        *val_m_Speed |= ((exp_m_Speed)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->m_Speed = -this->m_Speed;
      uint32_t * val_m_RotationalSpeed = (uint32_t*) &(this->m_RotationalSpeed);
      offset += 3;
      *val_m_RotationalSpeed = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_m_RotationalSpeed |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_m_RotationalSpeed |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_m_RotationalSpeed |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_m_RotationalSpeed = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_m_RotationalSpeed |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_m_RotationalSpeed !=0)
        *val_m_RotationalSpeed |= ((exp_m_RotationalSpeed)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->m_RotationalSpeed = -this->m_RotationalSpeed;
      union {
        bool real;
        uint8_t base;
      } u_m_Turning;
      u_m_Turning.base = 0;
      u_m_Turning.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_Turning = u_m_Turning.real;
      offset += sizeof(this->m_Turning);
      union {
        bool real;
        uint8_t base;
      } u_m_Moving;
      u_m_Moving.base = 0;
      u_m_Moving.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_Moving = u_m_Moving.real;
      offset += sizeof(this->m_Moving);
      union {
        bool real;
        uint8_t base;
      } u_m_Connected;
      u_m_Connected.base = 0;
      u_m_Connected.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_Connected = u_m_Connected.real;
      offset += sizeof(this->m_Connected);
      uint32_t * val_m_XCoord = (uint32_t*) &(this->m_XCoord);
      offset += 3;
      *val_m_XCoord = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_m_XCoord |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_m_XCoord |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_m_XCoord |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_m_XCoord = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_m_XCoord |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_m_XCoord !=0)
        *val_m_XCoord |= ((exp_m_XCoord)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->m_XCoord = -this->m_XCoord;
      uint32_t * val_m_YCoord = (uint32_t*) &(this->m_YCoord);
      offset += 3;
      *val_m_YCoord = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_m_YCoord |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_m_YCoord |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_m_YCoord |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_m_YCoord = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_m_YCoord |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_m_YCoord !=0)
        *val_m_YCoord |= ((exp_m_YCoord)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->m_YCoord = -this->m_YCoord;
      uint32_t * val_m_Heading = (uint32_t*) &(this->m_Heading);
      offset += 3;
      *val_m_Heading = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_m_Heading |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_m_Heading |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_m_Heading |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_m_Heading = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_m_Heading |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_m_Heading !=0)
        *val_m_Heading |= ((exp_m_Heading)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->m_Heading = -this->m_Heading;
      union {
        bool real;
        uint8_t base;
      } u_m_Stalled;
      u_m_Stalled.base = 0;
      u_m_Stalled.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->m_Stalled = u_m_Stalled.real;
      offset += sizeof(this->m_Stalled);
     return offset;
    }

    const char * getType(){ return "katana_msgs/RobotDataM"; };
    const char * getMD5(){ return "86796f46489a67a9c3421252a1ffbb60"; };

  };

}
#endif