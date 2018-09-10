#ifndef _ROS_object_detection_DetectObjects_h
#define _ROS_object_detection_DetectObjects_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace object_detection
{

  class DetectObjects : public ros::Msg
  {
    public:
      bool filter_objects;
      bool recognize_objects;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_filter_objects;
      u_filter_objects.real = this->filter_objects;
      *(outbuffer + offset + 0) = (u_filter_objects.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->filter_objects);
      union {
        bool real;
        uint8_t base;
      } u_recognize_objects;
      u_recognize_objects.real = this->recognize_objects;
      *(outbuffer + offset + 0) = (u_recognize_objects.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->recognize_objects);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_filter_objects;
      u_filter_objects.base = 0;
      u_filter_objects.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->filter_objects = u_filter_objects.real;
      offset += sizeof(this->filter_objects);
      union {
        bool real;
        uint8_t base;
      } u_recognize_objects;
      u_recognize_objects.base = 0;
      u_recognize_objects.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->recognize_objects = u_recognize_objects.real;
      offset += sizeof(this->recognize_objects);
     return offset;
    }

    const char * getType(){ return "object_detection/DetectObjects"; };
    const char * getMD5(){ return "291ef7ce8410e8a71734530536bbb563"; };

  };

}
#endif