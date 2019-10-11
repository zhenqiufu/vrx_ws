#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>
#include <std_msgs/Float64.h>

int main(int argc, char **argv) {
  // ROS_INFO_STREAM("node one");
  ros::init(argc, argv, "goal_pub");
  ros::NodeHandle nh;
  ros::Publisher pub_UTMx =
      nh.advertise<std_msgs::Float64>("/vrx/station_keeping/UTMx", 1);
  ros::Publisher pub_UTMy =
      nh.advertise<std_msgs::Float64>("/vrx/station_keeping/UTMy", 1);
  ros::Rate loop_rate(10);
  while (ros::ok()) {
    std_msgs::Float64 UTMx, UTMy;
    UTMx.data = 10401337.5823 - 24;
    UTMy.data = 7157852.07175 - 24;
    pub_UTMx.publish(UTMx);
    pub_UTMy.publish(UTMy);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}