#ifndef _ROS_SERVICE_CaptureImage_h
#define _ROS_SERVICE_CaptureImage_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/Image.h"

namespace digicam
{

static const char CAPTUREIMAGE[] = "digicam/CaptureImage";

  class CaptureImageRequest : public ros::Msg
  {
    public:

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return CAPTUREIMAGE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class CaptureImageResponse : public ros::Msg
  {
    public:
      sensor_msgs::Image image;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->image.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->image.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return CAPTUREIMAGE; };
    const char * getMD5(){ return "b13d2865c5af2a64e6e30ab1b56e1dd5"; };

  };

  class CaptureImage {
    public:
    typedef CaptureImageRequest Request;
    typedef CaptureImageResponse Response;
  };

}
#endif
