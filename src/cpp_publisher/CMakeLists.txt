cmake_minimum_required(VERSION 3.8)
project(cpp_publisher)



# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(publisher_cpp src/publisher.cpp)
ament_target_dependencies(publisher_cpp rclcpp example_interfaces)

install(
  TARGETS
  publisher_cpp
  DESTINATION lib/${PROJECT_NAME}

)



ament_package()
