#ifndef _ROS_people_tracking_msgs_TrackedPerson_h
#define _ROS_people_tracking_msgs_TrackedPerson_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose2D.h"

namespace people_tracking_msgs
{

  class TrackedPerson : public ros::Msg
  {
    public:
      geometry_msgs::Pose2D pose;
      geometry_msgs::Pose2D scaleAndOrientation;
      float radius;
      int8_t id;
      int8_t boostingId;
      float probability;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->pose.serialize(outbuffer + offset);
      offset += this->scaleAndOrientation.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_radius;
      u_radius.real = this->radius;
      *(outbuffer + offset + 0) = (u_radius.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_radius.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_radius.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_radius.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->radius);
      union {
        int8_t real;
        uint8_t base;
      } u_id;
      u_id.real = this->id;
      *(outbuffer + offset + 0) = (u_id.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id);
      union {
        int8_t real;
        uint8_t base;
      } u_boostingId;
      u_boostingId.real = this->boostingId;
      *(outbuffer + offset + 0) = (u_boostingId.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->boostingId);
      int32_t * val_probability = (int32_t *) &(this->probability);
      int32_t exp_probability = (((*val_probability)>>23)&255);
      if(exp_probability != 0)
        exp_probability += 1023-127;
      int32_t sig_probability = *val_probability;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_probability<<5) & 0xff;
      *(outbuffer + offset++) = (sig_probability>>3) & 0xff;
      *(outbuffer + offset++) = (sig_probability>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_probability<<4) & 0xF0) | ((sig_probability>>19)&0x0F);
      *(outbuffer + offset++) = (exp_probability>>4) & 0x7F;
      if(this->probability < 0) *(outbuffer + offset -1) |= 0x80;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pose.deserialize(inbuffer + offset);
      offset += this->scaleAndOrientation.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_radius;
      u_radius.base = 0;
      u_radius.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_radius.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_radius.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_radius.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->radius = u_radius.real;
      offset += sizeof(this->radius);
      union {
        int8_t real;
        uint8_t base;
      } u_id;
      u_id.base = 0;
      u_id.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->id = u_id.real;
      offset += sizeof(this->id);
      union {
        int8_t real;
        uint8_t base;
      } u_boostingId;
      u_boostingId.base = 0;
      u_boostingId.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->boostingId = u_boostingId.real;
      offset += sizeof(this->boostingId);
      uint32_t * val_probability = (uint32_t*) &(this->probability);
      offset += 3;
      *val_probability = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_probability |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_probability |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_probability |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_probability = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_probability |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_probability !=0)
        *val_probability |= ((exp_probability)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->probability = -this->probability;
     return offset;
    }

    const char * getType(){ return "people_tracking_msgs/TrackedPerson"; };
    const char * getMD5(){ return "7f521899ab79931783fe750ab7834010"; };

  };

}
#endif