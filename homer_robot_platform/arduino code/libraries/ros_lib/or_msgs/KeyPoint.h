#ifndef _ROS_or_msgs_KeyPoint_h
#define _ROS_or_msgs_KeyPoint_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace or_msgs
{

  class KeyPoint : public ros::Msg
  {
    public:
      float x;
      float y;
      float scale;
      float strength;
      float orientation;
      int32_t sign;
      uint8_t feature_vector_length;
      float st_feature_vector;
      float * feature_vector;
      uint8_t vector_limits_length;
      uint32_t st_vector_limits;
      uint32_t * vector_limits;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_x;
      u_x.real = this->x;
      *(outbuffer + offset + 0) = (u_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x);
      union {
        float real;
        uint32_t base;
      } u_y;
      u_y.real = this->y;
      *(outbuffer + offset + 0) = (u_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y);
      union {
        float real;
        uint32_t base;
      } u_scale;
      u_scale.real = this->scale;
      *(outbuffer + offset + 0) = (u_scale.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_scale.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_scale.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_scale.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->scale);
      union {
        float real;
        uint32_t base;
      } u_strength;
      u_strength.real = this->strength;
      *(outbuffer + offset + 0) = (u_strength.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_strength.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_strength.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_strength.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->strength);
      union {
        float real;
        uint32_t base;
      } u_orientation;
      u_orientation.real = this->orientation;
      *(outbuffer + offset + 0) = (u_orientation.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_orientation.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_orientation.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_orientation.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->orientation);
      union {
        int32_t real;
        uint32_t base;
      } u_sign;
      u_sign.real = this->sign;
      *(outbuffer + offset + 0) = (u_sign.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sign.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sign.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sign.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sign);
      *(outbuffer + offset++) = feature_vector_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < feature_vector_length; i++){
      int32_t * val_feature_vectori = (int32_t *) &(this->feature_vector[i]);
      int32_t exp_feature_vectori = (((*val_feature_vectori)>>23)&255);
      if(exp_feature_vectori != 0)
        exp_feature_vectori += 1023-127;
      int32_t sig_feature_vectori = *val_feature_vectori;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_feature_vectori<<5) & 0xff;
      *(outbuffer + offset++) = (sig_feature_vectori>>3) & 0xff;
      *(outbuffer + offset++) = (sig_feature_vectori>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_feature_vectori<<4) & 0xF0) | ((sig_feature_vectori>>19)&0x0F);
      *(outbuffer + offset++) = (exp_feature_vectori>>4) & 0x7F;
      if(this->feature_vector[i] < 0) *(outbuffer + offset -1) |= 0x80;
      }
      *(outbuffer + offset++) = vector_limits_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < vector_limits_length; i++){
      *(outbuffer + offset + 0) = (this->vector_limits[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->vector_limits[i] >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->vector_limits[i] >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->vector_limits[i] >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vector_limits[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_x;
      u_x.base = 0;
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->x = u_x.real;
      offset += sizeof(this->x);
      union {
        float real;
        uint32_t base;
      } u_y;
      u_y.base = 0;
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->y = u_y.real;
      offset += sizeof(this->y);
      union {
        float real;
        uint32_t base;
      } u_scale;
      u_scale.base = 0;
      u_scale.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_scale.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_scale.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_scale.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->scale = u_scale.real;
      offset += sizeof(this->scale);
      union {
        float real;
        uint32_t base;
      } u_strength;
      u_strength.base = 0;
      u_strength.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_strength.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_strength.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_strength.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->strength = u_strength.real;
      offset += sizeof(this->strength);
      union {
        float real;
        uint32_t base;
      } u_orientation;
      u_orientation.base = 0;
      u_orientation.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_orientation.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_orientation.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_orientation.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->orientation = u_orientation.real;
      offset += sizeof(this->orientation);
      union {
        int32_t real;
        uint32_t base;
      } u_sign;
      u_sign.base = 0;
      u_sign.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sign.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_sign.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_sign.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->sign = u_sign.real;
      offset += sizeof(this->sign);
      uint8_t feature_vector_lengthT = *(inbuffer + offset++);
      if(feature_vector_lengthT > feature_vector_length)
        this->feature_vector = (float*)realloc(this->feature_vector, feature_vector_lengthT * sizeof(float));
      offset += 3;
      feature_vector_length = feature_vector_lengthT;
      for( uint8_t i = 0; i < feature_vector_length; i++){
      uint32_t * val_st_feature_vector = (uint32_t*) &(this->st_feature_vector);
      offset += 3;
      *val_st_feature_vector = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_st_feature_vector |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_st_feature_vector |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_st_feature_vector |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_st_feature_vector = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_st_feature_vector |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_st_feature_vector !=0)
        *val_st_feature_vector |= ((exp_st_feature_vector)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->st_feature_vector = -this->st_feature_vector;
        memcpy( &(this->feature_vector[i]), &(this->st_feature_vector), sizeof(float));
      }
      uint8_t vector_limits_lengthT = *(inbuffer + offset++);
      if(vector_limits_lengthT > vector_limits_length)
        this->vector_limits = (uint32_t*)realloc(this->vector_limits, vector_limits_lengthT * sizeof(uint32_t));
      offset += 3;
      vector_limits_length = vector_limits_lengthT;
      for( uint8_t i = 0; i < vector_limits_length; i++){
      this->st_vector_limits =  ((uint32_t) (*(inbuffer + offset)));
      this->st_vector_limits |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_vector_limits |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_vector_limits |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_vector_limits);
        memcpy( &(this->vector_limits[i]), &(this->st_vector_limits), sizeof(uint32_t));
      }
     return offset;
    }

    const char * getType(){ return "or_msgs/KeyPoint"; };
    const char * getMD5(){ return "76d31c56431a639c795b89ea93425098"; };

  };

}
#endif