#ifndef _ROS_or_msgs_OrObjectNames_h
#define _ROS_or_msgs_OrObjectNames_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace or_msgs
{

  class OrObjectNames : public ros::Msg
  {
    public:
      uint8_t object_names_length;
      char* st_object_names;
      char* * object_names;
      uint8_t object_types_length;
      char* st_object_types;
      char* * object_types;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = object_names_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < object_names_length; i++){
      uint32_t length_object_namesi = strlen(this->object_names[i]);
      memcpy(outbuffer + offset, &length_object_namesi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->object_names[i], length_object_namesi);
      offset += length_object_namesi;
      }
      *(outbuffer + offset++) = object_types_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < object_types_length; i++){
      uint32_t length_object_typesi = strlen(this->object_types[i]);
      memcpy(outbuffer + offset, &length_object_typesi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->object_types[i], length_object_typesi);
      offset += length_object_typesi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t object_names_lengthT = *(inbuffer + offset++);
      if(object_names_lengthT > object_names_length)
        this->object_names = (char**)realloc(this->object_names, object_names_lengthT * sizeof(char*));
      offset += 3;
      object_names_length = object_names_lengthT;
      for( uint8_t i = 0; i < object_names_length; i++){
      uint32_t length_st_object_names;
      memcpy(&length_st_object_names, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_object_names; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_object_names-1]=0;
      this->st_object_names = (char *)(inbuffer + offset-1);
      offset += length_st_object_names;
        memcpy( &(this->object_names[i]), &(this->st_object_names), sizeof(char*));
      }
      uint8_t object_types_lengthT = *(inbuffer + offset++);
      if(object_types_lengthT > object_types_length)
        this->object_types = (char**)realloc(this->object_types, object_types_lengthT * sizeof(char*));
      offset += 3;
      object_types_length = object_types_lengthT;
      for( uint8_t i = 0; i < object_types_length; i++){
      uint32_t length_st_object_types;
      memcpy(&length_st_object_types, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_object_types; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_object_types-1]=0;
      this->st_object_types = (char *)(inbuffer + offset-1);
      offset += length_st_object_types;
        memcpy( &(this->object_types[i]), &(this->st_object_types), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return "or_msgs/OrObjectNames"; };
    const char * getMD5(){ return "d5456c671830259134993c9a5d9d27ea"; };

  };

}
#endif