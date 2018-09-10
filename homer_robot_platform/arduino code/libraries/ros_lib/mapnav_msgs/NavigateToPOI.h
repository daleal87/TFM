#ifndef _ROS_mapnav_msgs_NavigateToPOI_h
#define _ROS_mapnav_msgs_NavigateToPOI_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mapnav_msgs
{

  class NavigateToPOI : public ros::Msg
  {
    public:
      const char* poi_name;
      float distance_to_target;
      bool skip_final_turn;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_poi_name = strlen(this->poi_name);
      memcpy(outbuffer + offset, &length_poi_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->poi_name, length_poi_name);
      offset += length_poi_name;
      union {
        float real;
        uint32_t base;
      } u_distance_to_target;
      u_distance_to_target.real = this->distance_to_target;
      *(outbuffer + offset + 0) = (u_distance_to_target.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance_to_target.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_distance_to_target.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_distance_to_target.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distance_to_target);
      union {
        bool real;
        uint8_t base;
      } u_skip_final_turn;
      u_skip_final_turn.real = this->skip_final_turn;
      *(outbuffer + offset + 0) = (u_skip_final_turn.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->skip_final_turn);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_poi_name;
      memcpy(&length_poi_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_poi_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_poi_name-1]=0;
      this->poi_name = (char *)(inbuffer + offset-1);
      offset += length_poi_name;
      union {
        float real;
        uint32_t base;
      } u_distance_to_target;
      u_distance_to_target.base = 0;
      u_distance_to_target.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance_to_target.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_distance_to_target.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_distance_to_target.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->distance_to_target = u_distance_to_target.real;
      offset += sizeof(this->distance_to_target);
      union {
        bool real;
        uint8_t base;
      } u_skip_final_turn;
      u_skip_final_turn.base = 0;
      u_skip_final_turn.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->skip_final_turn = u_skip_final_turn.real;
      offset += sizeof(this->skip_final_turn);
     return offset;
    }

    const char * getType(){ return "mapnav_msgs/NavigateToPOI"; };
    const char * getMD5(){ return "e91460fd0694b88ea22e42c09baee7f9"; };

  };

}
#endif