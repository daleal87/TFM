#ifndef _ROS_mapnav_msgs_ModifyPOI_h
#define _ROS_mapnav_msgs_ModifyPOI_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "mapnav_msgs/PointOfInterest.h"

namespace mapnav_msgs
{

  class ModifyPOI : public ros::Msg
  {
    public:
      mapnav_msgs::PointOfInterest poi;
      const char* old_name;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->poi.serialize(outbuffer + offset);
      uint32_t length_old_name = strlen(this->old_name);
      memcpy(outbuffer + offset, &length_old_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->old_name, length_old_name);
      offset += length_old_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->poi.deserialize(inbuffer + offset);
      uint32_t length_old_name;
      memcpy(&length_old_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_old_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_old_name-1]=0;
      this->old_name = (char *)(inbuffer + offset-1);
      offset += length_old_name;
     return offset;
    }

    const char * getType(){ return "mapnav_msgs/ModifyPOI"; };
    const char * getMD5(){ return "52af4ecb6ba8233a7a4e2df4e1032de6"; };

  };

}
#endif