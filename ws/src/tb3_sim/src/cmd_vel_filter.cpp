#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
using std::placeholders::_1;

class VelocityFilter : public rclcpp::Node
{
  public:
    VelocityFilter()
    : Node("velocity_filter")
    {
      subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
      "/robot1/cmd_vel", 10, std::bind(&VelocityFilter::topic_callback, this, _1));
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/robot1/modified_cmd_vel", 10);
    }

  private:
    void topic_callback(const geometry_msgs::msg::Twist & msg) const
    {
      //RCLCPP_INFO(this->get_logger(), msg.linear.x );
      publisher_->publish(msg);
      
    }





    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VelocityFilter>());
  rclcpp::shutdown();
  return 0;
}