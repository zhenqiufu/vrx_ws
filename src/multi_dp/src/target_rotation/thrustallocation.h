/*
*******************************************************************************
* thrustallocation.h:
* function for control allocation based on Quadratic programming, using
* Mosek solver API. Normally, thrust alloation is used in the fully-actuated
* control system.
* This header file can be read by C++ compilers
*
* by Hu.ZH(CrossOcean.ai)
*******************************************************************************
*/

#ifndef _THRUSTALLOCATION_H_
#define _THRUSTALLOCATION_H_
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <qpOASES.hpp>
#include <string>
#include <vector>
#include <cstdio>
#include "controllerdata.h"
#include "easylogging++.h"

// # of thread used by mosek
#define QP_THREADS_USED 1
extern const int dim_controlspace;
// m: # of all thrusters on the vessel
// n: # of dimension of control space
template <int m, ACTUATION index_actuation,
          int n = 3> //初始定义m index_actuation 和n类型 和默认值
class thrustallocation
{
  using vectormd = Eigen::Matrix<double, m, 1>;
  using vectormi = Eigen::Matrix<int, m, 1>;
  using vectornd = Eigen::Matrix<double, n, 1>;
  using matrixnmd = Eigen::Matrix<double, n, m>;
  using matrixmmd = Eigen::Matrix<double, m, m>;
  using matrixnnd = Eigen::Matrix<double, n, n>;

public:
  explicit thrustallocation(
      const thrustallocationdata &_thrustallocationdata,
      const std::vector<tunnelthrusterdata> &_v_tunnelthrusterdata,
      const std::vector<azimuththrusterdata> &_v_azimuththrusterdata,
      const std::vector<ruddermaindata> &_v_ruddermaindata)
      : num_tunnel(_thrustallocationdata.num_tunnel),
        num_azimuth(_thrustallocationdata.num_azimuth),
        num_mainrudder(_thrustallocationdata.num_mainrudder),
        numvar(2 * m + n),
        num_constraints(n),
        index_thrusters(_thrustallocationdata.index_thrusters),
        v_tunnelthrusterdata(_v_tunnelthrusterdata),
        v_azimuththrusterdata(_v_azimuththrusterdata),
        v_ruddermaindata(_v_ruddermaindata),
        lx(vectormd::Zero()),
        ly(vectormd::Zero()),
        upper_delta_alpha(vectormd::Zero()),
        lower_delta_alpha(vectormd::Zero()),
        upper_delta_u(vectormd::Zero()),
        lower_delta_u(vectormd::Zero()),
        Q(matrixnnd::Zero()),
        Omega(matrixmmd::Zero()),
        Q_deltau(matrixmmd::Zero()),
        g_deltau(vectormd::Zero()),
        d_rho(vectormd::Zero()),
        B_alpha(matrixnmd::Zero()),
        d_Balpha_u(matrixnmd::Zero()),
        b(vectornd::Zero()),
        delta_alpha(vectormd::Zero()),
        delta_u(vectormd::Zero()),
        derivative_dx(1e-6),
        results(Eigen::Matrix<double, 2 * m + n, 1>::Zero())
  {
    initializethrusterallocation();
    printparameter();
    std::cout << "initialize thruster allocation finished!" << std::endl;
  }

  thrustallocation() = delete;
  ~thrustallocation()
  {
    // MSK_deletetask(&task);
    // MSK_deleteenv(&env);
  }

  // perform the thrust allocation using QP solver (one step)
  void onestepthrustallocation(controllerRTdata<m, n> &_RTdata)
  {
    updateTAparameters(_RTdata);
    std::cout << "update TA parameters finished" << std::endl;

    // for mosek solver
    // updateMosekparameters();
    // onestepmosek();

    // for qpOASES solver
    updateqpOASESparameters();
    std::cout << "update qpOASES parameters finished" << std::endl;

    onestepqpOASES();
    std::cout << "run solver finished" << std::endl;
    // printparameter();

    updateNextstep(_RTdata);
    std::cout << "update Nextstep finished" << std::endl;
  }

  void initializapropeller(controllerRTdata<m, n> &_RTdata)
  {
    // alpha and thrust of each propeller
    for (int i = 0; i != num_tunnel; ++i)
    {
      _RTdata.rotation(i) = 1;
      _RTdata.u(i) = v_tunnelthrusterdata[i].K_positive;
      _RTdata.alpha(i) = M_PI / 2;
      _RTdata.alpha_deg(i) = 90;
    }
    for (int j = 0; j != num_azimuth; ++j)
    {
      int a_index = j + num_tunnel;
      _RTdata.rotation(a_index) = v_azimuththrusterdata[j].min_rotation;
      _RTdata.u(a_index) = v_azimuththrusterdata[j].min_thrust;
      _RTdata.alpha(a_index) = (v_azimuththrusterdata[j].min_alpha +
                                v_azimuththrusterdata[j].max_alpha) /
                               2;

      _RTdata.alpha_deg(a_index) =
          static_cast<int>(_RTdata.alpha(a_index) * 180 / M_PI);
    }
    for (int k = 0; k != num_mainrudder; ++k)
    {
      int a_index = k + num_tunnel + num_azimuth;
      _RTdata.rotation(a_index) = v_ruddermaindata[k].min_rotation;
      _RTdata.u(a_index) = v_ruddermaindata[k].min_thrust;
      _RTdata.alpha(a_index) = 0;
      _RTdata.alpha_deg(a_index) = 0;
    }
    // update BalphaU
    _RTdata.BalphaU = calculateBalphau(_RTdata.alpha, _RTdata.u);
  }
  // modify penality for each error (heading-only controller)
  void setQ(CONTROLMODE _cm)
  {
    if (index_actuation == FULLYACTUATED) //constexpr
    {
      switch (_cm)
      {
      case MANUAL:
        Q(0, 0) = 600;
        Q(1, 1) = 600;
        Q(2, 2) = 1000;
        break;
      case HEADINGONLY:
        Q(0, 0) = 100;
        Q(1, 1) = 100;
        Q(2, 2) = 2000;
        break;
      case MANEUVERING:
        Q(0, 0) = 1000;
        // Q(1, 1) = 0;  The penalty for sway error is zero
        Q(2, 2) = 100;
        break;
      case DYNAMICPOSITION:
        for (int i = 0; i != n; ++i)
          Q(i, i) = 1000;
        break;
      default:
        break;
      }
    }
    else
    { // underactuated
      switch (_cm)
      {
      case MANUAL:
        Q(0, 0) = 100;
        // Q(1, 1) = 0;  The penalty for sway error is zero
        Q(2, 2) = 1000;
        break;
      case HEADINGONLY:
        Q(0, 0) = 100;
        // Q(1, 1) = 0;  The penalty for sway error is zero
        Q(2, 2) = 2000;
        break;
      case MANEUVERING:
        Q(0, 0) = 1000;
        // Q(1, 1) = 0;  The penalty for sway error is zero
        Q(2, 2) = 100;
        break;
      default:
        break;
      }
    }
    // update mosek
    // for (int j = 0; j != n; ++j) {
    //   qval[j + 2 * m] = Q(j, j);
    // }
  }

  void update_propeller_parameter(std::vector<double> propeller_K_positive, std::vector<double> propeller_K_negtive,
                                  std::vector<int> propeller_delta_rotation, std::vector<double> propeller_delta_alfa,
                                  std::vector<int> propeller_max_rotation, std::vector<int> propeller_min_rotation,
                                  std::vector<double> propeller_max_alfa, std::vector<double> propeller_min_alfa)
  {
    for (int i = 0; i != num_tunnel; ++i)
    {
      //
      v_tunnelthrusterdata[i].K_positive = propeller_K_positive[i];
      v_tunnelthrusterdata[i].K_negative = propeller_K_negtive[i];              // K_negative
      v_tunnelthrusterdata[i].max_delta_rotation = propeller_delta_rotation[i]; // max_delta_rotation
      v_tunnelthrusterdata[i].max_rotation = propeller_max_rotation[i];         // max_rotation
      // v_tunnelthrusterdata[i].max_thrust_positive = propeller_max_thrust[i];    // max_thrust_positive 都为正值
      // v_tunnelthrusterdata[i].max_thrust_negative = propeller_min_thrust[i];    // max_thrust_negative 都为正值

      v_tunnelthrusterdata[i].max_thrust_positive =
          v_tunnelthrusterdata[i].K_positive * std::pow(v_tunnelthrusterdata[i].max_rotation, 2);
      v_tunnelthrusterdata[i].max_thrust_negative =
          v_tunnelthrusterdata[i].K_negative * std::pow(v_tunnelthrusterdata[i].max_rotation, 2);
    }
    for (int i = num_tunnel; i != num_azimuth + num_tunnel; ++i)
    {
      v_azimuththrusterdata[i].K = propeller_K_positive[i];
      v_azimuththrusterdata[i].max_delta_rotation = propeller_delta_rotation[i]; // max_delta_rotation
      v_azimuththrusterdata[i].max_rotation = propeller_max_rotation[i];         // max_rotation
      v_azimuththrusterdata[i].max_delta_alpha = propeller_delta_alfa[i];
      v_azimuththrusterdata[i].max_alpha = propeller_max_alfa[i],
      // v_azimuththrusterdata[i].max_thrust = propeller_max_thrust[i];
          v_azimuththrusterdata[i].min_rotation = propeller_min_rotation[i];
      v_azimuththrusterdata[i].min_alpha = propeller_min_alfa[i];
      // v_azimuththrusterdata[i].min_thrust = propeller_min_thrust[i];

      v_azimuththrusterdata[i].max_thrust =
          v_azimuththrusterdata[i].K * std::pow(v_azimuththrusterdata[i].max_rotation, 2);
      v_azimuththrusterdata[i].min_thrust =
          v_azimuththrusterdata[i].K * std::pow(v_azimuththrusterdata[i].min_rotation, 2);
    }
  }

  //
  vectormd getlx() const { return lx; }
  vectormd getly() const { return ly; }
  vectormd getupper_delta_alpha() const { return upper_delta_alpha; }
  vectormd getlower_delta_alpha() const { return lower_delta_alpha; }
  vectormd getupper_delta_u() const { return upper_delta_u; }
  vectormd getlower_delta_u() const { return lower_delta_u; }
  matrixnnd getQ() const { return Q; }
  matrixmmd getOmega() const { return Omega; }
  matrixmmd getQ_deltau() const { return Q_deltau; }
  vectormd getg_deltau() const { return g_deltau; }
  vectormd getd_rho() const { return d_rho; }
  matrixnmd getB_alpha() const { return B_alpha; }
  matrixnmd getd_Balpha_u() const { return d_Balpha_u; }
  vectornd getb() const { return b; }
  vectormd getdelta_alpha() const { return delta_alpha; }
  vectormd getdelta_u() const { return delta_u; }
  Eigen::Matrix<double, 2 * m + n, 1> getresults() const { return results; }

  // parameters for qpOASES
  //

private:
  const int num_tunnel;
  const int num_azimuth;
  const int num_mainrudder;
  const int numvar;
  const int num_constraints;

  // types of each thruster
  std::vector<int> index_thrusters;
  // constant value of all tunnel thrusters
  std::vector<tunnelthrusterdata> v_tunnelthrusterdata;
  // constant value of all tunnel thrusters
  std::vector<azimuththrusterdata> v_azimuththrusterdata;
  // constant value of all tunnel thrusters
  std::vector<ruddermaindata> v_ruddermaindata;
  // location of each thruster
  vectormd lx;
  vectormd ly;
  // real time constraints of each thruster
  vectormd upper_delta_alpha;
  vectormd lower_delta_alpha;
  vectormd upper_delta_u;
  vectormd lower_delta_u;
  // quadratic objective
  matrixnnd Q;
  matrixmmd Omega;
  matrixmmd Q_deltau;
  // linear objective
  vectormd g_deltau;
  vectormd d_rho;

  // real time constraint matrix in QP (equality constraint)
  matrixnmd B_alpha;
  matrixnmd d_Balpha_u; // Jocobian matrix of Balpha times u
  vectornd b;

  // real time physical variable in thruster allocation
  vectormd delta_alpha; // rad
  vectormd delta_u;     // N
  // linearized parameters
  double derivative_dx; // step size of the derivative

  qpOASES::real_t A_qp[n * (2 * m + n)];
  qpOASES::real_t lbA[n];
  qpOASES::real_t ubA[n];
  qpOASES::real_t H[(2 * m + n) * (2 * m + n)];
  qpOASES::real_t lb[2 * m + n];
  qpOASES::real_t ub[2 * m + n];
  qpOASES::real_t g_qp[2 * m + n];
  // // parameters for Mosek API
  // MSKint32t aptrb[2 * m + n], aptre[2 * m + n], asub[6 * m + n];
  // double aval[6 * m + n];
  // /* Bounds on constraints. */
  // MSKboundkeye bkc[n];
  // double blc[n];
  // double buc[n];
  // /* Bounds on variables. */
  // MSKboundkeye bkx[2 * m + n];
  // double blx[2 * m + n];
  // double bux[2 * m + n];

  // // objective g
  // double g[2 * m + n];

  // // The lower triangular part of the quadratic objective Q matrix in the
  // // objective is specified.
  // MSKint32t qsubi[2 * m + n];
  // MSKint32t qsubj[2 * m + n];
  // double qval[2 * m + n];
  // array to store the optimization results
  Eigen::Matrix<double, 2 * m + n, 1> results;

  // mosek environment
  // MSKenv_t env = NULL;
  // MSKtask_t task = NULL;
  // MSKrescodee r;

  void initializethrusterallocation()
  {
    for (int i = 0; i != num_tunnel; ++i)
    {
      lx(i) = v_tunnelthrusterdata[i].lx;
      ly(i) = v_tunnelthrusterdata[i].ly;
      Omega(i, i) = 1;
      // re-calculate the max thrust of tunnel thruser
      v_tunnelthrusterdata[i].max_thrust_positive =
          v_tunnelthrusterdata[i].K_positive *
          std::pow(v_tunnelthrusterdata[i].max_rotation, 2);
      v_tunnelthrusterdata[i].max_thrust_negative =
          v_tunnelthrusterdata[i].K_negative *
          std::pow(v_tunnelthrusterdata[i].max_rotation, 2);
    }
    for (int i = 0; i != num_azimuth; ++i)
    {
      int index_azimuth = num_tunnel + i;
      lx(index_azimuth) = v_azimuththrusterdata[i].lx;
      ly(index_azimuth) = v_azimuththrusterdata[i].ly;
      Omega(index_azimuth, index_azimuth) = 50;
      // re-calculate the max thrust of azimuth thruser
      v_azimuththrusterdata[i].max_thrust =
          v_azimuththrusterdata[i].K *
          std::pow(v_azimuththrusterdata[i].max_rotation, 2);
      v_azimuththrusterdata[i].min_thrust =
          v_azimuththrusterdata[i].K *
          std::pow(v_azimuththrusterdata[i].min_rotation, 2);
    }
    for (int i = 0; i != num_mainrudder; ++i)
    {
      int index_rudder = num_tunnel + num_azimuth + i;
      lx(index_rudder) = v_ruddermaindata[i].lx;
      ly(index_rudder) = v_ruddermaindata[i].ly;
      Omega(index_rudder, index_rudder) = 50;
      // re-calculate the max thrust of main thruser with rudder
      double Cy = v_ruddermaindata[i].Cy;
      v_ruddermaindata[i].max_thrust =
          v_ruddermaindata[i].K * std::pow(v_ruddermaindata[i].max_rotation, 2);
      v_ruddermaindata[i].min_thrust =
          v_ruddermaindata[i].K * std::pow(v_ruddermaindata[i].min_rotation, 2);
      v_ruddermaindata[i].max_alpha = std::atan(
          Cy * v_ruddermaindata[i].max_varphi /
          (1 - 0.02 * Cy * std::pow(v_ruddermaindata[i].max_varphi, 2)));
      v_ruddermaindata[i].min_alpha = std::atan(
          Cy * v_ruddermaindata[i].min_varphi /
          (1 - 0.02 * Cy * std::pow(v_ruddermaindata[i].min_varphi, 2)));
    }
    // quadratic penality matrix for error
    setQ(MANUAL);

    // initializemosekvariables();
    initializeqpOASESvariables();
    // initializeMosekAPI();
  }

  // void initializemosekvariables() {
  //   int _mdouble = 2 * m;
  //   int _mquintuple = 6 * m;
  //   // assign value to the bounds on variables
  //   for (int i = 0; i != _mdouble; ++i) {
  //     bkx[i] = MSK_BK_RA;
  //     blx[i] = 0.0;
  //     bux[i] = 0.0;
  //   }
  //   for (int j = 0; j != n; ++j) {
  //     int index_n = j + _mdouble;
  //     bkx[index_n] = MSK_BK_FR;
  //     blx[index_n] = -MSK_INFINITY;
  //     bux[index_n] = +MSK_INFINITY;
  //   }

  //   // assign value to the linear constraints
  //   for (int i = 0; i != _mdouble; ++i) {
  //     int _itriple = 3 * i;
  //     aptrb[i] = _itriple;
  //     aptre[i] = _itriple + 3;

  //     for (int j = 0; j != 3; ++j) {
  //       asub[_itriple + j] = j;
  //       aval[_itriple + j] = 0.0;
  //     }
  //   }
  //   for (int j = 0; j != n; ++j) {
  //     aptrb[j + _mdouble] = _mquintuple + j;
  //     aptre[j + _mdouble] = _mquintuple + j + 1;
  //     asub[j + _mquintuple] = j;
  //     aval[j + _mquintuple] = 1.0;
  //     bkc[j] = MSK_BK_FX;
  //     blc[j] = 0;
  //     buc[j] = 0;
  //   }

  //   // assign value to the objective
  //   for (int i = 0; i != numvar; ++i) {
  //     qsubi[i] = i;
  //     qsubj[i] = i;
  //     g[i] = 0;
  //   }
  //   for (int i = 0; i != m; ++i) {
  //     qval[i] = 0;
  //   }
  //   for (int i = 0; i != m; ++i) {
  //     qval[i + m] = Omega(i, i);
  //   }
  //   for (int j = 0; j != n; ++j) {
  //     qval[j + 2 * m] = Q(j, j);
  //   }
  // }

  // void initializeMosekAPI() {
  //   /* Create the mosek environment. */
  //   r = MSK_makeenv(&env, NULL);
  //   /* Create the optimization task. */
  //   r = MSK_maketask(env, num_constraints, numvar, &task);
  //   // set up the threads used by mosek
  //   r = MSK_putintparam(task, MSK_IPAR_NUM_THREADS, QP_THREADS_USED);
  //   // r = MSK_linkfunctotaskstream(task, MSK_STREAM_LOG, NULL, printstr);
  //   r = MSK_linkfunctotaskstream(task, MSK_STREAM_LOG, NULL, NULL);
  //   // append num_constrainsts empty contraints
  //   r = MSK_appendcons(task, num_constraints);
  //   // append numvar emtpy variables
  //   r = MSK_appendvars(task, numvar);
  // }

  // calculate the contraints of tunnel thruster
  // depend on the desired force in the Y direction or Mz direction
  void calculateconstraints_tunnel(const controllerRTdata<m, n> &_RTdata,
                                   double _desired_Mz)
  {
    for (int i = 0; i != num_tunnel; ++i)
    {
      int _maxdeltar = v_tunnelthrusterdata[i].max_delta_rotation;
      double _Kp = v_tunnelthrusterdata[i].K_positive;
      double _Kn = v_tunnelthrusterdata[i].K_negative;
      if (0 < _RTdata.rotation(i) && _RTdata.rotation(i) <= _maxdeltar)
      {
        // specify the first case
        if (_desired_Mz > 0)
        {
          upper_delta_alpha(i) = 0;
          lower_delta_alpha(i) = 0;
          lower_delta_u(i) = -_RTdata.u(i);
          upper_delta_u(i) =
              _Kp * std::pow(_RTdata.rotation(i) + _maxdeltar, 2) -
              _RTdata.u(i);
        }
        else
        {
          upper_delta_alpha(i) = -M_PI;
          lower_delta_alpha(i) = -M_PI;
          lower_delta_u(i) = -_RTdata.u(i);
          upper_delta_u(i) =
              _Kn * std::pow(_RTdata.rotation(i) - _maxdeltar, 2) -
              _RTdata.u(i);
        }
      }
      else if (-_maxdeltar <= _RTdata.rotation(i) &&
               _RTdata.rotation(i) < 0)
      {
        if (_desired_Mz > 0)
        {
          // specify the second case
          upper_delta_alpha(i) = M_PI;
          lower_delta_alpha(i) = M_PI;
          lower_delta_u(i) = -_RTdata.u(i);
          upper_delta_u(i) =
              _Kp * std::pow(_RTdata.rotation(i) + _maxdeltar, 2) -
              _RTdata.u(i);
        }
        else
        {
          // specify the first case
          upper_delta_alpha(i) = 0;
          lower_delta_alpha(i) = 0;
          lower_delta_u(i) = -_RTdata.u(i);
          upper_delta_u(i) =
              _Kn * std::pow(_RTdata.rotation(i) - _maxdeltar, 2) -
              _RTdata.u(i);
        }
      }
      else if (_RTdata.rotation(i) > _maxdeltar)
      {
        lower_delta_alpha(i) = 0;
        upper_delta_alpha(i) = 0;
        upper_delta_u(i) = std::min(
            v_tunnelthrusterdata[i].max_thrust_positive - _RTdata.u(i),
            _Kp * std::pow(_RTdata.rotation(i) + _maxdeltar, 2) - _RTdata.u(i));
        lower_delta_u(i) =
            _Kp * std::pow(_RTdata.rotation(i) - _maxdeltar, 2) - _RTdata.u(i);
      }
      else
      {
        lower_delta_alpha(i) = 0;
        upper_delta_alpha(i) = 0;
        upper_delta_u(i) = std::min(
            _Kn * std::pow(_RTdata.rotation(i) - _maxdeltar, 2) - _RTdata.u(i),
            v_tunnelthrusterdata[i].max_thrust_negative - _RTdata.u(i));
        lower_delta_u(i) =
            _Kn * std::pow(_RTdata.rotation(i) + _maxdeltar, 2) - _RTdata.u(i);
      }
    }
  }

  // calculate the consraints of azimuth thruster
  void calculateconstraints_azimuth(const controllerRTdata<m, n> &_RTdata)
  {
    for (int j = 0; j != num_azimuth; ++j)
    {
      int index_azimuth = j + num_tunnel;
      /* contraints on the increment of angle */
      upper_delta_alpha(index_azimuth) = std::min(
          v_azimuththrusterdata[j].max_delta_alpha,
          v_azimuththrusterdata[j].max_alpha - _RTdata.alpha(index_azimuth));
      lower_delta_alpha(index_azimuth) = std::max(
          -v_azimuththrusterdata[j].max_delta_alpha,
          v_azimuththrusterdata[j].min_alpha - _RTdata.alpha(index_azimuth));
      /* contraints on the increment of thrust */
      double K = v_azimuththrusterdata[j].K;
      int _maxdeltar = v_azimuththrusterdata[j].max_delta_rotation;
      upper_delta_u(index_azimuth) =
          std::min(
              v_azimuththrusterdata[j].max_thrust,
              K * std::pow(_RTdata.rotation(index_azimuth) + _maxdeltar, 2)) -
          _RTdata.u(index_azimuth);

      if (_RTdata.rotation(index_azimuth) < _maxdeltar)
        lower_delta_u(index_azimuth) =
            v_azimuththrusterdata[j].min_thrust - _RTdata.u(index_azimuth);
      else
        lower_delta_u(index_azimuth) =
            std::max(
                K * std::pow(_RTdata.rotation(index_azimuth) - _maxdeltar, 2),
                v_azimuththrusterdata[j].min_thrust) -
            _RTdata.u(index_azimuth);
    }
  } // calculateconstraints_azimuth

  //  calculate the consraints of thruster with rudder
  void calculateconstraints_rudder(const controllerRTdata<m, n> &_RTdata)
  {
    for (int k = 0; k != num_mainrudder; ++k)
    {
      int index_rudder = k + num_tunnel + num_azimuth;
      double K = v_ruddermaindata[k].K;
      int _maxdeltar = v_ruddermaindata[k].max_delta_rotation;
      double Cy = v_ruddermaindata[k].Cy;
      /* contraints on the rudder angle */
      double rudderangle = static_cast<double>(_RTdata.alpha_deg(index_rudder));
      double rudderangle_upper =
          std::min(rudderangle + v_ruddermaindata[k].max_delta_varphi,
                   v_ruddermaindata[k].max_varphi);
      double rudderangle_lower =
          std::max(rudderangle - v_ruddermaindata[k].max_delta_varphi,
                   v_ruddermaindata[k].min_varphi);

      /* contraints on the increment of alpha */
      upper_delta_alpha(index_rudder) =
          std::atan(Cy * rudderangle_upper /
                    (1 - 0.02 * Cy * std::pow(rudderangle_upper, 2))) -
          _RTdata.alpha(index_rudder);
      lower_delta_alpha(index_rudder) =
          std::atan(Cy * rudderangle_lower /
                    (1 - 0.02 * Cy * std::pow(rudderangle_lower, 2))) -
          _RTdata.alpha(index_rudder);
      /* contraints on the increment of thrust */
      // max and min of effective thrust
      double _max_u = std::min(
          v_ruddermaindata[k].max_thrust,
          K * std::pow(_RTdata.rotation(index_rudder) + _maxdeltar, 2));

      double _min_u = 0;
      if (_RTdata.rotation(index_rudder) < _maxdeltar)
        _min_u = v_ruddermaindata[k].min_thrust;
      else
        _min_u = std::max(
            K * std::pow(_RTdata.rotation(index_rudder) - _maxdeltar, 2),
            v_ruddermaindata[k].min_thrust);

      // max and min of sqrt root
      double max_squrevarphi = 0;
      double min_squrevarphi = 0;
      if (rudderangle_upper > 0 && rudderangle_lower > 0)
      {
        max_squrevarphi = std::pow(rudderangle_upper, 2);
        min_squrevarphi = std::pow(rudderangle_lower, 2);
      }
      else if (rudderangle_upper < 0 && rudderangle_lower < 0)
      {
        max_squrevarphi = std::pow(rudderangle_lower, 2);
        min_squrevarphi = std::pow(rudderangle_upper, 2);
      }
      else
      {
        max_squrevarphi = std::max(std::pow(rudderangle_lower, 2),
                                   std::pow(rudderangle_upper, 2));
        min_squrevarphi = 0;
      }

      double _max_usqrtterm = 0;
      double _min_usqrtterm = 0;

      double _a = 0.0004 * std::pow(Cy, 2);
      double _b = std::pow(Cy, 2) - 0.04 * Cy;
      double _c = 1.0;
      double min_point_x = 100.0 / Cy - 2500.0;
      if (min_squrevarphi > min_point_x)
      {
        _max_usqrtterm =
            std::sqrt(computeabcvalue(_a, _b, _c, max_squrevarphi));
        _min_usqrtterm =
            std::sqrt(computeabcvalue(_a, _b, _c, min_squrevarphi));
      }
      else if (max_squrevarphi < min_point_x)
      {
        _max_usqrtterm =
            std::sqrt(computeabcvalue(_a, _b, _c, min_squrevarphi));
        _min_usqrtterm =
            std::sqrt(computeabcvalue(_a, _b, _c, max_squrevarphi));
      }
      else
      {
        _max_usqrtterm =
            std::sqrt(std::max(computeabcvalue(_a, _b, _c, min_squrevarphi),
                               computeabcvalue(_a, _b, _c, max_squrevarphi)));
        _min_usqrtterm = std::sqrt(computeabcvalue(_a, _b, _c, min_point_x));
      }
      upper_delta_u(index_rudder) =
          _max_u * _max_usqrtterm - _RTdata.u(index_rudder);

      lower_delta_u(index_rudder) =
          _min_u * _min_usqrtterm - _RTdata.u(index_rudder);
    }
  } // calculateconstraints_rudder

  // calculate vessel parameters at the next time step
  void updateNextstep(controllerRTdata<m, n> &_RTdata)
  {
    // calculate delta variable using Mosek results
    delta_u = results.head(m);
    delta_alpha = results.segment(m, m);
    // update alpha and u
    updateAlphaandU(_RTdata.u, _RTdata.alpha);
    // convert the double alpha(rad) to int alpha(deg)
    convertalpharadian2int(_RTdata.alpha, _RTdata.alpha_deg);
    // update rotation speed
    calculaterotation(_RTdata);
    // update BalphaU
    _RTdata.BalphaU = calculateBalphau(_RTdata.alpha, _RTdata.u);
  }

  // update alpha and u using computed delta_alpha and delta_u
  void updateAlphaandU(vectormd &_u, vectormd &_alpha)
  {
    _u += delta_u;
    _alpha += delta_alpha;
  }
  // convert the radian to deg, and round to integer
  void convertalpharadian2int(const vectormd &_alpha, vectormi &_alpha_deg)
  {
    // round to int (deg) for tunnel and azimuth thrusters
    for (int i = 0; i != (num_tunnel + num_azimuth); ++i)
      _alpha_deg(i) = static_cast<int>(_alpha(i) * 180 / M_PI);

    // convert alpha to varphi (rudder angle) for thrusters with rudder
    for (int k = 0; k != num_mainrudder; ++k)
    {
      int r_index = num_tunnel + num_azimuth + k;

      if (std::round(180 * _alpha(r_index) / M_PI) == 0)
      {
        _alpha_deg(r_index) = 0;
        continue;
      }

      double cytan = v_ruddermaindata[k].Cy / std::tan(_alpha(r_index));
      double sqrtterm =
          std::sqrt(std::pow(cytan, 2) + 0.08 * v_ruddermaindata[k].Cy);
      double varphi = 0;
      if (_alpha(r_index) > 0)
        varphi = 25 * (sqrtterm - cytan) / v_ruddermaindata[k].Cy;
      else
        varphi = 25 * (-sqrtterm - cytan) / v_ruddermaindata[k].Cy;
      _alpha_deg(r_index) = static_cast<int>(std::round(varphi));
    }
  }

  // calcuate rotation speed of each thruster based on thrust
  // 根据每个螺旋桨的力计算转速
  void calculaterotation(controllerRTdata<m, n> &_RTdata)
  {
    // bow thruster
    for (int i = 0; i != num_tunnel; ++i)
    {
      int t_rotation = 0;
      if (_RTdata.alpha(i) < 0)
      {
        t_rotation = static_cast<int>(
            std::sqrt(abs(_RTdata.u(i)) / v_tunnelthrusterdata[i].K_negative));
        if (t_rotation == 0)
        {
          _RTdata.rotation(i) = -1; // prevent zero
          _RTdata.u(i) = v_tunnelthrusterdata[i].K_negative;
        }
        else
          _RTdata.rotation(i) = -t_rotation;
      }
      else
      {
        t_rotation = static_cast<int>(
            std::sqrt(abs(_RTdata.u(i)) / v_tunnelthrusterdata[i].K_positive));

        if (t_rotation == 0)
        {
          _RTdata.rotation(i) = 1; // prevent zero
          _RTdata.u(i) = v_tunnelthrusterdata[i].K_positive;
        }
        else
          _RTdata.rotation(i) = t_rotation;
      }
    }

    // azimuth thruster
    for (int j = 0; j != num_azimuth; ++j)
    {
      int index_azimuth = j + num_tunnel;

      int t_rotation = static_cast<int>(
          sqrt(abs(_RTdata.u(index_azimuth)) / v_azimuththrusterdata[j].K));
      if (t_rotation < v_azimuththrusterdata[j].min_rotation)
      {
        _RTdata.rotation(index_azimuth) = v_azimuththrusterdata[j].min_rotation;
        _RTdata.u(index_azimuth) = v_azimuththrusterdata[j].min_thrust;
      }
      else
        _RTdata.rotation(index_azimuth) = t_rotation;
    }

    // thruster with rudder
    for (int k = 0; k != num_mainrudder; ++k)
    {
      int index_rudder = k + num_tunnel + num_azimuth;
      double Cy = v_ruddermaindata[k].Cy;
      double _a = 0.0004 * std::pow(Cy, 2);
      double _b = std::pow(Cy, 2) - 0.04 * Cy;
      double _c = 1.0;

      double sqrtrootterm = std::sqrt(computeabcvalue(
          _a, _b, _c, std::pow(_RTdata.alpha_deg(index_rudder), 2)));

      int t_rotation =
          static_cast<int>(sqrt(abs(_RTdata.u(index_rudder)) /
                                (sqrtrootterm * v_ruddermaindata[k].K)));
      if (t_rotation < v_ruddermaindata[k].min_rotation)
      {
        _RTdata.rotation(index_rudder) = v_ruddermaindata[k].min_rotation;
        _RTdata.u(index_rudder) = v_ruddermaindata[k].min_thrust;
      }
      else
        _RTdata.rotation(index_rudder) = t_rotation;
    }
  }

  // calculate Balpha as function of alpha
  matrixnmd calculateBalpha(const vectormd &t_alpha)
  {
    matrixnmd _B_alpha = matrixnmd::Zero();
    double angle = 0;
    double t_cos = 0;
    double t_sin = 0;
    for (int i = 0; i != m; ++i)
    {
      angle = t_alpha(i);
      t_cos = cos(angle);
      t_sin = sin(angle);
      _B_alpha(0, i) = t_cos;
      _B_alpha(1, i) = t_sin;
      _B_alpha(2, i) = -ly(i) * t_cos + lx(i) * t_sin;
    }
    return _B_alpha;
  }
  // calculate the rho term in thruster allocation
  double calculateRhoTerm(const vectormd &t_alpha, double epsilon = 0.1,
                          double rho = 10)
  {
    auto _B_alpha = calculateBalpha(t_alpha);
    matrixnnd BBT = _B_alpha * _B_alpha.transpose();
    return rho / (epsilon + BBT.determinant());
  }
  // calculate Jacobian using central difference
  void calculateJocobianRhoTerm(const vectormd &t_alpha)
  {
    for (int i = 0; i != m; ++i)
    {
      auto alpha_plus = t_alpha;
      auto alpha_minus = t_alpha;
      alpha_plus(i) += derivative_dx;
      alpha_minus(i) -= derivative_dx;
      d_rho(i) =
          (calculateRhoTerm(alpha_plus) - calculateRhoTerm(alpha_minus)) /
          (2 * derivative_dx);
    }
  }
  // calculate the Balpha u term
  vectornd calculateBalphau(const vectormd &t_alpha, const vectormd &t_u)
  {
    return calculateBalpha(t_alpha) * t_u;
  }
  // calculate derivative of Balpha times u
  void calculateJocobianBalphaU(const vectormd &t_alpha, const vectormd &t_u)
  {
    for (int i = 0; i != m; ++i)
    {
      auto alpha_plus = t_alpha;
      auto alpha_minus = t_alpha;
      alpha_plus(i) += derivative_dx;
      alpha_minus(i) -= derivative_dx;
      d_Balpha_u.col(i) = (calculateBalphau(alpha_plus, t_u) -
                           calculateBalphau(alpha_minus, t_u)) /
                          (2 * derivative_dx);
    }
  }
  // calculate g_deltau and Q_deltau
  void calculateDeltauQ(const vectormd &t_u)
  {
    vectormd d_utemp = vectormd::Zero();
    d_utemp = t_u.cwiseSqrt();
    g_deltau = 1.5 * d_utemp;
    vectormd Q_temp = vectormd::Zero();
    // Q_temp = 0.75 * d_utemp.cwiseInverse();
    Q_temp = 7.5 * d_utemp.cwiseInverse();
    Q_deltau = Q_temp.asDiagonal();
  }
  // calculate the BalphaU and b
  void calculateb(const vectornd &_tau, const vectornd &_BalphaU)
  {
    b = _tau - _BalphaU;
  }

  // update parameters in thruster allocation for each time step
  void updateTAparameters(const controllerRTdata<m, n> &_RTdata)
  {
    B_alpha = calculateBalpha(_RTdata.alpha);
    if (index_actuation == FULLYACTUATED) //constexpr
      calculateJocobianRhoTerm(_RTdata.alpha);
    calculateJocobianBalphaU(_RTdata.alpha, _RTdata.u);
    calculateDeltauQ(_RTdata.u);
    calculateb(_RTdata.tau, _RTdata.BalphaU);
    calculateconstraints_tunnel(_RTdata, _RTdata.tau(2));
    calculateconstraints_azimuth(_RTdata);
    calculateconstraints_rudder(_RTdata);
  }
  // // update parameters in QP for each time step
  // void updateMosekparameters() {
  //   // update A values
  //   for (int i = 0; i != m; ++i) {
  //     for (int j = 0; j != n; ++j) {
  //       aval[n * i + j] = B_alpha(j, i);
  //       aval[n * (i + m) + j] = d_Balpha_u(j, i);
  //     }
  //   }

  //   // update linear constraints
  //   for (int i = 0; i != num_constraints; ++i) {
  //     blc[i] = b(i);
  //     buc[i] = b(i);
  //   }

  //   for (int i = 0; i != m; ++i) {
  //     // update variable constraints
  //     blx[i] = lower_delta_u(i);
  //     bux[i] = upper_delta_u(i);
  //     blx[m + i] = lower_delta_alpha(i);
  //     bux[m + i] = upper_delta_alpha(i);
  //     // update objective g and Q
  //     g[i] = g_deltau(i);
  //     g[i + m] = d_rho(i);
  //     qval[i] = Q_deltau(i, i);
  //   }
  // }

  // 一元二次方程
  double computeabcvalue(double a, double b, double c, double x)
  {
    return a * x * x + b * x + c;
  }
  // // solve QP using Mosek solver
  // void onestepmosek() {
  //   MSKint32t i, j;
  //   double t_results[2 * m + n];
  //   results.setZero();
  //   if (r == MSK_RES_OK) {
  //     for (j = 0; j < numvar; ++j) {
  //       /* Set the linear term g_j in the objective.*/
  //       r = MSK_putcj(task, j, g[j]);

  //       /* Set the bounds on variable j.
  //        blx[j] <= x_j <= bux[j] */
  //       r = MSK_putvarbound(task, j, /* Index of variable.*/
  //                           bkx[j],  /* Bound key.*/
  //                           blx[j],  /* Numerical value of lower bound.*/
  //                           bux[j]); /* Numerical value of upper bound.*/

  //       /* Input column j of A */
  //       r = MSK_putacol(
  //           task, j,             /* Variable (column) index.*/
  //           aptre[j] - aptrb[j], /* Number of non-zeros in column j.*/
  //           asub + aptrb[j],     /* Pointer to row indexes of column j.*/
  //           aval + aptrb[j]);    /* Pointer to Values of column j.*/
  //     }

  //     /* Set the bounds on constraints.
  //        for i=1, ...,NUMCON : blc[i] <= constraint i <= buc[i] */
  //     for (i = 0; i < num_constraints; ++i)
  //       r = MSK_putconbound(task, i, /* Index of constraint.*/
  //                           bkc[i],  /* Bound key.*/
  //                           blc[i],  /* Numerical value of lower bound.*/
  //                           buc[i]); /* Numerical value of upper bound.*/

  //     /* Input the Q for the objective. */
  //     r = MSK_putqobj(task, numvar, qsubi, qsubj, qval);

  //     if (r == MSK_RES_OK) {
  //       MSKrescodee trmcode;

  //       /* Run optimizer */
  //       r = MSK_optimizetrm(task, &trmcode);

  //       /* Print a summary containing information
  //          about the solution for debugging purposes*/
  //       // MSK_solutionsummary(task, MSK_STREAM_MSG);

  //       if (r == MSK_RES_OK) {
  //         MSKsolstae solsta;
  //         MSK_getsolsta(task, MSK_SOL_ITR, &solsta);

  //         switch (solsta) {
  //           case MSK_SOL_STA_OPTIMAL:
  //           case MSK_SOL_STA_NEAR_OPTIMAL: {
  //             /* Request the interior solution. */
  //             MSK_getxx(task, MSK_SOL_ITR, t_results);
  //             for (int k = 0; k != numvar; ++k) results(k) = t_results[k];
  //             break;
  //           }

  //           case MSK_SOL_STA_DUAL_INFEAS_CER:
  //           case MSK_SOL_STA_PRIM_INFEAS_CER:
  //           case MSK_SOL_STA_NEAR_DUAL_INFEAS_CER:
  //           case MSK_SOL_STA_NEAR_PRIM_INFEAS_CER: {
  //             CLOG(ERROR, "mosek")
  //                 << "Primal or dual infeasibility certificate found.";
  //             break;
  //           }
  //           case MSK_SOL_STA_UNKNOWN: {
  //             CLOG(ERROR, "mosek") << "The status of the solution could not
  //             be "
  //                                     "determined.";
  //             break;
  //           }
  //           default: {
  //             CLOG(ERROR, "mosek") << "Other solution status.";
  //             break;
  //           }
  //         }
  //       } else {
  //         CLOG(ERROR, "mosek") << "Error while optimizing.";
  //       }
  //     }
  //     if (r != MSK_RES_OK) {
  //       /* In case of an error print error code and description. */
  //       char symname[MSK_MAX_STR_LEN];
  //       char desc[MSK_MAX_STR_LEN];
  //       MSK_getcodedesc(r, symname, desc);

  //       CLOG(ERROR, "mosek")
  //           << "An error occurred while optimizing. " << std::string(symname)
  //           << " - " << std::string(desc);
  //     }
  //   }
  // }
  void initializeqpOASESvariables()
  {
    int m_total_variable = 2 * m + n;
    int m_control_variable = 2 * m;
    for (int i = 0; i < (n * (2 * m + n)); i++)
      A_qp[i] = 0;
    for (int i = 0; i < n; i++)
    {
      A_qp[(2 * m + n + 1) * i + 2 * m] = 1;
    }
    for (int i = 0; i < n; i++)
    {
      lbA[i] = 0;
      ubA[i] = 0;
    }
    for (int i = 0; i < m_total_variable; i++)
    {
      g_qp[i] = 0;
    }
    for (int i = 0; i < m_total_variable - 3; i++)
    {
      lb[i] = 0;
      ub[i] = 0;
    }

    for (int i = m_total_variable - 3; i < m_total_variable; i++)
    {
      lb[i] = -1000;
      ub[i] = 1000;
    }

    for (int i = 0; i < ((2 * m + n) * (2 * m + n)); i++)
      H[i] = 0;
    for (int i = 0; i < m; i++)
      H[(2 * m + n + 1) * i] = 0;
    for (int i = m; i < 2 * m; i++)
      H[(2 * m + n + 1) * i] = Omega(i - m, i - m);
    for (int i = 2 * m; i < 2 * m + n; i++)
      H[(2 * m + n + 1) * i] = Q(i - 2 * m, i - 2 * m);
  }

  // updata parameters in QP for each step
  void updateqpOASESparameters()
  {
    // 更新A_qp的值 等式约束
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
        A_qp[i * (2 * m + n) + j] = B_alpha(i, j);
      for (int j = m; j < 2 * m; j++)
        A_qp[i * (2 * m + n) + j] = d_Balpha_u(i, j - m);
    }

    // 更新等式约束的等号右边
    for (int i = 0; i < n; ++i)
    {
      // tranfer linear constraints to qpOASES format
      ubA[i] = b(i);
      lbA[i] = b(i);
    }

    for (int i = 0; i != m; ++i)
    {
      // update variable constraints
      // tranfer variable constraints to qpOASES format
      // 更新Delta速度 Delta转角值的上下边界
      lb[i] = lower_delta_u(i);
      ub[i] = upper_delta_u(i);
      lb[m + i] = lower_delta_alpha(i);
      ub[m + i] = upper_delta_alpha(i);

      // update objective g
      // tranfer to qpOASES format
      // 更新凸规划目标函数一次项的参数g
      g_qp[i] = g_deltau(i);
      g_qp[i + m] = d_rho(i);
      // qval[i] = Q_deltau(i, i);
      //
    }

    // update objective Q
    // 更新凸规划目标函数二次项的参数Q 此处命名为H
    for (int i = 0; i < m; i++)
    {
      H[(2 * m + n + 1) * i] = Q_deltau(i, i);
    }
  }

  void printparameter()
  {
    using namespace std;
    std::cout << "the parameters" << std::endl;
    std::cout << "H: \n"
              << H << std::endl;
    for (int i = 0; i != (2 * m + n) * (2 * m + n); ++i)
    {
      std::cout << fixed << setprecision(2) << H[i] << " ";
      if ((i + 1) % (2 * m + n) == 0)
        std::cout << std::endl;
    }
    //
    std::cout << "g_qp: \n"
              << g_qp << std::endl;
    for (int i = 0; i != (2 * m + n); ++i)
      std::cout << g_qp[i] << std::endl;
    //
    std::cout << "A_qp: \n"
              << A_qp << std::endl;
    for (int i = 0; i != (2 * m + n) * n; ++i)
    {
      std::cout << fixed << setprecision(2) << A_qp[i] << " ";
      if ((i + 1) % (2 * m + n) == 0)
        std::cout << std::endl;
    }
    std::cout << "lb: \n"
              << fixed << setprecision(2) << lb << std::endl;
    for (int i = 0; i != (2 * m + n); ++i)
      std::cout << lb[i] << std::endl;
    std::cout << "ub: \n"
              << fixed << setprecision(2) << ub << std::endl;
    for (int i = 0; i != (2 * m + n); ++i)
      std::cout << ub[i] << std::endl;
    std::cout << "lbA: \n"
              << fixed << setprecision(2) << lbA << std::endl;
    for (int i = 0; i != n; ++i)
      std::cout << lbA[i] << std::endl;
    std::cout << "ubA: \n"
              << fixed << setprecision(2) << ubA << std::endl;
    for (int i = 0; i != n; ++i)
      std::cout << ubA[i] << std::endl;
  }

  void onestepqpOASES()
  {
    USING_NAMESPACE_QPOASES
    /* Setting up QProblem object. */
    QProblem TA(numvar, num_constraints);
    Options options;
    TA.setOptions(options);
    /* Solve first QP. */
    int_t nWSR = 100;
    TA.init(H, g_qp, A_qp, lb, ub, lbA, ubA, nWSR);
    TA.hotstart(g_qp, lb, ub, lbA, ubA, nWSR);
    std::cout << "QP problem is solved" << std::endl;
    /* Get and print solution of first QP. */
    real_t xOpt[2 * m + n];
    // real_t yOpt[2 + 1];

    TA.getPrimalSolution(xOpt);
    // example.getDualSolution(yOpt);
    // printf("\nxOpt = [ %e, %e ];  yOpt = [ %e, %e, %e ];  objVal =%e\n\n",
    // xOpt[0], xOpt[1], yOpt[0], yOpt[1], yOpt[2], example.getObjVal());
    for (int k = 0; k != numvar; ++k)
    {
      results(k) = xOpt[k];
      std::cout << "result" << k << ":  " << results(k) << std::endl;
    }
    TA.printOptions();
    /*example.printProperties();*/

    /*getGlobalMessageHandler()->listAllMessages();*/
  }
};

void string2double_array(std::string read_buffer, std::vector<double> &data)
{
  switch (data.size())
  {
  case 1:
    sscanf(read_buffer.c_str(), "%lf", &data[0]);
    break;
  case 2:
    sscanf(read_buffer.c_str(), "%lf,%lf", &data[0], &data[1]);
    break;
  case 3:
    sscanf(read_buffer.c_str(), "%lf,%lf,%lf", &data[0], &data[1], &data[2]);
    break;
  case 4:
    sscanf(read_buffer.c_str(), "%lf,%lf,%lf,%lf", &data[0], &data[1],
           &data[2], &data[3]);
    break;
  case 5:
    sscanf(read_buffer.c_str(), "%lf,%lf,%lf,%lf,%lf", &data[0], &data[1],
           &data[2], &data[3], &data[4]);
    break;
  case 6:
    sscanf(read_buffer.c_str(), "%lf,%lf,%lf,%lf,%lf,%lf", &data[0], &data[1],
           &data[2], &data[3], &data[4], &data[5]);
    break;
  }
}

void string2int_array(std::string read_buffer, std::vector<int> &data)
{
  switch (data.size())
  {
  case 1:
    sscanf(read_buffer.c_str(), "%i", &data[0]);
    break;
  case 2:
    sscanf(read_buffer.c_str(), "%i,%i", &data[0], &data[1]);
    break;
  case 3:
    sscanf(read_buffer.c_str(), "%i,%i,%i", &data[0], &data[1], &data[2]);
    break;
  case 4:
    sscanf(read_buffer.c_str(), "%i,%i,%i,%i", &data[0], &data[1],
           &data[2], &data[3]);
    break;
  case 5:
    sscanf(read_buffer.c_str(), "%i,%i,%i,%i,%i", &data[0], &data[1],
           &data[2], &data[3], &data[4]);
    break;
  case 6:
    sscanf(read_buffer.c_str(), "%i,%i,%i,%i,%i,%i", &data[0], &data[1],
           &data[2], &data[3], &data[4], &data[5]);
    break;
  }
}

// restrict the desired force to some value
double restrictdesiredforce(double _input, double _min, double _max)
{
  double t_input = _input;
  if (std::abs(_input) > _max)
    t_input = _max * _input / std::abs(_input);
  if (std::abs(_input) < _min)
    t_input = _min * _input / std::abs(_input);
  return t_input;
}
void restrictdesiredforce(double *target_force, std::vector<double> min_target_force, std::vector<double> max_target_force)
{

  for (int i = 0; i != dim_controlspace; ++i)
  {
    // ROS_INFO_STREAM(target_force[i]);
    // ROS_INFO_STREAM(min_target_force[i]);
    // ROS_INFO_STREAM(max_target_force[i]);
    target_force[i] = restrictdesiredforce(target_force[i], min_target_force[i],
                                           max_target_force[i]);
    // ROS_INFO_STREAM(target_force[i]);
  }
}

#endif /* _THRUSTALLOCATION_H_*/