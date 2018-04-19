cmake_minimum_required(VERSION 2.8.3)
project(vision)

#set (CMAKE_CXX_STANDARD 11)
#set(LIBS_LINK GL GLU cholmod cxsparse ${G2O_LIBRARIES} ${QT_LIBRARIES} ${QT_QTOPENGL_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${OpenCV_LIBS})

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages



find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  rospy
  sensor_msgs
  std_msgs
  geometry_msgs
  image_view
  tf
  std_srvs
  cvg_sim_msgs
  ardrone_autonomy
  dynamic_reconfigure
)

find_package(OpenCV REQUIRED)


## Find gazebo
find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

find_package(Boost REQUIRED COMPONENTS system)
find_package(Boost REQUIRED COMPONENTS thread)
include_directories(${Boost_INCLUDE_DIRS})





#Dynamic reconfiguration
generate_dynamic_reconfigure_options(
  cfg/TrackingReal.cfg  
)

generate_messages(
  DEPENDENCIES
  cvg_sim_msgs
)

catkin_package(
  DEPENDS gazebo
  CATKIN_DEPENDS roscpp std_msgs geometry_msgs tf 
  INCLUDE_DIRS include
)



set(HEADER_FILES
    include/vision/platform_detection/platform_detection_real.hpp
    
    include/vision/platform_tracking/platform_tracking_real.hpp

    include/vision/pos_transformer/pos_transformer_real.hpp    

    include/vision/ardrone_teleop.hpp

    include/vision/cancel_hovering.hpp
)


include_directories(include)
include_directories(${catkin_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS}) 
include_directories(${Boost_INCLUDE_DIRS})




#########################################################################################################

# PLATFORM_DETECTION_REAL NODE
add_executable(platform_detection_real 
                src/platform_detection/platform_detection_real.cpp
                ${HEADER_FILES}
)

target_link_libraries(platform_detection_real ${catkin_LIBRARIES} 
                                              ${OpenCV_LIBRARIES}
)


#########################################################################################################
###################################### WITH PREDICTION ##################################################
#########################################################################################################

################################ PLATFORM_TRACKING_REAL NODE ############################################
add_executable(platform_tracking_real 
                src/platform_tracking/platform_tracking_real.cpp
                ${HEADER_FILES}
)

target_link_libraries(
  platform_tracking_real ${Boost_LIBRARIES} ${GAZEBO_LIBRARIES} ${catkin_LIBRARIES}
)

add_dependencies(
  platform_tracking_real ${PROJECT_NAME}_gencfg
)


#########################################################################################################

#########################################################################################################

# POS_TRANSFORMER_REAL NODE
add_executable(pos_transformer_real 
                src/pos_transformer/pos_transformer_real.cpp
                ${HEADER_FILES}
)

target_link_libraries(pos_transformer_real ${catkin_LIBRARIES})
#########################################################################################################

#########################################################################################################
# ARDRONE_TELEOP NODE
add_executable(ardrone_teleop 
                src/ardrone_teleop.cpp
                ${HEADER_FILES}
)

target_link_libraries(ardrone_teleop ${catkin_LIBRARIES})
#########################################################################################################

#########################################################################################################
# CANCEL_HOVERING NODE
add_executable(cancel_hovering 
                src/cancel_hovering.cpp
                ${HEADER_FILES}                
)

target_link_libraries(cancel_hovering ${catkin_LIBRARIES})
#########################################################################################################


#add_library(vision src/ardrone_teleop.cpp)
add_dependencies(ardrone_teleop cvg_sim_msgs_gencpp)
add_dependencies(pos_transformer_real cvg_sim_msgs_gencpp)



#target_link_libraries(hector_uav_msgs ${catkin_LIBRARIES})
#add_dependencies(hector_uav_msgs msg_pkg_gencpp)
#add_dependencies(vision ${catkin_EXPORTED_TARGETS})
#add_dependencies(${p} ${catkin_EXPORTED_TARGETS} hector_uav_msgs_generate_messages_cpp)
#add_dependencies(${p} ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)
#target_link_libraries(hector_uav_msgs ${catkin_LIBRARIES})
#add_dependencies(hector_uav_msgs ${catkin_EXPORTED_TARGETS})
#add_dependencies(${p} ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)



#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS vision vision_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_vision.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)

