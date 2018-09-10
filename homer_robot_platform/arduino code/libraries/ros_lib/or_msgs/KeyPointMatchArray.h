#ifndef _ROS_or_msgs_KeyPointMatchArray_h
#define _ROS_or_msgs_KeyPointMatchArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "or_msgs/KeyPointMatch.h"

namespace or_msgs
{

  class KeyPointMatchArray : public ros::Msg
  {
    public:
      uint8_t key_point_match_array_length;
      or_msgs::KeyPointMatch st_key_point_match_array;
      or_msgs::KeyPointMatch * key_point_match_array;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = key_point_match_array_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < key_point_match_array_length; i++){
      offset += this->key_point_match_array[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t key_point_match_array_lengthT = *(inbuffer + offset++);
      if(key_point_match_array_lengthT > key_point_match_array_length)
        this->key_point_match_array = (or_msgs::KeyPointMatch*)realloc(this->key_point_match_array, key_point_match_array_lengthT * sizeof(or_msgs::KeyPointMatch));
      offset += 3;
      key_point_match_array_length = key_point_match_array_lengthT;
      for( uint8_t i = 0; i < key_point_match_array_length; i++){
      offset += this->st_key_point_match_array.deserialize(inbuffer + offset);
        memcpy( &(this->key_point_match_array[i]), &(this->st_key_point_match_array), sizeof(or_msgs::KeyPointMatch));
      }
     return offset;
    }

    const char * getType(){ return "or_msgs/KeyPointMatchArray"; };
    const char * getMD5(){ return "8694d922914be99cf106d32be3377777"; };

  };

}
#endif