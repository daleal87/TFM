#ifndef _ROS_leg_detection_msgs_DetectedLegs_h
#define _ROS_leg_detection_msgs_DetectedLegs_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Pose2D.h"

namespace leg_detection_msgs
{

  class DetectedLegs : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t poses_length;
      geometry_msgs::Pose2D st_poses;
      geometry_msgs::Pose2D * poses;
      uint8_t singleLegs_length;
      geometry_msgs::Pose2D st_singleLegs;
      geometry_msgs::Pose2D * singleLegs;
      uint8_t radius_length;
      float st_radius;
      float * radius;
      uint8_t id_length;
      int8_t st_id;
      int8_t * id;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = poses_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < poses_length; i++){
      offset += this->poses[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = singleLegs_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < singleLegs_length; i++){
      offset += this->singleLegs[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = radius_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < radius_length; i++){
      union {
        float real;
        uint32_t base;
      } u_radiusi;
      u_radiusi.real = this->radius[i];
      *(outbuffer + offset + 0) = (u_radiusi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_radiusi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_radiusi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_radiusi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->radius[i]);
      }
      *(outbuffer + offset++) = id_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < id_length; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_idi;
      u_idi.real = this->id[i];
      *(outbuffer + offset + 0) = (u_idi.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t poses_lengthT = *(inbuffer + offset++);
      if(poses_lengthT > poses_length)
        this->poses = (geometry_msgs::Pose2D*)realloc(this->poses, poses_lengthT * sizeof(geometry_msgs::Pose2D));
      offset += 3;
      poses_length = poses_lengthT;
      for( uint8_t i = 0; i < poses_length; i++){
      offset += this->st_poses.deserialize(inbuffer + offset);
        memcpy( &(this->poses[i]), &(this->st_poses), sizeof(geometry_msgs::Pose2D));
      }
      uint8_t singleLegs_lengthT = *(inbuffer + offset++);
      if(singleLegs_lengthT > singleLegs_length)
        this->singleLegs = (geometry_msgs::Pose2D*)realloc(this->singleLegs, singleLegs_lengthT * sizeof(geometry_msgs::Pose2D));
      offset += 3;
      singleLegs_length = singleLegs_lengthT;
      for( uint8_t i = 0; i < singleLegs_length; i++){
      offset += this->st_singleLegs.deserialize(inbuffer + offset);
        memcpy( &(this->singleLegs[i]), &(this->st_singleLegs), sizeof(geometry_msgs::Pose2D));
      }
      uint8_t radius_lengthT = *(inbuffer + offset++);
      if(radius_lengthT > radius_length)
        this->radius = (float*)realloc(this->radius, radius_lengthT * sizeof(float));
      offset += 3;
      radius_length = radius_lengthT;
      for( uint8_t i = 0; i < radius_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_radius;
      u_st_radius.base = 0;
      u_st_radius.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_radius.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_radius.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_radius.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_radius = u_st_radius.real;
      offset += sizeof(this->st_radius);
        memcpy( &(this->radius[i]), &(this->st_radius), sizeof(float));
      }
      uint8_t id_lengthT = *(inbuffer + offset++);
      if(id_lengthT > id_length)
        this->id = (int8_t*)realloc(this->id, id_lengthT * sizeof(int8_t));
      offset += 3;
      id_length = id_lengthT;
      for( uint8_t i = 0; i < id_length; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_st_id;
      u_st_id.base = 0;
      u_st_id.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->st_id = u_st_id.real;
      offset += sizeof(this->st_id);
        memcpy( &(this->id[i]), &(this->st_id), sizeof(int8_t));
      }
     return offset;
    }

    const char * getType(){ return "leg_detection_msgs/DetectedLegs"; };
    const char * getMD5(){ return "f773a6fd79178ccbb2a530e30545a269"; };

  };

}
#endif