#ifndef _ROS_object_detection_DetectedObjects_h
#define _ROS_object_detection_DetectedObjects_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "object_detection/Object.h"

namespace object_detection
{

  class DetectedObjects : public ros::Msg
  {
    public:
      uint8_t objects_length;
      object_detection::Object st_objects;
      object_detection::Object * objects;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = objects_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < objects_length; i++){
      offset += this->objects[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t objects_lengthT = *(inbuffer + offset++);
      if(objects_lengthT > objects_length)
        this->objects = (object_detection::Object*)realloc(this->objects, objects_lengthT * sizeof(object_detection::Object));
      offset += 3;
      objects_length = objects_lengthT;
      for( uint8_t i = 0; i < objects_length; i++){
      offset += this->st_objects.deserialize(inbuffer + offset);
        memcpy( &(this->objects[i]), &(this->st_objects), sizeof(object_detection::Object));
      }
     return offset;
    }

    const char * getType(){ return "object_detection/DetectedObjects"; };
    const char * getMD5(){ return "7cd89e3de6c39e84136a3dfd50afe920"; };

  };

}
#endif