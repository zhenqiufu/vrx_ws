#include <ros/ros.h>
#include <std_msgs/Float64.h>
double UTMx_goal = 0, UTMy_goal = 0, UTMx = 0, UTMy = 0, head = 1000;
ros::Publisher pub_xr, pub_yr, pub_zero;
void callback_UTMx_goal(const std_msgs::Float64::ConstPtr &msg) {
  UTMx_goal = msg->data;
}
void callback_UTMy_goal(const std_msgs::Float64::ConstPtr &msg) {
  UTMy_goal = msg->data;
  // ROS_INFO_STREAM("head" << head);
  // ROS_INFO_STREAM("UTMx" << UTMx);
  // ROS_INFO_STREAM("UTMx_goal" << UTMx_goal);
  // ROS_INFO_STREAM("UTMy" << UTMy);
  // ROS_INFO_STREAM("UTMy_goal" << UTMy_goal);
  if (head != 1000 && UTMx != 0 && UTMx_goal != 0 && UTMy != 0 &&
      UTMy_goal != 0) {
    // ROS_INFO_STREAM("NODE0000");
    double x, y;
    x = UTMx_goal - UTMx;
    y = UTMy_goal - UTMy;
    std_msgs::Float64 xr, yr, zero;
    xr.data = cos(head) * x + sin(head) * y;
    yr.data = cos(head) * y - sin(head) * x;
    zero.data = 0;
    pub_xr.publish(xr);
    pub_yr.publish(yr);
    pub_zero.publish(zero);
  }
}
void callback_UTMx(const std_msgs::Float64::ConstPtr &msg) { UTMx = msg->data; }
void callback_UTMy(const std_msgs::Float64::ConstPtr &msg) { UTMy = msg->data; }
void callback_head(const std_msgs::Float64::ConstPtr &msg) { head = msg->data; }
int main(int argc, char **argv) {
  // ROS_INFO_STREAM("node one");
  ros::init(argc, argv, "pid_coordinate");
  ros::NodeHandle nh;
  ros::Subscriber sub_UTMx_goal =
      nh.subscribe("/vrx/station_keeping/UTMx", 1, callback_UTMx_goal);
  ros::Subscriber sub_UTMy_goal =
      nh.subscribe("/vrx/station_keeping/UTMy", 1, callback_UTMy_goal);
  ros::Subscriber sub_UTMx =
      nh.subscribe("/wamv/sensors/gps/gps/UTMx", 1, callback_UTMx);
  ros::Subscriber sub_UTMy =
      nh.subscribe("/wamv/sensors/gps/gps/UTMy", 1, callback_UTMy);
  ros::Subscriber sub_head =
      nh.subscribe("/wamv/sensors/imu/imu/yaw", 1, callback_head);

  pub_zero = nh.advertise<std_msgs::Float64>("/float64_zero", 1);
  pub_xr = nh.advertise<std_msgs::Float64>("/vrx/station_keeping/x_r", 1);
  pub_yr = nh.advertise<std_msgs::Float64>("/vrx/station_keeping/y_r", 1);
  ros::spin();
  return 0;
}
