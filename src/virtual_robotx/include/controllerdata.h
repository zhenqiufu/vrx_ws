/*
****************************************************************************
* controllerdata.h:
* define the data struct used in the controller
* This header file can be read by C++ compilers
*
* by Hu.ZH(CrossOcean.ai)
****************************************************************************
*/

#ifndef _CONTROLLERDATA_H_
#define _CONTROLLERDATA_H_

#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>

enum CONTROLMODE {
  MANUAL = 0,      // manual controller
  HEADINGONLY,     // heading only controller (autopilot)
  MANEUVERING,     // maneuvering model
  DYNAMICPOSITION  // DP (3 DOF, position control: only for fully-actuated
                   // vessel)
};

enum ACTUATION {
  UNDERACTUATED = 0,  // underactuated usv
  FULLYACTUATED       // fully actuated usv
};

// indicator in the controller
struct controllerdata {
  double sample_time;  // sample time of controller((unit: second)),
  CONTROLMODE controlmode;
  ACTUATION index_actuation;
};

// real-time data in the controller
template <int m, int n = 3>
struct controllerRTdata {
  // Fx, Fy, Mz (desired force) in the body coordinate
  Eigen::Matrix<double, n, 1> tau;
  // Fx, Fy, Mz (estimated generalized thrust) in the body-fixed coordinates
  Eigen::Matrix<double, n, 1> BalphaU;
  // N, estimated thrust of all propellers
  Eigen::Matrix<double, m, 1> u;
  // rpm, rotation of all propellers
  Eigen::Matrix<int, m, 1> rotation;
  // rad, angle of all propellers (compute the estimated force)
  Eigen::Matrix<double, m, 1> alpha;
  // deg, angle of all propellers (sent to the actuators)
  Eigen::Matrix<int, m, 1> alpha_deg;
};

struct thrustallocationdata {
  int num_tunnel;      // # of tunnel thruster
  int num_azimuth;     // # of azimuth thruster
  int num_mainrudder;  // # of main thruster with rudder
  std::vector<int> index_thrusters;
};

// constant data of tunnel thruster, index = 1
struct tunnelthrusterdata {
  double lx;                   // m
  double ly;                   // m
  double K_positive;           // positive value
  double K_negative;           // positive value
  int max_delta_rotation;      // rpm(no less than 1)
  int max_rotation;            // rpm
  double max_thrust_positive;  // positive value
  double max_thrust_negative;  // positive value
};

// constant data of azimuth thruster, index = 2
// Azimuth thruster can be used for fixed thruster, with a fixed alpha
struct azimuththrusterdata {
  double lx;               // m
  double ly;               // m
  double K;                //
  int max_delta_rotation;  // rpm (no less than 1)
  int max_rotation;        // rpm
  int min_rotation;        // rpm
  double max_delta_alpha;  // rad
  double max_alpha;        // rad
  double min_alpha;        // rad
  double max_thrust;       // N, positive value
  double min_thrust;       // N, positive value
};

// constant data of main propeller with rudder, index = 3
struct ruddermaindata {
  double lx;                  // m
  double ly;                  // m
  double K;                   //
  double Cy;                  // Cx=0.02Cy
  double max_delta_rotation;  // rpm (no less than 1)
  double max_rotation;        // rpm
  double min_rotation;        // rpm
  double max_thrust;          // N
  double min_thrust;          // N
  double max_alpha;           // rad
  double min_alpha;           // rad
  double max_delta_varphi;    // deg(rudder angle: no less than 1)
  double max_varphi;          // deg(rudder)
  double min_varphi;          // deg(rudder)
};

#endif /* _CONTROLLERDATA_H_ */