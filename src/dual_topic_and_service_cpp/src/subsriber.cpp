#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/int64.hpp>
#include <example_interfaces/srv/set_bool.hpp>

class myMultiNode : public rclcpp::Node
{
    private:
        int64_t _counter;
        rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr _subsciber;
        void subs_callBack(const example_interfaces::msg::Int64 msg);



       

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

myMultiNode::myMultiNode():Node("sub_multi_node"),_counter(0)
{

}

void myMultiNode::subs_callBack(const example_interfaces::msg::Int64 msg)
{
    RCLCPP_INFO(this->get_logger(),"Subscriber has been started.");
    // std::string data = std::to_string(msg->data);
    // RCLCPP_INFO(this->get_logger(),"data: %s",data);

}
