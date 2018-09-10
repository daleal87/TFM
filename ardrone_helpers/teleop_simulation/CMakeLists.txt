cmake_minimum_required(VERSION 2.8.3)
project(teleop_simulation)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
  std_srvs
  rosaria
)



catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES teleop_gazebo
#  CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs
#  DEPENDS system_lib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()


#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

add_executable(ard2_joystic src/main.cpp)

add_executable(teleoperacion_pura src/teleoperacion_pura.cpp)

add_executable(p3at_keyboard_gazebo src/teleop_gazebo.cpp)

add_executable(p3at_keyboard_rosaria src/teleop_rosaria.cpp)

add_executable(p3at_keyboard_dual src/teleop_dual.cpp)

add_executable(rosaria_publisher src/rosaria_publisher.cpp)


target_link_libraries(ard2_joystic 
   ${catkin_LIBRARIES}
)

target_link_libraries(teleoperacion_pura 
   ${catkin_LIBRARIES}
)

target_link_libraries(p3at_keyboard_gazebo 
   ${catkin_LIBRARIES}
)

target_link_libraries(p3at_keyboard_rosaria 
   ${catkin_LIBRARIES}
)

target_link_libraries(p3at_keyboard_dual 
   ${catkin_LIBRARIES}
)

target_link_libraries(rosaria_publisher 
   ${catkin_LIBRARIES}
)
