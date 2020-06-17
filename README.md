# 多船协同动力定位仿真系统

- 基于Ubuntu
- 基于C++

- 基于ROS系统
- 给予GAZEBO
- 可视化仿真



## 安装

### prerequisites

```shell
$ sudo apt update
$ sudo apt full-upgrade
```



```shell
$ sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
$ sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
$ sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
$ wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
$ sudo apt update
$ DIST=melodic
$ GAZ=gazebo9
$ sudo apt install cmake mercurial git ruby libeigen3-dev ${GAZ} lib${GAZ}-dev pkg-config python ros-${DIST}-gazebo-plugins ros-${DIST}-gazebo-ros ros-${DIST}-hector-gazebo-plugins ros-${DIST}-joy ros-${DIST}-joy-teleop ros-${DIST}-key-teleop ros-${DIST}-robot-localization ros-${DIST}-robot-state-publisher ros-${DIST}-joint-state-publisher ros-${DIST}-rviz ros-${DIST}-ros-base ros-${DIST}-teleop-tools ros-${DIST}-teleop-twist-keyboard ros-${DIST}-velodyne-simulator ros-${DIST}-xacro ros-${DIST}-rqt ros-${DIST}-rqt-common-plugins protobuf-compiler
```



### install(可能暂时有点问题)

```shell
$ mkdir -p ~/vrx_ws/src
$ cd ~/vrx_ws/src
$ git clone https://github.com/zhenqiufu/vrx_ws.git
```

```shell
$ source /opt/ros/melodic/setup.bash
```

```shell
$ cd ~/vrx_ws
$ catkin_make
```



## 测试一

```shell
$ source  ~/vrx_ws/devel/setup.bash
```



```shell
$ roslaunch vrx_gazebo sandisland.launch
```



- 如果出现仿真界面, 则第一步成功,已经安装成功单船仿真.



## 测试二

```shell
cd ~/vrx_ws
catkin_make
source devel/setup.bash
```

```shell
roslaunch rxi rxi_multi.launch verbose:=true
```



## 节点关系与话题

`rosrun rqt_graph rqt_graph`



## 键盘控制

```shell
roslaunch rxi defender_keydrive.launch namespace:=defender_a
roslaunch rxi defender_keydrive.launch namespace:=defender_b
```



## joystick控制