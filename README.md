# Tal-Brabo-ROS-MC4N-triomotion-controller
Controlling a triomotion MC4N controller in order to move a Tal Brabo robotic arm under ROS and ubuntu 16.04
    1) Tested system:

-ubuntu 16.04

-ros kinetic

   2) Communication with Linux:

The IP address of the controller is 192.168.0.250

You should add a new connection with the configuration below:

IPv4 Settings

Method: Manual

Addresses

Address: 192.168.0.251

Netmask: 24

Gateway: 192.168.0.1

    3) Installation:

3.1) copy the file libTrioPC-x86_64.so from:

/tal brabo documentation/tal_arm_doc/trio_motion_arm/include to this two folders: /usr/local/lib and /usr/lib

3.2) clone this project to your workspace:

3.3) open terminal and run:

cd catkin_ws

source devel/setup.bash

catkin_make

    4)Programs explanation:

For further ActiveX cammands informations please refer to ActiveX manual.

4.1) arm control.cpp:

This program is used to control the arm as followed:

axis 1, 2, 3, 4, 5 are defined respectively as axis 8, 9, 10, 11, 13. two commands were mainly used:

RemoteExecuteCommand(“BASE(1,x)”)

RemoteExecuteCommand(“MOVE(1,y)”)

x:the axis number

y:the desired distance

4.2) arm position.cpp:

This program is used to display the joints positions.

Two commands were mainly used:

RemoteExecuteCommand(“BASE(x)”)

RemoteGetVariable(“MPOS”,&i)

x:the axis number

MPOS:the measured position of the x axis

Arm control steps:

    5) Arm control:

==>to control the arm,run on the terminal: rosrun trio_motion_arm talarm_control

==>to receive the position of the arm,run on the terminal: rosrun trio_motion_arm talarm_position
