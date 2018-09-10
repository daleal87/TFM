#ifndef _ROS_pcl_people_detection_DetectedPerson_h
#define _ROS_pcl_people_detection_DetectedPerson_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Point32.h"
#include "sensor_msgs/Image.h"

namespace pcl_people_detection
{

  class DetectedPerson : public ros::Msg
  {
    public:
      geometry_msgs::Point32 position;
      float confidence;
      sensor_msgs::Image image;
      sensor_msgs::Image mask;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->position.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_confidence;
      u_confidence.real = this->confidence;
      *(outbuffer + offset + 0) = (u_confidence.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_confidence.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_confidence.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_confidence.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->confidence);
      offset += this->image.serialize(outbuffer + offset);
      offset += this->mask.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->position.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_confidence;
      u_confidence.base = 0;
      u_confidence.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_confidence.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_confidence.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_confidence.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->confidence = u_confidence.real;
      offset += sizeof(this->confidence);
      offset += this->image.deserialize(inbuffer + offset);
      offset += this->mask.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "pcl_people_detection/DetectedPerson"; };
    const char * getMD5(){ return "a78acf682dd58ccb8c95ea1c25ec5445"; };

  };

}
#endif