#ifndef INTEGRATED_CONTROL_HPP
#define INTEGRATED_CONTROL_HPP

#include <vector>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/trigger.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "robotiq_gripper/msg/gripper_command.hpp"
#include "robotiq_gripper/msg/gripper_status.hpp"
#include "moveit/move_group_interface/move_group_interface.h"
#include "moveit/planning_interface/planning_interface.h"

static inline robotiq_gripper::msg::GripperCommand g_activate() {
    robotiq_gripper::msg::GripperCommand cmd;
    cmd.act = 1;
    return cmd;
}

static inline robotiq_gripper::msg::GripperCommand g_go_to(uint8_t pos, uint8_t speed=255, uint8_t force=0) {
    robotiq_gripper::msg::GripperCommand cmd;
    cmd.act = 1;
    cmd.gto = 1;
    cmd.pr = pos;
    cmd.sp = speed;
    cmd.fr = force;
    return cmd;
}

static inline robotiq_gripper::msg::GripperCommand g_emove(uint8_t open) {
    robotiq_gripper::msg::GripperCommand cmd;
    cmd.atr = 1;
    cmd.ard = (open != 0);
    return cmd;
}

namespace integrated_ur_robotiq {

constexpr uint8_t GRIPPER_OPEN = 0;
constexpr uint8_t GRIPPER_CLOSE = 255;

std::string generate_urscript_joint_trajectory(const trajectory_msgs::msg::JointTrajectory &trajectory, double* final_time = nullptr);

class Context : public rclcpp::Node {
public:
    Context(const std::string &name, const rclcpp::NodeOptions options = rclcpp::NodeOptions());

    std::pair<std::shared_ptr<rclcpp::Executor>, std::thread> start_spin_thread(Context::SharedPtr ctx);

    bool plan_movej(std::vector<double> &q, moveit_msgs::msg::RobotTrajectory &t);

    bool plan_movel(const std::vector<geometry_msgs::msg::Pose> &waypoints, moveit_msgs::msg::RobotTrajectory &t);

    bool movej(std::vector<double> q);

    bool movel(geometry_msgs::msg::Pose waypoint);

    bool movel(const std::vector<geometry_msgs::msg::Pose> &waypoints);

    bool gripper_activate(bool async = false);

    bool gripper_move(uint8_t close_amt, uint8_t speed, uint8_t force, bool async = false);

    bool gripper_emergency_move(bool should_close, bool async = false);

    inline void init_move_group(Context::SharedPtr ctx) {
        this_shared = ctx;
        if (!move_group) {
            move_group = std::make_unique<moveit::planning_interface::MoveGroupInterface>(ctx, move_group_name);
            move_group->startStateMonitor();
        }
    }

    void execute_trajectory(const moveit_msgs::msg::RobotTrajectory &t);

private:
    Context::SharedPtr this_shared;
    std::mutex lock;
    std::string move_group_name;
    std::unique_ptr<moveit::planning_interface::MoveGroupInterface> move_group;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr urscript_pub;
    rclcpp::Publisher<robotiq_gripper::msg::GripperCommand>::SharedPtr gripper_pub;
    rclcpp::Subscription<robotiq_gripper::msg::GripperStatus>::SharedPtr gripper_sub;
    // rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr ur_dashboard_player;
    robotiq_gripper::msg::GripperStatus gripper_status;
};


}

#endif

#ifdef INTEGRATED_CONTROL_IMPL

namespace integrated_ur_robotiq
{

using std_srvs::srv::Trigger;
using geometry_msgs::msg::Pose;
using trajectory_msgs::msg::JointTrajectory;
using robotiq_gripper::msg::GripperCommand;
using robotiq_gripper::msg::GripperStatus;
using moveit_msgs::msg::RobotTrajectory;

std::string generate_urscript_joint_trajectory(const JointTrajectory &trajectory, double* final_time) {
    const std::string names[6] = {
        "shoulder_pan_joint",
        "shoulder_lift_joint",
        "elbow_joint",
        "wrist_1_joint",
        "wrist_2_joint",
        "wrist_3_joint",
    };
    // idx maps from urscript index to trajectory index:
    // names[i] should equal trajectory.joint_names[idx[i]]
    std::array<size_t, 6> idx = {0};
    for(size_t i = 0; i < idx.size(); i++) {
        size_t j = 0;
        for(; j < 6; j++) {
            if (names[i] == trajectory.joint_names.at(j)) break;
        }
        idx.at(i) = j;
    }
    
    std::stringstream ss;
    ss << std::setprecision(12);
    ss << "def follow_trajectory():\n";
    double prev_time = 0;
    for(size_t i = 0; i < trajectory.points.size(); i++) {
        const auto &pt = trajectory.points.at(i);
        double cur_time = pt.time_from_start.sec + 0.000000001*pt.time_from_start.nanosec;
        double dt = cur_time - prev_time;
        const auto &q = pt.positions;
        
        if (i == 0) {
            // First move
            ss << "    movej(["<<q.at(idx[0])<<", "<<q.at(idx[1])<<", "<<q.at(idx[2])<<", "<<q.at(idx[3])<<", "<<q.at(idx[4])<<", "<<q.at(idx[5])<<"], a=5, v=5, r=0)\n";
        } else if (i == (trajectory.points.size() - 1)) {
            // Last move
            ss << "    movej(["<<q.at(idx[0])<<", "<<q.at(idx[1])<<", "<<q.at(idx[2])<<", "<<q.at(idx[3])<<", "<<q.at(idx[4])<<", "<<q.at(idx[5])<<"], t="<<dt<<")\n";
        } else {
            // Path move
            ss << "    movej(["<<q.at(idx[0])<<", "<<q.at(idx[1])<<", "<<q.at(idx[2])<<", "<<q.at(idx[3])<<", "<<q.at(idx[4])<<", "<<q.at(idx[5])<<"], t="<<dt<<", r=0.001)\n";
        }

        prev_time = cur_time;
    }
    ss<<"end";
    if (final_time != nullptr) {
        *final_time = prev_time;
    }

    return ss.str();
}

// blocks but waits longer between successive evaluations of the condition
static bool block_until(std::function<bool(void)> condition, int64_t timeout_ms = 30000) {
    int64_t time_ms = 1;
    std::chrono::time_point<std::chrono::steady_clock> start_time = std::chrono::steady_clock::now();

    while (true) {
        if (condition()) return true;
        std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
        // time_ms *= 2;
        std::chrono::time_point<std::chrono::steady_clock> cur_time = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - start_time);
        if (elapsed_ms.count() > timeout_ms) return false;
    }
}

Context::Context(const std::string &name, const rclcpp::NodeOptions options) : Node(name, options), lock() {
    std::string exec_ns = declare_parameter("exec_ns", "/digital");
    if (exec_ns.size() > 0 && exec_ns.at(exec_ns.size()-1) != '/') {
        exec_ns.push_back('/');
    }
    std::string urscript_topic = exec_ns;
    urscript_topic.append("urscript_interface/script_command");
    std::string ur_dashboard_play = exec_ns;
    ur_dashboard_play.append("dashboard_client/play");
    move_group_name = declare_parameter("move_group_name", "ur_manipulator");
    urscript_pub = create_publisher<std_msgs::msg::String>(urscript_topic, 10);
    gripper_pub = create_publisher<GripperCommand>("/robotiq_gripper_cmd", 10);
    gripper_sub = create_subscription<GripperStatus>("gripper_state", 10, [this](const GripperStatus::SharedPtr status){
        auto guard = std::lock_guard(lock);
        gripper_status = *status;
    });
    // ur_dashboard_player = create_client<std_srvs::srv::Trigger>(ur_dashboard_play, 10);
}

std::pair<std::shared_ptr<rclcpp::Executor>, std::thread> Context::start_spin_thread(Context::SharedPtr ctx) {
    init_move_group(ctx);
    // unique ptr will destroy the executor when the thread is interrupted due to leaving scope;
    auto exec = std::make_shared<rclcpp::executors::MultiThreadedExecutor>();
    exec->add_node(ctx);
    return {exec, std::thread([exec](){
        exec->spin();
    })};
}

bool Context::plan_movej(std::vector<double> &q, moveit_msgs::msg::RobotTrajectory &t) {
    if (move_group == nullptr) {
        RCLCPP_ERROR(get_logger(), "Context was not initialized! Call .init_move_group() or .start_spin_thread()!");
    }
    if (q.size() != 6) {
        RCLCPP_ERROR(get_logger(), "Joint target has wrong number of targets. Want 6, got %ld", (long) q.size());
        return false;
    }
    move_group->setReplanAttempts(10);
    move_group->allowReplanning(true);
    move_group->setPlanningTime(30.0);
    move_group->setGoalPositionTolerance(0.0001);
    move_group->setGoalOrientationTolerance(0.001);
    move_group->setGoalJointTolerance(0.001);
    moveit::planning_interface::MoveGroupInterface::Plan joint_plan;
    printf("MoveJ target: {");
    for (auto &j : q) {
        printf("%.2f, ", j);
    }
    printf("}\n");
    bool valid_target = move_group->setJointValueTarget(q);
    
    if (!valid_target) {
        RCLCPP_ERROR(get_logger(), "Invalid joint targets: [%.2f, %.2f, %.2f, %.2f, %.2f, %.2f]", q[0], q[1], q[2], q[3], q[4], q[5]);
        return false;
    };
    auto plan_err = move_group->plan(joint_plan);
    if (plan_err != plan_err.SUCCESS) {
        RCLCPP_ERROR(get_logger(), "Failed to plan movej: %s\n", moveit::core::error_code_to_string(plan_err).c_str());
        return false;
    }
    t = joint_plan.trajectory;
    return true;
}

bool Context::plan_movel(const std::vector<Pose> &waypoints, moveit_msgs::msg::RobotTrajectory &t) {
    if (move_group == nullptr) {
        RCLCPP_ERROR(get_logger(), "Context was not initialized! Call .init_move_group() or .start_spin_thread()!");
    }
    if (waypoints.size() == 0) {
        RCLCPP_ERROR(get_logger(), "Need at least one waypoint for movel");
        return false;
    }
    move_group->setReplanAttempts(10);
    move_group->allowReplanning(true);
    move_group->setPlanningTime(30.0);
    move_group->setGoalPositionTolerance(0.0001);
    move_group->setGoalOrientationTolerance(0.001);
    move_group->setGoalJointTolerance(0.001);
    move_group->setPoseReferenceFrame("world");

    move_group->setStartStateToCurrentState();
    double progress = move_group->computeCartesianPath(waypoints, 0.0001, 5.0, t);
    if (progress < 0.0) {
        RCLCPP_ERROR(get_logger(), "Failed to compute cartesian path for movel.");
    } else {
        RCLCPP_INFO(get_logger(), "Planned %.2f%% of linear path\n", progress*100);
    }
    return progress == 1.0;
}

void Context::execute_trajectory(const moveit_msgs::msg::RobotTrajectory &trajectory) {
    
    std_msgs::msg::String urscript_msg;
    double trajectory_time = 0;
    urscript_msg.data = generate_urscript_joint_trajectory(trajectory.joint_trajectory, &trajectory_time);
    RCLCPP_INFO(get_logger(), "Executing trajectory with %ld frames for %fs", trajectory.joint_trajectory.points.size(), trajectory_time);

    urscript_pub->publish(urscript_msg);
    // std::chrono::time_point<std::chrono::steady_clock> start_time = std::chrono::steady_clock::now();
    move_group->execute(trajectory);
    // std::chrono::time_point<std::chrono::steady_clock> stop_time = std::chrono::steady_clock::now();
    // auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time);
    // trajectory_time *= 1e9; // convert seconds to nanoseconds
    // std::chrono::nanoseconds target_ns = std::chrono::nanoseconds((int64_t)trajectory_time);
    
    // if (target_ns > elapsed_ns) {
    // std::this_thread::sleep_for(target_ns - elapsed_ns);
    // //std::this_thread::sleep_for(target_ns);
    // }
}

bool Context::movej(std::vector<double> q) {
    RobotTrajectory trajectory;
    bool plan_success = plan_movej(q, trajectory);
    if (!plan_success) return false;
    execute_trajectory(trajectory);
    return true;
}

bool Context::movel(geometry_msgs::msg::Pose waypoint) {
    std::vector<geometry_msgs::msg::Pose> pts = {waypoint};
    return movel(pts);
}

bool Context::movel(const std::vector<geometry_msgs::msg::Pose> &waypoints) {
    RobotTrajectory trajectory;
    bool plan_success = plan_movel(waypoints, trajectory);
    if (!plan_success) return false;
    execute_trajectory(trajectory);
    return true;
}

bool Context::gripper_activate(bool async) {
    auto msg = g_activate();
    gripper_pub->publish(msg);
    if (!async) {
        return block_until([this](){
            auto guard = std::lock_guard(lock);
            return gripper_status.sta == 3;
        }, 2000);
    }
    return true;
}

bool Context::gripper_move(uint8_t pos, uint8_t speed, uint8_t force, bool async) {
    auto msg = g_go_to(pos, speed, force);
    gripper_pub->publish(msg);
    if (!async) {
        return block_until([this, pos](){
            auto guard = std::lock_guard(lock);
            return abs(gripper_status.po - pos) <= 6; // 3 ticks is about 1 mm of travel, so this waits until we are within 2 mm of target
        }, 2000);
    }
    return true;
}

bool Context::gripper_emergency_move(bool should_close, bool async) {
    auto guard = std::lock_guard(lock);
    auto msg = g_emove(!should_close);
    gripper_pub->publish(msg);
    if (!async) {
        return block_until([this](){
            auto guard = std::lock_guard(lock);
            return gripper_status.act == 0;
        }, 2000);
    }
    return true;
}

}

#endif