#ifndef _ROS_SERVICE_SemanticQueryAllSiblings_h
#define _ROS_SERVICE_SemanticQueryAllSiblings_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace semantic_knowledgebase_messages
{

static const char SEMANTICQUERYALLSIBLINGS[] = "semantic_knowledgebase_messages/SemanticQueryAllSiblings";

  class SemanticQueryAllSiblingsRequest : public ros::Msg
  {
    public:
      const char* node;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_node = strlen(this->node);
      memcpy(outbuffer + offset, &length_node, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->node, length_node);
      offset += length_node;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_node;
      memcpy(&length_node, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_node; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_node-1]=0;
      this->node = (char *)(inbuffer + offset-1);
      offset += length_node;
     return offset;
    }

    const char * getType(){ return SEMANTICQUERYALLSIBLINGS; };
    const char * getMD5(){ return "a94c40e70a4b82863e6e52ec16732447"; };

  };

  class SemanticQueryAllSiblingsResponse : public ros::Msg
  {
    public:
      uint8_t siblings_length;
      char* st_siblings;
      char* * siblings;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = siblings_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < siblings_length; i++){
      uint32_t length_siblingsi = strlen(this->siblings[i]);
      memcpy(outbuffer + offset, &length_siblingsi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->siblings[i], length_siblingsi);
      offset += length_siblingsi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t siblings_lengthT = *(inbuffer + offset++);
      if(siblings_lengthT > siblings_length)
        this->siblings = (char**)realloc(this->siblings, siblings_lengthT * sizeof(char*));
      offset += 3;
      siblings_length = siblings_lengthT;
      for( uint8_t i = 0; i < siblings_length; i++){
      uint32_t length_st_siblings;
      memcpy(&length_st_siblings, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_siblings; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_siblings-1]=0;
      this->st_siblings = (char *)(inbuffer + offset-1);
      offset += length_st_siblings;
        memcpy( &(this->siblings[i]), &(this->st_siblings), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return SEMANTICQUERYALLSIBLINGS; };
    const char * getMD5(){ return "f34ee923c6e619fcd3ace449c1191324"; };

  };

  class SemanticQueryAllSiblings {
    public:
    typedef SemanticQueryAllSiblingsRequest Request;
    typedef SemanticQueryAllSiblingsResponse Response;
  };

}
#endif
