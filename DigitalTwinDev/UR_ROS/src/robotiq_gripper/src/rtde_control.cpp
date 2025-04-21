#include <ur_rtde/robotiq_gripper.h>
#include "rclcpp/rclcpp.hpp"
#include "robotiq_gripper/msg/gripper_status.hpp"
#include "robotiq_gripper/msg/gripper_command.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

static void check_param(const char *prefix, const char *entry, std::function<void(const char *, size_t)> apply_fun) {
  size_t prefix_len = strlen(prefix);
  if (strncmp(entry, prefix, prefix_len) == 0) {
    size_t entry_len = strlen(entry);
    if (entry_len > prefix_len) {
      apply_fun(entry + prefix_len, entry_len - prefix_len);
    }
  }
}

int main(int argc, const char *argv[]) {
  std::string addr = "127.0.0.1";
  std::vector<int> client_fds;
  for (int i = 1; i < argc; i++) {
    check_param("ip:=", argv[i], [&addr](const char *s, size_t len) {
      (void)len;
      addr = s;
    });
  }

  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("robotiq_rtde_control");
  node->declare_parameter("ip", addr);
  node->declare_parameter("dt", 0.01);
  node->declare_parameter("joint_name", "");
  std::string joint_name = node->get_parameter("joint_name").as_string();
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_pub;
  addr = node->get_parameter_or("ip", addr);
  auto period = std::chrono::milliseconds((unsigned long)(node->get_parameter("dt").as_double()*1000));

  ur_rtde::RobotiqGripper gripper(addr, 63352, true);
  printf("Connecting to gripper\n");
  while (true) {
    try {
      gripper.connect();
      break;
    } catch(std::runtime_error &e) {
      printf("Error connecting to gripper: %s\nRetrying...\n", e.what());
      exit(1);
    }
  }
  
  /*
  uint8 act # Activate (0 or 1)
  uint8 gto # Go to (0 or 1)
  uint8 atr # Automatic release (0 or 1)
  uint8 ard # Auto release direction (0 = closing, 1 = opening)
  uint8 pr # Position request (0-255) (0=open, 255=close)
  uint8 sp # Speed request (0-255) (0=slowest, 255=fastest)
  uint8 fr # Force request (0-255) (0=fragile mode, 1=weakest, 255=strongest)
  */
  auto cmd_callback = [&gripper](const robotiq_gripper::msg::GripperCommand::SharedPtr cmd){
    std::vector<std::pair<std::string, int>> vars = {
      {"GTO", cmd->gto},
      {"ATR", cmd->atr},
      {"ARD", cmd->ard},
      {"FOR", cmd->fr},
      {"SPE", cmd->sp},
      {"POS", cmd->pr},
    };
    if (cmd->act && !cmd->gto && !cmd->atr) {
      vars.push_back({"ACT", cmd->act});
    }
    bool success = gripper.setVars(vars);
    if(!success) {
      printf("Gripper command failed\n");
    }
  };
  
  auto qos_in = rclcpp::ServicesQoS();
  auto sub = node->create_subscription<robotiq_gripper::msg::GripperCommand>("/robotiq_gripper_cmd", qos_in, cmd_callback);
  auto qos_out = rclcpp::SystemDefaultsQoS();
  auto pub = node->create_publisher<robotiq_gripper::msg::GripperStatus>("gripper_state", qos_out);
  if (joint_name.size() > 0) {
    joint_pub = node->create_publisher<sensor_msgs::msg::JointState>("joint_states", qos_out);
    printf("Publishing joint state with joint name: %s\n", joint_name.c_str());
  }
  
  auto pub_timer = node->create_timer(period, [&](){
    static uint8_t prev_po = 0;
    // Send gripper state
    robotiq_gripper::msg::GripperStatus status;
    const std::vector<std::string> varnames = {
      "ACT",
      "GTO",
      "STA",
      "OBJ",
      "FLT",
      "PRE",
      "POS",
    };
    auto res = gripper.getVars(varnames);
    status.act = res[0];
    status.gto = res[1];
    status.sta = res[2];
    status.obj = res[3];
    status.flt = res[4];
    status.pr = res[5];
    status.po = res[6];
    pub->publish(status);

    uint8_t delta_po = status.po - prev_po;
    prev_po = status.po;
    float velocity = (float) delta_po/(period.count()*0.001f);

    if (joint_pub != nullptr) {
      sensor_msgs::msg::JointState j;
      j.header.stamp = node->get_clock()->now();
      j.name.push_back(joint_name);
      float rads_per_unit = 0.7929f/255.0f;
      float joint_pos = status.po*rads_per_unit; // rad
      float joint_vel = velocity*rads_per_unit; // rad/s
      j.position.push_back(joint_pos);
      j.velocity.push_back(joint_vel);
      joint_pub->publish(j);
    }
  });

  rclcpp::spin(node); // blocks until program is brutally assassinated by the operating system
  rclcpp::shutdown(nullptr);
  
  printf("Disconnecting from gripper\n");
  gripper.disconnect();
}