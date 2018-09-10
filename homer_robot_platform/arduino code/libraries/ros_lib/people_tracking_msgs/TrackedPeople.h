#ifndef _ROS_people_tracking_msgs_TrackedPeople_h
#define _ROS_people_tracking_msgs_TrackedPeople_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "people_tracking_msgs/TrackedPerson.h"

namespace people_tracking_msgs
{

  class TrackedPeople : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t trackedPersons_length;
      people_tracking_msgs::TrackedPerson st_trackedPersons;
      people_tracking_msgs::TrackedPerson * trackedPersons;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = trackedPersons_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < trackedPersons_length; i++){
      offset += this->trackedPersons[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t trackedPersons_lengthT = *(inbuffer + offset++);
      if(trackedPersons_lengthT > trackedPersons_length)
        this->trackedPersons = (people_tracking_msgs::TrackedPerson*)realloc(this->trackedPersons, trackedPersons_lengthT * sizeof(people_tracking_msgs::TrackedPerson));
      offset += 3;
      trackedPersons_length = trackedPersons_lengthT;
      for( uint8_t i = 0; i < trackedPersons_length; i++){
      offset += this->st_trackedPersons.deserialize(inbuffer + offset);
        memcpy( &(this->trackedPersons[i]), &(this->st_trackedPersons), sizeof(people_tracking_msgs::TrackedPerson));
      }
     return offset;
    }

    const char * getType(){ return "people_tracking_msgs/TrackedPeople"; };
    const char * getMD5(){ return "e2134a46f4fd02776383523e275e1de2"; };

  };

}
#endif