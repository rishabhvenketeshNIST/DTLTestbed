// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robotiq_gripper:msg/GripperStatus.idl
// generated code does not contain a copyright notice

#ifndef ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_STATUS__TRAITS_HPP_
#define ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robotiq_gripper/msg/detail/gripper_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robotiq_gripper
{

namespace msg
{

inline void to_flow_style_yaml(
  const GripperStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: act
  {
    out << "act: ";
    rosidl_generator_traits::value_to_yaml(msg.act, out);
    out << ", ";
  }

  // member: gto
  {
    out << "gto: ";
    rosidl_generator_traits::value_to_yaml(msg.gto, out);
    out << ", ";
  }

  // member: sta
  {
    out << "sta: ";
    rosidl_generator_traits::value_to_yaml(msg.sta, out);
    out << ", ";
  }

  // member: obj
  {
    out << "obj: ";
    rosidl_generator_traits::value_to_yaml(msg.obj, out);
    out << ", ";
  }

  // member: flt
  {
    out << "flt: ";
    rosidl_generator_traits::value_to_yaml(msg.flt, out);
    out << ", ";
  }

  // member: pr
  {
    out << "pr: ";
    rosidl_generator_traits::value_to_yaml(msg.pr, out);
    out << ", ";
  }

  // member: po
  {
    out << "po: ";
    rosidl_generator_traits::value_to_yaml(msg.po, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GripperStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: act
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "act: ";
    rosidl_generator_traits::value_to_yaml(msg.act, out);
    out << "\n";
  }

  // member: gto
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gto: ";
    rosidl_generator_traits::value_to_yaml(msg.gto, out);
    out << "\n";
  }

  // member: sta
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sta: ";
    rosidl_generator_traits::value_to_yaml(msg.sta, out);
    out << "\n";
  }

  // member: obj
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "obj: ";
    rosidl_generator_traits::value_to_yaml(msg.obj, out);
    out << "\n";
  }

  // member: flt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "flt: ";
    rosidl_generator_traits::value_to_yaml(msg.flt, out);
    out << "\n";
  }

  // member: pr
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pr: ";
    rosidl_generator_traits::value_to_yaml(msg.pr, out);
    out << "\n";
  }

  // member: po
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "po: ";
    rosidl_generator_traits::value_to_yaml(msg.po, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GripperStatus & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace robotiq_gripper

namespace rosidl_generator_traits
{

[[deprecated("use robotiq_gripper::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robotiq_gripper::msg::GripperStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  robotiq_gripper::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robotiq_gripper::msg::to_yaml() instead")]]
inline std::string to_yaml(const robotiq_gripper::msg::GripperStatus & msg)
{
  return robotiq_gripper::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robotiq_gripper::msg::GripperStatus>()
{
  return "robotiq_gripper::msg::GripperStatus";
}

template<>
inline const char * name<robotiq_gripper::msg::GripperStatus>()
{
  return "robotiq_gripper/msg/GripperStatus";
}

template<>
struct has_fixed_size<robotiq_gripper::msg::GripperStatus>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<robotiq_gripper::msg::GripperStatus>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<robotiq_gripper::msg::GripperStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_STATUS__TRAITS_HPP_
