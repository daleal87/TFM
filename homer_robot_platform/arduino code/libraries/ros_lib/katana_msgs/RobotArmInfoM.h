#ifndef _ROS_katana_msgs_RobotArmInfoM_h
#define _ROS_katana_msgs_RobotArmInfoM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace katana_msgs
{

  class RobotArmInfoM : public ros::Msg
  {
    public:
      int32_t m_NumAxes;
      uint8_t m_AxesMin_length;
      float st_m_AxesMin;
      float * m_AxesMin;
      uint8_t m_AxesMax_length;
      float st_m_AxesMax;
      float * m_AxesMax;
      const char* m_Id;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
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
      *(outbuffer + offset++) = m_AxesMin_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < m_AxesMin_length; i++){
      int32_t * val_m_AxesMini = (int32_t *) &(this->m_AxesMin[i]);
      int32_t exp_m_AxesMini = (((*val_m_AxesMini)>>23)&255);
      if(exp_m_AxesMini != 0)
        exp_m_AxesMini += 1023-127;
      int32_t sig_m_AxesMini = *val_m_AxesMini;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_AxesMini<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_AxesMini>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_AxesMini>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_AxesMini<<4) & 0xF0) | ((sig_m_AxesMini>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_AxesMini>>4) & 0x7F;
      if(this->m_AxesMin[i] < 0) *(outbuffer + offset -1) |= 0x80;
      }
      *(outbuffer + offset++) = m_AxesMax_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < m_AxesMax_length; i++){
      int32_t * val_m_AxesMaxi = (int32_t *) &(this->m_AxesMax[i]);
      int32_t exp_m_AxesMaxi = (((*val_m_AxesMaxi)>>23)&255);
      if(exp_m_AxesMaxi != 0)
        exp_m_AxesMaxi += 1023-127;
      int32_t sig_m_AxesMaxi = *val_m_AxesMaxi;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_m_AxesMaxi<<5) & 0xff;
      *(outbuffer + offset++) = (sig_m_AxesMaxi>>3) & 0xff;
      *(outbuffer + offset++) = (sig_m_AxesMaxi>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_m_AxesMaxi<<4) & 0xF0) | ((sig_m_AxesMaxi>>19)&0x0F);
      *(outbuffer + offset++) = (exp_m_AxesMaxi>>4) & 0x7F;
      if(this->m_AxesMax[i] < 0) *(outbuffer + offset -1) |= 0x80;
      }
      uint32_t length_m_Id = strlen(this->m_Id);
      memcpy(outbuffer + offset, &length_m_Id, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->m_Id, length_m_Id);
      offset += length_m_Id;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
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
      uint8_t m_AxesMin_lengthT = *(inbuffer + offset++);
      if(m_AxesMin_lengthT > m_AxesMin_length)
        this->m_AxesMin = (float*)realloc(this->m_AxesMin, m_AxesMin_lengthT * sizeof(float));
      offset += 3;
      m_AxesMin_length = m_AxesMin_lengthT;
      for( uint8_t i = 0; i < m_AxesMin_length; i++){
      uint32_t * val_st_m_AxesMin = (uint32_t*) &(this->st_m_AxesMin);
      offset += 3;
      *val_st_m_AxesMin = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_st_m_AxesMin |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_st_m_AxesMin |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_st_m_AxesMin |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_st_m_AxesMin = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_st_m_AxesMin |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_st_m_AxesMin !=0)
        *val_st_m_AxesMin |= ((exp_st_m_AxesMin)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->st_m_AxesMin = -this->st_m_AxesMin;
        memcpy( &(this->m_AxesMin[i]), &(this->st_m_AxesMin), sizeof(float));
      }
      uint8_t m_AxesMax_lengthT = *(inbuffer + offset++);
      if(m_AxesMax_lengthT > m_AxesMax_length)
        this->m_AxesMax = (float*)realloc(this->m_AxesMax, m_AxesMax_lengthT * sizeof(float));
      offset += 3;
      m_AxesMax_length = m_AxesMax_lengthT;
      for( uint8_t i = 0; i < m_AxesMax_length; i++){
      uint32_t * val_st_m_AxesMax = (uint32_t*) &(this->st_m_AxesMax);
      offset += 3;
      *val_st_m_AxesMax = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_st_m_AxesMax |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_st_m_AxesMax |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_st_m_AxesMax |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_st_m_AxesMax = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_st_m_AxesMax |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_st_m_AxesMax !=0)
        *val_st_m_AxesMax |= ((exp_st_m_AxesMax)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->st_m_AxesMax = -this->st_m_AxesMax;
        memcpy( &(this->m_AxesMax[i]), &(this->st_m_AxesMax), sizeof(float));
      }
      uint32_t length_m_Id;
      memcpy(&length_m_Id, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_m_Id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_m_Id-1]=0;
      this->m_Id = (char *)(inbuffer + offset-1);
      offset += length_m_Id;
     return offset;
    }

    const char * getType(){ return "katana_msgs/RobotArmInfoM"; };
    const char * getMD5(){ return "903ac544d3281d61fe8554530a5fdd84"; };

  };

}
#endif