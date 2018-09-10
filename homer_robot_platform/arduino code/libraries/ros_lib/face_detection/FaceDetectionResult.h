#ifndef _ROS_face_detection_FaceDetectionResult_h
#define _ROS_face_detection_FaceDetectionResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Polygon.h"
#include "sensor_msgs/Image.h"

namespace face_detection
{

  class FaceDetectionResult : public ros::Msg
  {
    public:
      uint8_t bounding_boxes_length;
      geometry_msgs::Polygon st_bounding_boxes;
      geometry_msgs::Polygon * bounding_boxes;
      sensor_msgs::Image image;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = bounding_boxes_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < bounding_boxes_length; i++){
      offset += this->bounding_boxes[i].serialize(outbuffer + offset);
      }
      offset += this->image.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t bounding_boxes_lengthT = *(inbuffer + offset++);
      if(bounding_boxes_lengthT > bounding_boxes_length)
        this->bounding_boxes = (geometry_msgs::Polygon*)realloc(this->bounding_boxes, bounding_boxes_lengthT * sizeof(geometry_msgs::Polygon));
      offset += 3;
      bounding_boxes_length = bounding_boxes_lengthT;
      for( uint8_t i = 0; i < bounding_boxes_length; i++){
      offset += this->st_bounding_boxes.deserialize(inbuffer + offset);
        memcpy( &(this->bounding_boxes[i]), &(this->st_bounding_boxes), sizeof(geometry_msgs::Polygon));
      }
      offset += this->image.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "face_detection/FaceDetectionResult"; };
    const char * getMD5(){ return "392d8c315ad91d2c87ff20f0809ba7b4"; };

  };

}
#endif