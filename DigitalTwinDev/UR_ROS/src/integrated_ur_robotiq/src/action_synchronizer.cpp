// THIS CODE DOES NOT WORK (CURRENTLY)
// FILE ONLY HERE AS REFERENCE
// This node synchronizes the physical and digital versions of the robot arm and gripper

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <stdint.h>

#include "sensor_msgs/msg/joint_state.hpp"
#include "trajectory_msgs/msg/joint_trajectory.hpp"
#include "control_msgs/action/follow_joint_trajectory.hpp"
#include "control_msgs/msg/joint_trajectory_controller_state.hpp"
#include "control_msgs/srv/query_trajectory_state.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

using namespace std::chrono_literals;

class Synchronizer : public rclcpp::Node {
public:

    Synchronizer(const std::string &node_name) : Node(node_name) {
        source = declare_parameter<std::string>("src", "");
        dest = declare_parameter<std::string>("dest", "");

        action = rclcpp_action::create_server<control_msgs::action::FollowJointTrajectory>(
            this, "follow_joint_trajectory",
            [this](auto uuid, auto goal){ return handle_goal(uuid, goal); },
            [this](auto handle){ return handle_cancel(handle); },
            [this](auto handle){ handle_accepted(handle); }
        );
    }

private:
    rclcpp_action::GoalResponse handle_goal(
        const rclcpp_action::GoalUUID &uuid,
        std::shared_ptr<const control_msgs::action::FollowJointTrajectory::Goal> goal
    ) {
        (void)uuid;
        (void)goal;
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    rclcpp_action::CancelResponse handle_cancel(
        const std::shared_ptr<rclcpp_action::ServerGoalHandle<control_msgs::action::FollowJointTrajectory>> goal_handle
    ) {
        (void)goal_handle;
        src_action->async_cancel_all_goals();
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    void handle_accepted(
        const std::shared_ptr<rclcpp_action::ServerGoalHandle<control_msgs::action::FollowJointTrajectory>> goal_handle
    ) {
        auto send_goal_options = rclcpp_action::Client<control_msgs::action::FollowJointTrajectory>::SendGoalOptions();
        send_goal_options.goal_response_callback = [this, goal_handle](
            const rclcpp_action::ClientGoalHandle<control_msgs::action::FollowJointTrajectory>::SharedPtr &client_goal_handle
        ){
            if(!client_goal_handle) {
                auto result = std::make_shared<control_msgs::action::FollowJointTrajectory_Result>();
                result->error_code = result->INVALID_GOAL;
                result->error_string = "invalid goal";
                goal_handle->abort(result);
            }
        };
        send_goal_options.feedback_callback = [this, goal_handle](
            auto handle, const std::shared_ptr<const control_msgs::action::FollowJointTrajectory::Feedback> feedback
        ){
            (void) handle;
            auto to_send = std::make_shared<control_msgs::action::FollowJointTrajectory::Feedback>();
            *to_send = *feedback;
            goal_handle->publish_feedback(to_send);
        };
        send_goal_options.result_callback = [this, goal_handle](
            const rclcpp_action::ClientGoalHandle<control_msgs::action::FollowJointTrajectory>::WrappedResult &result
        ){
            switch(result.code) {
            case rclcpp_action::ResultCode::SUCCEEDED:
                goal_handle->succeed(result.result);
                break;
            case rclcpp_action::ResultCode::ABORTED:
                goal_handle->abort(result.result);
                break;
            case rclcpp_action::ResultCode::CANCELED:
                goal_handle->canceled(result.result);
                break;
            case rclcpp_action::ResultCode::UNKNOWN:
                goal_handle->abort(result.result);
                break;
            }
        };
        src_action->async_send_goal(*(goal_handle->get_goal()));
    }

    std::string source, dest;
    
    // Control receive
    rclcpp_action::Server<control_msgs::action::FollowJointTrajectory>::SharedPtr action;
    rclcpp::Subscription<trajectory_msgs::msg::JointTrajectory>::SharedPtr topic;
    // Control send
    rclcpp_action::Client<control_msgs::action::FollowJointTrajectory>::SharedPtr src_action, dest_action;
    rclcpp::Publisher<trajectory_msgs::msg::JointTrajectory>::SharedPtr src_topic, dest_topic;
    // State receive

    // State send
    rclcpp::Publisher<control_msgs::msg::JointTrajectoryControllerState>::SharedPtr state_pub;
    rclcpp::Service<control_msgs::srv::QueryTrajectoryState>::SharedPtr state_service;
};

int main(int argc, const char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Synchronizer>("synchronizer");
    rclcpp::spin(node);
    rclcpp::shutdown();
}