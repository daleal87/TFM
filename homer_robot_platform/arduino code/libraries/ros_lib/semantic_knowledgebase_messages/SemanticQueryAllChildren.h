#ifndef _ROS_SERVICE_SemanticQueryAllChildren_h
#define _ROS_SERVICE_SemanticQueryAllChildren_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace semantic_knowledgebase_messages
{

static const char SEMANTICQUERYALLCHILDREN[] = "semantic_knowledgebase_messages/SemanticQueryAllChildren";

  class SemanticQueryAllChildrenRequest : public ros::Msg
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

    const char * getType(){ return SEMANTICQUERYALLCHILDREN; };
    const char * getMD5(){ return "2bd90c00241b835336402ad130902710"; };

  };

  class SemanticQueryAllChildrenResponse : public ros::Msg
  {
    public:
      uint8_t children_length;
      char* st_children;
      char* * children;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = children_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < children_length; i++){
      uint32_t length_childreni = strlen(this->children[i]);
      memcpy(outbuffer + offset, &length_childreni, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->children[i], length_childreni);
      offset += length_childreni;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t children_lengthT = *(inbuffer + offset++);
      if(children_lengthT > children_length)
        this->children = (char**)realloc(this->children, children_lengthT * sizeof(char*));
      offset += 3;
      children_length = children_lengthT;
      for( uint8_t i = 0; i < children_length; i++){
      uint32_t length_st_children;
      memcpy(&length_st_children, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_children; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_children-1]=0;
      this->st_children = (char *)(inbuffer + offset-1);
      offset += length_st_children;
        memcpy( &(this->children[i]), &(this->st_children), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return SEMANTICQUERYALLCHILDREN; };
    const char * getMD5(){ return "128eb51923c3f2d8579f5d26b7b8fdcb"; };

  };

  class SemanticQueryAllChildren {
    public:
    typedef SemanticQueryAllChildrenRequest Request;
    typedef SemanticQueryAllChildrenResponse Response;
  };

}
#endif
