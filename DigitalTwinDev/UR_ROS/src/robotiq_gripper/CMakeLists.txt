cmake_minimum_required(VERSION 3.8)
project(robotiq_gripper)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)
find_package(ur_rtde REQUIRED)
find_package(sensor_msgs REQUIRED)

# find_library(LIBMODBUS modbus)

rosidl_generate_interfaces(${PROJECT_NAME}
  msg/GripperStatus.msg
  msg/GripperCommand.msg
)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp
)

# add_executable(test_gripper src/test_gripper.cpp)
# target_compile_features(test_gripper PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
# target_link_libraries(test_gripper ${LIBMODBUS} "${cpp_typesupport_target}")
# ament_target_dependencies(test_gripper
#   rclcpp
# )

# add_executable(dummy_gripper src/dummy_gripper.cpp)
# target_link_libraries(dummy_gripper ${LIBMODBUS} "${cpp_typesupport_target}")

add_executable(rtde_control src/rtde_control.cpp)
ament_target_dependencies(rtde_control rclcpp sensor_msgs)
target_link_libraries(rtde_control rtde "${cpp_typesupport_target}")

add_executable(gripper_twin src/gripper_twin.cpp)
ament_target_dependencies(gripper_twin rclcpp sensor_msgs)
target_link_libraries(gripper_twin "${cpp_typesupport_target}")

install(TARGETS
  gripper_twin
  rtde_control
  DESTINATION lib/${PROJECT_NAME})

install(
  DIRECTORY include/
  DESTINATION include
)

install(DIRECTORY
  launch rviz
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
