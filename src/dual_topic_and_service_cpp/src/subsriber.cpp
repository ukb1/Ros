#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/int64.hpp>
#include <example_interfaces/srv/set_bool.hpp>

class myMultiNode : public rclcpp::Node
{
    private:
        int64_t _counter;
        rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr _subsciber;
        void subs_callBack(const example_interfaces::msg::Int64::SharedPtr msg);
    public:
        myMultiNode();
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<myMultiNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}


myMultiNode::myMultiNode():Node("Subscriber_Node"),_counter(0)
{
    _subsciber = this->create_subscription<example_interfaces::msg::Int64>("pub_node_counter",10,
                                                                        std::bind(&myMultiNode::subs_callBack, this, std::placeholders::_1));
    RCLCPP_INFO(this->get_logger(),"Subscriber has been started");

}

void myMultiNode::subs_callBack(const example_interfaces::msg::Int64::SharedPtr msg)
{
    int _counter = msg->data;
    RCLCPP_INFO(this->get_logger(), "%d",_counter);

}
