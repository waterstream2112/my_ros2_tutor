#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;
using std::placeholders::_1;

using ServiceResponseFuture = rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture;

class NodeServiceClient : public rclcpp::Node
{
public:
    NodeServiceClient() : Node("node_service_client")
    {
        serviceClient_ = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints_service");

        while (!serviceClient_->wait_for_service(1s))
        {
            RCLCPP_INFO(this->get_logger(), "Keep waiting for service to be available...");
        }
        
        example_interfaces::srv::AddTwoInts::Request::SharedPtr request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = 2;
        request->b = 3;

        serviceClient_->async_send_request(request, std::bind(&NodeServiceClient::onReceiveResponse, this, _1));

    }

private:
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr serviceClient_;

    void onReceiveResponse(ServiceResponseFuture response)
    {
        RCLCPP_INFO(this->get_logger(), "Response is %ld", response.get()->sum);
    }
};


int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<NodeServiceClient>());
    rclcpp::shutdown();

    return 0;
}