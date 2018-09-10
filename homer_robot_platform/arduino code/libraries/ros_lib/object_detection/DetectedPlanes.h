#ifndef _ROS_object_detection_DetectedPlanes_h
#define _ROS_object_detection_DetectedPlanes_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "object_detection/SupportPlane.h"

namespace object_detection
{

  class DetectedPlanes : public ros::Msg
  {
    public:
      uint8_t planes_length;
      object_detection::SupportPlane st_planes;
      object_detection::SupportPlane * planes;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = planes_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < planes_length; i++){
      offset += this->planes[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t planes_lengthT = *(inbuffer + offset++);
      if(planes_lengthT > planes_length)
        this->planes = (object_detection::SupportPlane*)realloc(this->planes, planes_lengthT * sizeof(object_detection::SupportPlane));
      offset += 3;
      planes_length = planes_lengthT;
      for( uint8_t i = 0; i < planes_length; i++){
      offset += this->st_planes.deserialize(inbuffer + offset);
        memcpy( &(this->planes[i]), &(this->st_planes), sizeof(object_detection::SupportPlane));
      }
     return offset;
    }

    const char * getType(){ return "object_detection/DetectedPlanes"; };
    const char * getMD5(){ return "2df6dffac99621fb7e27b7591d653df2"; };

  };

}
#endif