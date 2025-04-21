#pragma once

#include "robotiq_gripper/msg/gripper_command.hpp"
#include "robotiq_gripper/msg/gripper_status.hpp"

namespace robotiq_gripper {

inline msg::GripperCommand g_activate() {
    msg::GripperCommand cmd;
    cmd.act = 1;
    return cmd;
}

inline msg::GripperCommand g_go_to(uint8_t pos, uint8_t speed=255, uint8_t force=0) {
    msg::GripperCommand cmd;
    cmd.act = 1;
    cmd.gto = 1;
    cmd.pr = pos;
    cmd.sp = speed;
    cmd.fr = force;
    return cmd;
}

inline msg::GripperCommand g_emove(uint8_t open) {
    msg::GripperCommand cmd;
    cmd.atr = 1;
    cmd.ard = (open != 0);
    return cmd;


}

}