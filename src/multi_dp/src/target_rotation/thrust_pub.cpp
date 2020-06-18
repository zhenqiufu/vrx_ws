#include <multi_dp/motor_msgs.h>
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64MultiArray.h>
const double PI = 3.1415926;
ros::Publisher pub_lateral_angle, pub_lateral_cmd, pub_left_angle, pub_left_cmd,
    pub_right_angle, pub_right_cmd;
void callback(const multi_dp::motor_msgs &msg) {
  std_msgs::Float32 lateral_angle, lateral_cmd, left_angle, left_cmd,
      right_angle, right_cmd;
  left_angle.data = -msg.alpha[0];
  // left_angle.data = 270;
  left_cmd.data = msg.rotation[0] / 100;
  right_angle.data = -msg.alpha[1];
  // right_angle.data = 0;
  right_cmd.data = msg.rotation[1] / 100;
  lateral_angle.data = -PI / 2 - msg.alpha[2];
  // lateral_angle.data = 0;
  lateral_cmd.data = msg.rotation[2] / 100;
  if (lateral_angle.data > PI) {
    lateral_angle.data = lateral_angle.data - 2 * PI;
  }

  if (lateral_angle.data < -PI) {
    lateral_angle.data = lateral_angle.data + 2 * PI;
  }
  pub_lateral_angle.publish(lateral_angle);
  pub_lateral_cmd.publish(lateral_cmd);
  pub_left_angle.publish(left_angle);
  pub_left_cmd.publish(left_cmd);
  pub_right_angle.publish(right_angle);
  pub_right_cmd.publish(right_cmd);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "thrust_pub");
  ros::NodeHandle nh;
  ros::NodeHandle priv("~");
  std::string topic_sub, topic_pub_lateral_angle, topic_pub_lateral_cmd,
      topic_pub_left_angle, topic_pub_left_cmd, topic_pub_right_angle,
      topic_pub_right_cmd;

  priv.param<std::string>("topic_sub", topic_sub,
                          std::string("/k_a/target_rotation"));
  //中-角度
  priv.param<std::string>(
      "topic_pub_lateral_angle", topic_pub_lateral_angle,
      std::string("/defender_a/thrusters/lateral_thrust_angle"));
  //中-转速
  priv.param<std::string>(
      "topic_pub_lateral_cmd", topic_pub_lateral_cmd,
      std::string("/defender_a/thrusters/lateral_thrust_cmd"));
  //左-角度
  priv.param<std::string>(
      "topic_pub_left_angle", topic_pub_left_angle,
      std::string("/defender_a/thrusters/left_thrust_angle"));
  //左-转速
  priv.param<std::string>("topic_pub_left_cmd", topic_pub_left_cmd,
                          std::string("/defender_a/thrusters/left_thrust_cmd"));
  //右-角度
  priv.param<std::string>(
      "topic_pub_right_angle", topic_pub_right_angle,
      std::string("/defender_a/thrusters/right_thrust_angle"));
  //右-转速
  priv.param<std::string>(
      "topic_pub_right_cmd", topic_pub_right_cmd,
      std::string("/defender_a/thrusters/right_thrust_cmd"));

  ros::Subscriber sub_target_rotation = nh.subscribe(topic_sub, 1, callback);

  pub_lateral_angle =
      nh.advertise<std_msgs::Float32>(topic_pub_lateral_angle, 1);
  pub_lateral_cmd = nh.advertise<std_msgs::Float32>(topic_pub_lateral_cmd, 1);
  pub_left_angle = nh.advertise<std_msgs::Float32>(topic_pub_left_angle, 1);
  pub_left_cmd = nh.advertise<std_msgs::Float32>(topic_pub_left_cmd, 1);
  pub_right_angle = nh.advertise<std_msgs::Float32>(topic_pub_right_angle, 1);
  pub_right_cmd = nh.advertise<std_msgs::Float32>(topic_pub_right_cmd, 1);
  ros::spin();
}