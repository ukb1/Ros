cmake_minimum_required(VERSION 3.8)
project(service_server_cpp)


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(server src/server.cpp)
ament_target_dependencies(server rclcpp example_interfaces)

install(
  TARGETS
  server
  DESTINATION lib/${PROJECT_NAME}
)
ament_package()
