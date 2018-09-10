#ifndef _ROS_robot_platform_RobotData_h
#define _ROS_robot_platform_RobotData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace robot_platform
{

  class RobotData : public ros::Msg
  {
    public:
      uint32_t timestamp;
      float batteryVoltage;
      float speed;
      float rotationalSpeed;
      float xCoord;
      float yCoord;
      float th;
      bool turning;
      bool moving;
      bool connected;
      bool stall;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->timestamp >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->timestamp >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->timestamp >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->timestamp >> (8 * 3)) & 0xFF;
      offset += sizeof(this->timestamp);
      int32_t * val_batteryVoltage = (int32_t *) &(this->batteryVoltage);
      int32_t exp_batteryVoltage = (((*val_batteryVoltage)>>23)&255);
      if(exp_batteryVoltage != 0)
        exp_batteryVoltage += 1023-127;
      int32_t sig_batteryVoltage = *val_batteryVoltage;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_batteryVoltage<<5) & 0xff;
      *(outbuffer + offset++) = (sig_batteryVoltage>>3) & 0xff;
      *(outbuffer + offset++) = (sig_batteryVoltage>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_batteryVoltage<<4) & 0xF0) | ((sig_batteryVoltage>>19)&0x0F);
      *(outbuffer + offset++) = (exp_batteryVoltage>>4) & 0x7F;
      if(this->batteryVoltage < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_speed = (int32_t *) &(this->speed);
      int32_t exp_speed = (((*val_speed)>>23)&255);
      if(exp_speed != 0)
        exp_speed += 1023-127;
      int32_t sig_speed = *val_speed;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_speed<<5) & 0xff;
      *(outbuffer + offset++) = (sig_speed>>3) & 0xff;
      *(outbuffer + offset++) = (sig_speed>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_speed<<4) & 0xF0) | ((sig_speed>>19)&0x0F);
      *(outbuffer + offset++) = (exp_speed>>4) & 0x7F;
      if(this->speed < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_rotationalSpeed = (int32_t *) &(this->rotationalSpeed);
      int32_t exp_rotationalSpeed = (((*val_rotationalSpeed)>>23)&255);
      if(exp_rotationalSpeed != 0)
        exp_rotationalSpeed += 1023-127;
      int32_t sig_rotationalSpeed = *val_rotationalSpeed;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_rotationalSpeed<<5) & 0xff;
      *(outbuffer + offset++) = (sig_rotationalSpeed>>3) & 0xff;
      *(outbuffer + offset++) = (sig_rotationalSpeed>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_rotationalSpeed<<4) & 0xF0) | ((sig_rotationalSpeed>>19)&0x0F);
      *(outbuffer + offset++) = (exp_rotationalSpeed>>4) & 0x7F;
      if(this->rotationalSpeed < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_xCoord = (int32_t *) &(this->xCoord);
      int32_t exp_xCoord = (((*val_xCoord)>>23)&255);
      if(exp_xCoord != 0)
        exp_xCoord += 1023-127;
      int32_t sig_xCoord = *val_xCoord;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_xCoord<<5) & 0xff;
      *(outbuffer + offset++) = (sig_xCoord>>3) & 0xff;
      *(outbuffer + offset++) = (sig_xCoord>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_xCoord<<4) & 0xF0) | ((sig_xCoord>>19)&0x0F);
      *(outbuffer + offset++) = (exp_xCoord>>4) & 0x7F;
      if(this->xCoord < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_yCoord = (int32_t *) &(this->yCoord);
      int32_t exp_yCoord = (((*val_yCoord)>>23)&255);
      if(exp_yCoord != 0)
        exp_yCoord += 1023-127;
      int32_t sig_yCoord = *val_yCoord;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_yCoord<<5) & 0xff;
      *(outbuffer + offset++) = (sig_yCoord>>3) & 0xff;
      *(outbuffer + offset++) = (sig_yCoord>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_yCoord<<4) & 0xF0) | ((sig_yCoord>>19)&0x0F);
      *(outbuffer + offset++) = (exp_yCoord>>4) & 0x7F;
      if(this->yCoord < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_th = (int32_t *) &(this->th);
      int32_t exp_th = (((*val_th)>>23)&255);
      if(exp_th != 0)
        exp_th += 1023-127;
      int32_t sig_th = *val_th;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_th<<5) & 0xff;
      *(outbuffer + offset++) = (sig_th>>3) & 0xff;
      *(outbuffer + offset++) = (sig_th>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_th<<4) & 0xF0) | ((sig_th>>19)&0x0F);
      *(outbuffer + offset++) = (exp_th>>4) & 0x7F;
      if(this->th < 0) *(outbuffer + offset -1) |= 0x80;
      union {
        bool real;
        uint8_t base;
      } u_turning;
      u_turning.real = this->turning;
      *(outbuffer + offset + 0) = (u_turning.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->turning);
      union {
        bool real;
        uint8_t base;
      } u_moving;
      u_moving.real = this->moving;
      *(outbuffer + offset + 0) = (u_moving.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->moving);
      union {
        bool real;
        uint8_t base;
      } u_connected;
      u_connected.real = this->connected;
      *(outbuffer + offset + 0) = (u_connected.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->connected);
      union {
        bool real;
        uint8_t base;
      } u_stall;
      u_stall.real = this->stall;
      *(outbuffer + offset + 0) = (u_stall.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->stall);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->timestamp =  ((uint32_t) (*(inbuffer + offset)));
      this->timestamp |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->timestamp |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->timestamp |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->timestamp);
      uint32_t * val_batteryVoltage = (uint32_t*) &(this->batteryVoltage);
      offset += 3;
      *val_batteryVoltage = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_batteryVoltage |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_batteryVoltage |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_batteryVoltage |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_batteryVoltage = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_batteryVoltage |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_batteryVoltage !=0)
        *val_batteryVoltage |= ((exp_batteryVoltage)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->batteryVoltage = -this->batteryVoltage;
      uint32_t * val_speed = (uint32_t*) &(this->speed);
      offset += 3;
      *val_speed = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_speed |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_speed |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_speed |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_speed = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_speed |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_speed !=0)
        *val_speed |= ((exp_speed)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->speed = -this->speed;
      uint32_t * val_rotationalSpeed = (uint32_t*) &(this->rotationalSpeed);
      offset += 3;
      *val_rotationalSpeed = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_rotationalSpeed |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_rotationalSpeed |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_rotationalSpeed |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_rotationalSpeed = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_rotationalSpeed |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_rotationalSpeed !=0)
        *val_rotationalSpeed |= ((exp_rotationalSpeed)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->rotationalSpeed = -this->rotationalSpeed;
      uint32_t * val_xCoord = (uint32_t*) &(this->xCoord);
      offset += 3;
      *val_xCoord = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_xCoord |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_xCoord |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_xCoord |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_xCoord = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_xCoord |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_xCoord !=0)
        *val_xCoord |= ((exp_xCoord)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->xCoord = -this->xCoord;
      uint32_t * val_yCoord = (uint32_t*) &(this->yCoord);
      offset += 3;
      *val_yCoord = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_yCoord |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_yCoord |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_yCoord |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_yCoord = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_yCoord |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_yCoord !=0)
        *val_yCoord |= ((exp_yCoord)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->yCoord = -this->yCoord;
      uint32_t * val_th = (uint32_t*) &(this->th);
      offset += 3;
      *val_th = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_th |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_th |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_th |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_th = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_th |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_th !=0)
        *val_th |= ((exp_th)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->th = -this->th;
      union {
        bool real;
        uint8_t base;
      } u_turning;
      u_turning.base = 0;
      u_turning.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->turning = u_turning.real;
      offset += sizeof(this->turning);
      union {
        bool real;
        uint8_t base;
      } u_moving;
      u_moving.base = 0;
      u_moving.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->moving = u_moving.real;
      offset += sizeof(this->moving);
      union {
        bool real;
        uint8_t base;
      } u_connected;
      u_connected.base = 0;
      u_connected.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->connected = u_connected.real;
      offset += sizeof(this->connected);
      union {
        bool real;
        uint8_t base;
      } u_stall;
      u_stall.base = 0;
      u_stall.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->stall = u_stall.real;
      offset += sizeof(this->stall);
     return offset;
    }

    const char * getType(){ return "robot_platform/RobotData"; };
    const char * getMD5(){ return "90f0d734100ff8faf3f934267878d2f0"; };

  };

}
#endif