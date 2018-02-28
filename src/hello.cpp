
#include "hello/Greeting.h"
#include "ros/ros.h"

char const* node_name = "hello_node";

int main(int argc, char** argv) {
  ros::init(argc, argv, node_name);
  ros::NodeHandle node;
  auto greetPublisher = node.advertise<hello::Greeting>(/*topic=*/"greet", /*queue_size=*/1);

  ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug);

  auto timer = node.createTimer(ros::Duration(/*seconds=*/0.1), [&](ros::TimerEvent const& ev) {
    ros::Duration jitter = ev.current_real - ev.current_expected;
    ROS_DEBUG("Publish jitter %d ms", static_cast<int>(jitter.sec * 1e3 + jitter.nsec / 1e6));
    hello::Greeting greet;
    greet.text = "Hello !!";
    greetPublisher.publish(greet);
  });

  ROS_INFO("Running ...");
  ros::spin();
}