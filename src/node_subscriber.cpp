#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class NodeSubscriber : public rclcpp::Node
{
public:
    NodeSubscriber() : Node("node_subscriber")
    {
        subscription_ = this->create_subscription<std_msgs::msg::String>("hello_topic", 10, std::bind(&NodeSubscriber::onReceivingHello, this, _1));

    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;

    void onReceivingHello(const std_msgs::msg::String &msg) const
    {
        RCLCPP_INFO(this->get_logger(), "Receive msg: %s", msg.data.c_str());
    }

};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<NodeSubscriber>());
    rclcpp::shutdown();

    return 0;
}