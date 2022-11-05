#include <rclcpp/rclcpp.hpp>

class myNode: public rclcpp::Node
{
    public:
        myNode():Node("OOP_Node"),_counter(0)
        {
            RCLCPP_INFO(this->get_logger(),"Hello Cpp OPP node");
            _timer = this->create_wall_timer(std::chrono::seconds(1),
                                            std::bind(&myNode::timerCallBack,this));
        }
    
    private:
        void timerCallBack()
        {
            _counter++;
            RCLCPP_INFO(this->get_logger(),"%d) hello",_counter);
        }

    rclcpp::TimerBase::SharedPtr _timer;
    unsigned   int _counter;


};

int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<myNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();

}