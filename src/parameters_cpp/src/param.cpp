#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class ParamNode : public rclcpp::Node
{
private:
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr _publisher;
    rclcpp::TimerBase::SharedPtr _timer;
    int _number;

    void paramCallbak()
    {
        auto msg = example_interfaces::msg::Int64();
        msg.data = _number;
        _publisher->publish(msg);

    }
public:
    ParamNode() : Node("param_node"), _number(0)
    {
        this->declare_parameter("first_param",10); // ilk parametre belirlenmiş olduk.
        _number =  this->get_parameter("first_param").as_int(); // Parametreden beklenen değerin int olduğunu belirtiyoruz.
        _publisher = this->create_publisher<example_interfaces::msg::Int64>("number",10);
        _timer = this->create_wall_timer(std::chrono::seconds(1),std::bind(&ParamNode::paramCallbak,this));

    }



};



int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ParamNode>());
    rclcpp::shutdown();
    return 0;
}
