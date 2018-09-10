#ifndef _ROS_ptu_person_detection_ptu_detected_persons_h
#define _ROS_ptu_person_detection_ptu_detected_persons_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ptu_person_detection
{

  class ptu_detected_persons : public ros::Msg
  {
    public:
      uint8_t headX_length;
      float st_headX;
      float * headX;
      uint8_t headY_length;
      float st_headY;
      float * headY;
      uint8_t headZ_length;
      float st_headZ;
      float * headZ;
      uint8_t handX_length;
      float st_handX;
      float * handX;
      uint8_t handY_length;
      float st_handY;
      float * handY;
      uint8_t handZ_length;
      float st_handZ;
      float * handZ;
      uint8_t headWithHandX_length;
      float st_headWithHandX;
      float * headWithHandX;
      uint8_t headWithHandY_length;
      float st_headWithHandY;
      float * headWithHandY;
      uint8_t headWithHandZ_length;
      float st_headWithHandZ;
      float * headWithHandZ;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = headX_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < headX_length; i++){
      union {
        float real;
        uint32_t base;
      } u_headXi;
      u_headXi.real = this->headX[i];
      *(outbuffer + offset + 0) = (u_headXi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_headXi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_headXi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_headXi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->headX[i]);
      }
      *(outbuffer + offset++) = headY_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < headY_length; i++){
      union {
        float real;
        uint32_t base;
      } u_headYi;
      u_headYi.real = this->headY[i];
      *(outbuffer + offset + 0) = (u_headYi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_headYi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_headYi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_headYi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->headY[i]);
      }
      *(outbuffer + offset++) = headZ_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < headZ_length; i++){
      union {
        float real;
        uint32_t base;
      } u_headZi;
      u_headZi.real = this->headZ[i];
      *(outbuffer + offset + 0) = (u_headZi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_headZi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_headZi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_headZi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->headZ[i]);
      }
      *(outbuffer + offset++) = handX_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < handX_length; i++){
      union {
        float real;
        uint32_t base;
      } u_handXi;
      u_handXi.real = this->handX[i];
      *(outbuffer + offset + 0) = (u_handXi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_handXi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_handXi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_handXi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->handX[i]);
      }
      *(outbuffer + offset++) = handY_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < handY_length; i++){
      union {
        float real;
        uint32_t base;
      } u_handYi;
      u_handYi.real = this->handY[i];
      *(outbuffer + offset + 0) = (u_handYi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_handYi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_handYi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_handYi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->handY[i]);
      }
      *(outbuffer + offset++) = handZ_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < handZ_length; i++){
      union {
        float real;
        uint32_t base;
      } u_handZi;
      u_handZi.real = this->handZ[i];
      *(outbuffer + offset + 0) = (u_handZi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_handZi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_handZi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_handZi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->handZ[i]);
      }
      *(outbuffer + offset++) = headWithHandX_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < headWithHandX_length; i++){
      union {
        float real;
        uint32_t base;
      } u_headWithHandXi;
      u_headWithHandXi.real = this->headWithHandX[i];
      *(outbuffer + offset + 0) = (u_headWithHandXi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_headWithHandXi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_headWithHandXi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_headWithHandXi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->headWithHandX[i]);
      }
      *(outbuffer + offset++) = headWithHandY_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < headWithHandY_length; i++){
      union {
        float real;
        uint32_t base;
      } u_headWithHandYi;
      u_headWithHandYi.real = this->headWithHandY[i];
      *(outbuffer + offset + 0) = (u_headWithHandYi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_headWithHandYi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_headWithHandYi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_headWithHandYi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->headWithHandY[i]);
      }
      *(outbuffer + offset++) = headWithHandZ_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < headWithHandZ_length; i++){
      union {
        float real;
        uint32_t base;
      } u_headWithHandZi;
      u_headWithHandZi.real = this->headWithHandZ[i];
      *(outbuffer + offset + 0) = (u_headWithHandZi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_headWithHandZi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_headWithHandZi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_headWithHandZi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->headWithHandZ[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t headX_lengthT = *(inbuffer + offset++);
      if(headX_lengthT > headX_length)
        this->headX = (float*)realloc(this->headX, headX_lengthT * sizeof(float));
      offset += 3;
      headX_length = headX_lengthT;
      for( uint8_t i = 0; i < headX_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_headX;
      u_st_headX.base = 0;
      u_st_headX.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_headX.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_headX.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_headX.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_headX = u_st_headX.real;
      offset += sizeof(this->st_headX);
        memcpy( &(this->headX[i]), &(this->st_headX), sizeof(float));
      }
      uint8_t headY_lengthT = *(inbuffer + offset++);
      if(headY_lengthT > headY_length)
        this->headY = (float*)realloc(this->headY, headY_lengthT * sizeof(float));
      offset += 3;
      headY_length = headY_lengthT;
      for( uint8_t i = 0; i < headY_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_headY;
      u_st_headY.base = 0;
      u_st_headY.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_headY.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_headY.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_headY.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_headY = u_st_headY.real;
      offset += sizeof(this->st_headY);
        memcpy( &(this->headY[i]), &(this->st_headY), sizeof(float));
      }
      uint8_t headZ_lengthT = *(inbuffer + offset++);
      if(headZ_lengthT > headZ_length)
        this->headZ = (float*)realloc(this->headZ, headZ_lengthT * sizeof(float));
      offset += 3;
      headZ_length = headZ_lengthT;
      for( uint8_t i = 0; i < headZ_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_headZ;
      u_st_headZ.base = 0;
      u_st_headZ.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_headZ.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_headZ.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_headZ.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_headZ = u_st_headZ.real;
      offset += sizeof(this->st_headZ);
        memcpy( &(this->headZ[i]), &(this->st_headZ), sizeof(float));
      }
      uint8_t handX_lengthT = *(inbuffer + offset++);
      if(handX_lengthT > handX_length)
        this->handX = (float*)realloc(this->handX, handX_lengthT * sizeof(float));
      offset += 3;
      handX_length = handX_lengthT;
      for( uint8_t i = 0; i < handX_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_handX;
      u_st_handX.base = 0;
      u_st_handX.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_handX.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_handX.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_handX.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_handX = u_st_handX.real;
      offset += sizeof(this->st_handX);
        memcpy( &(this->handX[i]), &(this->st_handX), sizeof(float));
      }
      uint8_t handY_lengthT = *(inbuffer + offset++);
      if(handY_lengthT > handY_length)
        this->handY = (float*)realloc(this->handY, handY_lengthT * sizeof(float));
      offset += 3;
      handY_length = handY_lengthT;
      for( uint8_t i = 0; i < handY_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_handY;
      u_st_handY.base = 0;
      u_st_handY.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_handY.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_handY.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_handY.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_handY = u_st_handY.real;
      offset += sizeof(this->st_handY);
        memcpy( &(this->handY[i]), &(this->st_handY), sizeof(float));
      }
      uint8_t handZ_lengthT = *(inbuffer + offset++);
      if(handZ_lengthT > handZ_length)
        this->handZ = (float*)realloc(this->handZ, handZ_lengthT * sizeof(float));
      offset += 3;
      handZ_length = handZ_lengthT;
      for( uint8_t i = 0; i < handZ_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_handZ;
      u_st_handZ.base = 0;
      u_st_handZ.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_handZ.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_handZ.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_handZ.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_handZ = u_st_handZ.real;
      offset += sizeof(this->st_handZ);
        memcpy( &(this->handZ[i]), &(this->st_handZ), sizeof(float));
      }
      uint8_t headWithHandX_lengthT = *(inbuffer + offset++);
      if(headWithHandX_lengthT > headWithHandX_length)
        this->headWithHandX = (float*)realloc(this->headWithHandX, headWithHandX_lengthT * sizeof(float));
      offset += 3;
      headWithHandX_length = headWithHandX_lengthT;
      for( uint8_t i = 0; i < headWithHandX_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_headWithHandX;
      u_st_headWithHandX.base = 0;
      u_st_headWithHandX.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_headWithHandX.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_headWithHandX.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_headWithHandX.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_headWithHandX = u_st_headWithHandX.real;
      offset += sizeof(this->st_headWithHandX);
        memcpy( &(this->headWithHandX[i]), &(this->st_headWithHandX), sizeof(float));
      }
      uint8_t headWithHandY_lengthT = *(inbuffer + offset++);
      if(headWithHandY_lengthT > headWithHandY_length)
        this->headWithHandY = (float*)realloc(this->headWithHandY, headWithHandY_lengthT * sizeof(float));
      offset += 3;
      headWithHandY_length = headWithHandY_lengthT;
      for( uint8_t i = 0; i < headWithHandY_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_headWithHandY;
      u_st_headWithHandY.base = 0;
      u_st_headWithHandY.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_headWithHandY.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_headWithHandY.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_headWithHandY.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_headWithHandY = u_st_headWithHandY.real;
      offset += sizeof(this->st_headWithHandY);
        memcpy( &(this->headWithHandY[i]), &(this->st_headWithHandY), sizeof(float));
      }
      uint8_t headWithHandZ_lengthT = *(inbuffer + offset++);
      if(headWithHandZ_lengthT > headWithHandZ_length)
        this->headWithHandZ = (float*)realloc(this->headWithHandZ, headWithHandZ_lengthT * sizeof(float));
      offset += 3;
      headWithHandZ_length = headWithHandZ_lengthT;
      for( uint8_t i = 0; i < headWithHandZ_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_headWithHandZ;
      u_st_headWithHandZ.base = 0;
      u_st_headWithHandZ.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_headWithHandZ.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_headWithHandZ.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_headWithHandZ.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_headWithHandZ = u_st_headWithHandZ.real;
      offset += sizeof(this->st_headWithHandZ);
        memcpy( &(this->headWithHandZ[i]), &(this->st_headWithHandZ), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "ptu_person_detection/ptu_detected_persons"; };
    const char * getMD5(){ return "3ac58461a8f7e74701625bcb967b025f"; };

  };

}
#endif