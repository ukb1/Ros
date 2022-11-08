cmake_minimum_required(VERSION 3.8)
project(topic_subscriber_cpp)


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(subscriber_cpp src/subscriber.cpp)
ament_target_dependencies(subscriber_cpp rclcpp example_interfaces)

install(
    TARGETS
    subscriber_cpp
    DESTINATION lib/${PROJECT_NAME}
)


ament_package()
