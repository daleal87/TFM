#ifndef _ROS_robot_platform_RobotState_h
#define _ROS_robot_platform_RobotState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace robot_platform
{

  class RobotState : public ros::Msg
  {
    public:
      float targetSpeedLeft;
      float targetSpeedRight;
      float currentSpeedLeft;
      float currentSpeedRight;
      float encoderLeft;
      float encoderRight;
      float wheelDiff;
      float distancePerTick;
      bool encoderForCalc;
      bool emergencyPressed;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      int32_t * val_targetSpeedLeft = (int32_t *) &(this->targetSpeedLeft);
      int32_t exp_targetSpeedLeft = (((*val_targetSpeedLeft)>>23)&255);
      if(exp_targetSpeedLeft != 0)
        exp_targetSpeedLeft += 1023-127;
      int32_t sig_targetSpeedLeft = *val_targetSpeedLeft;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_targetSpeedLeft<<5) & 0xff;
      *(outbuffer + offset++) = (sig_targetSpeedLeft>>3) & 0xff;
      *(outbuffer + offset++) = (sig_targetSpeedLeft>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_targetSpeedLeft<<4) & 0xF0) | ((sig_targetSpeedLeft>>19)&0x0F);
      *(outbuffer + offset++) = (exp_targetSpeedLeft>>4) & 0x7F;
      if(this->targetSpeedLeft < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_targetSpeedRight = (int32_t *) &(this->targetSpeedRight);
      int32_t exp_targetSpeedRight = (((*val_targetSpeedRight)>>23)&255);
      if(exp_targetSpeedRight != 0)
        exp_targetSpeedRight += 1023-127;
      int32_t sig_targetSpeedRight = *val_targetSpeedRight;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_targetSpeedRight<<5) & 0xff;
      *(outbuffer + offset++) = (sig_targetSpeedRight>>3) & 0xff;
      *(outbuffer + offset++) = (sig_targetSpeedRight>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_targetSpeedRight<<4) & 0xF0) | ((sig_targetSpeedRight>>19)&0x0F);
      *(outbuffer + offset++) = (exp_targetSpeedRight>>4) & 0x7F;
      if(this->targetSpeedRight < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_currentSpeedLeft = (int32_t *) &(this->currentSpeedLeft);
      int32_t exp_currentSpeedLeft = (((*val_currentSpeedLeft)>>23)&255);
      if(exp_currentSpeedLeft != 0)
        exp_currentSpeedLeft += 1023-127;
      int32_t sig_currentSpeedLeft = *val_currentSpeedLeft;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_currentSpeedLeft<<5) & 0xff;
      *(outbuffer + offset++) = (sig_currentSpeedLeft>>3) & 0xff;
      *(outbuffer + offset++) = (sig_currentSpeedLeft>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_currentSpeedLeft<<4) & 0xF0) | ((sig_currentSpeedLeft>>19)&0x0F);
      *(outbuffer + offset++) = (exp_currentSpeedLeft>>4) & 0x7F;
      if(this->currentSpeedLeft < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_currentSpeedRight = (int32_t *) &(this->currentSpeedRight);
      int32_t exp_currentSpeedRight = (((*val_currentSpeedRight)>>23)&255);
      if(exp_currentSpeedRight != 0)
        exp_currentSpeedRight += 1023-127;
      int32_t sig_currentSpeedRight = *val_currentSpeedRight;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_currentSpeedRight<<5) & 0xff;
      *(outbuffer + offset++) = (sig_currentSpeedRight>>3) & 0xff;
      *(outbuffer + offset++) = (sig_currentSpeedRight>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_currentSpeedRight<<4) & 0xF0) | ((sig_currentSpeedRight>>19)&0x0F);
      *(outbuffer + offset++) = (exp_currentSpeedRight>>4) & 0x7F;
      if(this->currentSpeedRight < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_encoderLeft = (int32_t *) &(this->encoderLeft);
      int32_t exp_encoderLeft = (((*val_encoderLeft)>>23)&255);
      if(exp_encoderLeft != 0)
        exp_encoderLeft += 1023-127;
      int32_t sig_encoderLeft = *val_encoderLeft;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_encoderLeft<<5) & 0xff;
      *(outbuffer + offset++) = (sig_encoderLeft>>3) & 0xff;
      *(outbuffer + offset++) = (sig_encoderLeft>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_encoderLeft<<4) & 0xF0) | ((sig_encoderLeft>>19)&0x0F);
      *(outbuffer + offset++) = (exp_encoderLeft>>4) & 0x7F;
      if(this->encoderLeft < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_encoderRight = (int32_t *) &(this->encoderRight);
      int32_t exp_encoderRight = (((*val_encoderRight)>>23)&255);
      if(exp_encoderRight != 0)
        exp_encoderRight += 1023-127;
      int32_t sig_encoderRight = *val_encoderRight;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_encoderRight<<5) & 0xff;
      *(outbuffer + offset++) = (sig_encoderRight>>3) & 0xff;
      *(outbuffer + offset++) = (sig_encoderRight>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_encoderRight<<4) & 0xF0) | ((sig_encoderRight>>19)&0x0F);
      *(outbuffer + offset++) = (exp_encoderRight>>4) & 0x7F;
      if(this->encoderRight < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_wheelDiff = (int32_t *) &(this->wheelDiff);
      int32_t exp_wheelDiff = (((*val_wheelDiff)>>23)&255);
      if(exp_wheelDiff != 0)
        exp_wheelDiff += 1023-127;
      int32_t sig_wheelDiff = *val_wheelDiff;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_wheelDiff<<5) & 0xff;
      *(outbuffer + offset++) = (sig_wheelDiff>>3) & 0xff;
      *(outbuffer + offset++) = (sig_wheelDiff>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_wheelDiff<<4) & 0xF0) | ((sig_wheelDiff>>19)&0x0F);
      *(outbuffer + offset++) = (exp_wheelDiff>>4) & 0x7F;
      if(this->wheelDiff < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_distancePerTick = (int32_t *) &(this->distancePerTick);
      int32_t exp_distancePerTick = (((*val_distancePerTick)>>23)&255);
      if(exp_distancePerTick != 0)
        exp_distancePerTick += 1023-127;
      int32_t sig_distancePerTick = *val_distancePerTick;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_distancePerTick<<5) & 0xff;
      *(outbuffer + offset++) = (sig_distancePerTick>>3) & 0xff;
      *(outbuffer + offset++) = (sig_distancePerTick>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_distancePerTick<<4) & 0xF0) | ((sig_distancePerTick>>19)&0x0F);
      *(outbuffer + offset++) = (exp_distancePerTick>>4) & 0x7F;
      if(this->distancePerTick < 0) *(outbuffer + offset -1) |= 0x80;
      union {
        bool real;
        uint8_t base;
      } u_encoderForCalc;
      u_encoderForCalc.real = this->encoderForCalc;
      *(outbuffer + offset + 0) = (u_encoderForCalc.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->encoderForCalc);
      union {
        bool real;
        uint8_t base;
      } u_emergencyPressed;
      u_emergencyPressed.real = this->emergencyPressed;
      *(outbuffer + offset + 0) = (u_emergencyPressed.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->emergencyPressed);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t * val_targetSpeedLeft = (uint32_t*) &(this->targetSpeedLeft);
      offset += 3;
      *val_targetSpeedLeft = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_targetSpeedLeft |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_targetSpeedLeft |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_targetSpeedLeft |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_targetSpeedLeft = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_targetSpeedLeft |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_targetSpeedLeft !=0)
        *val_targetSpeedLeft |= ((exp_targetSpeedLeft)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->targetSpeedLeft = -this->targetSpeedLeft;
      uint32_t * val_targetSpeedRight = (uint32_t*) &(this->targetSpeedRight);
      offset += 3;
      *val_targetSpeedRight = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_targetSpeedRight |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_targetSpeedRight |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_targetSpeedRight |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_targetSpeedRight = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_targetSpeedRight |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_targetSpeedRight !=0)
        *val_targetSpeedRight |= ((exp_targetSpeedRight)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->targetSpeedRight = -this->targetSpeedRight;
      uint32_t * val_currentSpeedLeft = (uint32_t*) &(this->currentSpeedLeft);
      offset += 3;
      *val_currentSpeedLeft = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_currentSpeedLeft |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_currentSpeedLeft |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_currentSpeedLeft |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_currentSpeedLeft = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_currentSpeedLeft |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_currentSpeedLeft !=0)
        *val_currentSpeedLeft |= ((exp_currentSpeedLeft)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->currentSpeedLeft = -this->currentSpeedLeft;
      uint32_t * val_currentSpeedRight = (uint32_t*) &(this->currentSpeedRight);
      offset += 3;
      *val_currentSpeedRight = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_currentSpeedRight |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_currentSpeedRight |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_currentSpeedRight |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_currentSpeedRight = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_currentSpeedRight |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_currentSpeedRight !=0)
        *val_currentSpeedRight |= ((exp_currentSpeedRight)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->currentSpeedRight = -this->currentSpeedRight;
      uint32_t * val_encoderLeft = (uint32_t*) &(this->encoderLeft);
      offset += 3;
      *val_encoderLeft = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_encoderLeft |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_encoderLeft |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_encoderLeft |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_encoderLeft = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_encoderLeft |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_encoderLeft !=0)
        *val_encoderLeft |= ((exp_encoderLeft)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->encoderLeft = -this->encoderLeft;
      uint32_t * val_encoderRight = (uint32_t*) &(this->encoderRight);
      offset += 3;
      *val_encoderRight = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_encoderRight |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_encoderRight |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_encoderRight |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_encoderRight = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_encoderRight |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_encoderRight !=0)
        *val_encoderRight |= ((exp_encoderRight)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->encoderRight = -this->encoderRight;
      uint32_t * val_wheelDiff = (uint32_t*) &(this->wheelDiff);
      offset += 3;
      *val_wheelDiff = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_wheelDiff |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_wheelDiff |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_wheelDiff |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_wheelDiff = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_wheelDiff |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_wheelDiff !=0)
        *val_wheelDiff |= ((exp_wheelDiff)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->wheelDiff = -this->wheelDiff;
      uint32_t * val_distancePerTick = (uint32_t*) &(this->distancePerTick);
      offset += 3;
      *val_distancePerTick = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_distancePerTick |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_distancePerTick |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_distancePerTick |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_distancePerTick = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_distancePerTick |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_distancePerTick !=0)
        *val_distancePerTick |= ((exp_distancePerTick)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->distancePerTick = -this->distancePerTick;
      union {
        bool real;
        uint8_t base;
      } u_encoderForCalc;
      u_encoderForCalc.base = 0;
      u_encoderForCalc.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->encoderForCalc = u_encoderForCalc.real;
      offset += sizeof(this->encoderForCalc);
      union {
        bool real;
        uint8_t base;
      } u_emergencyPressed;
      u_emergencyPressed.base = 0;
      u_emergencyPressed.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->emergencyPressed = u_emergencyPressed.real;
      offset += sizeof(this->emergencyPressed);
     return offset;
    }

    const char * getType(){ return "robot_platform/RobotState"; };
    const char * getMD5(){ return "ab647de6f3a3b2fe02cbebce54dca8e4"; };

  };

}
#endif