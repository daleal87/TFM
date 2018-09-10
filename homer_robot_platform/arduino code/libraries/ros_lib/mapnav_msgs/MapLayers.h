#ifndef _ROS_mapnav_msgs_MapLayers_h
#define _ROS_mapnav_msgs_MapLayers_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mapnav_msgs
{

  class MapLayers : public ros::Msg
  {
    public:
      int32_t layer;
      bool state;
      enum { SLAM_LAYER = 0 };
      enum { MASKING_LAYER = 1 };
      enum { KINECT_LAYER = 2 };
      enum { SICK_LAYER = 3 };

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_layer;
      u_layer.real = this->layer;
      *(outbuffer + offset + 0) = (u_layer.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_layer.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_layer.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_layer.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->layer);
      union {
        bool real;
        uint8_t base;
      } u_state;
      u_state.real = this->state;
      *(outbuffer + offset + 0) = (u_state.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_layer;
      u_layer.base = 0;
      u_layer.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_layer.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_layer.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_layer.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->layer = u_layer.real;
      offset += sizeof(this->layer);
      union {
        bool real;
        uint8_t base;
      } u_state;
      u_state.base = 0;
      u_state.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->state = u_state.real;
      offset += sizeof(this->state);
     return offset;
    }

    const char * getType(){ return "mapnav_msgs/MapLayers"; };
    const char * getMD5(){ return "316b62aa46b38d5d49b946608b284eb9"; };

  };

}
#endif