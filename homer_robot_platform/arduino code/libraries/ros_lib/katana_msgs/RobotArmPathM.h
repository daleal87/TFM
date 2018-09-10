#ifndef _ROS_katana_msgs_RobotArmPathM_h
#define _ROS_katana_msgs_RobotArmPathM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Vector3.h"
#include "katana_msgs/PathNodeM.h"

namespace katana_msgs
{

  class RobotArmPathM : public ros::Msg
  {
    public:
      uint8_t m_StartConfig_length;
      float st_m_StartConfig;
      float * m_StartConfig;
      uint8_t m_EndConfig_length;
      float st_m_EndConfig;
      float * m_EndConfig;
      geometry_msgs::Vector3 m_StartPoint;
      geometry_msgs::Vector3 m_EndPoint;
      int32_t m_NumAxes;
      uint8_t m_Path_length;
      katana_msgs::PathNodeM st_m_Path;
      katana_msgs::PathNodeM * m_Path;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = m_StartConfig_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < m_StartConfig_length; i++){
      int32_t * val_m_StartConfigi = (int32_t *) &(this->m_StartConfig[i]);
      int32_t exp_m_StartConfigi = (((*val_m_StartConfigi)>>23)&255);
      if(exp_m_StartConfigi != 0)
        exp_m_StartConfigi += 1023-127;
      int32_t sig_m_StartConfigi = *val_m_StartConfigi;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_StartConfigi<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_StartConfigi>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_StartConfigi>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_StartConfigi<<4) & 0xF0) | ((sig_m_StartConfigi>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_StartConfigi>>4) & 0x7F;
      if(this->m_StartConfig[i] < 0) *(outbuffer + offset -1) |= 0x80;
      }
      *(outbuffer + offset++) = m_EndConfig_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < m_EndConfig_length; i++){
      int32_t * val_m_EndConfigi = (int32_t *) &(this->m_EndConfig[i]);
      int32_t exp_m_EndConfigi = (((*val_m_EndConfigi)>>23)&255);
      if(exp_m_EndConfigi != 0)
        exp_m_EndConfigi += 1023-127;
      int32_t sig_m_EndConfigi = *val_m_EndConfigi;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_EndConfigi<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_EndConfigi>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_EndConfigi>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_EndConfigi<<4) & 0xF0) | ((sig_m_EndConfigi>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_EndConfigi>>4) & 0x7F;
      if(this->m_EndConfig[i] < 0) *(outbuffer + offset -1) |= 0x80;
      }
      offset += this->m_StartPoint.serialize(outbuffer + offset);
      offset += this->m_EndPoint.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_m_NumAxes;
      u_m_NumAxes.real = this->m_NumAxes;
      *(outbuffer + offset + 0) = (u_m_NumAxes.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_m_NumAxes.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_m_NumAxes.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_m_NumAxes.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->m_NumAxes);
      *(outbuffer + offset++) = m_Path_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < m_Path_length; i++){
      offset += this->m_Path[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t m_StartConfig_lengthT = *(inbuffer + offset++);
      if(m_StartConfig_lengthT > m_StartConfig_length)
        this->m_StartConfig = (float*)realloc(this->m_StartConfig, m_StartConfig_lengthT * sizeof(float));
      offset += 3;
      m_StartConfig_length = m_StartConfig_lengthT;
      for( uint8_t i = 0; i < m_StartConfig_length; i++){
      uint32_t * val_st_m_StartConfig = (uint32_t*) &(this->st_m_StartConfig);
      offset += 3;
      *val_st_m_StartConfig = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_st_m_StartConfig |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_st_m_StartConfig |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_st_m_StartConfig |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_st_m_StartConfig = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_st_m_StartConfig |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_st_m_StartConfig !=0)
        *val_st_m_StartConfig |= ((exp_st_m_StartConfig)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->st_m_StartConfig = -this->st_m_StartConfig;
        memcpy( &(this->m_StartConfig[i]), &(this->st_m_StartConfig), sizeof(float));
      }
      uint8_t m_EndConfig_lengthT = *(inbuffer + offset++);
      if(m_EndConfig_lengthT > m_EndConfig_length)
        this->m_EndConfig = (float*)realloc(this->m_EndConfig, m_EndConfig_lengthT * sizeof(float));
      offset += 3;
      m_EndConfig_length = m_EndConfig_lengthT;
      for( uint8_t i = 0; i < m_EndConfig_length; i++){
      uint32_t * val_st_m_EndConfig = (uint32_t*) &(this->st_m_EndConfig);
      offset += 3;
      *val_st_m_EndConfig = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_st_m_EndConfig |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_st_m_EndConfig |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_st_m_EndConfig |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_st_m_EndConfig = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_st_m_EndConfig |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_st_m_EndConfig !=0)
        *val_st_m_EndConfig |= ((exp_st_m_EndConfig)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->st_m_EndConfig = -this->st_m_EndConfig;
        memcpy( &(this->m_EndConfig[i]), &(this->st_m_EndConfig), sizeof(float));
      }
      offset += this->m_StartPoint.deserialize(inbuffer + offset);
      offset += this->m_EndPoint.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_m_NumAxes;
      u_m_NumAxes.base = 0;
      u_m_NumAxes.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_m_NumAxes.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_m_NumAxes.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_m_NumAxes.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->m_NumAxes = u_m_NumAxes.real;
      offset += sizeof(this->m_NumAxes);
      uint8_t m_Path_lengthT = *(inbuffer + offset++);
      if(m_Path_lengthT > m_Path_length)
        this->m_Path = (katana_msgs::PathNodeM*)realloc(this->m_Path, m_Path_lengthT * sizeof(katana_msgs::PathNodeM));
      offset += 3;
      m_Path_length = m_Path_lengthT;
      for( uint8_t i = 0; i < m_Path_length; i++){
      offset += this->st_m_Path.deserialize(inbuffer + offset);
        memcpy( &(this->m_Path[i]), &(this->st_m_Path), sizeof(katana_msgs::PathNodeM));
      }
     return offset;
    }

    const char * getType(){ return "katana_msgs/RobotArmPathM"; };
    const char * getMD5(){ return "4705d28908f0e01c060bab974061c7b7"; };

  };

}
#endif