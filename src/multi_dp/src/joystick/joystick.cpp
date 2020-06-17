#include "joystick.h"

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>

#include <iostream>

int main(int argc, char** argv) {
  ros::init(argc, argv, "joystick_cmd");
  ros::NodeHandle nh;
  ros::NodeHandle priv("~");
  std::string topic_sub, topic_pub;
  priv.param<std::string>("topic_sub", topic_sub,
                          std::string("/dev/input/js0"));
  priv.param<std::string>("topic_pub", topic_pub, std::string("k_a/joystick"));
  char* op_js_name = (char*)topic_sub.c_str();
  ros::Publisher pub_joystick_msg =
      nh.advertise<std_msgs::Float64MultiArray>(topic_pub, 1);
  std_msgs::Float64MultiArray joystick_msg;
  joystick_msg.data.push_back(0);
  joystick_msg.data.push_back(0);
  joystick_msg.data.push_back(0);  //初始化三维数组
  initial_joystick(op_js_name);    //打开手柄
  ros::Rate loop_rate(100);
  while (ros::ok()) {
    getjoystick_cmd();  //更新手柄数据
    joystick_msg.data[0] = joystick_cmd[0];
    joystick_msg.data[1] = -joystick_cmd[1];
    joystick_msg.data[2] = joystick_cmd[2] - joystick_cmd[3];
    pub_joystick_msg.publish(joystick_msg);
    std::cout << "X: " << joystick_msg.data[0]
              << "  Y:  " << joystick_msg.data[1]
              << "  Z:  " << joystick_msg.data[2] << std::endl;
    loop_rate.sleep();
  }
  return 0;
}
///////////////////////
// std::string js_num = "/dev/input/js0";

// char* op_js_name = (char*)js_num.c_str();
// int main() {
//   initial_joystick(op_js_name);  //打开手柄
//   while (1) {
//     getjoystick_cmd();  //更新手柄数据
//     std::cout << "X: " << joystick_cmd[0] << "  Y:  " << -joystick_cmd[1]
//               << "  Z_l:  " << joystick_cmd[2] << "  Z_r:  " <<
//               -joystick_cmd[3]
//               << std::endl;
//   }
//   return 0;
// }