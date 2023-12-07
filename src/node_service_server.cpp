#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

#include <memory>

using std::placeholders::_1;
using std::placeholders::_2;


class NodeServiceServer : public rclcpp::Node
{
public:
    NodeServiceServer() : Node("node_service_server")
    {
        serviceServer_ = this->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints_service", std::bind(&NodeServiceServer::onReceiveRequest, this, _1, _2));

    }

private:
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr serviceServer_;

    void onReceiveRequest(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request, 
                                std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
    {
        RCLCPP_INFO(this->get_logger(), "Receive request to add %ld and %ld...", request->a, request->b);
        response->sum = request->a + request->b;
        RCLCPP_INFO(this->get_logger(), "Sent response %ld...", response->sum);
    }

};


int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<NodeServiceServer>());
    rclcpp::shutdown();

    return 0;

}