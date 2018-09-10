#ifndef _ROS_katana_msgs_PathNodeM_h
#define _ROS_katana_msgs_PathNodeM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Vector3.h"

namespace katana_msgs
{

  class PathNodeM : public ros::Msg
  {
    public:
      int32_t m_Axis;
      float m_Change;
      geometry_msgs::Vector3 m_EffectorPoint;
      uint8_t m_Configuration_length;
      float st_m_Configuration;
      float * m_Configuration;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_m_Axis;
      u_m_Axis.real = this->m_Axis;
      *(outbuffer + offset + 0) = (u_m_Axis.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_m_Axis.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_m_Axis.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_m_Axis.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->m_Axis);
      int32_t * val_m_Change = (int32_t *) &(this->m_Change);
      int32_t exp_m_Change = (((*val_m_Change)>>23)&255);
      if(exp_m_Change != 0)
        exp_m_Change += 1023-127;
      int32_t sig_m_Change = *val_m_Change;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_Change<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_Change>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_Change>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_Change<<4) & 0xF0) | ((sig_m_Change>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_Change>>4) & 0x7F;
      if(this->m_Change < 0) *(outbuffer + offset -1) |= 0x80;
      offset += this->m_EffectorPoint.serialize(outbuffer + offset);
      *(outbuffer + offset++) = m_Configuration_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < m_Configuration_length; i++){
      int32_t * val_m_Configurationi = (int32_t *) &(this->m_Configuration[i]);
      int32_t exp_m_Configurationi = (((*val_m_Configurationi)>>23)&255);
      if(exp_m_Configurationi != 0)
        exp_m_Configurationi += 1023-127;
      int32_t sig_m_Configurationi = *val_m_Configurationi;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_Configurationi<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_Configurationi>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_Configurationi>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_Configurationi<<4) & 0xF0) | ((sig_m_Configurationi>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_Configurationi>>4) & 0x7F;
      if(this->m_Configuration[i] < 0) *(outbuffer + offset -1) |= 0x80;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_m_Axis;
      u_m_Axis.base = 0;
      u_m_Axis.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_m_Axis.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_m_Axis.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_m_Axis.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->m_Axis = u_m_Axis.real;
      offset += sizeof(this->m_Axis);
      uint32_t * val_m_Change = (uint32_t*) &(this->m_Change);
      offset += 3;
      *val_m_Change = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_m_Change |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_m_Change |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_m_Change |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_m_Change = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_m_Change |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_m_Change !=0)
        *val_m_Change |= ((exp_m_Change)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->m_Change = -this->m_Change;
      offset += this->m_EffectorPoint.deserialize(inbuffer + offset);
      uint8_t m_Configuration_lengthT = *(inbuffer + offset++);
      if(m_Configuration_lengthT > m_Configuration_length)
        this->m_Configuration = (float*)realloc(this->m_Configuration, m_Configuration_lengthT * sizeof(float));
      offset += 3;
      m_Configuration_length = m_Configuration_lengthT;
      for( uint8_t i = 0; i < m_Configuration_length; i++){
      uint32_t * val_st_m_Configuration = (uint32_t*) &(this->st_m_Configuration);
      offset += 3;
      *val_st_m_Configuration = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_st_m_Configuration |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_st_m_Configuration |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_st_m_Configuration |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_st_m_Configuration = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_st_m_Configuration |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_st_m_Configuration !=0)
        *val_st_m_Configuration |= ((exp_st_m_Configuration)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->st_m_Configuration = -this->st_m_Configuration;
        memcpy( &(this->m_Configuration[i]), &(this->st_m_Configuration), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "katana_msgs/PathNodeM"; };
    const char * getMD5(){ return "124ab07be4a5f741b2aef6c77d224ee8"; };

  };

}
#endif