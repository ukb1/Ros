#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/add_two_ints.hpp>


class clientNode: public rclcpp::Node
{
    public:
        clientNode():Node("Client_node_opp")
        {
            thread1 = std::thread(std::bind(&clientNode::callBackService,this, 12,20)); //Parametre olarak burda direkt değer vermek istiyoruz yer tutmak yerine
            thread2 = std::thread(std::bind(&clientNode::callBackService,this, 5,45)); //Parametre olarak burda direkt değer vermek istiyoruz yer tutmak yerine
            // Ya da 
            _thread.push_back(std::thread(std::bind(&clientNode::callBackService,this, 6,45)));
            _thread.push_back(std::thread(std::bind(&clientNode::callBackService,this, 9,45)));
            _thread.push_back(std::thread(std::bind(&clientNode::callBackService,this, 456,45)));
        }

        void callBackService(int a, int b)
        {
            auto _client = this->create_client<example_interfaces::srv::AddTwoInts>("service_server");

            while(!_client->wait_for_service(std::chrono::seconds(1)))
            {
                RCLCPP_WARN(this->get_logger(),"Wait for the server to be up ...");
            }
            auto _request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
            _request->a=a;
            _request->b=b;
            
            auto future = _client->async_send_request(_request);

            try
            {
                auto response = future.get();
                RCLCPP_INFO(this->get_logger(),"%d+%d=%ld",a,b,response->sum);
            }
            catch(const std::exception &e)
            {
                RCLCPP_ERROR(this->get_logger(), "Error while calling service.");

            }


        }
    private:
        std::thread thread1 ;
        std::thread thread2 ;
        std::vector<std::thread> _thread ;


};


int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<clientNode>();


    // if(rclcpp::spin_until_future_complete(node,future) == rclcpp::FutureReturnCode::SUCCESS)
    // {
    //     RCLCPP_INFO(node->get_logger(),"%ld+%ld=%ld",_request->a,_request->b,future.get()->sum);
    // }
    // else 
    // {
    //     RCLCPP_ERROR(node->get_logger(),"Error while calling service");
    // }

    rclcpp::spin(node);
    rclcpp::shutdown();

}
