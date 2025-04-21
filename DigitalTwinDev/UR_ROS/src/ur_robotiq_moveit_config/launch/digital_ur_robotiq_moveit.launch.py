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
            "controllers_file": "digital_controllers.yaml",
            "kinematics_file": "digital_kinematics.yaml",
        }.items()
    )

    return launch.LaunchDescription([
        actions.PushROSNamespace("digital"),
        actions.SetRemap("/trajectory_execution_event", "/digital/trajectory_execution_event"),
        actions.SetRemap("/attached_collision_object", "/digital/attached_collision_object"),
        actions.SetRemap("/clicked_point", "/digital/clicked_point"),
        actions.SetRemap("/display_planned_path", "/digital/display_planned_path"),
        actions.SetRemap("/initialpose", "/digital/initialpose"),
        actions.SetRemap("/goal_pose", "/digital/goal_pose"),
        actions.SetRemap("/execute_trajectory", "/digital/execute_trajectory"),
        actions.SetRemap("/move_action", "/digital/move_action"),
        actions.SetRemap("/planning_scene", "/digital/planning_scene"),
        actions.SetRemap("/joint_states", "/digital/joint_states"),
        actions.SetRemap("/move_group", "/digital/move_group"),
        moveit
    ])
