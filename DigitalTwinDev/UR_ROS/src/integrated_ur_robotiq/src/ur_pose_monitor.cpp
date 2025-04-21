/**
 * Run with ur_robotiq_moveit_config:
 * ros2 launch ur_robotiq_moveit_config run.launch.py run:="integrated_ur_robotiq ur_pose_monitor src_ns:=/"
 * ros2 launch ur_robotiq_moveit_config run.launch.py run:="integrated_ur_robotiq ur_pose_monitor src_ns:=/digital"
 */

#include <ranges>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "moveit/move_group_interface/move_group_interface.h"
#include "urdf_parser/urdf_parser.h"

using sensor_msgs::msg::JointState;
using geometry_msgs::msg::Pose;
using geometry_msgs::msg::PoseStamped;

template<class T>
static size_t index_of(const std::vector<T> &v, const T& val) {
    for (size_t i = 0; i < v.size(); i++)
    {
        if (val == v.at(i)) {
            return i;
        }
    }
    return -1;
}

class PoseMonitor : public rclcpp::Node {
public:

    PoseMonitor(const rclcpp::NodeOptions options = rclcpp::NodeOptions()) : Node("ur_pose_monitor", options) {
        std::string ns = declare_parameter("src_ns", "/");
        if (ns.size() > 0 && ns.at(ns.size()-1) != '/') {
            ns.push_back('/');
        }
        RCLCPP_INFO(get_logger(), "source namespace := %s", ns.c_str());
        
        double hz = declare_parameter("hz", 100);
        assert(hz > 0);
        int64_t us = (int64_t)(1000000.0/hz);
        urdf_content = declare_parameter("robot_description", rclcpp::ParameterType::PARAMETER_STRING).get<std::string>();
        srdf_content = declare_parameter("robot_description_semantic", rclcpp::ParameterType::PARAMETER_STRING).get<std::string>();
        auto urdf_model = urdf::parseURDF(urdf_content);
        auto srdf_model = std::make_shared<srdf::Model>();
        srdf_model->initString(*urdf_model, srdf_content);
        robot_model = std::make_shared<moveit::core::RobotModel>(urdf_model, srdf_model);
        joint_names = robot_model->getJointModelNames();
        joint_angles.assign(joint_names.size(), 0.0);
        
        std::string monitored_pose_topic = ns+std::string("ur_tool_pose");
        std::string joint_states_topic = ns+std::string("joint_states");
        pose_pub = create_publisher<PoseStamped>(monitored_pose_topic, 10);
        joint_sub = create_subscription<JointState>(joint_states_topic, 10, [this](const JointState &js){
            update_joint_angles(js);
        });
        
        pub_timer = create_timer(std::chrono::microseconds(us), [this](){
            publish_pose();
        });

        RCLCPP_INFO(get_logger(),
            "Listening for joint states on: %s, Publishing Pose to: %s at %.2f hz",
            joint_states_topic.c_str(), monitored_pose_topic.c_str(), hz
        );
    }

private:
    std::string urdf_content;
    std::string srdf_content;
    moveit::core::RobotModelConstPtr robot_model;
    std::vector<std::string> joint_names;
    rclcpp::Publisher<PoseStamped>::SharedPtr pose_pub;
    rclcpp::TimerBase::SharedPtr pub_timer;
    rclcpp::Subscription<JointState>::SharedPtr joint_sub;
    // thread safe members
    std::mutex lock;
    std::vector<double> joint_angles;
    
    void update_joint_angles(const JointState &js) {
        auto guard = std::lock_guard(lock);
        for (size_t i = 0; i < js.name.size(); i++) {
            auto &name = js.name.at(i);
            size_t j = index_of(joint_names, name);
            if (j < joint_names.size()) {
                joint_angles.at(j) = js.position.at(i);
            }
        }
    } // end update_joint_angles

    void publish_pose() {
        auto guard = std::lock_guard(lock);
        moveit::core::RobotStatePtr state(new moveit::core::RobotState(robot_model));
        state->setToDefaultValues();
        // auto jmg = state->getJointModelGroup(move_group_name);
        // state->setJointGroupPositions(jmg, joint_angles);
        if (joint_names.size() != joint_angles.size()) {
            return;
        }
        for (size_t i = 0; i < joint_names.size(); i++) {
            auto &name = joint_names.at(i);
            const double *position = &joint_angles.at(i);
            state->setJointPositions(name, position);
        }
        // RCLCPP_INFO(get_logger(), "Read joints:\n%s: %.2f\n%s: %.2f\n%s: %.2f\n%s: %.2f\n%s: %.2f\n%s: %.2f\n",
        //     "shoulder_pan_joint", *state->getJointPositions("shoulder_pan_joint"),
        //     "shoulder_lift_joint", *state->getJointPositions("shoulder_lift_joint"),
        //     "elbow_joint", *state->getJointPositions("elbow_joint"),
        //     "wrist_1_joint", *state->getJointPositions("wrist_1_joint"),
        //     "wrist_2_joint", *state->getJointPositions("wrist_2_joint"),
        //     "wrist_3_joint", *state->getJointPositions("wrist_3_joint")
        // );
        
        // Find a link that ends with name "tool0", to account for prefixes in the URDF.
        const std::string tool0_literal = "tool0";
        std::string tool0_name = tool0_literal;
        auto link_names = robot_model->getLinkModelNames();
        for (auto &name : link_names) {
            if (name.size() >= tool0_literal.size() && name.compare(name.size()-tool0_literal.size(), tool0_literal.size(), tool0_literal) == 0) {
                tool0_name = name;
                break;
            }
        }
        auto &xform = state->getGlobalLinkTransform(tool0_name);
        
        auto pos = xform.translation();
        auto rot = Eigen::Quaternion<double>(xform.rotation());
        PoseStamped pose_stamped;
        Pose &pose = pose_stamped.pose;
        pose.position.x = pos.x();
        pose.position.y = pos.y();
        pose.position.z = pos.z();
        pose.orientation.x = rot.x();
        pose.orientation.y = rot.y();
        pose.orientation.z = rot.z();
        pose.orientation.w = rot.w();
        pose_stamped.header.stamp = get_clock()->now();
        pose_pub->publish(pose_stamped);
        // RCLCPP_INFO(get_logger(), "Pos: {%.5f %.5f %.5f} Rot: {%.3f %.3f %.3f %.3f}", pos.x(), pos.y(), pos.z(), rot.x(), rot.y(), rot.z(), rot.w());
    } // end publish_pose
}; // end class PoseMonitor

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto options = rclcpp::NodeOptions();
    options.allow_undeclared_parameters(true);
    auto node = std::make_shared<PoseMonitor>(options);
    rclcpp::spin(node);
    rclcpp::shutdown();
}