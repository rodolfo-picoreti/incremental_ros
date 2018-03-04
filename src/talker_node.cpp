
#include <hello/talker.hpp>
#include <ros/ros.h>

char const* node_name = "talker_node";

int main(int argc, char** argv) {
  ros::init(argc, argv, node_name);
  ros::NodeHandle node;
  // ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug);
  hello::Talker talker(node);
  ROS_INFO("Running ...");
  ros::spin();
}