cmake_minimum_required(VERSION 3.8)
project(my_robot)


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(data_type REQUIRED)

add_executable(my_robot_node src/led_state.cpp)
ament_target_dependencies(my_robot_node rclcpp data_type)

install(
  TARGETS
  my_robot_node
  DESTINATION lib/${PROJECT_NAME}
)



ament_package()
