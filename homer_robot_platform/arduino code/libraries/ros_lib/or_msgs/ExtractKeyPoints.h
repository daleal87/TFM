#ifndef _ROS_or_msgs_ExtractKeyPoints_h
#define _ROS_or_msgs_ExtractKeyPoints_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "or_msgs/BoundingBox2D.h"

namespace or_msgs
{

  class ExtractKeyPoints : public ros::Msg
  {
    public:
      int32_t img_source;
      uint8_t bounding_boxes_length;
      or_msgs::BoundingBox2D st_bounding_boxes;
      or_msgs::BoundingBox2D * bounding_boxes;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_img_source;
      u_img_source.real = this->img_source;
      *(outbuffer + offset + 0) = (u_img_source.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_img_source.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_img_source.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_img_source.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->img_source);
      *(outbuffer + offset++) = bounding_boxes_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < bounding_boxes_length; i++){
      offset += this->bounding_boxes[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_img_source;
      u_img_source.base = 0;
      u_img_source.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_img_source.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_img_source.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_img_source.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->img_source = u_img_source.real;
      offset += sizeof(this->img_source);
      uint8_t bounding_boxes_lengthT = *(inbuffer + offset++);
      if(bounding_boxes_lengthT > bounding_boxes_length)
        this->bounding_boxes = (or_msgs::BoundingBox2D*)realloc(this->bounding_boxes, bounding_boxes_lengthT * sizeof(or_msgs::BoundingBox2D));
      offset += 3;
      bounding_boxes_length = bounding_boxes_lengthT;
      for( uint8_t i = 0; i < bounding_boxes_length; i++){
      offset += this->st_bounding_boxes.deserialize(inbuffer + offset);
        memcpy( &(this->bounding_boxes[i]), &(this->st_bounding_boxes), sizeof(or_msgs::BoundingBox2D));
      }
     return offset;
    }

    const char * getType(){ return "or_msgs/ExtractKeyPoints"; };
    const char * getMD5(){ return "e4c6be9e7ca7a55c0d490d540506faff"; };

  };

}
#endif