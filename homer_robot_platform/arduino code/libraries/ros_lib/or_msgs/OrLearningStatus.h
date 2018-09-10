#ifndef _ROS_or_msgs_OrLearningStatus_h
#define _ROS_or_msgs_OrLearningStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace or_msgs
{

  class OrLearningStatus : public ros::Msg
  {
    public:
      uint8_t image_names_length;
      char* st_image_names;
      char* * image_names;
      const char* object_type;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = image_names_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < image_names_length; i++){
      uint32_t length_image_namesi = strlen(this->image_names[i]);
      memcpy(outbuffer + offset, &length_image_namesi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->image_names[i], length_image_namesi);
      offset += length_image_namesi;
      }
      uint32_t length_object_type = strlen(this->object_type);
      memcpy(outbuffer + offset, &length_object_type, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->object_type, length_object_type);
      offset += length_object_type;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t image_names_lengthT = *(inbuffer + offset++);
      if(image_names_lengthT > image_names_length)
        this->image_names = (char**)realloc(this->image_names, image_names_lengthT * sizeof(char*));
      offset += 3;
      image_names_length = image_names_lengthT;
      for( uint8_t i = 0; i < image_names_length; i++){
      uint32_t length_st_image_names;
      memcpy(&length_st_image_names, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_image_names; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_image_names-1]=0;
      this->st_image_names = (char *)(inbuffer + offset-1);
      offset += length_st_image_names;
        memcpy( &(this->image_names[i]), &(this->st_image_names), sizeof(char*));
      }
      uint32_t length_object_type;
      memcpy(&length_object_type, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_object_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_object_type-1]=0;
      this->object_type = (char *)(inbuffer + offset-1);
      offset += length_object_type;
     return offset;
    }

    const char * getType(){ return "or_msgs/OrLearningStatus"; };
    const char * getMD5(){ return "d9c0a0aceb2bd1dece4a754f7975b63b"; };

  };

}
#endif