cmake_minimum_required(VERSION 3.5)
project(robotics_camp_cpp)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(feed_forward_circle_node src/feed_forward_circle.cpp)
ament_target_dependencies(feed_forward_circle_node rclcpp geometry_msgs turtlesim)

install(TARGETS
  feed_forward_circle_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
