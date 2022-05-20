cmake_minimum_required(VERSION 2.8)
project(image_transport_tutorial)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  image_transport
)
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp
  sensor_msgs
  std_msgs
  image_transport
  DEPENDS system_lib
)
include_directories(
  ${OpenCV_INCLUDE_DIRS}
  ${cv_bridge_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
  include
)
find_package( OpenCV REQUIRED )
find_package( cv_bridge REQUIRED )


add_executable(my_subscriber src/my_subscriber.cpp)
target_link_libraries(my_subscriber   ${catkin_LIBRARIES} ${OpenCV_LIBS} ${cv_bridge_LIBRARIES}
)
