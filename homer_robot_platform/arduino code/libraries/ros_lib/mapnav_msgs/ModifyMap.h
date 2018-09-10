#ifndef _ROS_mapnav_msgs_ModifyMap_h
#define _ROS_mapnav_msgs_ModifyMap_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Point.h"

namespace mapnav_msgs
{

  class ModifyMap : public ros::Msg
  {
    public:
      uint8_t region_length;
      geometry_msgs::Point st_region;
      geometry_msgs::Point * region;
      int32_t maskAction;
      int32_t mapLayer;
      enum { FREE =  0           };
      enum { BLOCKED =  100        };
      enum { OBSTACLE =  99       };
      enum { NOT_MASKED =  -1      };
      enum { SET_FREE =  0        };
      enum { SET_BLOCKED =  100        };
      enum { SET_OBSTACLE =  99      };

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = region_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < region_length; i++){
      offset += this->region[i].serialize(outbuffer + offset);
      }
      union {
        int32_t real;
        uint32_t base;
      } u_maskAction;
      u_maskAction.real = this->maskAction;
      *(outbuffer + offset + 0) = (u_maskAction.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_maskAction.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_maskAction.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_maskAction.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->maskAction);
      union {
        int32_t real;
        uint32_t base;
      } u_mapLayer;
      u_mapLayer.real = this->mapLayer;
      *(outbuffer + offset + 0) = (u_mapLayer.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mapLayer.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_mapLayer.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_mapLayer.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mapLayer);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t region_lengthT = *(inbuffer + offset++);
      if(region_lengthT > region_length)
        this->region = (geometry_msgs::Point*)realloc(this->region, region_lengthT * sizeof(geometry_msgs::Point));
      offset += 3;
      region_length = region_lengthT;
      for( uint8_t i = 0; i < region_length; i++){
      offset += this->st_region.deserialize(inbuffer + offset);
        memcpy( &(this->region[i]), &(this->st_region), sizeof(geometry_msgs::Point));
      }
      union {
        int32_t real;
        uint32_t base;
      } u_maskAction;
      u_maskAction.base = 0;
      u_maskAction.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_maskAction.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_maskAction.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_maskAction.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->maskAction = u_maskAction.real;
      offset += sizeof(this->maskAction);
      union {
        int32_t real;
        uint32_t base;
      } u_mapLayer;
      u_mapLayer.base = 0;
      u_mapLayer.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mapLayer.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_mapLayer.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_mapLayer.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->mapLayer = u_mapLayer.real;
      offset += sizeof(this->mapLayer);
     return offset;
    }

    const char * getType(){ return "mapnav_msgs/ModifyMap"; };
    const char * getMD5(){ return "d6e3111d8e8e68b7ee7afcb40ed8e3d9"; };

  };

}
#endif