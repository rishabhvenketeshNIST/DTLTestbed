import os
from ament_index_python.packages import get_package_share_directory
import launch
import launch_ros
from launch.actions import IncludeLaunchDescription, GroupAction, DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros import actions

def generate_launch_description():
    ur_type_arg = DeclareLaunchArgument("ur_type", default_value="ur5e")
    view = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('ur_description'), 'launch'), '/view_ur.launch.py']),
        launch_arguments={
            "ur_type": LaunchConfiguration("ur_type", default=ur_type_arg.default_value),
            "description_package": "ur_robotiq_description",
            "description_file": "ur_robotiq.urdf.xacro",
        }.items()
    )

    return launch.LaunchDescription([
        view
    ])