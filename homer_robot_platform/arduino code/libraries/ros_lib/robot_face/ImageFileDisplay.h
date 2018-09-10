#ifndef _ROS_robot_face_ImageFileDisplay_h
#define _ROS_robot_face_ImageFileDisplay_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace robot_face
{

  class ImageFileDisplay : public ros::Msg
  {
    public:
      uint32_t time;
      const char* filename;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->time >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time);
      uint32_t length_filename = strlen(this->filename);
      memcpy(outbuffer + offset, &length_filename, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->filename, length_filename);
      offset += length_filename;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->time =  ((uint32_t) (*(inbuffer + offset)));
      this->time |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->time |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->time |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->time);
      uint32_t length_filename;
      memcpy(&length_filename, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_filename; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_filename-1]=0;
      this->filename = (char *)(inbuffer + offset-1);
      offset += length_filename;
     return offset;
    }

    const char * getType(){ return "robot_face/ImageFileDisplay"; };
    const char * getMD5(){ return "555ab1621eed726d39fb245d22a8d352"; };

  };

}
#endif