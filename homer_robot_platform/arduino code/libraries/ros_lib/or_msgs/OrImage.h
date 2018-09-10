#ifndef _ROS_or_msgs_OrImage_h
#define _ROS_or_msgs_OrImage_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/Image.h"
#include "or_msgs/VectorObject2D.h"

namespace or_msgs
{

  class OrImage : public ros::Msg
  {
    public:
      sensor_msgs::Image image_gray;
      sensor_msgs::Image image_color;
      const char* filename;
      int32_t img_source;
      uint8_t vector_objects_length;
      or_msgs::VectorObject2D st_vector_objects;
      or_msgs::VectorObject2D * vector_objects;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->image_gray.serialize(outbuffer + offset);
      offset += this->image_color.serialize(outbuffer + offset);
      uint32_t length_filename = strlen(this->filename);
      memcpy(outbuffer + offset, &length_filename, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->filename, length_filename);
      offset += length_filename;
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
      *(outbuffer + offset++) = vector_objects_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < vector_objects_length; i++){
      offset += this->vector_objects[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->image_gray.deserialize(inbuffer + offset);
      offset += this->image_color.deserialize(inbuffer + offset);
      uint32_t length_filename;
      memcpy(&length_filename, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_filename; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_filename-1]=0;
      this->filename = (char *)(inbuffer + offset-1);
      offset += length_filename;
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
      uint8_t vector_objects_lengthT = *(inbuffer + offset++);
      if(vector_objects_lengthT > vector_objects_length)
        this->vector_objects = (or_msgs::VectorObject2D*)realloc(this->vector_objects, vector_objects_lengthT * sizeof(or_msgs::VectorObject2D));
      offset += 3;
      vector_objects_length = vector_objects_lengthT;
      for( uint8_t i = 0; i < vector_objects_length; i++){
      offset += this->st_vector_objects.deserialize(inbuffer + offset);
        memcpy( &(this->vector_objects[i]), &(this->st_vector_objects), sizeof(or_msgs::VectorObject2D));
      }
     return offset;
    }

    const char * getType(){ return "or_msgs/OrImage"; };
    const char * getMD5(){ return "732142b19180f3c8b042c51867d42b64"; };

  };

}
#endif