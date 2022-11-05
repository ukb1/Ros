#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/string.hpp>

class myNode: public rclcpp::Node
{
    public:
        myNode():Node("OOP_Node")
        {
            _Subscriber = this->create_subscription<example_interfaces::msg::String>("Publisher_Node",10,
                                                                                    std::bind(&myNode::callBackSubscriber, this, std::placeholders::_1));

            RCLCPP_INFO(this->get_logger(),"Subscriber has been started.");
        }
    
    private:
        void callBackSubscriber(const example_interfaces::msg::String::SharedPtr msg )
        {
            RCLCPP_INFO(this->get_logger(), "%s",msg->data.c_str());
        }
        rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr _Subscriber;
      
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<myNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();

}