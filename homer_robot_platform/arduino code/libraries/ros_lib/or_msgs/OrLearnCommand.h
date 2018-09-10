#ifndef _ROS_or_msgs_OrLearnCommand_h
#define _ROS_or_msgs_OrLearnCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace or_msgs
{

  class OrLearnCommand : public ros::Msg
  {
    public:
      int32_t command;
      int32_t value_type;
      int32_t int_value;
      float float_value;
      const char* string_value;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_command;
      u_command.real = this->command;
      *(outbuffer + offset + 0) = (u_command.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_command.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_command.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_command.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->command);
      union {
        int32_t real;
        uint32_t base;
      } u_value_type;
      u_value_type.real = this->value_type;
      *(outbuffer + offset + 0) = (u_value_type.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_value_type.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_value_type.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_value_type.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->value_type);
      union {
        int32_t real;
        uint32_t base;
      } u_int_value;
      u_int_value.real = this->int_value;
      *(outbuffer + offset + 0) = (u_int_value.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_int_value.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_int_value.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_int_value.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->int_value);
      union {
        float real;
        uint32_t base;
      } u_float_value;
      u_float_value.real = this->float_value;
      *(outbuffer + offset + 0) = (u_float_value.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_float_value.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_float_value.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_float_value.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->float_value);
      uint32_t length_string_value = strlen(this->string_value);
      memcpy(outbuffer + offset, &length_string_value, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->string_value, length_string_value);
      offset += length_string_value;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_command;
      u_command.base = 0;
      u_command.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_command.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_command.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_command.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->command = u_command.real;
      offset += sizeof(this->command);
      union {
        int32_t real;
        uint32_t base;
      } u_value_type;
      u_value_type.base = 0;
      u_value_type.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_value_type.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_value_type.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_value_type.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->value_type = u_value_type.real;
      offset += sizeof(this->value_type);
      union {
        int32_t real;
        uint32_t base;
      } u_int_value;
      u_int_value.base = 0;
      u_int_value.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_int_value.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_int_value.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_int_value.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->int_value = u_int_value.real;
      offset += sizeof(this->int_value);
      union {
        float real;
        uint32_t base;
      } u_float_value;
      u_float_value.base = 0;
      u_float_value.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_float_value.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_float_value.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_float_value.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->float_value = u_float_value.real;
      offset += sizeof(this->float_value);
      uint32_t length_string_value;
      memcpy(&length_string_value, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_string_value; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_string_value-1]=0;
      this->string_value = (char *)(inbuffer + offset-1);
      offset += length_string_value;
     return offset;
    }

    const char * getType(){ return "or_msgs/OrLearnCommand"; };
    const char * getMD5(){ return "dbe659851c6543d9b445e0fb289343b2"; };

  };

}
#endif