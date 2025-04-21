#define INTEGRATED_CONTROL_IMPL
#include "../include/integrated_ur_robotiq/integrated_control.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace integrated_ur_robotiq;

static std::vector<double> &deg2rad(std::vector<double> &&v) {
    for (auto &val : v) {
        val *= M_PI/180.0;
    }
    return v;
}

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    std::shared_ptr<Context> ctx = std::make_shared<Context>("integrated_control_test");
    auto keepalive = ctx->start_spin_thread(ctx);
    
    ctx->gripper_activate();
    ctx->gripper_move(GRIPPER_CLOSE, 128, 0);
    ctx->gripper_move(GRIPPER_OPEN, 128, 0);
    ctx->movej(deg2rad({-270, -135, 90, 315, 90, 0}));
    ctx->movej(deg2rad({-270, -135, 135, 270, 90, 180}));
    Pose start_pose;
    start_pose.position.x = -0.1333;
    start_pose.position.y = 0.1914;
    start_pose.position.z = 0.5626;

    Pose end_pose = start_pose;
    end_pose.position.x = -0.1333;
    end_pose.position.y = 0.1914;
    end_pose.position.z = 0.8500;
    ctx->movel({start_pose, end_pose, start_pose});
    
    rclcpp::shutdown();
}