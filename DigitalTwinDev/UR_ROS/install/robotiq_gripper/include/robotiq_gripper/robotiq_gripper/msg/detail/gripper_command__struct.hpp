// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robotiq_gripper:msg/GripperCommand.idl
// generated code does not contain a copyright notice

#ifndef ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_COMMAND__STRUCT_HPP_
#define ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robotiq_gripper__msg__GripperCommand __attribute__((deprecated))
#else
# define DEPRECATED__robotiq_gripper__msg__GripperCommand __declspec(deprecated)
#endif

namespace robotiq_gripper
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GripperCommand_
{
  using Type = GripperCommand_<ContainerAllocator>;

  explicit GripperCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->act = 0;
      this->gto = 0;
      this->atr = 0;
      this->ard = 0;
      this->pr = 0;
      this->sp = 0;
      this->fr = 0;
    }
  }

  explicit GripperCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->act = 0;
      this->gto = 0;
      this->atr = 0;
      this->ard = 0;
      this->pr = 0;
      this->sp = 0;
      this->fr = 0;
    }
  }

  // field types and members
  using _act_type =
    uint8_t;
  _act_type act;
  using _gto_type =
    uint8_t;
  _gto_type gto;
  using _atr_type =
    uint8_t;
  _atr_type atr;
  using _ard_type =
    uint8_t;
  _ard_type ard;
  using _pr_type =
    uint8_t;
  _pr_type pr;
  using _sp_type =
    uint8_t;
  _sp_type sp;
  using _fr_type =
    uint8_t;
  _fr_type fr;

  // setters for named parameter idiom
  Type & set__act(
    const uint8_t & _arg)
  {
    this->act = _arg;
    return *this;
  }
  Type & set__gto(
    const uint8_t & _arg)
  {
    this->gto = _arg;
    return *this;
  }
  Type & set__atr(
    const uint8_t & _arg)
  {
    this->atr = _arg;
    return *this;
  }
  Type & set__ard(
    const uint8_t & _arg)
  {
    this->ard = _arg;
    return *this;
  }
  Type & set__pr(
    const uint8_t & _arg)
  {
    this->pr = _arg;
    return *this;
  }
  Type & set__sp(
    const uint8_t & _arg)
  {
    this->sp = _arg;
    return *this;
  }
  Type & set__fr(
    const uint8_t & _arg)
  {
    this->fr = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robotiq_gripper::msg::GripperCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const robotiq_gripper::msg::GripperCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robotiq_gripper::msg::GripperCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robotiq_gripper::msg::GripperCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robotiq_gripper::msg::GripperCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robotiq_gripper::msg::GripperCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robotiq_gripper::msg::GripperCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robotiq_gripper::msg::GripperCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robotiq_gripper::msg::GripperCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robotiq_gripper::msg::GripperCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robotiq_gripper__msg__GripperCommand
    std::shared_ptr<robotiq_gripper::msg::GripperCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robotiq_gripper__msg__GripperCommand
    std::shared_ptr<robotiq_gripper::msg::GripperCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GripperCommand_ & other) const
  {
    if (this->act != other.act) {
      return false;
    }
    if (this->gto != other.gto) {
      return false;
    }
    if (this->atr != other.atr) {
      return false;
    }
    if (this->ard != other.ard) {
      return false;
    }
    if (this->pr != other.pr) {
      return false;
    }
    if (this->sp != other.sp) {
      return false;
    }
    if (this->fr != other.fr) {
      return false;
    }
    return true;
  }
  bool operator!=(const GripperCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GripperCommand_

// alias to use template instance with default allocator
using GripperCommand =
  robotiq_gripper::msg::GripperCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robotiq_gripper

#endif  // ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_COMMAND__STRUCT_HPP_
