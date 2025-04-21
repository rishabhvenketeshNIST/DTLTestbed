#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

#include "raylib.h"
#include "rlgl.h"
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

using std_msgs::msg::Float64MultiArray;
using geometry_msgs::msg::PoseStamped;
using geometry_msgs::msg::Pose;

// Converts a ROS timestamp into a double. Will lose precision,
// but offers a more convenient method of comparison.
static double TimeToDouble(builtin_interfaces::msg::Time t) {
    return t.sec + 1.0e-9*t.nanosec;
}

template<typename T>
static void remove_old(std::deque<T> &q, double now, double duration) {
    while(!q.empty() && (now - TimeToDouble(q.front().header.stamp)) > duration) {
        q.pop_front();
    }
}

struct ErrorStamped {
    std_msgs::msg::Header header;
    double pos_err = 0;
    double rot_err = 0;
};

static Color severity_color(int severity) {
    switch(severity) {
    case 0:
        return GREEN;
    case 1:
        return YELLOW;
    case 2:
        return ORANGE;
    default:
        return RED;
    }
}

class UINode : public rclcpp::Node {
public:
    UINode() : Node("integrated_ui"), lock() {
        physical_pose_topic = declare_parameter("physical_pose_topic", "/ur_tool_pose");
        digital_pose_topic = declare_parameter("digital_pose_topic", "/digital/ur_tool_pose");
        error_topic = declare_parameter("error_topic", "/ur_pose_error");

        physical_pose_sub = create_subscription<PoseStamped>(physical_pose_topic, 10, [this](const PoseStamped &ps){
            auto guard = std::lock_guard(lock);
            physical_poses.push_back(ps);
        });
        digital_pose_sub = create_subscription<PoseStamped>(digital_pose_topic, 10, [this](const PoseStamped &ps){
            auto guard = std::lock_guard(lock);
            digital_poses.push_front(ps);
        });
        error_sub = create_subscription<Float64MultiArray>(error_topic, 10, [this](const Float64MultiArray &errs){
            if (errs.data.size() < 2) return;
            auto guard = std::lock_guard(lock);
            ErrorStamped val;
            val.header.stamp = get_clock()->now();
            val.pos_err = errs.data.at(0);
            val.rot_err = errs.data.at(1);
            int severity = error_severity(val);
            if (severity > 0 && (error_vals.size() == 0 || severity > error_severity(error_vals.back()))) {
                event_list_dirty = true;
                error_events.push_back(val);
                auto fmt_str = "Pose Error: {timestamp: %f, pos_mm: %f, rot_deg: %f}";
                double v1 = TimeToDouble(val.header.stamp);
                double v2 = val.pos_err*1000.0;
                double v3 = val.rot_err*180/PI;
                switch(severity) {
                case 0:
                    RCLCPP_INFO(get_logger(), fmt_str, v1, v2, v3);
                    break;
                case 1:
                    RCLCPP_WARN(get_logger(), fmt_str, v1, v2, v3);
                    break;
                default:
                    RCLCPP_ERROR(get_logger(), fmt_str, v1, v2, v3);
                    break;
                }
            }
            error_vals.push_back(val);
        });
        constexpr float dt = 1.0/60;
        frame_timer = create_timer(std::chrono::microseconds((int64_t)(1000000*dt)), [this, dt](){update(dt);});
    }

    // How many multiples of the error threshold does the error exceed?
    int error_severity(const ErrorStamped &e) {
        return std::max<int>(e.pos_err/pos_err_max, e.rot_err/rot_err_max);
    }

private:
    std::mutex lock;

    std::string physical_pose_topic;
    std::string digital_pose_topic;
    std::string error_topic;
    
    rclcpp::Subscription<PoseStamped>::SharedPtr physical_pose_sub;
    rclcpp::Subscription<PoseStamped>::SharedPtr digital_pose_sub;
    rclcpp::Subscription<Float64MultiArray>::SharedPtr error_sub;

    rclcpp::TimerBase::SharedPtr frame_timer;

    std::deque<PoseStamped> physical_poses;
    std::deque<PoseStamped> digital_poses;
    std::deque<ErrorStamped> error_vals;
    std::deque<ErrorStamped> error_events; // logs errors which exceeded the threshold

    double history_sec = 60;
    double pos_err_max = 0.001;
    double rot_err_max = 0.02;

    // UI state
    bool event_list_visible = false;
    bool event_list_dirty = false;
    Vector2 event_list_scroll;

    void update(double dt) {
        auto guard = std::lock_guard(lock);
        (void)dt;
        // Remove old data
        double now = TimeToDouble(get_clock()->now());
        remove_old(physical_poses, now, history_sec);
        remove_old(digital_poses, now, history_sec);
        remove_old(error_vals, now, history_sec);
        

        if (WindowShouldClose()) {
            rclcpp::shutdown();
            return;
        }
        int width = GetScreenWidth();
        int height = GetScreenHeight();

        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        float margin = 50;
        Rectangle graph_bounds = {margin, margin, width-2*margin, height-2*margin};

        ErrorStamped max_err;
        for (auto &e : error_vals) {
            max_err.pos_err = std::max(max_err.pos_err, e.pos_err);
            max_err.rot_err = std::max(max_err.rot_err, e.rot_err);
        }
        float visual_max_pos_err = std::max(2*pos_err_max, max_err.pos_err);
        float visual_max_rot_err = std::max(2*rot_err_max, max_err.rot_err);
        for (auto &e : error_vals) {
            double sample_time = TimeToDouble(e.header.stamp);
            double t = (now - sample_time) / history_sec;
            float x = Lerp(graph_bounds.x, graph_bounds.x+graph_bounds.width, (float) t);
            float pos_y = Remap(e.pos_err, 0, visual_max_pos_err, graph_bounds.y+graph_bounds.height, graph_bounds.y);
            float rot_y = Remap(e.rot_err, 0, visual_max_rot_err, graph_bounds.y+graph_bounds.height, graph_bounds.y);
            // DrawPixel(x, rot_y, BLUE);
            // DrawPixel(x, pos_y, RED);
            DrawCircle(x, rot_y, 2, BLUE);
            DrawCircle(x, pos_y, 2, RED);
        }

        // Graph labels and graphics
        GuiDrawText("Error vs. Time", {margin, 0, width-2*margin, margin}, TEXT_ALIGN_LEFT, BLACK); // Title
        GuiDrawText("Time Elapsed (s)", {margin, height-margin*0.5f, width-2*margin, margin*0.5f}, TEXT_ALIGN_CENTER, BLACK); // x axis
        GuiDrawText("pos\n(mm)", {5, 0, margin, height-margin}, TEXT_ALIGN_LEFT, RED); // left y axis
        GuiDrawText("rot\n(deg)", {width-margin, 0, margin-5, height-margin}, TEXT_ALIGN_RIGHT, BLUE); // right y axis
        DrawLine(margin, height-margin, width-margin, height-margin, BLACK); // x axis
        DrawLine(margin, height-margin, margin, margin, BLACK); // left y axis
        DrawLine(width-margin, height-margin, width-margin, margin, BLACK); // right y axis
        for (double s = 0; s <= history_sec; s += 5) { // x axis
            float x = Lerp(graph_bounds.x, graph_bounds.x+graph_bounds.width, s/history_sec);
            float y = graph_bounds.y+graph_bounds.height;
            DrawLine(x, y, x, y+10, BLACK);
            GuiDrawText(TextFormat("%.0f", s), {x-20, y+11, 40, 12}, TEXT_ALIGN_CENTER, BLACK);
        }
        for (double p = 0; p <= visual_max_pos_err+EPSILON; p += visual_max_pos_err*0.1) { // left y axis
            float x = graph_bounds.x;
            float y = Lerp(graph_bounds.y+graph_bounds.height, margin, p/visual_max_pos_err);
            DrawLine(x, y, x-10, y, BLACK);
            GuiDrawText(TextFormat("%.1f", 1000*p), {0, y-10, x-11, 20}, TEXT_ALIGN_RIGHT, RED);
        }
        for (double p = 0; p <= visual_max_rot_err+EPSILON; p += visual_max_rot_err/12) { // right y axis
            float x = graph_bounds.x+graph_bounds.width;
            float y = Lerp(graph_bounds.y+graph_bounds.height, margin, p/visual_max_rot_err);
            DrawLine(x, y, x+10, y, BLACK);
            GuiDrawText(TextFormat("%.2f", 180*p/PI), {x+11, y-10, margin-11, 20}, TEXT_ALIGN_LEFT, BLUE);
        }

        float event_view_width = std::min(width, 200);
        Rectangle event_button_bounds = {width-event_view_width, 5, event_view_width-5, margin-10};
        int max_severity = 0;
        for (const auto &e : error_events) {
            max_severity = std::max(max_severity, error_severity(e));
        }
        
        GuiDrawRectangle(event_button_bounds, 1, BLACK, (event_list_dirty && !event_list_visible) ? severity_color(max_severity) : LIGHTGRAY);
        if (GuiLabelButton(event_button_bounds, GuiIconText(event_list_visible ? ICON_ARROW_UP : ICON_ARROW_DOWN, event_list_visible ? "Hide Events" : "View Events"))) {
            event_list_visible = !event_list_visible;
        }
        if (event_list_visible) {
            event_list_dirty = false;
            float event_height = 50;
            Rectangle list_bounds = event_button_bounds;
            list_bounds.y = event_button_bounds.y+event_button_bounds.height;
            list_bounds.width -= 10;
            list_bounds.height = (error_events.size()+1)*event_height;
            Vector2 &scroll = event_list_scroll;
            Rectangle scissor = {0, 0, 0, 0};
            
            GuiScrollPanel({list_bounds.x, list_bounds.y, list_bounds.width+10, height-list_bounds.y}, NULL, list_bounds, &scroll, &scissor);

            BeginScissorMode(scissor.x, scissor.y, scissor.width, scissor.height);

            if(GuiButton({list_bounds.x+scroll.x+5, list_bounds.y+scroll.y, scissor.width-10, event_height}, GuiIconText(ICON_BRUSH_CLASSIC, "Clear Event List"))) {
                error_events.clear();
            }
            rlPushMatrix();
            rlTranslatef(list_bounds.x+scroll.x, list_bounds.y+scroll.y, 0);
            // 0, 0 is now top left of scroll area
            for(size_t i = 0; i < error_events.size(); i++) {
                auto &e = error_events.at(i);
                Rectangle r = {5, (error_events.size()-i)*event_height, scissor.width-10, event_height};
                int severity = error_severity(e);
                Color c = severity_color(severity);
                GuiDrawRectangle(r, 1, BLACK, c);
                r.x += 5;
                r.width -= 10;
                GuiDrawText(TextFormat("timestamp: %f\npos_err=%.3f mm\nrot_err=%.3f deg", TimeToDouble(e.header.stamp), e.pos_err*1000, e.rot_err*180/PI), r, TEXT_ALIGN_LEFT, BLACK);
            }
            
            rlPopMatrix();
            EndScissorMode();
        }

        EndDrawing();
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    SetTargetFPS(30);
    InitWindow(800, 600, "Integrated UI");
    auto node = std::make_shared<UINode>();
    rclcpp::spin(node);
    CloseWindow();
    rclcpp::shutdown();
}