#ifndef _ROS_mapnav_msgs_TargetUnreachable_h
#define _ROS_mapnav_msgs_TargetUnreachable_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mapnav_msgs
{

  class TargetUnreachable : public ros::Msg
  {
    public:
      int8_t reason;
      enum { UNKNOWN = 0 };
      enum { TILT_OCCURED = 10 };
      enum { GRAVE_TILT_OCCURED = 15 };
      enum { STALL_OCCURED = 20 };
      enum { LASER_OBSTACLE = 30 };

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_reason;
      u_reason.real = this->reason;
      *(outbuffer + offset + 0) = (u_reason.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->reason);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_reason;
      u_reason.base = 0;
      u_reason.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->reason = u_reason.real;
      offset += sizeof(this->reason);
     return offset;
    }

    const char * getType(){ return "mapnav_msgs/TargetUnreachable"; };
    const char * getMD5(){ return "a9f2d933e976adfbc21866cc5076a294"; };

  };

}
#endif