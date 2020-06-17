##########################################################################
# File Name: run.sh
# Function: 
# Author: Zhenqiu Fu
# Mail: fuzhenqiu0810@gmail.com
# Created Time: 2020年06月16日 星期二 20时39分56秒
#########################################################################
#!/bin/zsh

echo "***********************************************************"
echo "*                                                         *"
echo "*              多浮体协同动力定位仿真软件                   *"
echo "*                                                         *"
echo "*                      V 0.0.1                            *"
echo "*                                                         *"
echo "*                 CopyRight@ Zhenqiu Fu                   *"
echo "*                                                         *"
echo "*             Email:fuzhenqiu0810@gmail.com               *"
echo "*                                                         *"
echo "***********************************************************"

echo "*                 启动中......                             *"
sleep 3

# run multi vessel model
roslaunch rxi rxi_multi.launch verbose:=true &

sleep 5


echo "*******************************************"
echo "*                                         *"
echo "*     Multi vessels starting success!     *"
echo "*       多船仿真模型启动成功               *"
echo "*                                         *"
echo "*                                         *"
echo "*******************************************"

# 动力定位包启动
roslaunch multi_dp dp.launch &
sleep 3

echo "*******************************************"
echo "*                                         *"
echo "*    DP controller starting success!      *"
echo "*      动力定位控制系统启动成功             *"
echo "*                                         *"
echo "*                                         *"
echo "*****************************************"

sleep 3



# 数据库包


# run controller



sleep 0.1
wait
exit 0