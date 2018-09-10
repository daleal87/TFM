#ifndef _ROS_SERVICE_SemanticQuery_h
#define _ROS_SERVICE_SemanticQuery_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace semantic_knowledgebase_messages
{

static const char SEMANTICQUERY[] = "semantic_knowledgebase_messages/SemanticQuery";

  class SemanticQueryRequest : public ros::Msg
  {
    public:
      int8_t querytype;
      const char* node;
      const char* child;
      enum { EXISTS = 0 };
      enum { IS_DIRECT_CHILD_OF = 1 };
      enum { IS_CHILD_OF = 2 };
      enum { DIRECT_PARENT = 3 };
      enum { ALL_PARENTS = 4 };
      enum { ALL_DIRECT_CHILDREN = 5 };
      enum { ALL_CHILDREN = 6 };
      enum { ALL_SIBLINGS = 7 };
      enum { LEAST_COMMON_PARENT = 8 };
      enum { ARE_SIBLINGS = 9 };
      enum { IS_LEAF = 10 };
      enum { ALL_LEAVES = 11 };

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_querytype;
      u_querytype.real = this->querytype;
      *(outbuffer + offset + 0) = (u_querytype.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->querytype);
      uint32_t length_node = strlen(this->node);
      memcpy(outbuffer + offset, &length_node, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->node, length_node);
      offset += length_node;
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
      union {
        int8_t real;
        uint8_t base;
      } u_querytype;
      u_querytype.base = 0;
      u_querytype.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->querytype = u_querytype.real;
      offset += sizeof(this->querytype);
      uint32_t length_node;
      memcpy(&length_node, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_node; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_node-1]=0;
      this->node = (char *)(inbuffer + offset-1);
      offset += length_node;
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

    const char * getType(){ return SEMANTICQUERY; };
    const char * getMD5(){ return "84652f3ddd85cdf6cf35d05b585fdfd0"; };

  };

  class SemanticQueryResponse : public ros::Msg
  {
    public:
      bool result;
      uint8_t nodes_length;
      char* st_nodes;
      char* * nodes;

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
      *(outbuffer + offset++) = nodes_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < nodes_length; i++){
      uint32_t length_nodesi = strlen(this->nodes[i]);
      memcpy(outbuffer + offset, &length_nodesi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->nodes[i], length_nodesi);
      offset += length_nodesi;
      }
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
      uint8_t nodes_lengthT = *(inbuffer + offset++);
      if(nodes_lengthT > nodes_length)
        this->nodes = (char**)realloc(this->nodes, nodes_lengthT * sizeof(char*));
      offset += 3;
      nodes_length = nodes_lengthT;
      for( uint8_t i = 0; i < nodes_length; i++){
      uint32_t length_st_nodes;
      memcpy(&length_st_nodes, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_nodes; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_nodes-1]=0;
      this->st_nodes = (char *)(inbuffer + offset-1);
      offset += length_st_nodes;
        memcpy( &(this->nodes[i]), &(this->st_nodes), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return SEMANTICQUERY; };
    const char * getMD5(){ return "be6e8076f0259c5da0d2f7a2d9c03073"; };

  };

  class SemanticQuery {
    public:
    typedef SemanticQueryRequest Request;
    typedef SemanticQueryResponse Response;
  };

}
#endif
