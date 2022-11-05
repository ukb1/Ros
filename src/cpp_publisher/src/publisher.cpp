#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/string.hpp>

class myNode: public rclcpp::Node
{
    public:
        myNode():Node("OOP_Node"),_counter(0),node_name("Veronica")
        {
            _publisher = this->create_publisher<example_interfaces::msg::String>("Publisher_Node",10);
            RCLCPP_INFO(this->get_logger(),"Hello Cpp OPP node");
            RCLCPP_INFO(this->get_logger(),"Node station has been started.");
            _timer = this->create_wall_timer(std::chrono::seconds(1),
                                            std::bind(&myNode::publishNews,this));
        }
    
    private:
        void publishNews()
        {
            _counter++;
            auto msg = example_interfaces::msg::String();
            msg.data = std::to_string(_counter) + std::string(" Hi, this is ") + node_name;
            _publisher->publish(msg);
        }
      
        std::string node_name;
        rclcpp::TimerBase::SharedPtr _timer;
        unsigned int _counter;
        rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr _publisher;


};

int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<myNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();

}