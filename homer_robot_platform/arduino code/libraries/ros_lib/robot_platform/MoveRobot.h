#ifndef _ROS_robot_platform_MoveRobot_h
#define _ROS_robot_platform_MoveRobot_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace robot_platform
{

  class MoveRobot : public ros::Msg
  {
    public:
      float m_Distance;
      float m_Speed;
      float m_Permanent;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      int32_t * val_m_Distance = (int32_t *) &(this->m_Distance);
      int32_t exp_m_Distance = (((*val_m_Distance)>>23)&255);
      if(exp_m_Distance != 0)
        exp_m_Distance += 1023-127;
      int32_t sig_m_Distance = *val_m_Distance;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_Distance<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_Distance>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_Distance>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_Distance<<4) & 0xF0) | ((sig_m_Distance>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_Distance>>4) & 0x7F;
      if(this->m_Distance < 0) *(outbuffer + offset -1) |= 0x80;
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
      int32_t * val_m_Permanent = (int32_t *) &(this->m_Permanent);
      int32_t exp_m_Permanent = (((*val_m_Permanent)>>23)&255);
      if(exp_m_Permanent != 0)
        exp_m_Permanent += 1023-127;
      int32_t sig_m_Permanent = *val_m_Permanent;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_Permanent<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_Permanent>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_Permanent>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_Permanent<<4) & 0xF0) | ((sig_m_Permanent>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_Permanent>>4) & 0x7F;
      if(this->m_Permanent < 0) *(outbuffer + offset -1) |= 0x80;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t * val_m_Distance = (uint32_t*) &(this->m_Distance);
      offset += 3;
      *val_m_Distance = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_m_Distance |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_m_Distance |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_m_Distance |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_m_Distance = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_m_Distance |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_m_Distance !=0)
        *val_m_Distance |= ((exp_m_Distance)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->m_Distance = -this->m_Distance;
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
      uint32_t * val_m_Permanent = (uint32_t*) &(this->m_Permanent);
      offset += 3;
      *val_m_Permanent = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_m_Permanent |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_m_Permanent |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_m_Permanent |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_m_Permanent = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_m_Permanent |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_m_Permanent !=0)
        *val_m_Permanent |= ((exp_m_Permanent)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->m_Permanent = -this->m_Permanent;
     return offset;
    }

    const char * getType(){ return "robot_platform/MoveRobot"; };
    const char * getMD5(){ return "067fd21930ecaebc8c92a4e69e4e110c"; };

  };

}
#endif