#ifndef _ROS_SERVICE_SemanticQueryDirectParent_h
#define _ROS_SERVICE_SemanticQueryDirectParent_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace semantic_knowledgebase_messages
{

static const char SEMANTICQUERYDIRECTPARENT[] = "semantic_knowledgebase_messages/SemanticQueryDirectParent";

  class SemanticQueryDirectParentRequest : public ros::Msg
  {
    public:
      const char* child;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_child = strlen(this->child);
      memcpy(outbuffer + offset, &length_child, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->child, length_child);
      offset += length_child;
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
     return offset;
    }

    const char * getType(){ return SEMANTICQUERYDIRECTPARENT; };
    const char * getMD5(){ return "482f538f6e86e071cca0a365ab1e82f3"; };

  };

  class SemanticQueryDirectParentResponse : public ros::Msg
  {
    public:
      const char* parent;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
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

    const char * getType(){ return SEMANTICQUERYDIRECTPARENT; };
    const char * getMD5(){ return "2bd90c00241b835336402ad130902710"; };

  };

  class SemanticQueryDirectParent {
    public:
    typedef SemanticQueryDirectParentRequest Request;
    typedef SemanticQueryDirectParentResponse Response;
  };

}
#endif
