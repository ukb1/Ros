cmake_minimum_required(VERSION 3.8)
project(service_client_no_opp_cpp)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

find_package(example_interfaces REQUIRED)

add_executable(clien_no_opp src/client.cpp)
ament_target_dependencies(clien_no_opp rclcpp example_interfaces)

install(
  TARGETS
  clien_no_opp
  DESTINATION lib/${PROJECT_NAME}
)



ament_package()
