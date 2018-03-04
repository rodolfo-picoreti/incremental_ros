
#include <hello/Greeting.h>
#include <ros/ros.h>

char const* node_name = "listen_node";

class Listener {
  ros::Subscriber greetSubscriber;

 public:
  Listener(ros::NodeHandle& node) {
    // prefer udp over tcp
    auto hints = ros::TransportHints().unreliable().reliable().tcpNoDelay();
    greetSubscriber = node.subscribe(
        /*topic=*/"greet", /*queue_size=*/1, &Listener::onGreet, this);
  }

  void onGreet(hello::Greeting::ConstPtr const& msg) const {
    ROS_INFO("Received greeting: %d %s", msg->header.seq, msg->text.c_str());
  };
};

int main(int argc, char** argv) {
  ros::init(argc, argv, node_name);
  ros::NodeHandle node;
  Listener listener(node);
  ROS_INFO("Running ...");
  ros::spin();
}