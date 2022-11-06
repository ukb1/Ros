#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/add_two_ints.hpp>

class ServerNode: public rclcpp::Node
{
    public:
        ServerNode():Node("ServerNode")
        {
            _server = this->create_service<example_interfaces::srv::AddTwoInts>("service_server",
                                                                                std::bind(&ServerNode::callBackServer, this,
                                                                                std::placeholders::_1,std::placeholders::_2));
            RCLCPP_INFO(this->get_logger(),"Server has been started.");


        }
    private:
        void callBackServer(const example_interfaces::srv::AddTwoInts::Request::SharedPtr _request,
                            const example_interfaces::srv::AddTwoInts::Response::SharedPtr _response)
                            {
                                _response->sum = _request->a + _request->b;
                                RCLCPP_INFO(this->get_logger(),"%d + %d = %d",_request->a,_request->b,_response->sum);
                            }
        rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr _server;


};


int main()
{

}