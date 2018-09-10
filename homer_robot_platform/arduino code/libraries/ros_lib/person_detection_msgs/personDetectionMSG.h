#ifndef _ROS_person_detection_msgs_personDetectionMSG_h
#define _ROS_person_detection_msgs_personDetectionMSG_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace person_detection_msgs
{

  class personDetectionMSG : public ros::Msg
  {
    public:
      uint8_t kv_length;
      float st_kv;
      float * kv;
      uint8_t kw_length;
      float st_kw;
      float * kw;
      uint8_t kx_length;
      float st_kx;
      float * kx;
      uint8_t ky_length;
      float st_ky;
      float * ky;
      uint8_t kz_length;
      float st_kz;
      float * kz;
      uint8_t hav_length;
      float st_hav;
      float * hav;
      uint8_t haw_length;
      float st_haw;
      float * haw;
      uint8_t hax_length;
      float st_hax;
      float * hax;
      uint8_t hay_length;
      float st_hay;
      float * hay;
      uint8_t haz_length;
      float st_haz;
      float * haz;
      uint8_t hbv_length;
      float st_hbv;
      float * hbv;
      uint8_t hbw_length;
      float st_hbw;
      float * hbw;
      uint8_t hbx_length;
      float st_hbx;
      float * hbx;
      uint8_t hby_length;
      float st_hby;
      float * hby;
      uint8_t hbz_length;
      float st_hbz;
      float * hbz;
      uint8_t s1_length;
      float st_s1;
      float * s1;
      uint8_t s2_length;
      float st_s2;
      float * s2;
      uint8_t s3_length;
      float st_s3;
      float * s3;
      uint8_t s4_length;
      float st_s4;
      float * s4;
      uint8_t s5_length;
      float st_s5;
      float * s5;
      uint8_t s6_length;
      float st_s6;
      float * s6;
      uint8_t s7_length;
      float st_s7;
      float * s7;
      uint8_t s8_length;
      float st_s8;
      float * s8;
      uint8_t s9_length;
      float st_s9;
      float * s9;
      uint8_t s10_length;
      float st_s10;
      float * s10;
      uint8_t s11_length;
      float st_s11;
      float * s11;
      uint8_t s12_length;
      float st_s12;
      float * s12;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = kv_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < kv_length; i++){
      union {
        float real;
        uint32_t base;
      } u_kvi;
      u_kvi.real = this->kv[i];
      *(outbuffer + offset + 0) = (u_kvi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_kvi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_kvi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_kvi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->kv[i]);
      }
      *(outbuffer + offset++) = kw_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < kw_length; i++){
      union {
        float real;
        uint32_t base;
      } u_kwi;
      u_kwi.real = this->kw[i];
      *(outbuffer + offset + 0) = (u_kwi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_kwi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_kwi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_kwi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->kw[i]);
      }
      *(outbuffer + offset++) = kx_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < kx_length; i++){
      union {
        float real;
        uint32_t base;
      } u_kxi;
      u_kxi.real = this->kx[i];
      *(outbuffer + offset + 0) = (u_kxi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_kxi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_kxi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_kxi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->kx[i]);
      }
      *(outbuffer + offset++) = ky_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < ky_length; i++){
      union {
        float real;
        uint32_t base;
      } u_kyi;
      u_kyi.real = this->ky[i];
      *(outbuffer + offset + 0) = (u_kyi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_kyi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_kyi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_kyi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ky[i]);
      }
      *(outbuffer + offset++) = kz_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < kz_length; i++){
      union {
        float real;
        uint32_t base;
      } u_kzi;
      u_kzi.real = this->kz[i];
      *(outbuffer + offset + 0) = (u_kzi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_kzi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_kzi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_kzi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->kz[i]);
      }
      *(outbuffer + offset++) = hav_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < hav_length; i++){
      union {
        float real;
        uint32_t base;
      } u_havi;
      u_havi.real = this->hav[i];
      *(outbuffer + offset + 0) = (u_havi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_havi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_havi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_havi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->hav[i]);
      }
      *(outbuffer + offset++) = haw_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < haw_length; i++){
      union {
        float real;
        uint32_t base;
      } u_hawi;
      u_hawi.real = this->haw[i];
      *(outbuffer + offset + 0) = (u_hawi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_hawi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_hawi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_hawi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->haw[i]);
      }
      *(outbuffer + offset++) = hax_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < hax_length; i++){
      union {
        float real;
        uint32_t base;
      } u_haxi;
      u_haxi.real = this->hax[i];
      *(outbuffer + offset + 0) = (u_haxi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_haxi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_haxi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_haxi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->hax[i]);
      }
      *(outbuffer + offset++) = hay_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < hay_length; i++){
      union {
        float real;
        uint32_t base;
      } u_hayi;
      u_hayi.real = this->hay[i];
      *(outbuffer + offset + 0) = (u_hayi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_hayi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_hayi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_hayi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->hay[i]);
      }
      *(outbuffer + offset++) = haz_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < haz_length; i++){
      union {
        float real;
        uint32_t base;
      } u_hazi;
      u_hazi.real = this->haz[i];
      *(outbuffer + offset + 0) = (u_hazi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_hazi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_hazi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_hazi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->haz[i]);
      }
      *(outbuffer + offset++) = hbv_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < hbv_length; i++){
      union {
        float real;
        uint32_t base;
      } u_hbvi;
      u_hbvi.real = this->hbv[i];
      *(outbuffer + offset + 0) = (u_hbvi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_hbvi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_hbvi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_hbvi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->hbv[i]);
      }
      *(outbuffer + offset++) = hbw_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < hbw_length; i++){
      union {
        float real;
        uint32_t base;
      } u_hbwi;
      u_hbwi.real = this->hbw[i];
      *(outbuffer + offset + 0) = (u_hbwi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_hbwi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_hbwi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_hbwi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->hbw[i]);
      }
      *(outbuffer + offset++) = hbx_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < hbx_length; i++){
      union {
        float real;
        uint32_t base;
      } u_hbxi;
      u_hbxi.real = this->hbx[i];
      *(outbuffer + offset + 0) = (u_hbxi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_hbxi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_hbxi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_hbxi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->hbx[i]);
      }
      *(outbuffer + offset++) = hby_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < hby_length; i++){
      union {
        float real;
        uint32_t base;
      } u_hbyi;
      u_hbyi.real = this->hby[i];
      *(outbuffer + offset + 0) = (u_hbyi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_hbyi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_hbyi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_hbyi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->hby[i]);
      }
      *(outbuffer + offset++) = hbz_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < hbz_length; i++){
      union {
        float real;
        uint32_t base;
      } u_hbzi;
      u_hbzi.real = this->hbz[i];
      *(outbuffer + offset + 0) = (u_hbzi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_hbzi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_hbzi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_hbzi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->hbz[i]);
      }
      *(outbuffer + offset++) = s1_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < s1_length; i++){
      union {
        float real;
        uint32_t base;
      } u_s1i;
      u_s1i.real = this->s1[i];
      *(outbuffer + offset + 0) = (u_s1i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_s1i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_s1i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_s1i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->s1[i]);
      }
      *(outbuffer + offset++) = s2_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < s2_length; i++){
      union {
        float real;
        uint32_t base;
      } u_s2i;
      u_s2i.real = this->s2[i];
      *(outbuffer + offset + 0) = (u_s2i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_s2i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_s2i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_s2i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->s2[i]);
      }
      *(outbuffer + offset++) = s3_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < s3_length; i++){
      union {
        float real;
        uint32_t base;
      } u_s3i;
      u_s3i.real = this->s3[i];
      *(outbuffer + offset + 0) = (u_s3i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_s3i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_s3i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_s3i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->s3[i]);
      }
      *(outbuffer + offset++) = s4_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < s4_length; i++){
      union {
        float real;
        uint32_t base;
      } u_s4i;
      u_s4i.real = this->s4[i];
      *(outbuffer + offset + 0) = (u_s4i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_s4i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_s4i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_s4i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->s4[i]);
      }
      *(outbuffer + offset++) = s5_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < s5_length; i++){
      union {
        float real;
        uint32_t base;
      } u_s5i;
      u_s5i.real = this->s5[i];
      *(outbuffer + offset + 0) = (u_s5i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_s5i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_s5i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_s5i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->s5[i]);
      }
      *(outbuffer + offset++) = s6_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < s6_length; i++){
      union {
        float real;
        uint32_t base;
      } u_s6i;
      u_s6i.real = this->s6[i];
      *(outbuffer + offset + 0) = (u_s6i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_s6i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_s6i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_s6i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->s6[i]);
      }
      *(outbuffer + offset++) = s7_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < s7_length; i++){
      union {
        float real;
        uint32_t base;
      } u_s7i;
      u_s7i.real = this->s7[i];
      *(outbuffer + offset + 0) = (u_s7i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_s7i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_s7i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_s7i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->s7[i]);
      }
      *(outbuffer + offset++) = s8_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < s8_length; i++){
      union {
        float real;
        uint32_t base;
      } u_s8i;
      u_s8i.real = this->s8[i];
      *(outbuffer + offset + 0) = (u_s8i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_s8i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_s8i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_s8i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->s8[i]);
      }
      *(outbuffer + offset++) = s9_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < s9_length; i++){
      union {
        float real;
        uint32_t base;
      } u_s9i;
      u_s9i.real = this->s9[i];
      *(outbuffer + offset + 0) = (u_s9i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_s9i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_s9i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_s9i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->s9[i]);
      }
      *(outbuffer + offset++) = s10_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < s10_length; i++){
      union {
        float real;
        uint32_t base;
      } u_s10i;
      u_s10i.real = this->s10[i];
      *(outbuffer + offset + 0) = (u_s10i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_s10i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_s10i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_s10i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->s10[i]);
      }
      *(outbuffer + offset++) = s11_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < s11_length; i++){
      union {
        float real;
        uint32_t base;
      } u_s11i;
      u_s11i.real = this->s11[i];
      *(outbuffer + offset + 0) = (u_s11i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_s11i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_s11i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_s11i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->s11[i]);
      }
      *(outbuffer + offset++) = s12_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < s12_length; i++){
      union {
        float real;
        uint32_t base;
      } u_s12i;
      u_s12i.real = this->s12[i];
      *(outbuffer + offset + 0) = (u_s12i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_s12i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_s12i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_s12i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->s12[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t kv_lengthT = *(inbuffer + offset++);
      if(kv_lengthT > kv_length)
        this->kv = (float*)realloc(this->kv, kv_lengthT * sizeof(float));
      offset += 3;
      kv_length = kv_lengthT;
      for( uint8_t i = 0; i < kv_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_kv;
      u_st_kv.base = 0;
      u_st_kv.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_kv.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_kv.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_kv.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_kv = u_st_kv.real;
      offset += sizeof(this->st_kv);
        memcpy( &(this->kv[i]), &(this->st_kv), sizeof(float));
      }
      uint8_t kw_lengthT = *(inbuffer + offset++);
      if(kw_lengthT > kw_length)
        this->kw = (float*)realloc(this->kw, kw_lengthT * sizeof(float));
      offset += 3;
      kw_length = kw_lengthT;
      for( uint8_t i = 0; i < kw_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_kw;
      u_st_kw.base = 0;
      u_st_kw.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_kw.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_kw.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_kw.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_kw = u_st_kw.real;
      offset += sizeof(this->st_kw);
        memcpy( &(this->kw[i]), &(this->st_kw), sizeof(float));
      }
      uint8_t kx_lengthT = *(inbuffer + offset++);
      if(kx_lengthT > kx_length)
        this->kx = (float*)realloc(this->kx, kx_lengthT * sizeof(float));
      offset += 3;
      kx_length = kx_lengthT;
      for( uint8_t i = 0; i < kx_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_kx;
      u_st_kx.base = 0;
      u_st_kx.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_kx.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_kx.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_kx.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_kx = u_st_kx.real;
      offset += sizeof(this->st_kx);
        memcpy( &(this->kx[i]), &(this->st_kx), sizeof(float));
      }
      uint8_t ky_lengthT = *(inbuffer + offset++);
      if(ky_lengthT > ky_length)
        this->ky = (float*)realloc(this->ky, ky_lengthT * sizeof(float));
      offset += 3;
      ky_length = ky_lengthT;
      for( uint8_t i = 0; i < ky_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_ky;
      u_st_ky.base = 0;
      u_st_ky.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_ky.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_ky.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_ky.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_ky = u_st_ky.real;
      offset += sizeof(this->st_ky);
        memcpy( &(this->ky[i]), &(this->st_ky), sizeof(float));
      }
      uint8_t kz_lengthT = *(inbuffer + offset++);
      if(kz_lengthT > kz_length)
        this->kz = (float*)realloc(this->kz, kz_lengthT * sizeof(float));
      offset += 3;
      kz_length = kz_lengthT;
      for( uint8_t i = 0; i < kz_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_kz;
      u_st_kz.base = 0;
      u_st_kz.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_kz.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_kz.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_kz.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_kz = u_st_kz.real;
      offset += sizeof(this->st_kz);
        memcpy( &(this->kz[i]), &(this->st_kz), sizeof(float));
      }
      uint8_t hav_lengthT = *(inbuffer + offset++);
      if(hav_lengthT > hav_length)
        this->hav = (float*)realloc(this->hav, hav_lengthT * sizeof(float));
      offset += 3;
      hav_length = hav_lengthT;
      for( uint8_t i = 0; i < hav_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_hav;
      u_st_hav.base = 0;
      u_st_hav.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_hav.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_hav.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_hav.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_hav = u_st_hav.real;
      offset += sizeof(this->st_hav);
        memcpy( &(this->hav[i]), &(this->st_hav), sizeof(float));
      }
      uint8_t haw_lengthT = *(inbuffer + offset++);
      if(haw_lengthT > haw_length)
        this->haw = (float*)realloc(this->haw, haw_lengthT * sizeof(float));
      offset += 3;
      haw_length = haw_lengthT;
      for( uint8_t i = 0; i < haw_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_haw;
      u_st_haw.base = 0;
      u_st_haw.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_haw.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_haw.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_haw.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_haw = u_st_haw.real;
      offset += sizeof(this->st_haw);
        memcpy( &(this->haw[i]), &(this->st_haw), sizeof(float));
      }
      uint8_t hax_lengthT = *(inbuffer + offset++);
      if(hax_lengthT > hax_length)
        this->hax = (float*)realloc(this->hax, hax_lengthT * sizeof(float));
      offset += 3;
      hax_length = hax_lengthT;
      for( uint8_t i = 0; i < hax_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_hax;
      u_st_hax.base = 0;
      u_st_hax.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_hax.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_hax.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_hax.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_hax = u_st_hax.real;
      offset += sizeof(this->st_hax);
        memcpy( &(this->hax[i]), &(this->st_hax), sizeof(float));
      }
      uint8_t hay_lengthT = *(inbuffer + offset++);
      if(hay_lengthT > hay_length)
        this->hay = (float*)realloc(this->hay, hay_lengthT * sizeof(float));
      offset += 3;
      hay_length = hay_lengthT;
      for( uint8_t i = 0; i < hay_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_hay;
      u_st_hay.base = 0;
      u_st_hay.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_hay.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_hay.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_hay.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_hay = u_st_hay.real;
      offset += sizeof(this->st_hay);
        memcpy( &(this->hay[i]), &(this->st_hay), sizeof(float));
      }
      uint8_t haz_lengthT = *(inbuffer + offset++);
      if(haz_lengthT > haz_length)
        this->haz = (float*)realloc(this->haz, haz_lengthT * sizeof(float));
      offset += 3;
      haz_length = haz_lengthT;
      for( uint8_t i = 0; i < haz_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_haz;
      u_st_haz.base = 0;
      u_st_haz.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_haz.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_haz.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_haz.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_haz = u_st_haz.real;
      offset += sizeof(this->st_haz);
        memcpy( &(this->haz[i]), &(this->st_haz), sizeof(float));
      }
      uint8_t hbv_lengthT = *(inbuffer + offset++);
      if(hbv_lengthT > hbv_length)
        this->hbv = (float*)realloc(this->hbv, hbv_lengthT * sizeof(float));
      offset += 3;
      hbv_length = hbv_lengthT;
      for( uint8_t i = 0; i < hbv_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_hbv;
      u_st_hbv.base = 0;
      u_st_hbv.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_hbv.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_hbv.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_hbv.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_hbv = u_st_hbv.real;
      offset += sizeof(this->st_hbv);
        memcpy( &(this->hbv[i]), &(this->st_hbv), sizeof(float));
      }
      uint8_t hbw_lengthT = *(inbuffer + offset++);
      if(hbw_lengthT > hbw_length)
        this->hbw = (float*)realloc(this->hbw, hbw_lengthT * sizeof(float));
      offset += 3;
      hbw_length = hbw_lengthT;
      for( uint8_t i = 0; i < hbw_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_hbw;
      u_st_hbw.base = 0;
      u_st_hbw.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_hbw.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_hbw.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_hbw.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_hbw = u_st_hbw.real;
      offset += sizeof(this->st_hbw);
        memcpy( &(this->hbw[i]), &(this->st_hbw), sizeof(float));
      }
      uint8_t hbx_lengthT = *(inbuffer + offset++);
      if(hbx_lengthT > hbx_length)
        this->hbx = (float*)realloc(this->hbx, hbx_lengthT * sizeof(float));
      offset += 3;
      hbx_length = hbx_lengthT;
      for( uint8_t i = 0; i < hbx_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_hbx;
      u_st_hbx.base = 0;
      u_st_hbx.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_hbx.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_hbx.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_hbx.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_hbx = u_st_hbx.real;
      offset += sizeof(this->st_hbx);
        memcpy( &(this->hbx[i]), &(this->st_hbx), sizeof(float));
      }
      uint8_t hby_lengthT = *(inbuffer + offset++);
      if(hby_lengthT > hby_length)
        this->hby = (float*)realloc(this->hby, hby_lengthT * sizeof(float));
      offset += 3;
      hby_length = hby_lengthT;
      for( uint8_t i = 0; i < hby_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_hby;
      u_st_hby.base = 0;
      u_st_hby.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_hby.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_hby.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_hby.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_hby = u_st_hby.real;
      offset += sizeof(this->st_hby);
        memcpy( &(this->hby[i]), &(this->st_hby), sizeof(float));
      }
      uint8_t hbz_lengthT = *(inbuffer + offset++);
      if(hbz_lengthT > hbz_length)
        this->hbz = (float*)realloc(this->hbz, hbz_lengthT * sizeof(float));
      offset += 3;
      hbz_length = hbz_lengthT;
      for( uint8_t i = 0; i < hbz_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_hbz;
      u_st_hbz.base = 0;
      u_st_hbz.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_hbz.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_hbz.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_hbz.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_hbz = u_st_hbz.real;
      offset += sizeof(this->st_hbz);
        memcpy( &(this->hbz[i]), &(this->st_hbz), sizeof(float));
      }
      uint8_t s1_lengthT = *(inbuffer + offset++);
      if(s1_lengthT > s1_length)
        this->s1 = (float*)realloc(this->s1, s1_lengthT * sizeof(float));
      offset += 3;
      s1_length = s1_lengthT;
      for( uint8_t i = 0; i < s1_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_s1;
      u_st_s1.base = 0;
      u_st_s1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_s1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_s1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_s1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_s1 = u_st_s1.real;
      offset += sizeof(this->st_s1);
        memcpy( &(this->s1[i]), &(this->st_s1), sizeof(float));
      }
      uint8_t s2_lengthT = *(inbuffer + offset++);
      if(s2_lengthT > s2_length)
        this->s2 = (float*)realloc(this->s2, s2_lengthT * sizeof(float));
      offset += 3;
      s2_length = s2_lengthT;
      for( uint8_t i = 0; i < s2_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_s2;
      u_st_s2.base = 0;
      u_st_s2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_s2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_s2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_s2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_s2 = u_st_s2.real;
      offset += sizeof(this->st_s2);
        memcpy( &(this->s2[i]), &(this->st_s2), sizeof(float));
      }
      uint8_t s3_lengthT = *(inbuffer + offset++);
      if(s3_lengthT > s3_length)
        this->s3 = (float*)realloc(this->s3, s3_lengthT * sizeof(float));
      offset += 3;
      s3_length = s3_lengthT;
      for( uint8_t i = 0; i < s3_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_s3;
      u_st_s3.base = 0;
      u_st_s3.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_s3.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_s3.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_s3.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_s3 = u_st_s3.real;
      offset += sizeof(this->st_s3);
        memcpy( &(this->s3[i]), &(this->st_s3), sizeof(float));
      }
      uint8_t s4_lengthT = *(inbuffer + offset++);
      if(s4_lengthT > s4_length)
        this->s4 = (float*)realloc(this->s4, s4_lengthT * sizeof(float));
      offset += 3;
      s4_length = s4_lengthT;
      for( uint8_t i = 0; i < s4_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_s4;
      u_st_s4.base = 0;
      u_st_s4.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_s4.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_s4.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_s4.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_s4 = u_st_s4.real;
      offset += sizeof(this->st_s4);
        memcpy( &(this->s4[i]), &(this->st_s4), sizeof(float));
      }
      uint8_t s5_lengthT = *(inbuffer + offset++);
      if(s5_lengthT > s5_length)
        this->s5 = (float*)realloc(this->s5, s5_lengthT * sizeof(float));
      offset += 3;
      s5_length = s5_lengthT;
      for( uint8_t i = 0; i < s5_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_s5;
      u_st_s5.base = 0;
      u_st_s5.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_s5.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_s5.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_s5.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_s5 = u_st_s5.real;
      offset += sizeof(this->st_s5);
        memcpy( &(this->s5[i]), &(this->st_s5), sizeof(float));
      }
      uint8_t s6_lengthT = *(inbuffer + offset++);
      if(s6_lengthT > s6_length)
        this->s6 = (float*)realloc(this->s6, s6_lengthT * sizeof(float));
      offset += 3;
      s6_length = s6_lengthT;
      for( uint8_t i = 0; i < s6_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_s6;
      u_st_s6.base = 0;
      u_st_s6.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_s6.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_s6.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_s6.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_s6 = u_st_s6.real;
      offset += sizeof(this->st_s6);
        memcpy( &(this->s6[i]), &(this->st_s6), sizeof(float));
      }
      uint8_t s7_lengthT = *(inbuffer + offset++);
      if(s7_lengthT > s7_length)
        this->s7 = (float*)realloc(this->s7, s7_lengthT * sizeof(float));
      offset += 3;
      s7_length = s7_lengthT;
      for( uint8_t i = 0; i < s7_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_s7;
      u_st_s7.base = 0;
      u_st_s7.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_s7.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_s7.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_s7.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_s7 = u_st_s7.real;
      offset += sizeof(this->st_s7);
        memcpy( &(this->s7[i]), &(this->st_s7), sizeof(float));
      }
      uint8_t s8_lengthT = *(inbuffer + offset++);
      if(s8_lengthT > s8_length)
        this->s8 = (float*)realloc(this->s8, s8_lengthT * sizeof(float));
      offset += 3;
      s8_length = s8_lengthT;
      for( uint8_t i = 0; i < s8_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_s8;
      u_st_s8.base = 0;
      u_st_s8.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_s8.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_s8.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_s8.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_s8 = u_st_s8.real;
      offset += sizeof(this->st_s8);
        memcpy( &(this->s8[i]), &(this->st_s8), sizeof(float));
      }
      uint8_t s9_lengthT = *(inbuffer + offset++);
      if(s9_lengthT > s9_length)
        this->s9 = (float*)realloc(this->s9, s9_lengthT * sizeof(float));
      offset += 3;
      s9_length = s9_lengthT;
      for( uint8_t i = 0; i < s9_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_s9;
      u_st_s9.base = 0;
      u_st_s9.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_s9.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_s9.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_s9.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_s9 = u_st_s9.real;
      offset += sizeof(this->st_s9);
        memcpy( &(this->s9[i]), &(this->st_s9), sizeof(float));
      }
      uint8_t s10_lengthT = *(inbuffer + offset++);
      if(s10_lengthT > s10_length)
        this->s10 = (float*)realloc(this->s10, s10_lengthT * sizeof(float));
      offset += 3;
      s10_length = s10_lengthT;
      for( uint8_t i = 0; i < s10_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_s10;
      u_st_s10.base = 0;
      u_st_s10.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_s10.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_s10.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_s10.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_s10 = u_st_s10.real;
      offset += sizeof(this->st_s10);
        memcpy( &(this->s10[i]), &(this->st_s10), sizeof(float));
      }
      uint8_t s11_lengthT = *(inbuffer + offset++);
      if(s11_lengthT > s11_length)
        this->s11 = (float*)realloc(this->s11, s11_lengthT * sizeof(float));
      offset += 3;
      s11_length = s11_lengthT;
      for( uint8_t i = 0; i < s11_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_s11;
      u_st_s11.base = 0;
      u_st_s11.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_s11.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_s11.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_s11.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_s11 = u_st_s11.real;
      offset += sizeof(this->st_s11);
        memcpy( &(this->s11[i]), &(this->st_s11), sizeof(float));
      }
      uint8_t s12_lengthT = *(inbuffer + offset++);
      if(s12_lengthT > s12_length)
        this->s12 = (float*)realloc(this->s12, s12_lengthT * sizeof(float));
      offset += 3;
      s12_length = s12_lengthT;
      for( uint8_t i = 0; i < s12_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_s12;
      u_st_s12.base = 0;
      u_st_s12.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_s12.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_s12.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_s12.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_s12 = u_st_s12.real;
      offset += sizeof(this->st_s12);
        memcpy( &(this->s12[i]), &(this->st_s12), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "person_detection_msgs/personDetectionMSG"; };
    const char * getMD5(){ return "3c6d25fb5fb6e1363c786663973bc161"; };

  };

}
#endif