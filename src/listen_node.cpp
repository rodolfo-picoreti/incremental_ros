
#include <hello/listener.hpp>
#include <ros/ros.h>

char const* node_name = "listen_node";

int main(int argc, char** argv) {
  ros::init(argc, argv, node_name);
  ros::NodeHandle node;
  hello::Listener listener(node);
  ROS_INFO("Running ...");
  ros::spin();
}