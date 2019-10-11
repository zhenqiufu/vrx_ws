#include <dynamic_reconfigure/server.h>
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>
#include <virtual_robotx/motor_msgs.h>
#include <virtual_robotx/thrustallocationConfig.h>
#include "controllerdata.h"
#include "thrustallocation.h"
//本函数通过坐标、首相角的差值得到目标DP力
const int propeller_num = 4;
const int dim_controlspace = 3;  //控制维数
int allman_switch_prev, dp_switch_prev;
double target_force[dim_controlspace], controller_f[dim_controlspace],
    controller_f_dv[dim_controlspace],
    windload[dim_controlspace] = {0},
    joyload[dim_controlspace] = {
        0};  //三维数组 代表目标位置 分别为UTM_x UTM_y 和首相角
std::vector<double> propeller_position_x, propeller_position_y,
    propeller_K_positive, propeller_K_negtive, propeller_max_alfa,
    propeller_min_alfa, propeller_delta_alfa, propeller_max_thrust,
    propeller_min_thrust, max_target_force, min_target_force;

std::vector<int> propeller_min_rotation, propeller_max_rotation,
    propeller_delta_rotation;
std::vector<int> index_thrusters;  // 0 艏侧推；1全回转;
std::vector<double> propeller_rotation, output_u, output_alpha,
    output_alpha_deg, output_Balphau, output_rotation;
int debug_mode, dp_switch, allman_switch;  // 0 手动 1 自动
double joystick_cmd[3];
int dim_switch[3] = {0};

constexpr ACTUATION index_actuation = FULLYACTUATED;
controllerRTdata<propeller_num, dim_controlspace> _controllerRTdata{
    Eigen::Matrix<double, dim_controlspace, 1>::Zero(),  // tau
    Eigen::Matrix<double, dim_controlspace, 1>::Zero(),  // BalphaU
    Eigen::Matrix<double, propeller_num, 1>::Zero(),     // u
    Eigen::Matrix<int, propeller_num, 1>::Zero(),        // rotation
    Eigen::Matrix<double, propeller_num, 1>::Zero(),     // alpha
    Eigen::Matrix<int, propeller_num, 1>::Zero()         // alpha_deg
};

//
void fxCallback(const std_msgs::Float64::ConstPtr &msg) {
  controller_f[0] = msg->data;
}
void fyCallback(const std_msgs::Float64::ConstPtr &msg) {
  controller_f[1] = msg->data;
}
void mzCallback(const std_msgs::Float64::ConstPtr &msg) {
  controller_f[2] = msg->data;
}
void fx_dv_Callback(const std_msgs::Float64::ConstPtr &msg) {
  controller_f_dv[0] = msg->data;
}
void fy_dv_Callback(const std_msgs::Float64::ConstPtr &msg) {
  controller_f_dv[1] = msg->data;
}
void mz_dv_Callback(const std_msgs::Float64::ConstPtr &msg) {
  controller_f_dv[2] = msg->data;
}
void wind_load_Callback(const std_msgs::Float64MultiArray::ConstPtr &msg) {
  windload[0] = msg->data[0];
  windload[1] = msg->data[1];
  windload[2] = msg->data[2];
}

void joystick_cmd_Callback(const std_msgs::Float64MultiArray &msg) {
  for (int i = 0; i != 3; ++i)
    joyload[i] = msg.data[i] * max_target_force[i] / 100;
  allman_switch = msg.data[3];
}

void dynamic_callback(dp_core::thrustallocationConfig &config, uint32_t level) {
  string2int_array(config.propeller_max_rotation, propeller_max_rotation);
  string2int_array(config.propeller_min_rotation, propeller_min_rotation);
  string2int_array(config.propeller_delta_rotation, propeller_delta_rotation);
  string2double_array(config.propeller_max_alfa, propeller_max_alfa);
  string2double_array(config.propeller_min_alfa, propeller_min_alfa);
  string2double_array(config.propeller_delta_alfa, propeller_delta_alfa);
  string2double_array(config.max_target_force, max_target_force);
  string2double_array(config.min_target_force, min_target_force);
  // string2double_array(config.propeller_min_thrust, propeller_max_thrust);
  // string2double_array(config.propeller_min_thrust, propeller_min_thrust);
  string2double_array(config.propeller_K_positive, propeller_K_positive);
  string2double_array(config.propeller_K_negtive, propeller_K_negtive);

  allman_switch = (int)config.allman_switch;
  dp_switch = (int)config.dp_switch;
  dim_switch[0] = (int)config.UTMx_switch;
  dim_switch[1] = (int)config.UTMy_switch;
  dim_switch[2] = (int)config.head_switch;
  debug_mode = (int)config.debug_mode;
  if (allman_switch == 1 && allman_switch_prev == 0) {
    dp_switch = 0;
    config.dp_switch = false;
    dim_switch[0] = 0;
    config.UTMx_switch = false;
    dim_switch[1] = 0;
    config.UTMy_switch = false;
    dim_switch[2] = 0;
    config.head_switch = false;
  }
  if (dp_switch == 1 && dp_switch_prev == 0) {
    allman_switch = 0;
    config.allman_switch = false;
    dim_switch[0] = 1;
    config.UTMx_switch = true;
    dim_switch[1] = 1;
    config.UTMy_switch = true;
    dim_switch[2] = 1;
    config.head_switch = true;
  }
  if (dim_switch[0] == 1 || dim_switch[1] == 1 || dim_switch[2] == 1) {
    allman_switch = 0;
    config.allman_switch = false;
    dp_switch = 1;
    config.dp_switch = true;
  }
  if (dim_switch[0] == 0 && dim_switch[1] == 0 && dim_switch[2] == 0) {
    dp_switch = 0;
    config.dp_switch = false;
  }
  allman_switch_prev = allman_switch;
  dp_switch_prev = dp_switch;
  // ros::param::set("dp_switch", dp_switch);
  // for (int i = 0; i < propeller_num; i++)
  // {
  //   std::cout << "propeller_max_rotation" << propeller_max_rotation[i] <<
  //   std::endl;
  // }
}

int main(int argc, char **argv) {
  // ROS_INFO_STREAM("node one");
  ros::init(argc, argv, "target_rotation");
  ros::NodeHandle nh;
  nh.getParam("propeller_position_x", propeller_position_x);
  nh.getParam("propeller_position_y", propeller_position_y);
  nh.getParam("propeller_K_positive", propeller_K_positive);
  nh.getParam("propeller_K_negtive", propeller_K_negtive);
  nh.getParam("propeller_max_rotation", propeller_max_rotation);
  nh.getParam("propeller_min_rotation", propeller_min_rotation);
  nh.getParam("propeller_max_alfa", propeller_max_alfa);
  nh.getParam("propeller_min_alfa", propeller_min_alfa);
  nh.getParam("propeller_delta_alfa", propeller_delta_alfa);
  nh.getParam("propeller_delta_rotation", propeller_delta_rotation);
  nh.getParam("propeller_max_thrust", propeller_max_thrust);
  nh.getParam("propeller_min_thrust", propeller_min_thrust);
  nh.getParam("propeller_index", index_thrusters);
  // nh.getParam("propeller_num", propeller_num);
  nh.param("allman_switch", allman_switch, 1);
  nh.param("dp_switch", dp_switch, 0);
  nh.param("UTMx_switch", dim_switch[0], 0);  // true 自动dp 关joystick
  nh.param("UTMy_switch", dim_switch[1], 0);  // true 自动dp 关joystick
  nh.param("head_switch", dim_switch[2], 0);  // true 自动dp 关joystick
  nh.param("debug_mode", debug_mode, 0);
  nh.getParam("max_target_force", max_target_force);
  nh.getParam("min_target_force", min_target_force);

  allman_switch_prev = allman_switch;
  dp_switch_prev = dp_switch;
  ros::Publisher pub_target_rotation =
      nh.advertise<virtual_robotx::motor_msgs>("target_rotation", 1000);
  virtual_robotx::motor_msgs motor_msg;
  //消息初始化　propeller_num维数组 初始值皆为0
  for (int i = 0; i < propeller_num; i++) {
    motor_msg.stamp = ros::Time::now();
    motor_msg.rotation.push_back(0);
    motor_msg.alpha.push_back(0);
    motor_msg.alpha_deg.push_back(0);
    motor_msg.u.push_back(0);
  }

  for (int i = 0; i < dim_controlspace; i++) {
    motor_msg.tau.push_back(0);
    motor_msg.BalphaU.push_back(0);
  }

  ros::Subscriber sub_fx = nh.subscribe("controller_fx", 1000, fxCallback);
  ros::Subscriber sub_fy = nh.subscribe("controller_fy", 1, fyCallback);
  ros::Subscriber sub_mz = nh.subscribe("controller_mz", 1, mzCallback);
  ros::Subscriber sub_fx_dv =
      nh.subscribe("controller_fx_dv", 1, fx_dv_Callback);
  ros::Subscriber sub_fy_dv =
      nh.subscribe("controller_fy_dv", 1, fy_dv_Callback);
  ros::Subscriber sub_mz_dv =
      nh.subscribe("controller_mz_dv", 1, mz_dv_Callback);
  ros::Subscriber sub_windload =
      nh.subscribe("wind_load", 1, wind_load_Callback);
  ros::Subscriber sub_joystick_cmd =
      nh.subscribe("GUIcommunication", 1, joystick_cmd_Callback);
  // ROS_INFO_STREAM("propeller_max_rotation: " << propeller_max_rotation[1]);
  // ROS_INFO_STREAM("propeller_min_rotation: " << propeller_min_rotation[1]);
  // ROS_INFO_STREAM("propeller_K_positive: " << propeller_K_positive[1]);
  // ROS_INFO_STREAM("propeller_K_negtive: " << propeller_K_negtive[1]);
  // ROS_INFO_STREAM("debug_mode: " << debug_mode);
  dynamic_reconfigure::Server<dp_core::thrustallocationConfig> server;
  // dynamic_reconfigure::Server<dp_core::gps_fusionConfig>::CallbackType f;
  server.setCallback(boost::bind(&dynamic_callback, _1, _2));
  //初始化一些参数
  // set the parameters in the thrust allocation
  // ROS_INFO_STREAM("propeller_max_rotation: " << propeller_max_rotation[1]);
  // ROS_INFO_STREAM("propeller_min_rotation: " << propeller_min_rotation[1]);
  // ROS_INFO_STREAM("propeller_K_positive: " << propeller_K_positive[1]);
  // ROS_INFO_STREAM("propeller_K_negtive: " << propeller_K_negtive[1]);
  // ROS_INFO_STREAM("debug_mode: " << debug_mode);
  int num_tunnel =
      std::count(index_thrusters.begin(), index_thrusters.end(), 0);

  int num_azimuth =
      std::count(index_thrusters.begin(), index_thrusters.end(), 1);

  int num_mainrudder =
      std::count(index_thrusters.begin(), index_thrusters.end(), 2);

  thrustallocationdata _thrustallocationdata{num_tunnel, num_azimuth,
                                             num_mainrudder, index_thrusters};

  // initialize for solve the opt

  std::vector<tunnelthrusterdata> v_tunnelthrusterdata;
  v_tunnelthrusterdata.reserve(num_tunnel);
  std::vector<azimuththrusterdata> v_azimuththrusterdata;
  v_azimuththrusterdata.reserve(num_azimuth);
  std::vector<ruddermaindata> v_ruddermaindata;
  for (int i = 0; i != num_tunnel; ++i) {
    //
    v_tunnelthrusterdata.push_back({
        propeller_position_x[i],      // lx
        propeller_position_y[i],      // ly
        propeller_K_positive[i],      // K_positive
        propeller_K_negtive[i],       // K_negative
        propeller_delta_rotation[i],  // max_delta_rotation
        propeller_max_rotation[i],    // max_rotation
        propeller_max_thrust[i],      // max_thrust_positive
        propeller_min_thrust[i]       // max_thrust_negative
    });
  }
  for (int i = num_tunnel; i != num_azimuth + num_tunnel; ++i) {
    v_azimuththrusterdata.push_back({
        propeller_position_x[i],      // lx
        propeller_position_y[i],      // ly
        propeller_K_positive[i],      // K
        propeller_delta_rotation[i],  // max_delta_rotation
        propeller_max_rotation[i],    // max rotation
        propeller_min_rotation[i],    // min_rotation
        propeller_delta_alfa[i],      // max_delta_alpha
        propeller_max_alfa[i],        // max_alpha
        propeller_min_alfa[i],        // min_alpha
        propeller_max_thrust[i],      // max_thrust
        propeller_min_thrust[i]       // min_thrust

    });
  }

  thrustallocation<propeller_num, index_actuation, dim_controlspace>
      _thrustallocation(_thrustallocationdata, v_tunnelthrusterdata,
                        v_azimuththrusterdata, v_ruddermaindata);
  // initialize the thrust allocation

  _thrustallocation.initializapropeller(_controllerRTdata);
  ros::Rate loop_rate(10);

  //
  while (ros::ok()) {
    // ROS_INFO_STREAM("allman_switch:" << allman_switch);
    // switch (allman_switch)
    // {
    // case 0: //手动模式
    //   for (int i = 0; i < dim_controlspace; i++)
    //   {
    //     target_force[i] = joyload[i];
    //   }
    //   //约束最大最小力
    //   restrictdesiredforce(target_force);
    //   break; // 可选的
    // case 1:  // dp模式
    //   for (int i = 0; i < dim_controlspace; i++)
    //   {
    //     target_force[i] = controller_f[i] + controller_f_dv[i] - windload[i];
    //   }
    //   //约束最大最小力
    //   restrictdesiredforce(target_force);
    //   break;
    // }

    for (int i = 0; i < 3; i++) {
      if (dim_switch[i] == 0)
        target_force[i] = joyload[i] - windload[i];
      else
        target_force[i] = controller_f[i] + controller_f_dv[i] - windload[i];
    }

    // ROS_INFO_STREAM("max_target_force: " << max_target_force[0]);
    // ROS_INFO_STREAM("max_target_force: " << max_target_force[1]);
    // ROS_INFO_STREAM("max_target_force: " << max_target_force[2]);
    // ROS_INFO_STREAM("min_target_force: " << min_target_force[0]);
    // ROS_INFO_STREAM("min_target_force: " << min_target_force[1]);
    // ROS_INFO_STREAM("min_target_force: " << min_target_force[2]);

    restrictdesiredforce(target_force, min_target_force, max_target_force);
    //
    if (debug_mode == 1) {
      _thrustallocation.update_propeller_parameter(
          propeller_K_positive, propeller_K_negtive, propeller_delta_rotation,
          propeller_delta_alfa, propeller_max_rotation, propeller_min_rotation,
          propeller_max_alfa, propeller_min_alfa);
    }

    // 进行优化计算

    _controllerRTdata.tau(0, 0) = target_force[0];
    _controllerRTdata.tau(1, 0) = -target_force[1];
    _controllerRTdata.tau(2, 0) = -target_force[2];
    _thrustallocation.onestepthrustallocation(_controllerRTdata);
    // 为输出消息赋值

    for (int i = 0; i < propeller_num; i++) {
      motor_msg.stamp = ros::Time::now();
      motor_msg.rotation[i] = _controllerRTdata.rotation(i);
      motor_msg.alpha[i] = _controllerRTdata.alpha(i);
      motor_msg.alpha_deg[i] = _controllerRTdata.alpha_deg(i);

      motor_msg.u[i] = _controllerRTdata.u(i);
    }

    for (int i = 0; i < dim_controlspace; i++) {
      motor_msg.tau[i] = _controllerRTdata.tau(i);
      motor_msg.BalphaU[i] = _controllerRTdata.BalphaU(i);
    }
    //
    pub_target_rotation.publish(motor_msg);

    //打印出来
    for (int i = 0; i < propeller_num; i++) {
      ROS_INFO_STREAM("rotation " << i << " : " << motor_msg.rotation[i]);
    }
    for (int i = 0; i < propeller_num; i++) {
      ROS_INFO_STREAM("u " << i << " : " << motor_msg.u[i]);
    }
    for (int i = 0; i < propeller_num; i++) {
      ROS_INFO_STREAM("alpha_deg " << i << " : " << motor_msg.alpha_deg[i]);
    }
    for (int i = 0; i < dim_controlspace; i++) {
      ROS_INFO_STREAM("tau " << i << " : " << motor_msg.tau[i]);
    }
    for (int i = 0; i < dim_controlspace; i++) {
      ROS_INFO_STREAM("BalphaU " << i << " : " << motor_msg.BalphaU[i]);
    }

    // ROS_INFO_STREAM("dim_switch: " << dim_switch[0]);
    // ROS_INFO_STREAM("windload: " << windload[0]);
    // ROS_INFO_STREAM("windload: " << windload[1]);
    // ROS_INFO_STREAM("windload: " << windload[2]);
    // ROS_INFO_STREAM("propeller_max_thrust: " << propeller_max_thrust[0]);
    // ROS_INFO_STREAM("propeller_max_thrust: " << propeller_max_thrust[1]);
    // ROS_INFO_STREAM("propeller_max_thrust: " << propeller_max_thrust[2]);
    // ROS_INFO_STREAM("propeller_K_positive: " << propeller_K_positive[1]);
    // ROS_INFO_STREAM("propeller_K_negtive: " << propeller_K_negtive[1]);
    // ROS_INFO_STREAM("debug_mode: " << debug_mode);
    //
    ros::spinOnce();
    loop_rate.sleep(); // ros::Duration(0.001).sleep();
  }
  return 0;
}