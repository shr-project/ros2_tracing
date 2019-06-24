// Copyright 2019 Robert Bosch GmbH
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

#define NODE_NAME "test_ping"
#define SUB_TOPIC_NAME "pong"
#define PUB_TOPIC_NAME "ping"

class PingNode : public rclcpp::Node
{
public:
  explicit PingNode(rclcpp::NodeOptions options)
  : Node(NODE_NAME, options)
  {
    sub_ = this->create_subscription<std_msgs::msg::String>(
      SUB_TOPIC_NAME,
      rclcpp::QoS(10),
      std::bind(&PingNode::callback, this, std::placeholders::_1));
    pub_ = this->create_publisher<std_msgs::msg::String>(
      PUB_TOPIC_NAME,
      rclcpp::QoS(10));
    timer_ = this->create_wall_timer(
      500ms,
      std::bind(&PingNode::timer_callback, this));
  }

private:
  void callback(const std_msgs::msg::String::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "[output] %s", msg->data.c_str());
    rclcpp::shutdown();
  }

  void timer_callback()
  {
    auto msg = std::make_shared<std_msgs::msg::String>();
    msg->data = "some random ping string";
    pub_->publish(*msg);
  }

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  rclcpp::executors::SingleThreadedExecutor exec;
  auto ping_node = std::make_shared<PingNode>(rclcpp::NodeOptions());
  exec.add_node(ping_node);

  printf("spinning\n");
  exec.spin();

  // Will actually be called inside the node's callback
  rclcpp::shutdown();
  return 0;
}