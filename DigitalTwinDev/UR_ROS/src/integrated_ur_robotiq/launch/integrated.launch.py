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
    # digital = IncludeLaunchDescription([os.path.join(get_package_share_directory('integrated_ur_robotiq'), 'launch'), '/digital.launch.py'])
    # physical = IncludeLaunchDescription([os.path.join(get_package_share_directory('integrated_ur_robotiq'), 'launch'), '/physical.launch.py'])
    
    physical_pose_monitor = IncludeLaunchDescription(
        [os.path.join(get_package_share_directory('ur_robotiq_moveit_config'), 'launch'), '/run.launch.py'],
        launch_arguments={
            "run": "integrated_ur_robotiq ur_pose_monitor"
        }.items()
    )

    digital_pose_monitor = IncludeLaunchDescription(
        [os.path.join(get_package_share_directory('ur_robotiq_moveit_config'), 'launch'), '/run.launch.py'],
        launch_arguments={
            "run": "integrated_ur_robotiq ur_pose_monitor src_ns:=/digital"
        }.items()
    )

    comparator = actions.Node(
        package="integrated_ur_robotiq",
        executable="ur_trajectory_comparator",
    )
    
    ui = actions.Node(
        package="integrated_ur_robotiq",
        executable="integrated_ui",
    )

    return launch.LaunchDescription([
        physical_pose_monitor,
        digital_pose_monitor,
        comparator,
        ui,
    ])