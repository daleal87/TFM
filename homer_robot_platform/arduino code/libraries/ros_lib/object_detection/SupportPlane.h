#ifndef _ROS_object_detection_SupportPlane_h
#define _ROS_object_detection_SupportPlane_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/PointCloud2.h"
#include "sensor_msgs/Image.h"

namespace object_detection
{

  class SupportPlane : public ros::Msg
  {
    public:
      sensor_msgs::PointCloud2 points;
      sensor_msgs::Image mask;
      float height;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->points.serialize(outbuffer + offset);
      offset += this->mask.serialize(outbuffer + offset);
      int32_t * val_height = (int32_t *) &(this->height);
      int32_t exp_height = (((*val_height)>>23)&255);
      if(exp_height != 0)
        exp_height += 1023-127;
      int32_t sig_height = *val_height;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_height<<5) & 0xff;
      *(outbuffer + offset++) = (sig_height>>3) & 0xff;
      *(outbuffer + offset++) = (sig_height>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_height<<4) & 0xF0) | ((sig_height>>19)&0x0F);
      *(outbuffer + offset++) = (exp_height>>4) & 0x7F;
      if(this->height < 0) *(outbuffer + offset -1) |= 0x80;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->points.deserialize(inbuffer + offset);
      offset += this->mask.deserialize(inbuffer + offset);
      uint32_t * val_height = (uint32_t*) &(this->height);
      offset += 3;
      *val_height = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_height |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_height |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_height |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_height = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_height |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_height !=0)
        *val_height |= ((exp_height)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->height = -this->height;
     return offset;
    }

    const char * getType(){ return "object_detection/SupportPlane"; };
    const char * getMD5(){ return "2a0832c923767e81020a6fe7f33138de"; };

  };

}
#endif