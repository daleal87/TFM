#ifndef _ROS_selfawareness_node_CheckKatana_h
#define _ROS_selfawareness_node_CheckKatana_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Vector3.h"

namespace selfawareness_node
{

  class CheckKatana : public ros::Msg
  {
    public:
      bool learnEmptyPose;
      geometry_msgs::Vector3 endeffectorCenter;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_learnEmptyPose;
      u_learnEmptyPose.real = this->learnEmptyPose;
      *(outbuffer + offset + 0) = (u_learnEmptyPose.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->learnEmptyPose);
      offset += this->endeffectorCenter.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_learnEmptyPose;
      u_learnEmptyPose.base = 0;
      u_learnEmptyPose.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->learnEmptyPose = u_learnEmptyPose.real;
      offset += sizeof(this->learnEmptyPose);
      offset += this->endeffectorCenter.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "selfawareness_node/CheckKatana"; };
    const char * getMD5(){ return "a291745f056de9e035b80a85cfbdf542"; };

  };

}
#endif