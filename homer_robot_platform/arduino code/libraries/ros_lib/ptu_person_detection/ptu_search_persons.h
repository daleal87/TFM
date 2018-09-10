#ifndef _ROS_ptu_person_detection_ptu_search_persons_h
#define _ROS_ptu_person_detection_ptu_search_persons_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ptu_person_detection
{

  class ptu_search_persons : public ros::Msg
  {
    public:
      float angle;
      int32_t headsToFind;
      int32_t handsToFind;
      int32_t headsWithHandsToFind;
      float distanceBetweenPersons;
      float tiltAngle;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_angle;
      u_angle.real = this->angle;
      *(outbuffer + offset + 0) = (u_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle);
      union {
        int32_t real;
        uint32_t base;
      } u_headsToFind;
      u_headsToFind.real = this->headsToFind;
      *(outbuffer + offset + 0) = (u_headsToFind.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_headsToFind.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_headsToFind.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_headsToFind.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->headsToFind);
      union {
        int32_t real;
        uint32_t base;
      } u_handsToFind;
      u_handsToFind.real = this->handsToFind;
      *(outbuffer + offset + 0) = (u_handsToFind.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_handsToFind.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_handsToFind.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_handsToFind.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->handsToFind);
      union {
        int32_t real;
        uint32_t base;
      } u_headsWithHandsToFind;
      u_headsWithHandsToFind.real = this->headsWithHandsToFind;
      *(outbuffer + offset + 0) = (u_headsWithHandsToFind.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_headsWithHandsToFind.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_headsWithHandsToFind.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_headsWithHandsToFind.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->headsWithHandsToFind);
      union {
        float real;
        uint32_t base;
      } u_distanceBetweenPersons;
      u_distanceBetweenPersons.real = this->distanceBetweenPersons;
      *(outbuffer + offset + 0) = (u_distanceBetweenPersons.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distanceBetweenPersons.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_distanceBetweenPersons.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_distanceBetweenPersons.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distanceBetweenPersons);
      union {
        float real;
        uint32_t base;
      } u_tiltAngle;
      u_tiltAngle.real = this->tiltAngle;
      *(outbuffer + offset + 0) = (u_tiltAngle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_tiltAngle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_tiltAngle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_tiltAngle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->tiltAngle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_angle;
      u_angle.base = 0;
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angle = u_angle.real;
      offset += sizeof(this->angle);
      union {
        int32_t real;
        uint32_t base;
      } u_headsToFind;
      u_headsToFind.base = 0;
      u_headsToFind.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_headsToFind.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_headsToFind.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_headsToFind.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->headsToFind = u_headsToFind.real;
      offset += sizeof(this->headsToFind);
      union {
        int32_t real;
        uint32_t base;
      } u_handsToFind;
      u_handsToFind.base = 0;
      u_handsToFind.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_handsToFind.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_handsToFind.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_handsToFind.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->handsToFind = u_handsToFind.real;
      offset += sizeof(this->handsToFind);
      union {
        int32_t real;
        uint32_t base;
      } u_headsWithHandsToFind;
      u_headsWithHandsToFind.base = 0;
      u_headsWithHandsToFind.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_headsWithHandsToFind.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_headsWithHandsToFind.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_headsWithHandsToFind.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->headsWithHandsToFind = u_headsWithHandsToFind.real;
      offset += sizeof(this->headsWithHandsToFind);
      union {
        float real;
        uint32_t base;
      } u_distanceBetweenPersons;
      u_distanceBetweenPersons.base = 0;
      u_distanceBetweenPersons.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distanceBetweenPersons.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_distanceBetweenPersons.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_distanceBetweenPersons.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->distanceBetweenPersons = u_distanceBetweenPersons.real;
      offset += sizeof(this->distanceBetweenPersons);
      union {
        float real;
        uint32_t base;
      } u_tiltAngle;
      u_tiltAngle.base = 0;
      u_tiltAngle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_tiltAngle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_tiltAngle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_tiltAngle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->tiltAngle = u_tiltAngle.real;
      offset += sizeof(this->tiltAngle);
     return offset;
    }

    const char * getType(){ return "ptu_person_detection/ptu_search_persons"; };
    const char * getMD5(){ return "cdbb5da726979c20a8567f6bc51f0c22"; };

  };

}
#endif