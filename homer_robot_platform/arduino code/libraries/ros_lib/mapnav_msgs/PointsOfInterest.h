#ifndef _ROS_mapnav_msgs_PointsOfInterest_h
#define _ROS_mapnav_msgs_PointsOfInterest_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "mapnav_msgs/PointOfInterest.h"

namespace mapnav_msgs
{

  class PointsOfInterest : public ros::Msg
  {
    public:
      uint8_t pois_length;
      mapnav_msgs::PointOfInterest st_pois;
      mapnav_msgs::PointOfInterest * pois;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = pois_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < pois_length; i++){
      offset += this->pois[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t pois_lengthT = *(inbuffer + offset++);
      if(pois_lengthT > pois_length)
        this->pois = (mapnav_msgs::PointOfInterest*)realloc(this->pois, pois_lengthT * sizeof(mapnav_msgs::PointOfInterest));
      offset += 3;
      pois_length = pois_lengthT;
      for( uint8_t i = 0; i < pois_length; i++){
      offset += this->st_pois.deserialize(inbuffer + offset);
        memcpy( &(this->pois[i]), &(this->st_pois), sizeof(mapnav_msgs::PointOfInterest));
      }
     return offset;
    }

    const char * getType(){ return "mapnav_msgs/PointsOfInterest"; };
    const char * getMD5(){ return "8e4aec1e05985ea9759c21f572472fd3"; };

  };

}
#endif