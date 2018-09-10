#ifndef _ROS_katana_msgs_RobotArmLinearMoveM_h
#define _ROS_katana_msgs_RobotArmLinearMoveM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace katana_msgs
{

  class RobotArmLinearMoveM : public ros::Msg
  {
    public:
      uint8_t m_Target_length;
      float st_m_Target;
      float * m_Target;
      float m_Speed;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = m_Target_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < m_Target_length; i++){
      int32_t * val_m_Targeti = (int32_t *) &(this->m_Target[i]);
      int32_t exp_m_Targeti = (((*val_m_Targeti)>>23)&255);
      if(exp_m_Targeti != 0)
        exp_m_Targeti += 1023-127;
      int32_t sig_m_Targeti = *val_m_Targeti;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_Targeti<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_Targeti>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_Targeti>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_Targeti<<4) & 0xF0) | ((sig_m_Targeti>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_Targeti>>4) & 0x7F;
      if(this->m_Target[i] < 0) *(outbuffer + offset -1) |= 0x80;
      }
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
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t m_Target_lengthT = *(inbuffer + offset++);
      if(m_Target_lengthT > m_Target_length)
        this->m_Target = (float*)realloc(this->m_Target, m_Target_lengthT * sizeof(float));
      offset += 3;
      m_Target_length = m_Target_lengthT;
      for( uint8_t i = 0; i < m_Target_length; i++){
      uint32_t * val_st_m_Target = (uint32_t*) &(this->st_m_Target);
      offset += 3;
      *val_st_m_Target = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_st_m_Target |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_st_m_Target |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_st_m_Target |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_st_m_Target = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_st_m_Target |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_st_m_Target !=0)
        *val_st_m_Target |= ((exp_st_m_Target)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->st_m_Target = -this->st_m_Target;
        memcpy( &(this->m_Target[i]), &(this->st_m_Target), sizeof(float));
      }
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
     return offset;
    }

    const char * getType(){ return "katana_msgs/RobotArmLinearMoveM"; };
    const char * getMD5(){ return "18cdb0c0b2a8421f5fbb1f62b739efcc"; };

  };

}
#endif