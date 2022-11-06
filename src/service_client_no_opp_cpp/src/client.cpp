#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/add_two_ints.hpp>



int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<rclcpp::Node>("Client_node");
    auto client = node->create_client<example_interfaces::srv::AddTwoInts>("service_server");

    while(!client->wait_for_service(std::chrono::seconds(1)))
    {
        RCLCPP_WARN(node->get_logger(),"Wait for the server to be up...");
    }

    auto _request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    _request->a = 10;
    _request->b = 20;

    auto future = client->async_send_request(_request);



    if(rclcpp::spin_until_future_complete(node,future) == rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(node->get_logger(),"%ld+%ld=%ld",_request->a,_request->b,future.get()->sum);
    }
    else 
    {
        RCLCPP_ERROR(node->get_logger(),"Error while calling service");
    }

    rclcpp::spin(node);
    rclcpp::shutdown();

}