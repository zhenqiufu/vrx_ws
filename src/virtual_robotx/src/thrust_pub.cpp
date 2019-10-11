#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64MultiArray.h>
#include <virtual_robotx/motor_msgs.h>
const double PI = 3.1415926;

// / left_front_thrust_angle / left_front_thrust_cmd / left_rear_thrust_angle /
//     left_rear_thrust_cmd

ros::Publisher pub_left_front_angle, pub_left_front_cmd, pub_right_front_angle,
    pub_right_front_cmd, pub_left_rear_angle, pub_left_rear_cmd,
    pub_right_rear_angle, pub_right_rear_cmd;
void callback(const virtual_robotx::motor_msgs &msg) {
  std_msgs::Float32 lateral_angle, lateral_cmd, left_angle, left_cmd,
      right_angle, right_cmd;
  left_angle.data = -msg.alpha[0];
  left_cmd.data = msg.rotation[0] / 100;
  right_angle.data = -msg.alpha[1];
  right_cmd.data = msg.rotation[1] / 100;
  lateral_angle.data = -PI / 2 - msg.alpha[2];
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
  ros::Subscriber sub_target_rotation =
      nh.subscribe("target_rotation", 1, callback);
  pub_lateral_angle =
      nh.advertise<std_msgs::Float32>("/lateral_thrust_angle", 1);
  pub_lateral_cmd = nh.advertise<std_msgs::Float32>("/lateral_thrust_cmd", 1);
  pub_left_angle = nh.advertise<std_msgs::Float32>("/left_thrust_angle", 1);
  pub_left_cmd = nh.advertise<std_msgs::Float32>("/left_thrust_cmd", 1);
  pub_right_angle = nh.advertise<std_msgs::Float32>("/right_thrust_angle", 1);
  pub_right_cmd = nh.advertise<std_msgs::Float32>("/right_thrust_cmd", 1);
  ros::spin();
}