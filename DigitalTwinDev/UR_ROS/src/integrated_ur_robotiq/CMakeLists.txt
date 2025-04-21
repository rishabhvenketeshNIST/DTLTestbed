cmake_minimum_required(VERSION 3.8)
project(integrated_ur_robotiq)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(trajectory_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(robotiq_gripper REQUIRED)
find_package(moveit_msgs REQUIRED)
find_package(moveit_ros_planning REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(moveit_core REQUIRED)
find_library(libraylib raylib REQUIRED)

# Install headers
install(
  DIRECTORY include/
  DESTINATION include
)

# Install scripts
install(FILES
  src/ursim_init.py
  src/ur_dashboard_terminal.py
  src/ursim_play.py
  src/ursim_stop.py
  DESTINATION lib/${PROJECT_NAME}/
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

add_executable(synchronizer src/synchronizer.cpp)
ament_target_dependencies(synchronizer rclcpp std_srvs sensor_msgs trajectory_msgs)

add_executable(ur_pose_monitor src/ur_pose_monitor.cpp)
ament_target_dependencies(ur_pose_monitor rclcpp sensor_msgs geometry_msgs moveit_msgs moveit_ros_planning moveit_ros_planning_interface moveit_core)

add_executable(ur_trajectory_comparator src/ur_trajectory_comparator.cpp)
ament_target_dependencies(ur_trajectory_comparator rclcpp std_msgs geometry_msgs)

add_executable(integrated_ui src/integrated_ui.cpp)
ament_target_dependencies(integrated_ui rclcpp std_msgs geometry_msgs sensor_msgs)
target_link_libraries(integrated_ui ${libraylib})

add_executable(integrated_control_test src/integrated_control_test.cpp)
target_include_directories(integrated_control_test PRIVATE include)
ament_target_dependencies(integrated_control_test rclcpp std_msgs std_srvs sensor_msgs trajectory_msgs robotiq_gripper moveit_msgs moveit_ros_planning moveit_ros_planning_interface moveit_core)


install(TARGETS
synchronizer
ur_pose_monitor
ur_trajectory_comparator
integrated_ui
integrated_control_test
  DESTINATION lib/${PROJECT_NAME})

# Install shared files
install(DIRECTORY
  launch config
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
