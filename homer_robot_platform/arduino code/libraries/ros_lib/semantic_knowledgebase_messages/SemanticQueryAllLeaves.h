#ifndef _ROS_SERVICE_SemanticQueryAllLeaves_h
#define _ROS_SERVICE_SemanticQueryAllLeaves_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace semantic_knowledgebase_messages
{

static const char SEMANTICQUERYALLLEAVES[] = "semantic_knowledgebase_messages/SemanticQueryAllLeaves";

  class SemanticQueryAllLeavesRequest : public ros::Msg
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

    const char * getType(){ return SEMANTICQUERYALLLEAVES; };
    const char * getMD5(){ return "2bd90c00241b835336402ad130902710"; };

  };

  class SemanticQueryAllLeavesResponse : public ros::Msg
  {
    public:
      uint8_t leaves_length;
      char* st_leaves;
      char* * leaves;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = leaves_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < leaves_length; i++){
      uint32_t length_leavesi = strlen(this->leaves[i]);
      memcpy(outbuffer + offset, &length_leavesi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->leaves[i], length_leavesi);
      offset += length_leavesi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t leaves_lengthT = *(inbuffer + offset++);
      if(leaves_lengthT > leaves_length)
        this->leaves = (char**)realloc(this->leaves, leaves_lengthT * sizeof(char*));
      offset += 3;
      leaves_length = leaves_lengthT;
      for( uint8_t i = 0; i < leaves_length; i++){
      uint32_t length_st_leaves;
      memcpy(&length_st_leaves, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_leaves; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_leaves-1]=0;
      this->st_leaves = (char *)(inbuffer + offset-1);
      offset += length_st_leaves;
        memcpy( &(this->leaves[i]), &(this->st_leaves), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return SEMANTICQUERYALLLEAVES; };
    const char * getMD5(){ return "5f566d64a0bf83a8939ac7c4e8fe060b"; };

  };

  class SemanticQueryAllLeaves {
    public:
    typedef SemanticQueryAllLeavesRequest Request;
    typedef SemanticQueryAllLeavesResponse Response;
  };

}
#endif
