#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;


class NodePublisher : public rclcpp::Node
{
public:
    NodePublisher() : Node("node_publisher"), count_(0)
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("hello_topic", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&NodePublisher::timer_callback, this));
    }

private:
    size_t count_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        message.data = "Hello World" + std::to_string(count_++);
        RCLCPP_INFO(this->get_logger(), "Publishing: %s", message.data.c_str());
        publisher_->publish(message);

    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<NodePublisher>());
    rclcpp::shutdown();

    return 0;

}