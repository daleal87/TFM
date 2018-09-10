#ifndef _ROS_katana_gripping_msgs_SetArmPose_h
#define _ROS_katana_gripping_msgs_SetArmPose_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace katana_gripping_msgs
{

  class SetArmPose : public ros::Msg
  {
    public:
      float ax0;
      float ax1;
      float ax2;
      float ax3;
      float ax4;
      float ax5;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_ax0;
      u_ax0.real = this->ax0;
      *(outbuffer + offset + 0) = (u_ax0.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ax0.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ax0.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ax0.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ax0);
      union {
        float real;
        uint32_t base;
      } u_ax1;
      u_ax1.real = this->ax1;
      *(outbuffer + offset + 0) = (u_ax1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ax1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ax1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ax1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ax1);
      union {
        float real;
        uint32_t base;
      } u_ax2;
      u_ax2.real = this->ax2;
      *(outbuffer + offset + 0) = (u_ax2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ax2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ax2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ax2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ax2);
      union {
        float real;
        uint32_t base;
      } u_ax3;
      u_ax3.real = this->ax3;
      *(outbuffer + offset + 0) = (u_ax3.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ax3.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ax3.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ax3.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ax3);
      union {
        float real;
        uint32_t base;
      } u_ax4;
      u_ax4.real = this->ax4;
      *(outbuffer + offset + 0) = (u_ax4.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ax4.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ax4.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ax4.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ax4);
      union {
        float real;
        uint32_t base;
      } u_ax5;
      u_ax5.real = this->ax5;
      *(outbuffer + offset + 0) = (u_ax5.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ax5.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ax5.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ax5.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ax5);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_ax0;
      u_ax0.base = 0;
      u_ax0.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ax0.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ax0.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ax0.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ax0 = u_ax0.real;
      offset += sizeof(this->ax0);
      union {
        float real;
        uint32_t base;
      } u_ax1;
      u_ax1.base = 0;
      u_ax1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ax1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ax1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ax1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ax1 = u_ax1.real;
      offset += sizeof(this->ax1);
      union {
        float real;
        uint32_t base;
      } u_ax2;
      u_ax2.base = 0;
      u_ax2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ax2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ax2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ax2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ax2 = u_ax2.real;
      offset += sizeof(this->ax2);
      union {
        float real;
        uint32_t base;
      } u_ax3;
      u_ax3.base = 0;
      u_ax3.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ax3.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ax3.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ax3.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ax3 = u_ax3.real;
      offset += sizeof(this->ax3);
      union {
        float real;
        uint32_t base;
      } u_ax4;
      u_ax4.base = 0;
      u_ax4.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ax4.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ax4.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ax4.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ax4 = u_ax4.real;
      offset += sizeof(this->ax4);
      union {
        float real;
        uint32_t base;
      } u_ax5;
      u_ax5.base = 0;
      u_ax5.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ax5.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ax5.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ax5.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ax5 = u_ax5.real;
      offset += sizeof(this->ax5);
     return offset;
    }

    const char * getType(){ return "katana_gripping_msgs/SetArmPose"; };
    const char * getMD5(){ return "ffa8d3224cedcb8dba9ce2d44a14e233"; };

  };

}
#endif