cmake_minimum_required(VERSION 3.8)
project(node_hello_ros)



find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(hello src/hello_ros.cpp)

ament_target_dependencies(hello rclcpp)

install(
  TARGETS
  hello
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
