#ifndef _ROS_SERVICE_SemanticQueryIsDirectChild_h
#define _ROS_SERVICE_SemanticQueryIsDirectChild_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace semantic_knowledgebase_messages
{

static const char SEMANTICQUERYISDIRECTCHILD[] = "semantic_knowledgebase_messages/SemanticQueryIsDirectChild";

  class SemanticQueryIsDirectChildRequest : public ros::Msg
  {
    public:
      const char* child;
      const char* parent;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_child = strlen(this->child);
      memcpy(outbuffer + offset, &length_child, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->child, length_child);
      offset += length_child;
      uint32_t length_parent = strlen(this->parent);
      memcpy(outbuffer + offset, &length_parent, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->parent, length_parent);
      offset += length_parent;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_child;
      memcpy(&length_child, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_child; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_child-1]=0;
      this->child = (char *)(inbuffer + offset-1);
      offset += length_child;
      uint32_t length_parent;
      memcpy(&length_parent, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_parent; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_parent-1]=0;
      this->parent = (char *)(inbuffer + offset-1);
      offset += length_parent;
     return offset;
    }

    const char * getType(){ return SEMANTICQUERYISDIRECTCHILD; };
    const char * getMD5(){ return "97b5d37812c0ed48c761edb7c17bdf4d"; };

  };

  class SemanticQueryIsDirectChildResponse : public ros::Msg
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

    const char * getType(){ return SEMANTICQUERYISDIRECTCHILD; };
    const char * getMD5(){ return "eb13ac1f1354ccecb7941ee8fa2192e8"; };

  };

  class SemanticQueryIsDirectChild {
    public:
    typedef SemanticQueryIsDirectChildRequest Request;
    typedef SemanticQueryIsDirectChildResponse Response;
  };

}
#endif
