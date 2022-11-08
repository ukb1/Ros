
#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/int64.hpp>
#include <example_interfaces/srv/set_bool.hpp>

class myMultiNode : public rclcpp::Node
{
    public:
        myMultiNode():Node("sub_node"),_counter(0)
        {
            _publisher = this->create_publisher<example_interfaces::msg::Int64>("pub_node_counter",10);
            RCLCPP_INFO(this->get_logger(),"Counter started...");
            _timer = this->create_wall_timer(std::chrono::seconds(1),std::bind(&myMultiNode::pub_callBack,this));


        }
    
    private:
        int64_t _counter;
        void pub_callBack();
        rclcpp::TimerBase::SharedPtr _timer;
        rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr _publisher;

};

int main(int argc, char** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<myMultiNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    
}

void myMultiNode:: pub_callBack()
{
    _counter++;
    auto msg = example_interfaces::msg::Int64();
    RCLCPP_INFO(this->get_logger(),"%ld",_counter);
    msg.data = _counter;
    _publisher->publish(msg);

}