#ifndef _ROS_or_msgs_OrMatchResult_h
#define _ROS_or_msgs_OrMatchResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/Image.h"
#include "or_msgs/KeyPoint.h"
#include "or_msgs/MatchResult.h"
#include "or_msgs/BoundingBox2D.h"

namespace or_msgs
{

  class OrMatchResult : public ros::Msg
  {
    public:
      sensor_msgs::Image image;
      uint8_t key_points_length;
      or_msgs::KeyPoint st_key_points;
      or_msgs::KeyPoint * key_points;
      uint8_t match_results_length;
      or_msgs::MatchResult st_match_results;
      or_msgs::MatchResult * match_results;
      uint8_t bounding_boxes_length;
      or_msgs::BoundingBox2D st_bounding_boxes;
      or_msgs::BoundingBox2D * bounding_boxes;
      int32_t seq_num;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->image.serialize(outbuffer + offset);
      *(outbuffer + offset++) = key_points_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < key_points_length; i++){
      offset += this->key_points[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = match_results_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < match_results_length; i++){
      offset += this->match_results[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = bounding_boxes_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < bounding_boxes_length; i++){
      offset += this->bounding_boxes[i].serialize(outbuffer + offset);
      }
      union {
        int32_t real;
        uint32_t base;
      } u_seq_num;
      u_seq_num.real = this->seq_num;
      *(outbuffer + offset + 0) = (u_seq_num.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_seq_num.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_seq_num.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_seq_num.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->seq_num);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->image.deserialize(inbuffer + offset);
      uint8_t key_points_lengthT = *(inbuffer + offset++);
      if(key_points_lengthT > key_points_length)
        this->key_points = (or_msgs::KeyPoint*)realloc(this->key_points, key_points_lengthT * sizeof(or_msgs::KeyPoint));
      offset += 3;
      key_points_length = key_points_lengthT;
      for( uint8_t i = 0; i < key_points_length; i++){
      offset += this->st_key_points.deserialize(inbuffer + offset);
        memcpy( &(this->key_points[i]), &(this->st_key_points), sizeof(or_msgs::KeyPoint));
      }
      uint8_t match_results_lengthT = *(inbuffer + offset++);
      if(match_results_lengthT > match_results_length)
        this->match_results = (or_msgs::MatchResult*)realloc(this->match_results, match_results_lengthT * sizeof(or_msgs::MatchResult));
      offset += 3;
      match_results_length = match_results_lengthT;
      for( uint8_t i = 0; i < match_results_length; i++){
      offset += this->st_match_results.deserialize(inbuffer + offset);
        memcpy( &(this->match_results[i]), &(this->st_match_results), sizeof(or_msgs::MatchResult));
      }
      uint8_t bounding_boxes_lengthT = *(inbuffer + offset++);
      if(bounding_boxes_lengthT > bounding_boxes_length)
        this->bounding_boxes = (or_msgs::BoundingBox2D*)realloc(this->bounding_boxes, bounding_boxes_lengthT * sizeof(or_msgs::BoundingBox2D));
      offset += 3;
      bounding_boxes_length = bounding_boxes_lengthT;
      for( uint8_t i = 0; i < bounding_boxes_length; i++){
      offset += this->st_bounding_boxes.deserialize(inbuffer + offset);
        memcpy( &(this->bounding_boxes[i]), &(this->st_bounding_boxes), sizeof(or_msgs::BoundingBox2D));
      }
      union {
        int32_t real;
        uint32_t base;
      } u_seq_num;
      u_seq_num.base = 0;
      u_seq_num.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_seq_num.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_seq_num.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_seq_num.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->seq_num = u_seq_num.real;
      offset += sizeof(this->seq_num);
     return offset;
    }

    const char * getType(){ return "or_msgs/OrMatchResult"; };
    const char * getMD5(){ return "d0ebd77d6bbc76f2f364174e89959688"; };

  };

}
#endif