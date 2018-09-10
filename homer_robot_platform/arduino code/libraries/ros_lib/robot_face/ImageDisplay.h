#ifndef _ROS_robot_face_ImageDisplay_h
#define _ROS_robot_face_ImageDisplay_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/Image.h"

namespace robot_face
{

  class ImageDisplay : public ros::Msg
  {
    public:
      uint32_t time;
      sensor_msgs::Image Image;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->time >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time);
      offset += this->Image.serialize(outbuffer + offset);
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
      offset += this->Image.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "robot_face/ImageDisplay"; };
    const char * getMD5(){ return "4cb5936c87cc3ade4e47bc3943f154fc"; };

  };

}
#endif