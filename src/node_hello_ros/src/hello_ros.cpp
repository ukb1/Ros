#include <rclcpp/rclcpp.hpp>


int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<rclcpp::Node>("Hello_Node");
    RCLCPP_INFO(node->get_logger(),"Hello ROS 2");
    rclcpp::spin(node);
    rclcpp::shutdown();

}