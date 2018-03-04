#include <hello/talker.hpp>

namespace hello {

Talker::Talker(ros::NodeHandle& node) {
  greetPublisher = node.advertise<Greeting>(/*topic=*/"greet", /*queue_size=*/1);

  parameters.getConfigDefault(config);
  parameters.setCallback(boost::bind(&Talker::onParameterChange, this, _1, _2));

  ros::Duration timerPeriod(/*seconds=*/1.0 / config.greeter_hz);
  timer = node.createTimer(timerPeriod, &Talker::onTimerTick, this);
}

void Talker::onParameterChange(HelloConfig& newConfig, uint32_t) {
  config = newConfig;
  timer.setPeriod(ros::Duration(1.0 / config.greeter_hz));
  ROS_INFO("New parameters: name:=%s rate:=%d", config.greeter_name.c_str(), config.greeter_hz);
}

void Talker::onTimerTick(ros::TimerEvent const& ev) {
  ros::Duration jitter = ev.current_real - ev.current_expected;
  ROS_DEBUG("Publish jitter %d ms", static_cast<int>(jitter.sec * 1e3 + jitter.nsec / 1e6));

  Greeting greet;
  greet.header.stamp = ros::Time::now();
  greet.text = "Hello " + config.greeter_name;
  greetPublisher.publish(greet);
}

}  // namespace hello
