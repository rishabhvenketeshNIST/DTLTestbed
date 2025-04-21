// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robotiq_gripper:msg/GripperCommand.idl
// generated code does not contain a copyright notice

#ifndef ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_COMMAND__BUILDER_HPP_
#define ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robotiq_gripper/msg/detail/gripper_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robotiq_gripper
{

namespace msg
{

namespace builder
{

class Init_GripperCommand_fr
{
public:
  explicit Init_GripperCommand_fr(::robotiq_gripper::msg::GripperCommand & msg)
  : msg_(msg)
  {}
  ::robotiq_gripper::msg::GripperCommand fr(::robotiq_gripper::msg::GripperCommand::_fr_type arg)
  {
    msg_.fr = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robotiq_gripper::msg::GripperCommand msg_;
};

class Init_GripperCommand_sp
{
public:
  explicit Init_GripperCommand_sp(::robotiq_gripper::msg::GripperCommand & msg)
  : msg_(msg)
  {}
  Init_GripperCommand_fr sp(::robotiq_gripper::msg::GripperCommand::_sp_type arg)
  {
    msg_.sp = std::move(arg);
    return Init_GripperCommand_fr(msg_);
  }

private:
  ::robotiq_gripper::msg::GripperCommand msg_;
};

class Init_GripperCommand_pr
{
public:
  explicit Init_GripperCommand_pr(::robotiq_gripper::msg::GripperCommand & msg)
  : msg_(msg)
  {}
  Init_GripperCommand_sp pr(::robotiq_gripper::msg::GripperCommand::_pr_type arg)
  {
    msg_.pr = std::move(arg);
    return Init_GripperCommand_sp(msg_);
  }

private:
  ::robotiq_gripper::msg::GripperCommand msg_;
};

class Init_GripperCommand_ard
{
public:
  explicit Init_GripperCommand_ard(::robotiq_gripper::msg::GripperCommand & msg)
  : msg_(msg)
  {}
  Init_GripperCommand_pr ard(::robotiq_gripper::msg::GripperCommand::_ard_type arg)
  {
    msg_.ard = std::move(arg);
    return Init_GripperCommand_pr(msg_);
  }

private:
  ::robotiq_gripper::msg::GripperCommand msg_;
};

class Init_GripperCommand_atr
{
public:
  explicit Init_GripperCommand_atr(::robotiq_gripper::msg::GripperCommand & msg)
  : msg_(msg)
  {}
  Init_GripperCommand_ard atr(::robotiq_gripper::msg::GripperCommand::_atr_type arg)
  {
    msg_.atr = std::move(arg);
    return Init_GripperCommand_ard(msg_);
  }

private:
  ::robotiq_gripper::msg::GripperCommand msg_;
};

class Init_GripperCommand_gto
{
public:
  explicit Init_GripperCommand_gto(::robotiq_gripper::msg::GripperCommand & msg)
  : msg_(msg)
  {}
  Init_GripperCommand_atr gto(::robotiq_gripper::msg::GripperCommand::_gto_type arg)
  {
    msg_.gto = std::move(arg);
    return Init_GripperCommand_atr(msg_);
  }

private:
  ::robotiq_gripper::msg::GripperCommand msg_;
};

class Init_GripperCommand_act
{
public:
  Init_GripperCommand_act()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GripperCommand_gto act(::robotiq_gripper::msg::GripperCommand::_act_type arg)
  {
    msg_.act = std::move(arg);
    return Init_GripperCommand_gto(msg_);
  }

private:
  ::robotiq_gripper::msg::GripperCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robotiq_gripper::msg::GripperCommand>()
{
  return robotiq_gripper::msg::builder::Init_GripperCommand_act();
}

}  // namespace robotiq_gripper

#endif  // ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_COMMAND__BUILDER_HPP_
