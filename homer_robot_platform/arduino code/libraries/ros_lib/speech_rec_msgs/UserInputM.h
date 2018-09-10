#ifndef _ROS_speech_rec_msgs_UserInputM_h
#define _ROS_speech_rec_msgs_UserInputM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace speech_rec_msgs
{

  class UserInputM : public ros::Msg
  {
    public:
      const char* recognition;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_recognition = strlen(this->recognition);
      memcpy(outbuffer + offset, &length_recognition, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->recognition, length_recognition);
      offset += length_recognition;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_recognition;
      memcpy(&length_recognition, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_recognition; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_recognition-1]=0;
      this->recognition = (char *)(inbuffer + offset-1);
      offset += length_recognition;
     return offset;
    }

    const char * getType(){ return "speech_rec_msgs/UserInputM"; };
    const char * getMD5(){ return "dcd8702e822d2926d34ac6ea523ac2ce"; };

  };

}
#endif