import os
from ament_index_python.packages import get_package_share_directory
import launch
import launch_ros
from launch.actions import IncludeLaunchDescription, GroupAction, DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros import actions

def generate_launch_description():
    moveit = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('ur_moveit_config'), 'launch'), '/ur_moveit.launch.py']),
        launch_arguments={
            "ur_type": LaunchConfiguration("ur_type", default="ur5e"),
            "description_package": "ur_robotiq_description",
            "description_file": "ur_robotiq.urdf.xacro",
            "moveit_config_package": "ur_robotiq_moveit_config",
            "moveit_config_file": "ur_robotiq.srdf.xacro",
        }.items()
    )

    return launch.LaunchDescription([
        moveit
    ])
