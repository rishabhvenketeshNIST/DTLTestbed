# Integrated Digital Twin of Universal Robots UR5e and RobotIQ 2F85 Adaptive Gripper

# Overview of ROS Packages

integrated_ur_robotiq
- Programs related to inspecting and controlling a digital and physical version at the same time
- Launch files to control either type individually

robotiq_gripper
- Programs related to controlling the 2F85 gripper
- IDL message types for communicating with the gripper controllers

ur_robotiq_description
- URDF files which include the ur5e and 2F85 in the same model

ur_robotiq_moveit_config
- SRDF files which include the ur5e and 2F85
- Path planner configuration

# Setup

Before building and using this ros2 workspace, complete the following steps:

## ros2

Sources:
- https://docs.ros.org/en/iron/Installation/Ubuntu-Install-Debians.html
- https://colcon.readthedocs.io/en/released/user/installation.html#enable-completion

1. install ros2 iron apt repository:
```
sudo apt install software-properties-common
sudo add-apt-repository universe
sudo apt update && sudo apt upgrade && sudo apt install curl -y
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg

echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
```
2. Install and set up ros2 iron
```
sudo apt install ros-iron-desktop python3-colcon-common-extensions

echo "source /opt/ros/iron/setup.bash" >> ~/.bashrc
echo "export ROS_DOMAIN_ID=11" >> ~/.bashrc # Only ROS installations with the same domain id can communicate directly with each other, 11 chosen arbitrarily
echo "source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash" >> ~/.bashrc
```
3. Install packages for ros2, UR robots, and robotiq gripper
```
sudo apt install ros-iron-ur ros-iron-robotiq-controllers ros-iron-robotiq-description
pip install ur_rtde
```

## Docker
Docker is used to run URSim.
1. On Ubuntu, the easiest way to install docker is to run `sudo apt install docker.io`.
   This is sufficient for URSim.

## Raylib
Raylib is a graphics library used for the GUI.
1. Download and extract the raylib-5.0 release from https://github.com/raysan5/raylib
2. In a shell, open the directory `raylib-5.0/src`
3. Run `sudo make install` to build and install the library

## Raygui
Raygui is a GUI library for Raylib.
1. Download and extract the raygui-4.0 release from https://github.com/raysan5/raygui
2. In a shell, open the directory `raygui-4.0/src`
3. Run `sudo cp ./raygui.h /usr/local/include` to install the header alongside raylib

## URSim
1. Start URSim for the first time by running `ros2 run ur_client_library start_ursim.sh`.
   This will download the docker file from UR if it is not present.
2. If you do not have permission to run URSim because of `/run/docker.sock`, then take ownership of the file by running
   `sudo chown $USER:$USER /run/docker.sock`, and try to run URSim again.
3. Once URSim has started, navigate in the Installation tab to URCaps/External Control
4. Change the "Custom port" from the default of 50002 to 50012. This allows URSim and the physical robot to connect to the same machine.
    - Note: both ip address fields are 192.168.56.1 by default, you shouldn't have to change them
5. Save the installation by overwriting `default.installation`

## Physical UR Cobot
1. If it is not present, install the External Control URCap from https://github.com/UniversalRobots/Universal_Robots_ExternalControl_URCap
2. Create a program consisting of a single External Control block
3. Save the program as "External Control" (case-sensitive)
4. This program must be running without error for the robot to accept control commands from ROS
	- The program will error if the ur_robot_driver is not running in ROS

# Important Commands
```
# while in ros2_ws folder
source ./setup.bash
# or
. setup.bash
```
- Adds executables from this workspace to the environment of the current shell
- Without this, ros2 would not be able to find any of the files in the workspace
- This must be done for every new shell that you open before running any other ros commands
- You can automate this by adding this command to the ~/.bashrc file: `source ~/ros2_ws/install/setup.bash`
- If the workspace is in a folder with a different path than "~/ros2_ws", then the path in the above commands must reflect that change

Launch the following commands in order to run the full integrated digital twin:

```
# in the ros2_ws folder
colcon build
```
- This will build all packages in the workspace

```
ros2 launch integrated_ur_robotiq physical.launch.py robot_ip:=192.168.50.25
```
- Runs the ur_robot_driver for communication with the UR5e at IP 192.168.50.25
- Runs a program to communicate with the physical gripper

```
ros2 launch integrated_ur_robotiq digital.launch.py
```
- Launches URSim if it isn't already running
- Runs the ur_robot_driver for communication with URSim
- Runs a program to simulate the gripper, including communication with ROS
- Runs a visualization of the digital gripper

```
ros2 launch ur_robotiq_moveit_config ur_robotiq_moveit.launch.py
```
- Launches the MoveIt path planning service for the *physical* robot
- Launches RViz to view and manually control the path planner

```
ros2 launch integrated_ur_robotiq integrated.launch.py
```
- Launches programs which evaluate the synchronization of URSim and the physical robot
- Runs a UI to display that information

```
ros2 launch ur_robotiq_moveit_config run.launch.py run:="integrated_ur_robotiq integrated_control_test"
```
- Runs a script to test the functionality of the integrated digital twin composition
    - Activates the gripper
    - Moves the gripper
    - Moves the arm based on joints
    - Moves the arm along a linear path
- Use the source for itegrated_control_test.cpp as a reference for how to control the robot.
- The run.launch.py script is a general purpose script for running ros2 nodes with information relevant to moveit, such as URDF and SRDF files
- The run argument specifies the package, executable, and arguments to launch
    - As an example, consider: run:="integrated_ur_robotiq ur_pose_monitor src_ns:=/digital". The package is integrated_ur_robotiq, the executable is ur_pose_monitor, and the argument src_ns is set to "/digital"


# Libraries Used

For further development of this digital twin, refer to the linked documentation:
- [ROS 2](https://docs.ros.org/en/iron/index.html)
- [CMake](https://cmake.org/cmake/help/latest/)
- [UR_RTDE](https://sdurobotics.gitlab.io/ur_rtde/api/api.html)
- [URScript](https://www.universal-robots.com/download/manuals-e-seriesur20ur30/script/script-manual-e-series-sw-511/)
- [UR Dashboard Server](https://s3-eu-west-1.amazonaws.com/ur-support-site/42728/DashboardServer_e-Series_2022.pdf)
- [Moveit2](https://moveit.picknik.ai/main/index.html)
- [Raylib](https://www.raylib.com/)

# ROS Package Details

## integrated_ur_robotiq

include/integrated_ur_robotiq/integrated_control.hpp
- Single-header library that must be used to control the integrated digital twin and the physical robots at the same time.
- Allows for moving the arm and the gripper
- You must have `#define INTEGRATED_CONTROL_IMPL` before `#include integrated_ur_robotiq/integrated_control.hpp` for the function declarations to have definitions
	- Only do this in one file, otherwise the functions will have multiple definitions, resulting in a compiler error

src/integrated_ui.cpp
- Raylib-based UI that receives information from the ur_trajectory_comparator
- Displays the differences between the physical pose and digital pose in terms of cartesian and rotation error.
- Shows a dropdown of tolerance violations in the top-right, colored by severity. 

src/integrated_control_test.cpp
- Contains a sample control program for the system.
- You can use it as a reference for making your own. 
	- Note that the `#include ../include/integrated_ur_robotiq/integrated_control.hpp` line is a relative path include so it can compile in this workspace. It should be changed in yours.

src/synchronizer.cpp
- Runs a service called "/sychronize_joints", when called will take the current joint states of the physical robot and command URSim to go to those joint positions
	- Call the service in the terminal with `ros2 service call /synchronize_joints std_srvs/srv/Trigger {}`

src/ur_pose_monitor.cpp
- Receives joint states from the "joint_states" topic for the UR robot
- Uses forward kinematics to calculate the TCP pose for those joint values
- Publishes the TCP pose to the "ur_tool_pose" topic
- This node needs to be run with `ros2 launch ur_robotiq_moveit_config run.launch.py run:="integrated_ur_robotiq ur_pose_monitor [ns:=/namespace]"`
	- The moveit config contains information needed for forward kinematics

src/ur_trajectory_comparator.cpp
- Receives Poses from the physical and digital ur_pose_monitor and compares their error over time
- Applies latency compensation for up to 1 second of lag

src/ur_dashboard_terminal.py
- Script that allows for controlling the UR robot from the command line through the UR dashboard server
	- Mainly for system configuration (program loading, monitoring safety, etc.), not movement

src/ursim_init.py
- Script that uses the UR dashboard server to tell URSim to load and run the "External Control" program

src/ursim_play.py
- Script that uses the UR dashboard server to tell URSim to play the currently loaded program

src/ursim_stop.py
- Script that uses the UR dashboard server to tell URSim to stop the currently loaded program

launch/physical.launch.py
- Launches programs required to control the physical robot and gripper

launch/digital.launch.py
- Launches programs required to control URSim and the gripper simulator

launch/integrated.launch.py
- Launches programs for monitoring and controlling the physical and digital programs

launch/ur_control.launch.py
- Launches the ur_robot_driver

launch/ur_sim.launch.py
- Launches URSim

