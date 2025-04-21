import os
from ament_index_python.packages import get_package_share_directory
import launch
import launch_ros
from launch.actions import IncludeLaunchDescription, GroupAction, DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros import actions

def generate_launch_description():
    # ur_type_arg = DeclareLaunchArgument("ur_type", default_value="ur5e")

    ur_sim_cmd = ExecuteProcess(
        # cmd=["ros2 run ur_client_library start_ursim.sh -m ", LaunchConfiguration("ur_type", default="ur5e")],
        cmd=["ros2 run ur_client_library start_ursim.sh"],
        name="ursim",
        shell=True,
        output="both",
    )

    ursim_init = ExecuteProcess(
        cmd=["ros2 run integrated_ur_robotiq ursim_init.py"],
        name="ursim_init",
        env=dict(os.environ),
        shell=True,
        emulate_tty=True,
        output="both",
    )

    return launch.LaunchDescription([
        ur_sim_cmd,
        ursim_init
    ])