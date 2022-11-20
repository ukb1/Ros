#include "rclcpp/rclcpp.hpp"
#include "data_type/msg/led_state.hpp"
#include "data_type/srv/get_led.hpp"

class myRobot : public rclcpp::Node
{
private:
    rclcpp::TimerBase::SharedPtr _timer;
    rclcpp::Publisher<data_type::msg::LedState>::SharedPtr _publisher; 
    rclcpp::Service<data_type::srv::GetLed>::SharedPtr _server;
    std::vector<int8_t> led_states;
    void robotCallback()
    {
        auto msg = data_type::msg::LedState();
        msg.led_state = led_states;
        _publisher->publish(msg);

    }
    void SetLed(const data_type::srv::GetLed::Request::SharedPtr _request,
                const data_type::srv::GetLed::Response::SharedPtr _response)
    {
       if(_request->led_id > 3)  _response->success = 0;
       else if(!(_request->set_led ==0 || _request->set_led == 1 )) _response->success = 0;
       else
       {
             _response->success = 1;
             led_states[_request->led_id-1] = _request->set_led;
       }

    }

public:
    myRobot():Node("robot_node"),led_states(3,0) /* Bu kısımda 3 tamsayı ve hepsine 8 atanması
    gerektiğini anlarız ya da tek tek {1 2 3} şeklinde diyiyi doldurabiliriz.
    */
    {
        _publisher = this->create_publisher<data_type::msg::LedState>("robot_led_sate",10);
        _timer = this->create_wall_timer(std::chrono::seconds(1),std::bind(&myRobot::robotCallback, this));
        _server = this->create_service<data_type::srv::GetLed>("set_led",std::bind(&myRobot::SetLed, this,std::placeholders::_1,std::placeholders::_2));
    }
};




int main(int argc , char ** argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<myRobot>());
    rclcpp::shutdown();

}