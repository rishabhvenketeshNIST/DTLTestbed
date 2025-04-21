// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robotiq_gripper:msg/GripperStatus.idl
// generated code does not contain a copyright notice

#ifndef ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_STATUS__STRUCT_HPP_
#define ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robotiq_gripper__msg__GripperStatus __attribute__((deprecated))
#else
# define DEPRECATED__robotiq_gripper__msg__GripperStatus __declspec(deprecated)
#endif

namespace robotiq_gripper
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GripperStatus_
{
  using Type = GripperStatus_<ContainerAllocator>;

  explicit GripperStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->act = 0;
      this->gto = 0;
      this->sta = 0;
      this->obj = 0;
      this->flt = 0;
      this->pr = 0;
      this->po = 0;
    }
  }

  explicit GripperStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->act = 0;
      this->gto = 0;
      this->sta = 0;
      this->obj = 0;
      this->flt = 0;
      this->pr = 0;
      this->po = 0;
    }
  }

  // field types and members
  using _act_type =
    uint8_t;
  _act_type act;
  using _gto_type =
    uint8_t;
  _gto_type gto;
  using _sta_type =
    uint8_t;
  _sta_type sta;
  using _obj_type =
    uint8_t;
  _obj_type obj;
  using _flt_type =
    uint8_t;
  _flt_type flt;
  using _pr_type =
    uint8_t;
  _pr_type pr;
  using _po_type =
    uint8_t;
  _po_type po;

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
  Type & set__sta(
    const uint8_t & _arg)
  {
    this->sta = _arg;
    return *this;
  }
  Type & set__obj(
    const uint8_t & _arg)
  {
    this->obj = _arg;
    return *this;
  }
  Type & set__flt(
    const uint8_t & _arg)
  {
    this->flt = _arg;
    return *this;
  }
  Type & set__pr(
    const uint8_t & _arg)
  {
    this->pr = _arg;
    return *this;
  }
  Type & set__po(
    const uint8_t & _arg)
  {
    this->po = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robotiq_gripper::msg::GripperStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const robotiq_gripper::msg::GripperStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robotiq_gripper::msg::GripperStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robotiq_gripper::msg::GripperStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robotiq_gripper::msg::GripperStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robotiq_gripper::msg::GripperStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robotiq_gripper::msg::GripperStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robotiq_gripper::msg::GripperStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robotiq_gripper::msg::GripperStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robotiq_gripper::msg::GripperStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robotiq_gripper__msg__GripperStatus
    std::shared_ptr<robotiq_gripper::msg::GripperStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robotiq_gripper__msg__GripperStatus
    std::shared_ptr<robotiq_gripper::msg::GripperStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GripperStatus_ & other) const
  {
    if (this->act != other.act) {
      return false;
    }
    if (this->gto != other.gto) {
      return false;
    }
    if (this->sta != other.sta) {
      return false;
    }
    if (this->obj != other.obj) {
      return false;
    }
    if (this->flt != other.flt) {
      return false;
    }
    if (this->pr != other.pr) {
      return false;
    }
    if (this->po != other.po) {
      return false;
    }
    return true;
  }
  bool operator!=(const GripperStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GripperStatus_

// alias to use template instance with default allocator
using GripperStatus =
  robotiq_gripper::msg::GripperStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robotiq_gripper

#endif  // ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_STATUS__STRUCT_HPP_
