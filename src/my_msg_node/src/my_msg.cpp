#include "rclcpp/rclcpp.hpp"
#include "data_type/msg/first_msg.hpp"


class MyMsg: public rclcpp::Node
{
private:
    void publisCallback()
    {
        auto msg = data_type::msg::FirstMsg();
        msg.data = 32;
        msg.msg = "hello";
        msg.ready = 1;
        msg.temperature = 12.2;
        _publisher->publish(msg);

    }
    rclcpp::TimerBase::SharedPtr _timer;
    rclcpp::Publisher<data_type::msg::FirstMsg>::SharedPtr _publisher;
public:
    MyMsg(): Node("First_Msg")
    {
        _publisher = this->create_publisher<data_type::msg::FirstMsg>("Publisher_node",10);
        _timer = this->create_wall_timer(std::chrono::seconds(1),std::bind(&MyMsg::publisCallback, this));
    }

};

int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<MyMsg>());
    rclcpp::shutdown();

}
