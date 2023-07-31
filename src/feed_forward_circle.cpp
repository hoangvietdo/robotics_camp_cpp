#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

class RobotController : public rclcpp::Node{
public:
  RobotController(): Node("feed_forward_circle_node") {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 5);
    timer_ = this->create_wall_timer(0.05s, std::bind(&RobotController::feed_forward_controller, this));
  }
private:
  void feed_forward_controller(){
    auto msg = geometry_msgs::msg::Twist();
    x_d = -a * b * sin(b * t);
    y_d = a * b * cos(b * t);
    x_dd = -a * b * b * cos(b * t);
    y_dd = -a * b * b * sin(b * t);

    // TODO
    // Using keyboard to start and stop the robot

    if (t >= 5.0){
      msg.linear.x = sqrt(pow(x_d, 2) + pow(y_d, 2));
      msg.angular.z = (y_dd * x_d - y_d * x_dd) / msg.linear.x;
      publisher_->publish(msg);
      t += 0.05;
    }else{
      msg.linear.x = 0.0;
      msg.angular.z = 0.0;
      publisher_->publish(msg);
      t += 0.05;
    }
  }
  float t = 0.0;
  float a = 5.0;
  float b = 0.7;
  float x_d, y_d, x_dd, y_dd;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RobotController>());
  rclcpp::shutdown();
  return 0;
}
