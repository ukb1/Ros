cmake_minimum_required(VERSION 3.8)
project(dual_topic_and_service_cpp)


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(subs_cpp src/subsriber.cpp)
add_executable(pub_cpp src/publisher.cpp)

ament_target_dependencies(subs_cpp rclcpp example_interfaces)
ament_target_dependencies(pub_cpp rclcpp example_interfaces)

install(
  TARGETS
  subs_cpp
  pub_cpp
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
