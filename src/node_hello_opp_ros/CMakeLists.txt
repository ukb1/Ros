cmake_minimum_required(VERSION 3.8)
project(node_hello_opp_ros)



# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(hello_opp src/hello_ros_opp.cpp)
ament_target_dependencies(hello_opp rclcpp)

install(
  TARGETS
  hello_opp
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
