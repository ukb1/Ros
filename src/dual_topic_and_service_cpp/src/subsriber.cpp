#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/int64.hpp>
#include <example_interfaces/srv/set_bool.hpp>

class myMultiNode : public rclcpp::Node
{
    private:
        int64_t _counter;
        rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr _subsciber;
        rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr _publisher;
        rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr _service_servis;
        void subs_callBack(const example_interfaces::msg::Int64::SharedPtr);
        void reset_callBack(const example_interfaces::srv::SetBool::Request::SharedPtr , const example_interfaces::srv::SetBool::Response::SharedPtr);
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


myMultiNode::myMultiNode():Node("Subscriber_Node")
{
    _subsciber = this->create_subscription<example_interfaces::msg::Int64>("pub_node_counter",10,std::bind
                                                                         (&myMultiNode::subs_callBack,this, std::placeholders::_1));
    _publisher = this->create_publisher<example_interfaces::msg::Int64>("send_msg",10);
    _service_servis = this->create_service<example_interfaces::srv::SetBool>("reset_service",
                                                                            std::bind(&myMultiNode::reset_callBack,this,std::placeholders::_1,
                                                                            std::placeholders::_2));
    RCLCPP_INFO(this->get_logger(),"Subscriber has been started");

}

void myMultiNode::subs_callBack(const example_interfaces::msg::Int64::SharedPtr msg)
{
    _counter += msg->data;
    RCLCPP_INFO(this->get_logger(), "%ld",_counter);
    auto newData = example_interfaces::msg::Int64();
    newData.data = _counter;
    _publisher->publish(newData);

}

void myMultiNode::reset_callBack(const example_interfaces::srv::SetBool::Request::SharedPtr _request, const example_interfaces::srv::SetBool::Response::SharedPtr _response)
{
    if(_request->data==true)
    {
        _counter = 0;
        _response->success = true;
        _response->message = "transaction successful";
    }
    else 
    {
        _response->success = false;
        _response->message = "operation failed";    
    }

}
