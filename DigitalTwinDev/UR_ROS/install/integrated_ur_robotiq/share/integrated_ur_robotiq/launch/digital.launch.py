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
    robot_ip_arg = DeclareLaunchArgument("robot_ip", default_value="192.168.56.101")
    ur_type_arg = DeclareLaunchArgument("ur_type", default_value="ur5e")
    # gripper_dt_arg = DeclareLaunchArgument("gripper_dt", default_value="0.01")
    gripper_joint_name_arg = DeclareLaunchArgument("gripper_joint_name", default_value="robotiq_85_left_knuckle_joint")
    # gripper_min_speed_arg = DeclareLaunchArgument("gripper_min_speed", default_value="")
    # gripper_max_speed_arg = DeclareLaunchArgument("gripper_max_speed", default_value="")

    ur_sim_driver = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('integrated_ur_robotiq'), 'launch'), '/ur_control.launch.py']),
        launch_arguments={
            "ur_type": LaunchConfiguration("ur_type", default=ur_type_arg.default_value),
            "robot_ip": LaunchConfiguration("robot_ip", default=robot_ip_arg.default_value),
            "launch_rviz": "False",
            "controllers_file": os.path.join(get_package_share_directory('integrated_ur_robotiq'), 'config', 'digital_controllers.yaml'),
            "reverse_port": "50011",
            "script_sender_port": "50012",
            "trajectory_port": "50013",
            "script_command_port": "50014",

        }.items()
    )

    gripper_vis = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('robotiq_gripper'), 'launch'), '/view_gripper.launch.py']),
        launch_arguments={
            "ns": "/digital"
        }.items()
    )
    
    start_ursim = ExecuteProcess(
        # cmd=["ros2 run ur_client_library start_ursim.sh -m ", LaunchConfiguration("ur_type", default="ur5e")],
        cmd=["ros2 run ur_client_library start_ursim.sh"],
        name="ursim",
        shell=True,
        output="both",
    )

    init_ursim = actions.Node(
        package="integrated_ur_robotiq",
        executable="ursim_init.py"
    )

    gripper_twin = actions.Node(
        package="robotiq_gripper",
        executable="gripper_twin",
        parameters=[{
            "joint_name": LaunchConfiguration("gripper_joint_name", default="robotiq_85_left_knuckle_joint"),
        }]
    )

    digital = GroupAction([
        actions.PushROSNamespace("digital"),
        ur_sim_driver,
        gripper_twin,
    ])

    # ursim_play = actions.Node(
    #     package="integrated_ur_robotiq",
    #     executable="ursim_play.py"
    # )

    # ursim_play_after_time = launch.actions.TimerAction(period=15.0, actions=[ursim_play])

    # ursim_stop = actions.Node(
    #     package="integrated_ur_robotiq",
    #     executable="ursim_stop.py"
    # )

    digital_after_ursim_init = RegisterEventHandler(
        OnProcessExit(
            target_action=init_ursim,
            on_exit=[
                digital,
                # ursim_play_after_time,
                gripper_vis
            ]
        )
    )

    # stop_on_exit = RegisterEventHandler(
    #     OnShutdown(on_shutdown=ursim_stop)
    # )

    return launch.LaunchDescription([
        robot_ip_arg,
        ur_type_arg,
        # gripper_dt_arg,
        gripper_joint_name_arg,
        # gripper_min_speed_arg,
        # gripper_max_speed_arg,
        start_ursim,
        init_ursim,
        digital_after_ursim_init,
        # play_after_driver_start,
        # stop_on_exit
    ])
