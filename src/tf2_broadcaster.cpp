#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_broadcaster.h"

using namespace std::chrono_literals;

class Tf2Broadcaster : public rclcpp::Node
{
public:
  Tf2Broadcaster()
  : Node("tf2_broadcaster")
  {
    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

    timer_ = this->create_wall_timer(
      1s, std::bind(&Tf2Broadcaster::broadcast_transform, this));

    RCLCPP_INFO(this->get_logger(), "TF2 Broadcaster started");
  }

private:
  void broadcast_transform()
  {
    geometry_msgs::msg::TransformStamped transform;

    transform.header.stamp = this->get_clock()->now();
    transform.header.frame_id = "world";
    transform.child_frame_id = "robot";

    transform.transform.translation.x = 1.0;
    transform.transform.translation.y = 2.0;
    transform.transform.translation.z = 0.0;

    transform.transform.rotation.x = 0.0;
    transform.transform.rotation.y = 0.0;
    transform.transform.rotation.z = 0.0;
    transform.transform.rotation.w = 1.0;

    tf_broadcaster_->sendTransform(transform);
  }

  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Tf2Broadcaster>());
  rclcpp::shutdown();
  return 0;
}
