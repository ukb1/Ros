#include "rclcpp/rclcpp.hpp"
#include "data_type/srv/get_led.hpp"

class Battery: public rclcpp::Node
{
private:
    std::string battery_state;
    double battery_changed;
    rclcpp::TimerBase::SharedPtr _timer;
    std::vector<std::shared_ptr<std::thread>> set_led_threads;
    std::vector<std::thread> _threads;

    void setLed(int led_number, int state)
    {
        _threads.push_back(std::thread(std::bind(&Battery::callSetLedService,this, led_number, state)));
    }
    void callSetLedService(int led_number, int state)
    {
        auto _client = this->create_client<data_type::srv::GetLed>("set_led");
        while(!_client->wait_for_service(std::chrono::seconds(1)))
        {
           RCLCPP_WARN(this->get_logger(), "Waiting for Service Server to be up...");
        }

        auto request = std::make_shared<data_type::srv::GetLed::Request>();
        request->led_id = led_number;
        request->set_led = state;

        auto future = _client->async_send_request(request);

        try
        {
            auto response = future.get();
        }
        catch(const std::exception& e)
        {
           RCLCPP_ERROR(this->get_logger(), "Service call failed.");
        }
    }
    void checkBatteryState()
    {
        double time_now = this->get_clock()->now().seconds();
        if(battery_state == "full")
        {
            if(time_now - battery_changed > 4.0)
            {
                RCLCPP_INFO(this->get_logger(), "Battery is empty! Charging battery...");
                battery_state = "empty";
                battery_changed = time_now;
                setLed(3,1);
            }
        }
        else
        {
            if(time_now - battery_changed > 6.0)
            {
                battery_state = "full";
                battery_changed = time_now;
                setLed(3,0);
            }
        }
    }
public:
    Battery(): Node("Battery_state"), battery_state("full")
    {
        battery_changed = this->get_clock()->now().seconds();
        _timer = this->create_wall_timer(std::chrono::seconds(1),std::bind(&Battery::checkBatteryState,this));

    }
};

int main(int argc, char** argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<Battery>());
    rclcpp::shutdown();
}
