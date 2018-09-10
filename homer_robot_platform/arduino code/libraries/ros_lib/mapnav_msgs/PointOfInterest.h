#ifndef _ROS_mapnav_msgs_PointOfInterest_h
#define _ROS_mapnav_msgs_PointOfInterest_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"

namespace mapnav_msgs
{

  class PointOfInterest : public ros::Msg
  {
    public:
      int32_t type;
      const char* name;
      const char* remarks;
      geometry_msgs::Pose pose;
      enum { DEFAULT = 100 };
      enum { OBJECT = 300 };
      enum { GRIPPABLE_OBJECT = 400 };
      enum { PERSON = 600 };
      enum { START_POSITION = 900 };
      enum { START_ORIENTATION = 1000 };

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_type;
      u_type.real = this->type;
      *(outbuffer + offset + 0) = (u_type.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_type.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_type.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_type.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->type);
      uint32_t length_name = strlen(this->name);
      memcpy(outbuffer + offset, &length_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      uint32_t length_remarks = strlen(this->remarks);
      memcpy(outbuffer + offset, &length_remarks, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->remarks, length_remarks);
      offset += length_remarks;
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_type;
      u_type.base = 0;
      u_type.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_type.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_type.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_type.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->type = u_type.real;
      offset += sizeof(this->type);
      uint32_t length_name;
      memcpy(&length_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      uint32_t length_remarks;
      memcpy(&length_remarks, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_remarks; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_remarks-1]=0;
      this->remarks = (char *)(inbuffer + offset-1);
      offset += length_remarks;
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "mapnav_msgs/PointOfInterest"; };
    const char * getMD5(){ return "26da3fe9dca9931e03e1c638b717d95d"; };

  };

}
#endif