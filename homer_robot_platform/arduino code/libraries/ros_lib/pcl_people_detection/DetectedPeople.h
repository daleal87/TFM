#ifndef _ROS_pcl_people_detection_DetectedPeople_h
#define _ROS_pcl_people_detection_DetectedPeople_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "pcl_people_detection/DetectedPerson.h"

namespace pcl_people_detection
{

  class DetectedPeople : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t people_length;
      pcl_people_detection::DetectedPerson st_people;
      pcl_people_detection::DetectedPerson * people;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = people_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < people_length; i++){
      offset += this->people[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t people_lengthT = *(inbuffer + offset++);
      if(people_lengthT > people_length)
        this->people = (pcl_people_detection::DetectedPerson*)realloc(this->people, people_lengthT * sizeof(pcl_people_detection::DetectedPerson));
      offset += 3;
      people_length = people_lengthT;
      for( uint8_t i = 0; i < people_length; i++){
      offset += this->st_people.deserialize(inbuffer + offset);
        memcpy( &(this->people[i]), &(this->st_people), sizeof(pcl_people_detection::DetectedPerson));
      }
     return offset;
    }

    const char * getType(){ return "pcl_people_detection/DetectedPeople"; };
    const char * getMD5(){ return "db466ad24cf2925b0c2e89c69c4d74c1"; };

  };

}
#endif