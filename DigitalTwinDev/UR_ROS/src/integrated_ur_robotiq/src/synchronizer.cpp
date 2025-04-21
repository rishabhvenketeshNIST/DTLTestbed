#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "trajectory_msgs/msg/joint_trajectory_point.hpp"
#include "trajectory_msgs/msg/joint_trajectory.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/trigger.hpp"

using sensor_msgs::msg::JointState;
using trajectory_msgs::msg::JointTrajectory;
using trajectory_msgs::msg::JointTrajectoryPoint;
using std_srvs::srv::Trigger;

class Synchronizer : public rclcpp::Node {
public:
    Synchronizer(const std::string &name, rclcpp::NodeOptions options = rclcpp::NodeOptions()) : Node(name, options), state_lock() {
        src_name = declare_parameter("src", "/joint_states");
        dst_topic = declare_parameter("urscript_topic", "/digital/urscript_interface/script_command");

        src_sub = create_subscription<JointState>(src_name, 10, [this](const JointState::SharedPtr msg){
            std::lock_guard<std::mutex> lock(state_lock);
            if (msg->name.size() == 6) {
                src_state = *msg;
            }
        });

        // dst_sub = create_subscription<JointState>(dst_name, 10, [this](const JointState::SharedPtr msg){
        //     std::lock_guard<std::mutex> lock(state_lock);
        //     if (msg->name.size() > 1) {
        //         dst_state = *msg;
        //     }
        // });

        urscript_pub = create_publisher<std_msgs::msg::String>(dst_topic, 10);
        service = create_service<Trigger>("synchronize_joints", [this](const Trigger::Request::SharedPtr request, Trigger::Response::SharedPtr response) {
            sync(request, response);
        });
    }

    std::string src_name, dst_name, dst_topic;
    JointState src_state, dst_state;

    void sync(Trigger::Request::SharedPtr request, Trigger::Response::SharedPtr response) {
        std::lock_guard<std::mutex> lock(state_lock);
        (void)request; // "Empty" struct, just signals that we want something to happen
        response->success = true;
        response->message = "success";
        printf("Got sync request\n");
        sync_impl();
    }

private:
    std::mutex state_lock;
    rclcpp::Subscription<JointState>::SharedPtr src_sub, dst_sub;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr urscript_pub;
    rclcpp::Service<Trigger>::SharedPtr service;

    void sync_impl() {
        if (src_state.position.size() < 6) {
            printf("Joint states sizes < 6, cannot sync!\n");
            return;
        }

        const std::string names[6] = {
            "shoulder_pan_joint",
            "shoulder_lift_joint",
            "elbow_joint",
            "wrist_1_joint",
            "wrist_2_joint",
            "wrist_3_joint",
        };
        std::array<double, 6> q = {0};
        for(size_t i = 0; i < q.size(); i++) {
            size_t j = 0;
            for(; j < 6; j++) {
                if (names[i] == src_state.name.at(j)) break;
            }
            q.at(i) = src_state.position.at(j);
        } 

        
        auto ss = std::stringstream();
        ss << std::setprecision(10);
        ss << "movej(["<<q.at(0)<<", "<<q.at(1)<<", "<<q.at(2)<<", "<<q.at(3)<<", "<<q.at(4)<<", "<<q.at(5)<<"], t=4.0, r=0)\n";
        printf("Sending urscript program: %s", ss.str().c_str());
        std_msgs::msg::String msg;
        msg.data.assign(ss.str());
        urscript_pub->publish(msg);
        // sleep(5);
        // system("ros2 run integrated_ur_robotiq ursim_play.py");

        // auto tj = JointTrajectory();
        // tj.header = src_state.header;
        // tj.joint_names = src_state.name;
        
        // auto start = JointTrajectoryPoint();
        // auto end = JointTrajectoryPoint();
        
        // end.time_from_start.sec = 5;
        // end.time_from_start.nanosec = 0;
        // double dt = end.time_from_start.sec + 0.000000001*end.time_from_start.nanosec;
        
        // start.positions = dst_state.position;
        // start.velocities.assign(start.positions.size(), 0);
        // start.accelerations.assign(start.positions.size(), 0);
        // for(size_t i = 0; i < src_state.position.size(); i++) {
        //     start.velocities.at(i) = (src_state.position.at(i) - dst_state.position.at(i))/dt;
        //     start.accelerations.at(i) = (start.velocities.at(i))/dt;
        // }

        // end.positions = src_state.position;
        // end.velocities.assign(end.positions.size(), 0);
        // end.accelerations.assign(end.positions.size(), 0);
        
        // tj.points.assign({start, end});
        // trajectory_pub->publish(tj);
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Synchronizer>("ur_synchronizer");
    rclcpp::spin(node);
    rclcpp::shutdown();
}