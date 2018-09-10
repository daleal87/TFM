#ifndef _ROS_or_msgs_VectorObject2D_h
#define _ROS_or_msgs_VectorObject2D_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "or_msgs/Point2D.h"

namespace or_msgs
{

  class VectorObject2D : public ros::Msg
  {
    public:
      uint8_t vertices_length;
      or_msgs::Point2D st_vertices;
      or_msgs::Point2D * vertices;
      float r;
      float g;
      float b;
      float line_width;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = vertices_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < vertices_length; i++){
      offset += this->vertices[i].serialize(outbuffer + offset);
      }
      union {
        float real;
        uint32_t base;
      } u_r;
      u_r.real = this->r;
      *(outbuffer + offset + 0) = (u_r.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_r.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_r.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_r.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->r);
      union {
        float real;
        uint32_t base;
      } u_g;
      u_g.real = this->g;
      *(outbuffer + offset + 0) = (u_g.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_g.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_g.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_g.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->g);
      union {
        float real;
        uint32_t base;
      } u_b;
      u_b.real = this->b;
      *(outbuffer + offset + 0) = (u_b.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_b.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_b.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_b.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->b);
      union {
        float real;
        uint32_t base;
      } u_line_width;
      u_line_width.real = this->line_width;
      *(outbuffer + offset + 0) = (u_line_width.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_line_width.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_line_width.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_line_width.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->line_width);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t vertices_lengthT = *(inbuffer + offset++);
      if(vertices_lengthT > vertices_length)
        this->vertices = (or_msgs::Point2D*)realloc(this->vertices, vertices_lengthT * sizeof(or_msgs::Point2D));
      offset += 3;
      vertices_length = vertices_lengthT;
      for( uint8_t i = 0; i < vertices_length; i++){
      offset += this->st_vertices.deserialize(inbuffer + offset);
        memcpy( &(this->vertices[i]), &(this->st_vertices), sizeof(or_msgs::Point2D));
      }
      union {
        float real;
        uint32_t base;
      } u_r;
      u_r.base = 0;
      u_r.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_r.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_r.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_r.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->r = u_r.real;
      offset += sizeof(this->r);
      union {
        float real;
        uint32_t base;
      } u_g;
      u_g.base = 0;
      u_g.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_g.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_g.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_g.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->g = u_g.real;
      offset += sizeof(this->g);
      union {
        float real;
        uint32_t base;
      } u_b;
      u_b.base = 0;
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->b = u_b.real;
      offset += sizeof(this->b);
      union {
        float real;
        uint32_t base;
      } u_line_width;
      u_line_width.base = 0;
      u_line_width.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_line_width.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_line_width.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_line_width.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->line_width = u_line_width.real;
      offset += sizeof(this->line_width);
     return offset;
    }

    const char * getType(){ return "or_msgs/VectorObject2D"; };
    const char * getMD5(){ return "a37e6e904a8e07121b6ba2f47eaee96a"; };

  };

}
#endif