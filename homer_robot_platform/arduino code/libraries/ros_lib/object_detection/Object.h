#ifndef _ROS_object_detection_Object_h
#define _ROS_object_detection_Object_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/PointCloud2.h"
#include "sensor_msgs/Image.h"
#include "geometry_msgs/Vector3.h"

namespace object_detection
{

  class Object : public ros::Msg
  {
    public:
      sensor_msgs::PointCloud2 points;
      sensor_msgs::Image image;
      sensor_msgs::Image mask;
      uint8_t bounding_box_length;
      geometry_msgs::Vector3 st_bounding_box;
      geometry_msgs::Vector3 * bounding_box;
      uint8_t bounding_box_axis_aligned_length;
      geometry_msgs::Vector3 st_bounding_box_axis_aligned;
      geometry_msgs::Vector3 * bounding_box_axis_aligned;
      geometry_msgs::Vector3 extent;
      geometry_msgs::Vector3 centroid;
      const char* name;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->points.serialize(outbuffer + offset);
      offset += this->image.serialize(outbuffer + offset);
      offset += this->mask.serialize(outbuffer + offset);
      *(outbuffer + offset++) = bounding_box_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < bounding_box_length; i++){
      offset += this->bounding_box[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = bounding_box_axis_aligned_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < bounding_box_axis_aligned_length; i++){
      offset += this->bounding_box_axis_aligned[i].serialize(outbuffer + offset);
      }
      offset += this->extent.serialize(outbuffer + offset);
      offset += this->centroid.serialize(outbuffer + offset);
      uint32_t length_name = strlen(this->name);
      memcpy(outbuffer + offset, &length_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->points.deserialize(inbuffer + offset);
      offset += this->image.deserialize(inbuffer + offset);
      offset += this->mask.deserialize(inbuffer + offset);
      uint8_t bounding_box_lengthT = *(inbuffer + offset++);
      if(bounding_box_lengthT > bounding_box_length)
        this->bounding_box = (geometry_msgs::Vector3*)realloc(this->bounding_box, bounding_box_lengthT * sizeof(geometry_msgs::Vector3));
      offset += 3;
      bounding_box_length = bounding_box_lengthT;
      for( uint8_t i = 0; i < bounding_box_length; i++){
      offset += this->st_bounding_box.deserialize(inbuffer + offset);
        memcpy( &(this->bounding_box[i]), &(this->st_bounding_box), sizeof(geometry_msgs::Vector3));
      }
      uint8_t bounding_box_axis_aligned_lengthT = *(inbuffer + offset++);
      if(bounding_box_axis_aligned_lengthT > bounding_box_axis_aligned_length)
        this->bounding_box_axis_aligned = (geometry_msgs::Vector3*)realloc(this->bounding_box_axis_aligned, bounding_box_axis_aligned_lengthT * sizeof(geometry_msgs::Vector3));
      offset += 3;
      bounding_box_axis_aligned_length = bounding_box_axis_aligned_lengthT;
      for( uint8_t i = 0; i < bounding_box_axis_aligned_length; i++){
      offset += this->st_bounding_box_axis_aligned.deserialize(inbuffer + offset);
        memcpy( &(this->bounding_box_axis_aligned[i]), &(this->st_bounding_box_axis_aligned), sizeof(geometry_msgs::Vector3));
      }
      offset += this->extent.deserialize(inbuffer + offset);
      offset += this->centroid.deserialize(inbuffer + offset);
      uint32_t length_name;
      memcpy(&length_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
     return offset;
    }

    const char * getType(){ return "object_detection/Object"; };
    const char * getMD5(){ return "646b0c58fae71924677af4128996e178"; };

  };

}
#endif