#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Float64.h>
#include "tf/transform_datatypes.h"

ros::Publisher pub, pub_target;
void callback(const sensor_msgs::Imu::ConstPtr &msg) {
  tf::Quaternion quat;
  tf::quaternionMsgToTF(msg->orientation, quat);
  double roll, pitch, yaw;
  tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);
  std_msgs::Float64 yaw_msg, yaw_target;
  yaw_msg.data = yaw;
  yaw_target.data = 0;
  pub.publish(yaw_msg);
  pub_target.publish(yaw_target);
  // std::cout << "yaw: " << yaw / 3.141593 * 180 << std::endl;
}
int main(int argc, char **argv) {
  // ROS_INFO_STREAM("node one");
  ros::init(argc, argv, "eular_angle");
  ros::NodeHandle nh;
  ros::Subscriber sub_imu = nh.subscribe("imu/data", 1, callback);
  pub = nh.advertise<std_msgs::Float64>("wamv/sensors/imu/imu/yaw", 1);
  pub_target = nh.advertise<std_msgs::Float64>("/vrx/station_keeping/head", 1);
  ros::spin();
  return 0;
}