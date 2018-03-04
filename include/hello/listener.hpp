#pragma once

#include <hello/Greeting.h>
#include <ros/ros.h>

namespace hello {

class Listener {
  ros::Subscriber greetSubscriber;
  int greetSeq = -1;

 public:
  Listener(ros::NodeHandle& node);
  void onGreet(Greeting::ConstPtr const& msg);
};

};  // namespace hello