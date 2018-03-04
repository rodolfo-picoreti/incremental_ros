#include <hello/listener.hpp>

namespace hello {

Listener::Listener(ros::NodeHandle& node) {
  // prefer udp over tcp
  auto hints = ros::TransportHints().unreliable().reliable().tcpNoDelay();
  greetSubscriber = node.subscribe(
      /*topic=*/"greet", /*queue_size=*/1, &Listener::onGreet, this, hints);
}

void Listener::onGreet(hello::Greeting::ConstPtr const& msg) {
  auto latency = ros::Time::now() - msg->header.stamp;
  if (greetSubscriber.getNumPublishers() == 1) {
    // Sequence checking only works if we have a single publisher
    auto lostPackets = msg->header.seq - greetSeq - 1;
    if (greetSeq != -1 && lostPackets) { ROS_WARN("Lost %d message(s)", lostPackets); }
    greetSeq = msg->header.seq;
  }

  ROS_INFO("[%d][%dus] Greeting:='%s'", msg->header.seq,
           static_cast<int>(latency.sec * 1e6 + latency.nsec / 1e3), msg->text.c_str());
}

}  // namespace hello