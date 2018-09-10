cmake_minimum_required(VERSION 2.8.6)
project(homer_robot_platform)

find_package(catkin REQUIRED COMPONENTS message_generation roscpp 
	roslib 
	geometry_msgs 
    nav_msgs
)

add_message_files(FILES 
	EncoderValues.msg
	QuadEncoderValues.msg
	RobotState.msg
)

generate_messages(DEPENDENCIES geometry_msgs )

include_directories(
	${catkin_INCLUDE_DIRS}
	)

catkin_package(
    CATKIN_DEPENDS message_runtime std_msgs sensor_msgs geometry_msgs roscpp_serialization roslib tf
)

add_executable(enc_to_odom src/enc_to_odom.cpp)
target_link_libraries(enc_to_odom ${catkin_LIBRARIES})
add_dependencies(enc_to_odom ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

