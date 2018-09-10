#ifndef _ROS_selfawareness_node_PointCloudRobotCoord_h
#define _ROS_selfawareness_node_PointCloudRobotCoord_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/PointCloud2.h"
#include "geometry_msgs/Vector3.h"

namespace selfawareness_node
{

  class PointCloudRobotCoord : public ros::Msg
  {
    public:
      sensor_msgs::PointCloud2 pointCloud;
      sensor_msgs::PointCloud2 pointCloudEndEffector;
      geometry_msgs::Vector3 massPoint;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->pointCloud.serialize(outbuffer + offset);
      offset += this->pointCloudEndEffector.serialize(outbuffer + offset);
      offset += this->massPoint.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pointCloud.deserialize(inbuffer + offset);
      offset += this->pointCloudEndEffector.deserialize(inbuffer + offset);
      offset += this->massPoint.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "selfawareness_node/PointCloudRobotCoord"; };
    const char * getMD5(){ return "bd185c5f451432472da1829c501d93c2"; };

  };

}
#endif