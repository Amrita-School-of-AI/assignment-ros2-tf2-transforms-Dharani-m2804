cmake_minimum_required(VERSION 3.8)
project(ros2_tf2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find required packages
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)

# Create executable
add_executable(tf2_broadcaster src/tf2_broadcaster.cpp)

ament_target_dependencies(tf2_broadcaster
  rclcpp
  tf2_ros
  geometry_msgs
)

# Install executable
install(TARGETS
  tf2_broadcaster
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
