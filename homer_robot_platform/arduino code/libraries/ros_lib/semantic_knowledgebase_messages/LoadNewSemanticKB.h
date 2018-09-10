#ifndef _ROS_SERVICE_LoadNewSemanticKB_h
#define _ROS_SERVICE_LoadNewSemanticKB_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace semantic_knowledgebase_messages
{

static const char LOADNEWSEMANTICKB[] = "semantic_knowledgebase_messages/LoadNewSemanticKB";

  class LoadNewSemanticKBRequest : public ros::Msg
  {
    public:
      const char* path;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_path = strlen(this->path);
      memcpy(outbuffer + offset, &length_path, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->path, length_path);
      offset += length_path;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_path;
      memcpy(&length_path, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_path; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_path-1]=0;
      this->path = (char *)(inbuffer + offset-1);
      offset += length_path;
     return offset;
    }

    const char * getType(){ return LOADNEWSEMANTICKB; };
    const char * getMD5(){ return "1d00cd540af97efeb6b1589112fab63e"; };

  };

  class LoadNewSemanticKBResponse : public ros::Msg
  {
    public:
      bool succes;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_succes;
      u_succes.real = this->succes;
      *(outbuffer + offset + 0) = (u_succes.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->succes);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_succes;
      u_succes.base = 0;
      u_succes.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->succes = u_succes.real;
      offset += sizeof(this->succes);
     return offset;
    }

    const char * getType(){ return LOADNEWSEMANTICKB; };
    const char * getMD5(){ return "509793171e494962cd366ecf60e100e4"; };

  };

  class LoadNewSemanticKB {
    public:
    typedef LoadNewSemanticKBRequest Request;
    typedef LoadNewSemanticKBResponse Response;
  };

}
#endif
