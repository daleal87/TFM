#ifndef _ROS_or_msgs_MatchResult_h
#define _ROS_or_msgs_MatchResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/Image.h"
#include "or_msgs/Point2D.h"
#include "or_msgs/KeyPoint.h"
#include "or_msgs/KeyPointMatch.h"
#include "or_msgs/KeyPointMatchArray.h"

namespace or_msgs
{

  class MatchResult : public ros::Msg
  {
    public:
      const char* object_name;
      const char* object_type;
      sensor_msgs::Image image;
      int32_t image_index;
      const char* image_name;
      uint8_t outline_length;
      or_msgs::Point2D st_outline;
      or_msgs::Point2D * outline;
      uint8_t b_box_length;
      or_msgs::Point2D st_b_box;
      or_msgs::Point2D * b_box;
      or_msgs::Point2D center;
      int32_t bounding_box_index;
      uint8_t key_point_index_map_length;
      uint32_t st_key_point_index_map;
      uint32_t * key_point_index_map;
      uint8_t object_key_points_length;
      or_msgs::KeyPoint st_object_key_points;
      or_msgs::KeyPoint * object_key_points;
      uint8_t stage1_matches_length;
      or_msgs::KeyPointMatch st_stage1_matches;
      or_msgs::KeyPointMatch * stage1_matches;
      uint8_t stage2_matches_length;
      or_msgs::KeyPointMatchArray st_stage2_matches;
      or_msgs::KeyPointMatchArray * stage2_matches;
      uint8_t stage3_matches_length;
      or_msgs::KeyPointMatch st_stage3_matches;
      or_msgs::KeyPointMatch * stage3_matches;
      uint8_t scene_key_points_within_outline_length;
      or_msgs::KeyPoint st_scene_key_points_within_outline;
      or_msgs::KeyPoint * scene_key_points_within_outline;
      float homography[9];

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_object_name = strlen(this->object_name);
      memcpy(outbuffer + offset, &length_object_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->object_name, length_object_name);
      offset += length_object_name;
      uint32_t length_object_type = strlen(this->object_type);
      memcpy(outbuffer + offset, &length_object_type, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->object_type, length_object_type);
      offset += length_object_type;
      offset += this->image.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_image_index;
      u_image_index.real = this->image_index;
      *(outbuffer + offset + 0) = (u_image_index.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_image_index.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_image_index.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_image_index.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->image_index);
      uint32_t length_image_name = strlen(this->image_name);
      memcpy(outbuffer + offset, &length_image_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->image_name, length_image_name);
      offset += length_image_name;
      *(outbuffer + offset++) = outline_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < outline_length; i++){
      offset += this->outline[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = b_box_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < b_box_length; i++){
      offset += this->b_box[i].serialize(outbuffer + offset);
      }
      offset += this->center.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_bounding_box_index;
      u_bounding_box_index.real = this->bounding_box_index;
      *(outbuffer + offset + 0) = (u_bounding_box_index.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_bounding_box_index.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_bounding_box_index.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_bounding_box_index.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bounding_box_index);
      *(outbuffer + offset++) = key_point_index_map_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < key_point_index_map_length; i++){
      *(outbuffer + offset + 0) = (this->key_point_index_map[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->key_point_index_map[i] >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->key_point_index_map[i] >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->key_point_index_map[i] >> (8 * 3)) & 0xFF;
      offset += sizeof(this->key_point_index_map[i]);
      }
      *(outbuffer + offset++) = object_key_points_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < object_key_points_length; i++){
      offset += this->object_key_points[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = stage1_matches_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < stage1_matches_length; i++){
      offset += this->stage1_matches[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = stage2_matches_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < stage2_matches_length; i++){
      offset += this->stage2_matches[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = stage3_matches_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < stage3_matches_length; i++){
      offset += this->stage3_matches[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = scene_key_points_within_outline_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < scene_key_points_within_outline_length; i++){
      offset += this->scene_key_points_within_outline[i].serialize(outbuffer + offset);
      }
      for( uint8_t i = 0; i < 9; i++){
      int32_t * val_homographyi = (int32_t *) &(this->homography[i]);
      int32_t exp_homographyi = (((*val_homographyi)>>23)&255);
      if(exp_homographyi != 0)
        exp_homographyi += 1023-127;
      int32_t sig_homographyi = *val_homographyi;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_homographyi<<5) & 0xff;
      *(outbuffer + offset++) = (sig_homographyi>>3) & 0xff;
      *(outbuffer + offset++) = (sig_homographyi>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_homographyi<<4) & 0xF0) | ((sig_homographyi>>19)&0x0F);
      *(outbuffer + offset++) = (exp_homographyi>>4) & 0x7F;
      if(this->homography[i] < 0) *(outbuffer + offset -1) |= 0x80;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_object_name;
      memcpy(&length_object_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_object_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_object_name-1]=0;
      this->object_name = (char *)(inbuffer + offset-1);
      offset += length_object_name;
      uint32_t length_object_type;
      memcpy(&length_object_type, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_object_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_object_type-1]=0;
      this->object_type = (char *)(inbuffer + offset-1);
      offset += length_object_type;
      offset += this->image.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_image_index;
      u_image_index.base = 0;
      u_image_index.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_image_index.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_image_index.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_image_index.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->image_index = u_image_index.real;
      offset += sizeof(this->image_index);
      uint32_t length_image_name;
      memcpy(&length_image_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_image_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_image_name-1]=0;
      this->image_name = (char *)(inbuffer + offset-1);
      offset += length_image_name;
      uint8_t outline_lengthT = *(inbuffer + offset++);
      if(outline_lengthT > outline_length)
        this->outline = (or_msgs::Point2D*)realloc(this->outline, outline_lengthT * sizeof(or_msgs::Point2D));
      offset += 3;
      outline_length = outline_lengthT;
      for( uint8_t i = 0; i < outline_length; i++){
      offset += this->st_outline.deserialize(inbuffer + offset);
        memcpy( &(this->outline[i]), &(this->st_outline), sizeof(or_msgs::Point2D));
      }
      uint8_t b_box_lengthT = *(inbuffer + offset++);
      if(b_box_lengthT > b_box_length)
        this->b_box = (or_msgs::Point2D*)realloc(this->b_box, b_box_lengthT * sizeof(or_msgs::Point2D));
      offset += 3;
      b_box_length = b_box_lengthT;
      for( uint8_t i = 0; i < b_box_length; i++){
      offset += this->st_b_box.deserialize(inbuffer + offset);
        memcpy( &(this->b_box[i]), &(this->st_b_box), sizeof(or_msgs::Point2D));
      }
      offset += this->center.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_bounding_box_index;
      u_bounding_box_index.base = 0;
      u_bounding_box_index.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_bounding_box_index.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_bounding_box_index.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_bounding_box_index.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->bounding_box_index = u_bounding_box_index.real;
      offset += sizeof(this->bounding_box_index);
      uint8_t key_point_index_map_lengthT = *(inbuffer + offset++);
      if(key_point_index_map_lengthT > key_point_index_map_length)
        this->key_point_index_map = (uint32_t*)realloc(this->key_point_index_map, key_point_index_map_lengthT * sizeof(uint32_t));
      offset += 3;
      key_point_index_map_length = key_point_index_map_lengthT;
      for( uint8_t i = 0; i < key_point_index_map_length; i++){
      this->st_key_point_index_map =  ((uint32_t) (*(inbuffer + offset)));
      this->st_key_point_index_map |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_key_point_index_map |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_key_point_index_map |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_key_point_index_map);
        memcpy( &(this->key_point_index_map[i]), &(this->st_key_point_index_map), sizeof(uint32_t));
      }
      uint8_t object_key_points_lengthT = *(inbuffer + offset++);
      if(object_key_points_lengthT > object_key_points_length)
        this->object_key_points = (or_msgs::KeyPoint*)realloc(this->object_key_points, object_key_points_lengthT * sizeof(or_msgs::KeyPoint));
      offset += 3;
      object_key_points_length = object_key_points_lengthT;
      for( uint8_t i = 0; i < object_key_points_length; i++){
      offset += this->st_object_key_points.deserialize(inbuffer + offset);
        memcpy( &(this->object_key_points[i]), &(this->st_object_key_points), sizeof(or_msgs::KeyPoint));
      }
      uint8_t stage1_matches_lengthT = *(inbuffer + offset++);
      if(stage1_matches_lengthT > stage1_matches_length)
        this->stage1_matches = (or_msgs::KeyPointMatch*)realloc(this->stage1_matches, stage1_matches_lengthT * sizeof(or_msgs::KeyPointMatch));
      offset += 3;
      stage1_matches_length = stage1_matches_lengthT;
      for( uint8_t i = 0; i < stage1_matches_length; i++){
      offset += this->st_stage1_matches.deserialize(inbuffer + offset);
        memcpy( &(this->stage1_matches[i]), &(this->st_stage1_matches), sizeof(or_msgs::KeyPointMatch));
      }
      uint8_t stage2_matches_lengthT = *(inbuffer + offset++);
      if(stage2_matches_lengthT > stage2_matches_length)
        this->stage2_matches = (or_msgs::KeyPointMatchArray*)realloc(this->stage2_matches, stage2_matches_lengthT * sizeof(or_msgs::KeyPointMatchArray));
      offset += 3;
      stage2_matches_length = stage2_matches_lengthT;
      for( uint8_t i = 0; i < stage2_matches_length; i++){
      offset += this->st_stage2_matches.deserialize(inbuffer + offset);
        memcpy( &(this->stage2_matches[i]), &(this->st_stage2_matches), sizeof(or_msgs::KeyPointMatchArray));
      }
      uint8_t stage3_matches_lengthT = *(inbuffer + offset++);
      if(stage3_matches_lengthT > stage3_matches_length)
        this->stage3_matches = (or_msgs::KeyPointMatch*)realloc(this->stage3_matches, stage3_matches_lengthT * sizeof(or_msgs::KeyPointMatch));
      offset += 3;
      stage3_matches_length = stage3_matches_lengthT;
      for( uint8_t i = 0; i < stage3_matches_length; i++){
      offset += this->st_stage3_matches.deserialize(inbuffer + offset);
        memcpy( &(this->stage3_matches[i]), &(this->st_stage3_matches), sizeof(or_msgs::KeyPointMatch));
      }
      uint8_t scene_key_points_within_outline_lengthT = *(inbuffer + offset++);
      if(scene_key_points_within_outline_lengthT > scene_key_points_within_outline_length)
        this->scene_key_points_within_outline = (or_msgs::KeyPoint*)realloc(this->scene_key_points_within_outline, scene_key_points_within_outline_lengthT * sizeof(or_msgs::KeyPoint));
      offset += 3;
      scene_key_points_within_outline_length = scene_key_points_within_outline_lengthT;
      for( uint8_t i = 0; i < scene_key_points_within_outline_length; i++){
      offset += this->st_scene_key_points_within_outline.deserialize(inbuffer + offset);
        memcpy( &(this->scene_key_points_within_outline[i]), &(this->st_scene_key_points_within_outline), sizeof(or_msgs::KeyPoint));
      }
      for( uint8_t i = 0; i < 9; i++){
      uint32_t * val_homographyi = (uint32_t*) &(this->homography[i]);
      offset += 3;
      *val_homographyi = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_homographyi |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_homographyi |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_homographyi |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_homographyi = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_homographyi |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_homographyi !=0)
        *val_homographyi |= ((exp_homographyi)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->homography[i] = -this->homography[i];
      }
     return offset;
    }

    const char * getType(){ return "or_msgs/MatchResult"; };
    const char * getMD5(){ return "8cf7d42ec68f4a8034e8321f450cf35c"; };

  };

}
#endif