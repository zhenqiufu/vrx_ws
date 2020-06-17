```

```

启动

`roslaunch rxi rxi_multi.launch verbose:=true`

- 需要加入节点
  - PID控制
  - 转UTM
  - 坐标转换
  - 推力分配
  - 手柄
  - 同一控制器
  - 数据融合
  - 滤波
  - 波频运动

```
/clock
/defender_a/joint_states
/defender_a/sensors/cameras/front_left_camera/camera_info
/defender_a/sensors/cameras/front_left_camera/image_raw
/defender_a/sensors/cameras/front_left_camera/parameter_descriptions
/defender_a/sensors/cameras/front_left_camera/parameter_updates
/defender_a/sensors/cameras/front_right_camera/camera_info
/defender_a/sensors/cameras/front_right_camera/image_raw
/defender_a/sensors/cameras/front_right_camera/parameter_descriptions
/defender_a/sensors/cameras/front_right_camera/parameter_updates
/defender_a/sensors/cameras/middle_right_camera/camera_info
/defender_a/sensors/cameras/middle_right_camera/image_raw
/defender_a/sensors/cameras/middle_right_camera/parameter_descriptions
/defender_a/sensors/cameras/middle_right_camera/parameter_updates
/defender_a/sensors/gps/gps/fix
/defender_a/sensors/gps/gps/fix/position/parameter_descriptions
/defender_a/sensors/gps/gps/fix/position/parameter_updates
/defender_a/sensors/gps/gps/fix/status/parameter_descriptions
/defender_a/sensors/gps/gps/fix/status/parameter_updates
/defender_a/sensors/gps/gps/fix/velocity/parameter_descriptions
/defender_a/sensors/gps/gps/fix/velocity/parameter_updates
/defender_a/sensors/gps/gps/fix_velocity
/defender_a/sensors/imu/imu/data
/defender_a/sensors/imu/imu/data/accel/parameter_descriptions
/defender_a/sensors/imu/imu/data/accel/parameter_updates
/defender_a/sensors/imu/imu/data/bias
/defender_a/sensors/imu/imu/data/rate/parameter_descriptions
/defender_a/sensors/imu/imu/data/rate/parameter_updates
/defender_a/sensors/imu/imu/data/yaw/parameter_descriptions
/defender_a/sensors/imu/imu/data/yaw/parameter_updates
/defender_a/sensors/lidars/lidar_wamv/points
/defender_a/sensors/pingers/pinger/range_bearing
/defender_a/sensors/pingers/pinger/set_pinger_position
/defender_a/thrusters/lateral_thrust_angle
/defender_a/thrusters/lateral_thrust_cmd
/defender_a/thrusters/left_thrust_angle
/defender_a/thrusters/left_thrust_cmd
/defender_a/thrusters/right_thrust_angle
/defender_a/thrusters/right_thrust_cmd
/defender_b/joint_states
/defender_b/sensors/cameras/front_left_camera/camera_info
/defender_b/sensors/cameras/front_left_camera/image_raw
/defender_b/sensors/cameras/front_left_camera/parameter_descriptions
/defender_b/sensors/cameras/front_left_camera/parameter_updates
/defender_b/sensors/cameras/front_right_camera/camera_info
/defender_b/sensors/cameras/front_right_camera/image_raw
/defender_b/sensors/cameras/front_right_camera/parameter_descriptions
/defender_b/sensors/cameras/front_right_camera/parameter_updates
/defender_b/sensors/cameras/middle_right_camera/camera_info
/defender_b/sensors/cameras/middle_right_camera/image_raw
/defender_b/sensors/cameras/middle_right_camera/parameter_descriptions
/defender_b/sensors/cameras/middle_right_camera/parameter_updates
/defender_b/sensors/gps/gps/fix
/defender_b/sensors/gps/gps/fix/position/parameter_descriptions
/defender_b/sensors/gps/gps/fix/position/parameter_updates
/defender_b/sensors/gps/gps/fix/status/parameter_descriptions
/defender_b/sensors/gps/gps/fix/status/parameter_updates
/defender_b/sensors/gps/gps/fix/velocity/parameter_descriptions
/defender_b/sensors/gps/gps/fix/velocity/parameter_updates
/defender_b/sensors/gps/gps/fix_velocity
/defender_b/sensors/imu/imu/data
/defender_b/sensors/imu/imu/data/accel/parameter_descriptions
/defender_b/sensors/imu/imu/data/accel/parameter_updates
/defender_b/sensors/imu/imu/data/bias
/defender_b/sensors/imu/imu/data/rate/parameter_descriptions
/defender_b/sensors/imu/imu/data/rate/parameter_updates
/defender_b/sensors/imu/imu/data/yaw/parameter_descriptions
/defender_b/sensors/imu/imu/data/yaw/parameter_updates
/defender_b/sensors/lidars/lidar_wamv/points
/defender_b/sensors/pingers/pinger/range_bearing
/defender_b/sensors/pingers/pinger/set_pinger_position
/defender_b/thrusters/lateral_thrust_angle
/defender_b/thrusters/lateral_thrust_cmd
/defender_b/thrusters/left_thrust_angle
/defender_b/thrusters/left_thrust_cmd
/defender_b/thrusters/right_thrust_angle
/defender_b/thrusters/right_thrust_cmd
/gazebo/link_states
/gazebo/model_states
/gazebo/parameter_descriptions
/gazebo/parameter_updates
/gazebo/set_link_state
/gazebo/set_model_state
/rosout
/rosout_agg
/vrx/debug/wind/direction
/vrx/debug/wind/speed

```

