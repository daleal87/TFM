#ifndef _ROS_katana_msgs_RobotArmMoveAxisM_h
#define _ROS_katana_msgs_RobotArmMoveAxisM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace katana_msgs
{

  class RobotArmMoveAxisM : public ros::Msg
  {
    public:
      uint8_t m_AxisPositions_keys_length;
      int32_t st_m_AxisPositions_keys;
      int32_t * m_AxisPositions_keys;
      uint8_t m_AxisPositions_values_length;
      float st_m_AxisPositions_values;
      float * m_AxisPositions_values;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = m_AxisPositions_keys_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < m_AxisPositions_keys_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_m_AxisPositions_keysi;
      u_m_AxisPositions_keysi.real = this->m_AxisPositions_keys[i];
      *(outbuffer + offset + 0) = (u_m_AxisPositions_keysi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_m_AxisPositions_keysi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_m_AxisPositions_keysi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_m_AxisPositions_keysi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->m_AxisPositions_keys[i]);
      }
      *(outbuffer + offset++) = m_AxisPositions_values_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < m_AxisPositions_values_length; i++){
      int32_t * val_m_AxisPositions_valuesi = (int32_t *) &(this->m_AxisPositions_values[i]);
      int32_t exp_m_AxisPositions_valuesi = (((*val_m_AxisPositions_valuesi)>>23)&255);
      if(exp_m_AxisPositions_valuesi != 0)
        exp_m_AxisPositions_valuesi += 1023-127;
      int32_t sig_m_AxisPositions_valuesi = *val_m_AxisPositions_valuesi;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_AxisPositions_valuesi<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_AxisPositions_valuesi>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_AxisPositions_valuesi>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_AxisPositions_valuesi<<4) & 0xF0) | ((sig_m_AxisPositions_valuesi>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_AxisPositions_valuesi>>4) & 0x7F;
      if(this->m_AxisPositions_values[i] < 0) *(outbuffer + offset -1) |= 0x80;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t m_AxisPositions_keys_lengthT = *(inbuffer + offset++);
      if(m_AxisPositions_keys_lengthT > m_AxisPositions_keys_length)
        this->m_AxisPositions_keys = (int32_t*)realloc(this->m_AxisPositions_keys, m_AxisPositions_keys_lengthT * sizeof(int32_t));
      offset += 3;
      m_AxisPositions_keys_length = m_AxisPositions_keys_lengthT;
      for( uint8_t i = 0; i < m_AxisPositions_keys_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_m_AxisPositions_keys;
      u_st_m_AxisPositions_keys.base = 0;
      u_st_m_AxisPositions_keys.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_m_AxisPositions_keys.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_m_AxisPositions_keys.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_m_AxisPositions_keys.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_m_AxisPositions_keys = u_st_m_AxisPositions_keys.real;
      offset += sizeof(this->st_m_AxisPositions_keys);
        memcpy( &(this->m_AxisPositions_keys[i]), &(this->st_m_AxisPositions_keys), sizeof(int32_t));
      }
      uint8_t m_AxisPositions_values_lengthT = *(inbuffer + offset++);
      if(m_AxisPositions_values_lengthT > m_AxisPositions_values_length)
        this->m_AxisPositions_values = (float*)realloc(this->m_AxisPositions_values, m_AxisPositions_values_lengthT * sizeof(float));
      offset += 3;
      m_AxisPositions_values_length = m_AxisPositions_values_lengthT;
      for( uint8_t i = 0; i < m_AxisPositions_values_length; i++){
      uint32_t * val_st_m_AxisPositions_values = (uint32_t*) &(this->st_m_AxisPositions_values);
      offset += 3;
      *val_st_m_AxisPositions_values = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_st_m_AxisPositions_values |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_st_m_AxisPositions_values |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_st_m_AxisPositions_values |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_st_m_AxisPositions_values = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_st_m_AxisPositions_values |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_st_m_AxisPositions_values !=0)
        *val_st_m_AxisPositions_values |= ((exp_st_m_AxisPositions_values)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->st_m_AxisPositions_values = -this->st_m_AxisPositions_values;
        memcpy( &(this->m_AxisPositions_values[i]), &(this->st_m_AxisPositions_values), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "katana_msgs/RobotArmMoveAxisM"; };
    const char * getMD5(){ return "c8f879a84a935018ce69a33718a6d3c5"; };

  };

}
#endif