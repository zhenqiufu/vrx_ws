#include "include/gps.h"
// #include <gps_common/conversions.h>
#include <sensor_msgs/NavSatFix.h>
#include <std_msgs/Float64.h>

#include "ros/ros.h"
#include "std_msgs/String.h"
UTMalt tm(6378388, 1 / 297.0, 51, true);
ros::Publisher pub_UTMx, pub_UTMy;
void chatterCallback(const sensor_msgs::NavSatFix& msg) {
  double lat, lon, tmpUTMx, tmpUTMy;
  lat = msg.latitude;
  lon = msg.longitude;
  std_msgs::Float64 UTMx, UTMy;
  // gps_common::UTM(lat, lon, &UTMx.data, &UTMy.data);
  tm.Forward(msg.latitude, msg.longitude, tmpUTMx, tmpUTMy);
  UTMx.data = tmpUTMx;
  UTMy.data = tmpUTMy;
  pub_UTMx.publish(UTMx);
  pub_UTMy.publish(UTMy);
  // std::cout << "UTMx: " << UTMx.data << std::endl;
  // std::cout << "UTMy: " << UTMy.data << std::endl;
  // ROS_INFO_STREAM("run gps_converter chatterCallback");
}

int main(int argc, char** argv) {
  ROS_INFO_STREAM("run gps_converter");

  ros::init(argc, argv, "gps_converter");
  ros::NodeHandle n;
  ros::NodeHandle priv("~");
  std::string topic_sub, topic_pub_UTMx, topic_pub_UTMy;
  priv.param<std::string>("topic_sub", topic_sub,
                          std::string("/defender_a/sensors/gps/gps/fix"));
  priv.param<std::string>("topic_pub_UTMx", topic_pub_UTMx,
                          std::string("wamv/sensors/gps/gps/UTMx"));
  priv.param<std::string>("topic_pub_UTMy", topic_pub_UTMy,
                          std::string("wamv/sensors/gps/gps/UTMy"));
  ros::Subscriber sub = n.subscribe(topic_sub, 1, chatterCallback);
  pub_UTMx = n.advertise<std_msgs::Float64>(topic_pub_UTMx, 1);
  pub_UTMy = n.advertise<std_msgs::Float64>(topic_pub_UTMy, 1);
  ros::spin();
  return 0;
}
