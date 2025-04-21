#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/velocity_stamped.hpp"

#define dist3(a, b) sqrt(((a).x - (b).x)*((a).x - (b).x) + ((a).y - (b).y)*((a).y - (b).y) + ((a).z - (b).z)*((a).z - (b).z))

using namespace geometry_msgs::msg;

// Converts a ROS timestamp into a double. Will lose precision,
// but offers a more convenient method of comparison.
static double TimeToDouble(builtin_interfaces::msg::Time t) {
    return t.sec + 1.0e-9*t.nanosec;
}

static Quaternion QuaternionNormalize(Quaternion q)
{
    Quaternion result;

    float length = sqrtf(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
    if (length == 0.0f) length = 1.0f;
    float ilength = 1.0f/length;

    result.x = q.x*ilength;
    result.y = q.y*ilength;
    result.z = q.z*ilength;
    result.w = q.w*ilength;

    return result;
}

// Inverts a quaternion, including non-unit quaternions
static Quaternion QuaternionInvert(Quaternion q)
{
    Quaternion result = q;

    float lengthSq = q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w;

    if (lengthSq != 0.0f)
    {
        float invLength = 1.0f/lengthSq;

        result.x *= -invLength;
        result.y *= -invLength;
        result.z *= -invLength;
        result.w *= invLength;
    }

    return result;
}

// Returns the result of q1*q2
static Quaternion QuaternionMultiply(Quaternion q1, Quaternion q2)
{
    Quaternion result;

    float qax = q1.x, qay = q1.y, qaz = q1.z, qaw = q1.w;
    float qbx = q2.x, qby = q2.y, qbz = q2.z, qbw = q2.w;

    result.x = qax*qbw + qaw*qbx + qay*qbz - qaz*qby;
    result.y = qay*qbw + qaw*qby + qaz*qbx - qax*qbz;
    result.z = qaz*qbw + qaw*qbz + qax*qby - qay*qbx;
    result.w = qaw*qbw - qax*qbx - qay*qby - qaz*qbz;

    return result;
}

// Returns a quaternion 'q' such that
// to = q*from (q = to*from^-1)
static Quaternion QuaternionFromTo(Quaternion from, Quaternion to) {
    return QuaternionMultiply(to, QuaternionInvert(from));
}

// Returns a signed angle of this rotation relative to the unit quaternion,
// sign depends on the axis direction.
static double QuaternionSignedAngle(Quaternion q) {
    if (q.w > 1.0) {
        q = QuaternionNormalize(q);
    }
    return 2.0*acos(q.w);
}

// Returns an angle > 0, representing the amount of rotation from the unit quaternion
static double QuaternionAngle(Quaternion q) {
    if (q.w < 0) {
        // Then use the positive version of the quaternion for positive angles
        q.x = -q.x;
        q.y = -q.y;
        q.z = -q.z;
        q.w = -q.w;
    }
    return QuaternionSignedAngle(q);
}

// Converts a quaternion rotation to an axis-angle vector V,
// where the angle is |V| and the axis is V/|V|.
// This representation is the most compact way to store a rotation,
// but does not compose rotations well. It does compose angular velocity, though.
// static Vector3 QuaternionToAxisAngle(Quaternion q) {
//     Vector3 out;
//     double angle = QuaternionSignedAngle(q);

//     double scale = angle/sqrt(1.0f - q.w*q.w);
//     out.x = q.x*scale;
//     out.y = q.y*scale;
//     out.z = q.z*scale;
//     return out;
// }

class Comparator : public rclcpp::Node {
public:
    Comparator() : Node("ur_trajectory_comparator"), lock() {
        std::string sub1_name = declare_parameter("pose_topic_1", "/ur_tool_pose");
        std::string sub2_name = declare_parameter("pose_topic_2", "/digital/ur_tool_pose");
        max_desync_sec = declare_parameter("max_desync_sec", 1.0);
        pose_sub1 = create_subscription<PoseStamped>(sub1_name, 10, [this](const PoseStamped &ps){
            auto guard = std::lock_guard(lock);
            poses1.push_back(ps);
            poses1_dirty = true;
        });
        pose_sub2 = create_subscription<PoseStamped>(sub2_name, 10, [this](const PoseStamped &ps){
            auto guard = std::lock_guard(lock);
            poses2.push_back(ps);
            poses2_dirty = true;
        });
        err_pub = create_publisher<std_msgs::msg::Float64MultiArray>("ur_pose_error", 10);
        double period = 0.01; // seconds
        timer = create_timer(std::chrono::milliseconds((int64_t)(1000.0*period)), [this, period](){
            update(period);
        });
    }
private:
    std::mutex lock;
    std::deque<PoseStamped> poses1, poses2;
    rclcpp::Subscription<PoseStamped>::SharedPtr pose_sub1, pose_sub2;
    rclcpp::TimerBase::SharedPtr timer;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr err_pub;
    double max_desync_sec;
    bool poses1_dirty = false, poses2_dirty = false;

    void update(double dt) {
        (void)dt;
        auto guard = std::lock_guard(lock);
        // If no changes, then stop this loop early.
        if ((!poses1_dirty && !poses2_dirty) || (poses1.size() == 0 || poses2.size() == 0)) return;
        poses1_dirty = false;
        poses2_dirty = false;
        // TODO compare series of poses
        // HOWEVER, cannot use timestamp alone to identify same path
        // Path is series of poses, but we only have a path going back so far in time.
        // To keep the program running quickly, we throw away poses older than max_desync_sec from the current time.
        // We can store a velocity calculated based on previous pose, if the two poses are within the max_desync_sec time.
        // Then, using the position and velocity, we can find points in time when the two paths are most similar.
        // "Most similar" is an optimization problem. We can get local solutions with gradient descent:
        // Starting at the oldest timestamp available, we have two variables (indexes) which can change to increase or decrease the objective.
        // We only change one of them at a time, and always by 1. This way, we always approach a local minimum.
        // Once the local minimum is found, the indices can be used to report the displacement (and velocity) difference.

        double newest = 0;
        if (poses1.size() > 0) {
            newest = std::max(newest, TimeToDouble(poses1.back().header.stamp));
        }
        if (poses2.size() > 0) {
            newest = std::max(newest, TimeToDouble(poses2.back().header.stamp));
        }
        while((poses1.size() > 0) && (newest - TimeToDouble(poses1.front().header.stamp)) > max_desync_sec) {
            poses1.pop_front();
        }
        while((poses2.size() > 0) && (newest - TimeToDouble(poses2.front().header.stamp)) > max_desync_sec) {
            poses2.pop_front();
        }

        // auto vel_calc = [&](Pose &cur, Pose&prev, double dt) {
        //     Twist out;
        //     out.linear.x = (cur.position.x - prev.position.x)/dt;
        //     out.linear.y = (cur.position.y - prev.position.y)/dt;
        //     out.linear.z = (cur.position.z - prev.position.z)/dt;
        //     // q2 = r*q1
        //     // q2*q1' = r = "dr"
        //     auto r = QuaternionToAxisAngle(QuaternionFromTo(prev.orientation, cur.orientation));
        //     out.angular.x = r.x / dt;
        //     out.angular.y = r.y / dt;
        //     out.angular.z = r.z / dt;
        //     return out;
        // };
        
        auto error_calc = [&](Pose &pos_a, Pose &pos_b) {
            double err = 0.0;
            err += dist3(pos_a.position, pos_b.position);
            err += QuaternionAngle(QuaternionFromTo(pos_a.orientation, pos_b.orientation));
            // err += dist3(vel_a.linear, vel_a.linear);
            // err += dist3(vel_a.angular, vel_b.angular);
            return err;
        };

        auto error_at = [this, &error_calc](size_t i1, size_t i2){
            PoseStamped &a = poses1.at(i1);
            PoseStamped &b = poses2.at(i2);
            return error_calc(a.pose, b.pose);
        };

        size_t idx1 = 0, idx2 = 0;
        double cur_err = 0;
        while (idx1 < poses1.size() && idx2 < poses2.size()) {
            const size_t prev_idx1 = idx1, prev_idx2 = idx2;
            PoseStamped &a = poses1.at(idx1);
            PoseStamped &b = poses2.at(idx2);
            cur_err = error_calc(a.pose, b.pose);
            double possible_err_1 = (idx1+1 >= poses1.size()) ? HUGE_VAL : error_at(idx1+1, idx2);
            double possible_err_2 = (idx2+1 >= poses2.size()) ? HUGE_VAL : error_at(idx1, idx2+1);
            if (possible_err_1 < cur_err) {
                cur_err = possible_err_1;
                idx1 = idx1+1;
            }
            if (possible_err_2 < cur_err) {
                cur_err = possible_err_2;
                idx2 = idx2+1;
            }
            if (prev_idx1 == idx1 && prev_idx2 == idx2) {
                // Then no change occurred and we are at a local minimum.
                break;
            }
        }
        PoseStamped &a = poses1.at(idx1);
        PoseStamped &b = poses2.at(idx2);
        // PoseStamped &a = poses1.back();
        // PoseStamped &b = poses2.back();

        std_msgs::msg::Float64MultiArray err_msg;
        err_msg.data.assign({
            dist3(a.pose.position, b.pose.position),
            QuaternionAngle(QuaternionFromTo(a.pose.orientation, b.pose.orientation))
        });
        err_pub->publish(err_msg);
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Comparator>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}