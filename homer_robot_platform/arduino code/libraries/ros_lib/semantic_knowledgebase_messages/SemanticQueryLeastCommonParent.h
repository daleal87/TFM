#ifndef _ROS_SERVICE_SemanticQueryLeastCommonParent_h
#define _ROS_SERVICE_SemanticQueryLeastCommonParent_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace semantic_knowledgebase_messages
{

static const char SEMANTICQUERYLEASTCOMMONPARENT[] = "semantic_knowledgebase_messages/SemanticQueryLeastCommonParent";

  class SemanticQueryLeastCommonParentRequest : public ros::Msg
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

    const char * getType(){ return SEMANTICQUERYLEASTCOMMONPARENT; };
    const char * getMD5(){ return "0934ea5b9db4d2f55173e3afba924372"; };

  };

  class SemanticQueryLeastCommonParentResponse : public ros::Msg
  {
    public:
      const char* commonParent;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_commonParent = strlen(this->commonParent);
      memcpy(outbuffer + offset, &length_commonParent, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->commonParent, length_commonParent);
      offset += length_commonParent;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_commonParent;
      memcpy(&length_commonParent, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_commonParent; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_commonParent-1]=0;
      this->commonParent = (char *)(inbuffer + offset-1);
      offset += length_commonParent;
     return offset;
    }

    const char * getType(){ return SEMANTICQUERYLEASTCOMMONPARENT; };
    const char * getMD5(){ return "8a47a1933028d5d597db61b15627df0c"; };

  };

  class SemanticQueryLeastCommonParent {
    public:
    typedef SemanticQueryLeastCommonParentRequest Request;
    typedef SemanticQueryLeastCommonParentResponse Response;
  };

}
#endif
