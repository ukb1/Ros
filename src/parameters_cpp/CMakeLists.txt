cmake_minimum_required(VERSION 3.8)
project(parameters_cpp)


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)


add_executable(param_node src/param.cpp)
ament_target_dependencies(param_node rclcpp example_interfaces)

install(
  TARGETS
  param_node
  DESTINATION lib/${PROJECT_NAME}
)



ament_package()
