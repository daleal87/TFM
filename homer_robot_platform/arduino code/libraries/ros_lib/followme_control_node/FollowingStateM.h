#ifndef _ROS_followme_control_node_FollowingStateM_h
#define _ROS_followme_control_node_FollowingStateM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "people_tracking_msgs/TrackedPerson.h"

namespace followme_control_node
{

  class FollowingStateM : public ros::Msg
  {
    public:
      people_tracking_msgs::TrackedPerson tracked_operator;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->tracked_operator.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->tracked_operator.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "followme_control_node/FollowingStateM"; };
    const char * getMD5(){ return "563e19eb506c7f059c4893dfd25ddcb6"; };

  };

}
#endif