#ifndef _ROS_followme_control_node_StartFollowingM_h
#define _ROS_followme_control_node_StartFollowingM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace followme_control_node
{

  class StartFollowingM : public ros::Msg
  {
    public:
      bool specific_person;
      float max_angle;
      float max_distance;
      int16_t person_id;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_specific_person;
      u_specific_person.real = this->specific_person;
      *(outbuffer + offset + 0) = (u_specific_person.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->specific_person);
      int32_t * val_max_angle = (int32_t *) &(this->max_angle);
      int32_t exp_max_angle = (((*val_max_angle)>>23)&255);
      if(exp_max_angle != 0)
        exp_max_angle += 1023-127;
      int32_t sig_max_angle = *val_max_angle;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_max_angle<<5) & 0xff;
      *(outbuffer + offset++) = (sig_max_angle>>3) & 0xff;
      *(outbuffer + offset++) = (sig_max_angle>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_max_angle<<4) & 0xF0) | ((sig_max_angle>>19)&0x0F);
      *(outbuffer + offset++) = (exp_max_angle>>4) & 0x7F;
      if(this->max_angle < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_max_distance = (int32_t *) &(this->max_distance);
      int32_t exp_max_distance = (((*val_max_distance)>>23)&255);
      if(exp_max_distance != 0)
        exp_max_distance += 1023-127;
      int32_t sig_max_distance = *val_max_distance;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_max_distance<<5) & 0xff;
      *(outbuffer + offset++) = (sig_max_distance>>3) & 0xff;
      *(outbuffer + offset++) = (sig_max_distance>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_max_distance<<4) & 0xF0) | ((sig_max_distance>>19)&0x0F);
      *(outbuffer + offset++) = (exp_max_distance>>4) & 0x7F;
      if(this->max_distance < 0) *(outbuffer + offset -1) |= 0x80;
      union {
        int16_t real;
        uint16_t base;
      } u_person_id;
      u_person_id.real = this->person_id;
      *(outbuffer + offset + 0) = (u_person_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_person_id.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->person_id);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_specific_person;
      u_specific_person.base = 0;
      u_specific_person.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->specific_person = u_specific_person.real;
      offset += sizeof(this->specific_person);
      uint32_t * val_max_angle = (uint32_t*) &(this->max_angle);
      offset += 3;
      *val_max_angle = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_max_angle |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_max_angle |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_max_angle |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_max_angle = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_max_angle |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_max_angle !=0)
        *val_max_angle |= ((exp_max_angle)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->max_angle = -this->max_angle;
      uint32_t * val_max_distance = (uint32_t*) &(this->max_distance);
      offset += 3;
      *val_max_distance = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_max_distance |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_max_distance |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_max_distance |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_max_distance = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_max_distance |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_max_distance !=0)
        *val_max_distance |= ((exp_max_distance)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->max_distance = -this->max_distance;
      union {
        int16_t real;
        uint16_t base;
      } u_person_id;
      u_person_id.base = 0;
      u_person_id.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_person_id.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->person_id = u_person_id.real;
      offset += sizeof(this->person_id);
     return offset;
    }

    const char * getType(){ return "followme_control_node/StartFollowingM"; };
    const char * getMD5(){ return "e527696064c811d3c30c7c550fbfa889"; };

  };

}
#endif