// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robotiq_gripper:msg/GripperCommand.idl
// generated code does not contain a copyright notice

#ifndef ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_COMMAND__TRAITS_HPP_
#define ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robotiq_gripper/msg/detail/gripper_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robotiq_gripper
{

namespace msg
{

inline void to_flow_style_yaml(
  const GripperCommand & msg,
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

  // member: atr
  {
    out << "atr: ";
    rosidl_generator_traits::value_to_yaml(msg.atr, out);
    out << ", ";
  }

  // member: ard
  {
    out << "ard: ";
    rosidl_generator_traits::value_to_yaml(msg.ard, out);
    out << ", ";
  }

  // member: pr
  {
    out << "pr: ";
    rosidl_generator_traits::value_to_yaml(msg.pr, out);
    out << ", ";
  }

  // member: sp
  {
    out << "sp: ";
    rosidl_generator_traits::value_to_yaml(msg.sp, out);
    out << ", ";
  }

  // member: fr
  {
    out << "fr: ";
    rosidl_generator_traits::value_to_yaml(msg.fr, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GripperCommand & msg,
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

  // member: atr
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "atr: ";
    rosidl_generator_traits::value_to_yaml(msg.atr, out);
    out << "\n";
  }

  // member: ard
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ard: ";
    rosidl_generator_traits::value_to_yaml(msg.ard, out);
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

  // member: sp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sp: ";
    rosidl_generator_traits::value_to_yaml(msg.sp, out);
    out << "\n";
  }

  // member: fr
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fr: ";
    rosidl_generator_traits::value_to_yaml(msg.fr, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GripperCommand & msg, bool use_flow_style = false)
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
  const robotiq_gripper::msg::GripperCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  robotiq_gripper::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robotiq_gripper::msg::to_yaml() instead")]]
inline std::string to_yaml(const robotiq_gripper::msg::GripperCommand & msg)
{
  return robotiq_gripper::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robotiq_gripper::msg::GripperCommand>()
{
  return "robotiq_gripper::msg::GripperCommand";
}

template<>
inline const char * name<robotiq_gripper::msg::GripperCommand>()
{
  return "robotiq_gripper/msg/GripperCommand";
}

template<>
struct has_fixed_size<robotiq_gripper::msg::GripperCommand>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<robotiq_gripper::msg::GripperCommand>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<robotiq_gripper::msg::GripperCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_COMMAND__TRAITS_HPP_
