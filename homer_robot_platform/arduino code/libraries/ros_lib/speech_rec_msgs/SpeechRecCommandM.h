#ifndef _ROS_speech_rec_msgs_SpeechRecCommandM_h
#define _ROS_speech_rec_msgs_SpeechRecCommandM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace speech_rec_msgs
{

  class SpeechRecCommandM : public ros::Msg
  {
    public:
      int8_t command;
      const char* speechFile;
      enum { Calibrate = 0 };
      enum { Activate = 1 };
      enum { Deactivate = 2 };
      enum { ReadFromFile = 3 };
      enum { ReinitializeSpeechFile = 4 };

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_command;
      u_command.real = this->command;
      *(outbuffer + offset + 0) = (u_command.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->command);
      uint32_t length_speechFile = strlen(this->speechFile);
      memcpy(outbuffer + offset, &length_speechFile, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->speechFile, length_speechFile);
      offset += length_speechFile;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_command;
      u_command.base = 0;
      u_command.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->command = u_command.real;
      offset += sizeof(this->command);
      uint32_t length_speechFile;
      memcpy(&length_speechFile, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_speechFile; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_speechFile-1]=0;
      this->speechFile = (char *)(inbuffer + offset-1);
      offset += length_speechFile;
     return offset;
    }

    const char * getType(){ return "speech_rec_msgs/SpeechRecCommandM"; };
    const char * getMD5(){ return "4122c7b64ff3cd838fb761959aedaf38"; };

  };

}
#endif