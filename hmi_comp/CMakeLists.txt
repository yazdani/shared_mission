cmake_minimum_required(VERSION 2.8.3)
project(hmi_comp)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
  message_generation
  message_runtime
  tf)

add_message_files(
   FILES
   Propkey.msg
   Desig.msg)

add_service_files(
   FILES
   tldl_parser.srv
   HMIDesig.srv)

generate_messages(
   DEPENDENCIES
  geometry_msgs   std_msgs)

catkin_package(
  CATKIN_DEPENDS geometry_msgs message_generation message_runtime roscpp rospy std_msgs)

include_directories(
  ${catkin_INCLUDE_DIRS})

add_executable(tldl_parser src_cpp/tldl_parser.cpp)
target_link_libraries(tldl_parser ${catkin_LIBRARIES})
add_dependencies(tldl_parser hmi_comp_gencpp)


add_executable(shutdown_tldl_parser src_cpp/shutdown_tldl_parser.cpp)
target_link_libraries(shutdown_tldl_parser ${catkin_LIBRARIES})
add_dependencies(shutdown_tldl_parser hmi_comp_gencpp)
catkin_package()
