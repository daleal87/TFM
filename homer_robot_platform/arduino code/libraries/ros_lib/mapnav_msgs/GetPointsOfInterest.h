#ifndef _ROS_SERVICE_GetPointsOfInterest_h
#define _ROS_SERVICE_GetPointsOfInterest_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "mapnav_msgs/PointsOfInterest.h"

namespace mapnav_msgs
{

static const char GETPOINTSOFINTEREST[] = "mapnav_msgs/GetPointsOfInterest";

  class GetPointsOfInterestRequest : public ros::Msg
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

    const char * getType(){ return GETPOINTSOFINTEREST; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetPointsOfInterestResponse : public ros::Msg
  {
    public:
      mapnav_msgs::PointsOfInterest poi_list;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->poi_list.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->poi_list.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return GETPOINTSOFINTEREST; };
    const char * getMD5(){ return "e57421bbedca518ae2143c832bc28d85"; };

  };

  class GetPointsOfInterest {
    public:
    typedef GetPointsOfInterestRequest Request;
    typedef GetPointsOfInterestResponse Response;
  };

}
#endif
