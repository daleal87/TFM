#ifndef _ROS_SERVICE_SemanticQueryAllParents_h
#define _ROS_SERVICE_SemanticQueryAllParents_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace semantic_knowledgebase_messages
{

static const char SEMANTICQUERYALLPARENTS[] = "semantic_knowledgebase_messages/SemanticQueryAllParents";

  class SemanticQueryAllParentsRequest : public ros::Msg
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

    const char * getType(){ return SEMANTICQUERYALLPARENTS; };
    const char * getMD5(){ return "482f538f6e86e071cca0a365ab1e82f3"; };

  };

  class SemanticQueryAllParentsResponse : public ros::Msg
  {
    public:
      uint8_t parents_length;
      char* st_parents;
      char* * parents;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = parents_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < parents_length; i++){
      uint32_t length_parentsi = strlen(this->parents[i]);
      memcpy(outbuffer + offset, &length_parentsi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->parents[i], length_parentsi);
      offset += length_parentsi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t parents_lengthT = *(inbuffer + offset++);
      if(parents_lengthT > parents_length)
        this->parents = (char**)realloc(this->parents, parents_lengthT * sizeof(char*));
      offset += 3;
      parents_length = parents_lengthT;
      for( uint8_t i = 0; i < parents_length; i++){
      uint32_t length_st_parents;
      memcpy(&length_st_parents, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_parents; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_parents-1]=0;
      this->st_parents = (char *)(inbuffer + offset-1);
      offset += length_st_parents;
        memcpy( &(this->parents[i]), &(this->st_parents), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return SEMANTICQUERYALLPARENTS; };
    const char * getMD5(){ return "93e2481a73cf2266a4bcebeb832b0595"; };

  };

  class SemanticQueryAllParents {
    public:
    typedef SemanticQueryAllParentsRequest Request;
    typedef SemanticQueryAllParentsResponse Response;
  };

}
#endif
