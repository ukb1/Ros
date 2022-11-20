cmake_minimum_required(VERSION 3.8)
project(my_msg_node_cpp)


find_package(ament_cmake REQUIRED)
find_package(data_type REQUIRED)
find_package(rclcpp REQUIRED)


add_executable(first_msg_node src/my_msg.cpp)

ament_target_dependencies(first_msg_node rclcpp data_type)

install(
  TARGETS
  first_msg_node 
  DESTINATION lib/${PROJECT_NAME}

)

ament_package()
