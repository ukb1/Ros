cmake_minimum_required(VERSION 3.8)
project(data_type)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME} 
  "msg/FirstMsg.msg"
  )

ament_package()
