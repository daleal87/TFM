#ifndef _ROS_mapnav_msgs_StartNavigation_h
#define _ROS_mapnav_msgs_StartNavigation_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"

namespace mapnav_msgs
{

  class StartNavigation : public ros::Msg
  {
    public:
      geometry_msgs::Pose goal;
      float distance_to_target;
      bool skip_final_turn;
      bool fast_planning;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->goal.serialize(outbuffer + offset);
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
      union {
        bool real;
        uint8_t base;
      } u_fast_planning;
      u_fast_planning.real = this->fast_planning;
      *(outbuffer + offset + 0) = (u_fast_planning.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->fast_planning);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->goal.deserialize(inbuffer + offset);
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
      union {
        bool real;
        uint8_t base;
      } u_fast_planning;
      u_fast_planning.base = 0;
      u_fast_planning.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->fast_planning = u_fast_planning.real;
      offset += sizeof(this->fast_planning);
     return offset;
    }

    const char * getType(){ return "mapnav_msgs/StartNavigation"; };
    const char * getMD5(){ return "8c688dbc8241a59302ed9c48f9ec271c"; };

  };

}
#endif