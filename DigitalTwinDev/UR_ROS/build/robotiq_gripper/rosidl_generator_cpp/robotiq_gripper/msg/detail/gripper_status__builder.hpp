// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robotiq_gripper:msg/GripperStatus.idl
// generated code does not contain a copyright notice

#ifndef ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_STATUS__BUILDER_HPP_
#define ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robotiq_gripper/msg/detail/gripper_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robotiq_gripper
{

namespace msg
{

namespace builder
{

class Init_GripperStatus_po
{
public:
  explicit Init_GripperStatus_po(::robotiq_gripper::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  ::robotiq_gripper::msg::GripperStatus po(::robotiq_gripper::msg::GripperStatus::_po_type arg)
  {
    msg_.po = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robotiq_gripper::msg::GripperStatus msg_;
};

class Init_GripperStatus_pr
{
public:
  explicit Init_GripperStatus_pr(::robotiq_gripper::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  Init_GripperStatus_po pr(::robotiq_gripper::msg::GripperStatus::_pr_type arg)
  {
    msg_.pr = std::move(arg);
    return Init_GripperStatus_po(msg_);
  }

private:
  ::robotiq_gripper::msg::GripperStatus msg_;
};

class Init_GripperStatus_flt
{
public:
  explicit Init_GripperStatus_flt(::robotiq_gripper::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  Init_GripperStatus_pr flt(::robotiq_gripper::msg::GripperStatus::_flt_type arg)
  {
    msg_.flt = std::move(arg);
    return Init_GripperStatus_pr(msg_);
  }

private:
  ::robotiq_gripper::msg::GripperStatus msg_;
};

class Init_GripperStatus_obj
{
public:
  explicit Init_GripperStatus_obj(::robotiq_gripper::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  Init_GripperStatus_flt obj(::robotiq_gripper::msg::GripperStatus::_obj_type arg)
  {
    msg_.obj = std::move(arg);
    return Init_GripperStatus_flt(msg_);
  }

private:
  ::robotiq_gripper::msg::GripperStatus msg_;
};

class Init_GripperStatus_sta
{
public:
  explicit Init_GripperStatus_sta(::robotiq_gripper::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  Init_GripperStatus_obj sta(::robotiq_gripper::msg::GripperStatus::_sta_type arg)
  {
    msg_.sta = std::move(arg);
    return Init_GripperStatus_obj(msg_);
  }

private:
  ::robotiq_gripper::msg::GripperStatus msg_;
};

class Init_GripperStatus_gto
{
public:
  explicit Init_GripperStatus_gto(::robotiq_gripper::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  Init_GripperStatus_sta gto(::robotiq_gripper::msg::GripperStatus::_gto_type arg)
  {
    msg_.gto = std::move(arg);
    return Init_GripperStatus_sta(msg_);
  }

private:
  ::robotiq_gripper::msg::GripperStatus msg_;
};

class Init_GripperStatus_act
{
public:
  Init_GripperStatus_act()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GripperStatus_gto act(::robotiq_gripper::msg::GripperStatus::_act_type arg)
  {
    msg_.act = std::move(arg);
    return Init_GripperStatus_gto(msg_);
  }

private:
  ::robotiq_gripper::msg::GripperStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robotiq_gripper::msg::GripperStatus>()
{
  return robotiq_gripper::msg::builder::Init_GripperStatus_act();
}

}  // namespace robotiq_gripper

#endif  // ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_STATUS__BUILDER_HPP_
