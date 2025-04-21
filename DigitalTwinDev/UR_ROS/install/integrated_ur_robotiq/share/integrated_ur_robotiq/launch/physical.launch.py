import os
from ament_index_python.packages import get_package_share_directory
import launch
import launch.event_handlers
import launch_ros
from launch.actions import IncludeLaunchDescription, GroupAction, DeclareLaunchArgument, ExecuteProcess, RegisterEventHandler
from launch.substitutions import LaunchConfiguration
from launch.event_handlers import OnProcessExit, OnExecutionComplete, OnShutdown
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros import actions

def generate_launch_description():

    robot_ip_arg = DeclareLaunchArgument("robot_ip")
    ur_type_arg = DeclareLaunchArgument("ur_type", default_value="ur5e")

    ur_robot_driver = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('integrated_ur_robotiq'), 'launch'), '/ur_control.launch.py']),
        launch_arguments={
            "ur_type": LaunchConfiguration("ur_type", default=ur_type_arg.default_value),
            "robot_ip": LaunchConfiguration("robot_ip"),
            "launch_rviz": "False",
            # "controllers_file": os.path.join(get_package_share_directory('integrated_ur_robotiq'), 'config', 'physical_controllers.yaml'),
        }.items()
    )

    ur_moveit = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('ur_robotiq_moveit_config'), 'launch'), '/ur_robotiq_moveit.launch.py']),
        launch_arguments={
            # "controllers_file": os.path.join(get_package_share_directory('integrated_ur_robotiq'), 'config', 'digital_controllers.yaml'),
        }.items()
    )

    gripper_control = actions.Node(
        package="robotiq_gripper",
        executable="rtde_control",
        parameters=[{
            "ip": LaunchConfiguration("robot_ip"),
            "joint_name": "robotiq_85_left_knuckle_joint"
        }]
    )

    

    physical = GroupAction([
        # actions.PushROSNamespace("physical"),
        # launch_ros.actions.set_remap.SetRemap("scaled_joint_trajectory_controller:__ns", "/physical"),
        ur_robot_driver,
        gripper_control,
        # ur_moveit,
    ])

    return launch.LaunchDescription([
        robot_ip_arg,
        ur_type_arg,
        physical,
    ])