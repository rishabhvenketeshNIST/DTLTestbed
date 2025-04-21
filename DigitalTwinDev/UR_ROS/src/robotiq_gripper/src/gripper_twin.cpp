#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <stdint.h>

#include "sensor_msgs/msg/joint_state.hpp"
#include "rclcpp/rclcpp.hpp"
#include "robotiq_gripper/msg/gripper_command.hpp"
#include "robotiq_gripper/msg/gripper_status.hpp"

using namespace std::chrono_literals;

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

class GripperTwin : public rclcpp::Node {
public:
    robotiq_gripper::msg::GripperStatus state;
    robotiq_gripper::msg::GripperCommand cmd;

    GripperTwin(const std::string &node_name) : Node(node_name) {
        declare_parameter("dt", 0.01);
        declare_parameter("joint_name", "");
        declare_parameter("min_speed", min_speed);
        declare_parameter("max_speed", max_speed);
        min_speed = get_parameter("min_speed").as_double();
        max_speed = get_parameter("max_speed").as_double();
        float dt = get_parameter("dt").as_double();
        joint_name = get_parameter("joint_name").as_string();
        auto qos_in = rclcpp::ServicesQoS();
        auto qos_out = rclcpp::SystemDefaultsQoS();
        state_pub = create_publisher<robotiq_gripper::msg::GripperStatus>("gripper_state", qos_out);
        printf("Started gripper twin with timestep of %fs\n", dt);
        if (joint_name.size() > 0) {
            joint_pub = create_publisher<sensor_msgs::msg::JointState>("joint_states", qos_out);
            printf("Publishing joint state with joint name: %s\n", joint_name.c_str());
        }
        cmd_sub = create_subscription<robotiq_gripper::msg::GripperCommand>(
            "/robotiq_gripper_cmd", qos_in,
            [this](const robotiq_gripper::msg::GripperCommand::SharedPtr cmd) {
                command(*cmd);
            }
        );
        auto period = std::chrono::microseconds((int64_t)(dt*1000000));
        sim_timer = create_timer(period, [this, dt](){
            time_step(dt);
        });

    }

    void command(const robotiq_gripper::msg::GripperCommand &c) {
        std::lock_guard<std::mutex> LOCK(cmd_lock);
        RCLCPP_INFO(get_logger(),
            "Command: act:%d|gto:0x%d|atr:0x%d|ard:0x%d|pr:0x%d|sp:0x%d|fr:0x%d\n",
            c.act, c.gto, c.atr, c.ard, c.pr, c.sp, c.fr
        );
        // TODO check if activated for setting certain fields
        cmd = c;
    }

    private:

    void time_step(float dt) {
        std::lock_guard<std::mutex> LOCK(cmd_lock);
        const float move_speed_min = min_speed;
        const float move_speed_max = max_speed;
        float pos_goal = 0;
        // Evaluate current command, set velocity accordingly
        if (cmd.atr) {
            // Emergency move, deactivate and set fault state
            state.act = 0;
            state.sta = 0;
            state.gto = 0;
            bool move_done = false;
            if (cmd.ard == 0) {
                // closing
                velocity = -move_speed_min;
                pos_goal = 0;
                if (state.po == 0) move_done = true;
            } else {
                // opening
                velocity = move_speed_min;
                pos_goal = 255;
                if (state.po == 255) move_done = true;
            }
            state.flt = move_done ? 0x0f : 0x0b;
        }
        if (state.act) {
            // Gripper is active
            if (cmd.gto || state.gto) {
                // Move towards requested position
                switch (state.obj)
                {
                case 0:
                    // Moving and no object detected
                    {
                        state.gto = 1;
                        state.pr = cmd.pr;
                        pos_goal = cmd.pr;
                        float t = cmd.sp/255.0;
                        velocity = sign(pos_goal - position)*(move_speed_min*(1-t)+move_speed_max*(t));
                        if (velocity == 0) state.obj = 3;
                    }
                    break;
                case 1:
                    // Object hit while opening
                    velocity = 0;
                    state.gto = 0;
                    if (cmd.pr > position) {
                        // If the new position request causes the gripper to close, then close.
                        // Otherwise, do nothing (ignores redundant requests)
                        state.obj = 0;
                    }
                    break;
                case 2:
                    // Object hit while closing
                    velocity = 0;
                    state.gto = 0;
                    if (cmd.pr < position) {
                        // If the new position request causes the gripper to open, then open.
                        // Otherwise, do nothing (ignores redundant requests)
                        state.obj = 0;
                    }
                    break;
                case 3:
                    // Reached position without collision
                    state.gto = 0;
                    if (abs(cmd.pr - position) >= 0.5f) {
                        // If a new position request is initiated, then start moving again.
                        state.obj = 0;
                    }
                    break;
                }
            }
        } else {
            state.gto = 0;
            switch (state.sta) {
            case 0:
                // Activation conditions:
                // - Command is an activation command: act != 0 and gto == 0
                // - Gripper either not in fault state, or is finished with an automatic release
                if(cmd.act != 0 && cmd.gto == 0 && (state.flt == 0 || state.flt == 0x0f)) {
                    state.sta = 1; // activation in progress
                }
                break;
            case 1:
                velocity = -move_speed_max; // open gripper for activation
                pos_goal = 0;
                if (position <= 0) state.sta = 3;
                break;
            case 3:
                state.act = 1;
                velocity = 0;
                break;
            }
        }

        // move only if activated, in the process of activating, or in an emergency move state
        if (state.act || state.sta == 1 || state.flt == 0x0b) {
            float delta = velocity*dt;
            if (velocity > 0 && pos_goal >= position) {
                if (position+delta > pos_goal) position = pos_goal;
                else position += delta;
            } else if (velocity < 0 && pos_goal <= position) {
                if (position+delta < pos_goal) position = pos_goal;
                else position += delta;
            } else {
                position += delta;
            }
        }
        
        // Set state
        state.po = (uint8_t) position;
        // printf("State: act |gto |sta |obj |flt | pr | po | position | velocity\n"
        //        "       0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x|0x%02x| %f | %f\n",
        //        state.act, state.gto, state.sta, state.obj, state.flt, state.pr, state.po, position, velocity);
        state_pub->publish(state);
        if (joint_pub != nullptr) {
            sensor_msgs::msg::JointState j;
            j.header.stamp = get_clock()->now();
            j.name.push_back(joint_name);
            float rads_per_unit = 0.7929f/255.0f;
            float joint_pos = position*rads_per_unit; // rad
            float joint_vel = velocity*rads_per_unit; // rad/s
            j.position.push_back(joint_pos);
            j.velocity.push_back(joint_vel);
            joint_pub->publish(j);
        }
    }
    float min_speed = 53;
    float max_speed = 255;
    float position = 0;
    float velocity = 0;
    rclcpp::Publisher<robotiq_gripper::msg::GripperStatus>::SharedPtr state_pub;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_pub;
    rclcpp::Subscription<robotiq_gripper::msg::GripperCommand>::SharedPtr cmd_sub;
    rclcpp::TimerBase::SharedPtr sim_timer;
    std::string joint_name;
    std::mutex cmd_lock;
};

int main(int argc, const char *argv[]) { 
    rclcpp::init(argc, argv);
    auto node = std::make_shared<GripperTwin>("gripper_twin");
    rclcpp::spin(node);
    rclcpp::shutdown();
}
