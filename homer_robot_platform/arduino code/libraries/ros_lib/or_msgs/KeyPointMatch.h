#ifndef _ROS_or_msgs_KeyPointMatch_h
#define _ROS_or_msgs_KeyPointMatch_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace or_msgs
{

  class KeyPointMatch : public ros::Msg
  {
    public:
      uint32_t index1;
      uint32_t index2;
      float distance;
      float turn_angle;
      float scale_quotient;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->index1 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->index1 >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->index1 >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->index1 >> (8 * 3)) & 0xFF;
      offset += sizeof(this->index1);
      *(outbuffer + offset + 0) = (this->index2 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->index2 >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->index2 >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->index2 >> (8 * 3)) & 0xFF;
      offset += sizeof(this->index2);
      int32_t * val_distance = (int32_t *) &(this->distance);
      int32_t exp_distance = (((*val_distance)>>23)&255);
      if(exp_distance != 0)
        exp_distance += 1023-127;
      int32_t sig_distance = *val_distance;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_distance<<5) & 0xff;
      *(outbuffer + offset++) = (sig_distance>>3) & 0xff;
      *(outbuffer + offset++) = (sig_distance>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_distance<<4) & 0xF0) | ((sig_distance>>19)&0x0F);
      *(outbuffer + offset++) = (exp_distance>>4) & 0x7F;
      if(this->distance < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_turn_angle = (int32_t *) &(this->turn_angle);
      int32_t exp_turn_angle = (((*val_turn_angle)>>23)&255);
      if(exp_turn_angle != 0)
        exp_turn_angle += 1023-127;
      int32_t sig_turn_angle = *val_turn_angle;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_turn_angle<<5) & 0xff;
      *(outbuffer + offset++) = (sig_turn_angle>>3) & 0xff;
      *(outbuffer + offset++) = (sig_turn_angle>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_turn_angle<<4) & 0xF0) | ((sig_turn_angle>>19)&0x0F);
      *(outbuffer + offset++) = (exp_turn_angle>>4) & 0x7F;
      if(this->turn_angle < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_scale_quotient = (int32_t *) &(this->scale_quotient);
      int32_t exp_scale_quotient = (((*val_scale_quotient)>>23)&255);
      if(exp_scale_quotient != 0)
        exp_scale_quotient += 1023-127;
      int32_t sig_scale_quotient = *val_scale_quotient;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_scale_quotient<<5) & 0xff;
      *(outbuffer + offset++) = (sig_scale_quotient>>3) & 0xff;
      *(outbuffer + offset++) = (sig_scale_quotient>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_scale_quotient<<4) & 0xF0) | ((sig_scale_quotient>>19)&0x0F);
      *(outbuffer + offset++) = (exp_scale_quotient>>4) & 0x7F;
      if(this->scale_quotient < 0) *(outbuffer + offset -1) |= 0x80;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->index1 =  ((uint32_t) (*(inbuffer + offset)));
      this->index1 |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->index1 |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->index1 |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->index1);
      this->index2 =  ((uint32_t) (*(inbuffer + offset)));
      this->index2 |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->index2 |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->index2 |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->index2);
      uint32_t * val_distance = (uint32_t*) &(this->distance);
      offset += 3;
      *val_distance = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_distance |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_distance |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_distance |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_distance = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_distance |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_distance !=0)
        *val_distance |= ((exp_distance)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->distance = -this->distance;
      uint32_t * val_turn_angle = (uint32_t*) &(this->turn_angle);
      offset += 3;
      *val_turn_angle = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_turn_angle |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_turn_angle |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_turn_angle |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_turn_angle = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_turn_angle |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_turn_angle !=0)
        *val_turn_angle |= ((exp_turn_angle)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->turn_angle = -this->turn_angle;
      uint32_t * val_scale_quotient = (uint32_t*) &(this->scale_quotient);
      offset += 3;
      *val_scale_quotient = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_scale_quotient |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_scale_quotient |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_scale_quotient |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_scale_quotient = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_scale_quotient |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_scale_quotient !=0)
        *val_scale_quotient |= ((exp_scale_quotient)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->scale_quotient = -this->scale_quotient;
     return offset;
    }

    const char * getType(){ return "or_msgs/KeyPointMatch"; };
    const char * getMD5(){ return "769a2bde32b32becbbf14919fac2d5a5"; };

  };

}
#endif