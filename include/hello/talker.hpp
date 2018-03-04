#pragma once

#include <dynamic_reconfigure/server.h>
#include <hello/Greeting.h>
#include <hello/HelloConfig.h>
#include <ros/ros.h>

namespace hello {

class Talker {
  ros::Timer timer;
  ros::Publisher greetPublisher;
  dynamic_reconfigure::Server<HelloConfig> parameters;
  HelloConfig config;

 public:
  Talker(ros::NodeHandle& node);
  void onParameterChange(HelloConfig& newConfig, uint32_t level);
  void onTimerTick(ros::TimerEvent const& ev);
};

}  // namespace hello
