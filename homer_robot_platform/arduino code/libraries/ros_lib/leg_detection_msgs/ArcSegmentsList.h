#ifndef _ROS_leg_detection_msgs_ArcSegmentsList_h
#define _ROS_leg_detection_msgs_ArcSegmentsList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "leg_detection_msgs/ArcSegment.h"

namespace leg_detection_msgs
{

  class ArcSegmentsList : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t arcSegments_length;
      leg_detection_msgs::ArcSegment st_arcSegments;
      leg_detection_msgs::ArcSegment * arcSegments;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = arcSegments_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < arcSegments_length; i++){
      offset += this->arcSegments[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t arcSegments_lengthT = *(inbuffer + offset++);
      if(arcSegments_lengthT > arcSegments_length)
        this->arcSegments = (leg_detection_msgs::ArcSegment*)realloc(this->arcSegments, arcSegments_lengthT * sizeof(leg_detection_msgs::ArcSegment));
      offset += 3;
      arcSegments_length = arcSegments_lengthT;
      for( uint8_t i = 0; i < arcSegments_length; i++){
      offset += this->st_arcSegments.deserialize(inbuffer + offset);
        memcpy( &(this->arcSegments[i]), &(this->st_arcSegments), sizeof(leg_detection_msgs::ArcSegment));
      }
     return offset;
    }

    const char * getType(){ return "leg_detection_msgs/ArcSegmentsList"; };
    const char * getMD5(){ return "4595377a8b560626fc08e30a15098705"; };

  };

}
#endif