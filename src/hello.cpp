
#include "hello/Greeting.h"
#include "ros/ros.h"

char const* node_name = "hello_node";

int main(int argc, char** argv) {
  hello::Greeting greet;
  greet.text = "Hello !!";
  ROS_INFO("%s", greet.text.c_str());
}