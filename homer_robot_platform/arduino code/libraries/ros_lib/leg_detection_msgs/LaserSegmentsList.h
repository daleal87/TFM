#ifndef _ROS_leg_detection_msgs_LaserSegmentsList_h
#define _ROS_leg_detection_msgs_LaserSegmentsList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "leg_detection_msgs/LaserSegment.h"

namespace leg_detection_msgs
{

  class LaserSegmentsList : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t laserSegments_length;
      leg_detection_msgs::LaserSegment st_laserSegments;
      leg_detection_msgs::LaserSegment * laserSegments;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = laserSegments_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < laserSegments_length; i++){
      offset += this->laserSegments[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t laserSegments_lengthT = *(inbuffer + offset++);
      if(laserSegments_lengthT > laserSegments_length)
        this->laserSegments = (leg_detection_msgs::LaserSegment*)realloc(this->laserSegments, laserSegments_lengthT * sizeof(leg_detection_msgs::LaserSegment));
      offset += 3;
      laserSegments_length = laserSegments_lengthT;
      for( uint8_t i = 0; i < laserSegments_length; i++){
      offset += this->st_laserSegments.deserialize(inbuffer + offset);
        memcpy( &(this->laserSegments[i]), &(this->st_laserSegments), sizeof(leg_detection_msgs::LaserSegment));
      }
     return offset;
    }

    const char * getType(){ return "leg_detection_msgs/LaserSegmentsList"; };
    const char * getMD5(){ return "b520cdf9d0efc1fbce34441626579853"; };

  };

}
#endif