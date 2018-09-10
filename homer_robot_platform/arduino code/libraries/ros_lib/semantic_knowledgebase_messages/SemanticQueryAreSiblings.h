#ifndef _ROS_SERVICE_SemanticQueryAreSiblings_h
#define _ROS_SERVICE_SemanticQueryAreSiblings_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace semantic_knowledgebase_messages
{

static const char SEMANTICQUERYARESIBLINGS[] = "semantic_knowledgebase_messages/SemanticQueryAreSiblings";

  class SemanticQueryAreSiblingsRequest : public ros::Msg
  {
    public:
      const char* node1;
      const char* node2;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_node1 = strlen(this->node1);
      memcpy(outbuffer + offset, &length_node1, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->node1, length_node1);
      offset += length_node1;
      uint32_t length_node2 = strlen(this->node2);
      memcpy(outbuffer + offset, &length_node2, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->node2, length_node2);
      offset += length_node2;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_node1;
      memcpy(&length_node1, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_node1; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_node1-1]=0;
      this->node1 = (char *)(inbuffer + offset-1);
      offset += length_node1;
      uint32_t length_node2;
      memcpy(&length_node2, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_node2; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_node2-1]=0;
      this->node2 = (char *)(inbuffer + offset-1);
      offset += length_node2;
     return offset;
    }

    const char * getType(){ return SEMANTICQUERYARESIBLINGS; };
    const char * getMD5(){ return "0934ea5b9db4d2f55173e3afba924372"; };

  };

  class SemanticQueryAreSiblingsResponse : public ros::Msg
  {
    public:
      bool result;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.real = this->result;
      *(outbuffer + offset + 0) = (u_result.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.base = 0;
      u_result.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->result = u_result.real;
      offset += sizeof(this->result);
     return offset;
    }

    const char * getType(){ return SEMANTICQUERYARESIBLINGS; };
    const char * getMD5(){ return "eb13ac1f1354ccecb7941ee8fa2192e8"; };

  };

  class SemanticQueryAreSiblings {
    public:
    typedef SemanticQueryAreSiblingsRequest Request;
    typedef SemanticQueryAreSiblingsResponse Response;
  };

}
#endif
