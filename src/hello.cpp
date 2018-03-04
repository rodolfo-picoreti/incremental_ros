
#include <dynamic_reconfigure/server.h>
#include <hello/Greeting.h>
#include <hello/HelloConfig.h>
#include <ros/ros.h>

char const* node_name = "hello_node";

int main(int argc, char** argv) {
  ros::init(argc, argv, node_name);
  ros::NodeHandle node;

  // ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug);

  auto greetPublisher = node.advertise<hello::Greeting>(/*topic=*/"greet", /*queue_size=*/1);

  dynamic_reconfigure::Server<hello::HelloConfig> server;
  hello::HelloConfig config;
  server.getConfigDefault(config);

  auto timer = node.createTimer(ros::Duration(/*seconds=*/0.1), [&](ros::TimerEvent const& ev) {
    ros::Duration jitter = ev.current_real - ev.current_expected;
    ROS_DEBUG("Publish jitter %d ms", static_cast<int>(jitter.sec * 1e3 + jitter.nsec / 1e6));
    hello::Greeting greet;
    greet.header.stamp = ros::Time::now();
    greet.text = "Hello " + config.greeter_name;
    greetPublisher.publish(greet);
  });

  server.setCallback([&](hello::HelloConfig& newConfig, uint32_t level) {
    config = newConfig;
    ROS_INFO("New parameters: name:=%s rate:=%d", config.greeter_name.c_str(), config.greeter_hz);
    timer.setPeriod(ros::Duration(1.0 / config.greeter_hz));
  });

  ROS_INFO("Running ...");
  ros::spin();
}