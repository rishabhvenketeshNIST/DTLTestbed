// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from robotiq_gripper:msg/GripperCommand.idl
// generated code does not contain a copyright notice
#include "robotiq_gripper/msg/detail/gripper_command__rosidl_typesupport_fastrtps_cpp.hpp"
#include "robotiq_gripper/msg/detail/gripper_command__functions.h"
#include "robotiq_gripper/msg/detail/gripper_command__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace robotiq_gripper
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_robotiq_gripper
cdr_serialize(
  const robotiq_gripper::msg::GripperCommand & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: act
  cdr << ros_message.act;
  // Member: gto
  cdr << ros_message.gto;
  // Member: atr
  cdr << ros_message.atr;
  // Member: ard
  cdr << ros_message.ard;
  // Member: pr
  cdr << ros_message.pr;
  // Member: sp
  cdr << ros_message.sp;
  // Member: fr
  cdr << ros_message.fr;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_robotiq_gripper
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  robotiq_gripper::msg::GripperCommand & ros_message)
{
  // Member: act
  cdr >> ros_message.act;

  // Member: gto
  cdr >> ros_message.gto;

  // Member: atr
  cdr >> ros_message.atr;

  // Member: ard
  cdr >> ros_message.ard;

  // Member: pr
  cdr >> ros_message.pr;

  // Member: sp
  cdr >> ros_message.sp;

  // Member: fr
  cdr >> ros_message.fr;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_robotiq_gripper
get_serialized_size(
  const robotiq_gripper::msg::GripperCommand & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: act
  {
    size_t item_size = sizeof(ros_message.act);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: gto
  {
    size_t item_size = sizeof(ros_message.gto);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: atr
  {
    size_t item_size = sizeof(ros_message.atr);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: ard
  {
    size_t item_size = sizeof(ros_message.ard);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: pr
  {
    size_t item_size = sizeof(ros_message.pr);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: sp
  {
    size_t item_size = sizeof(ros_message.sp);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: fr
  {
    size_t item_size = sizeof(ros_message.fr);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_robotiq_gripper
max_serialized_size_GripperCommand(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: act
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: gto
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: atr
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: ard
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: pr
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: sp
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: fr
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = robotiq_gripper::msg::GripperCommand;
    is_plain =
      (
      offsetof(DataType, fr) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _GripperCommand__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const robotiq_gripper::msg::GripperCommand *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _GripperCommand__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<robotiq_gripper::msg::GripperCommand *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _GripperCommand__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const robotiq_gripper::msg::GripperCommand *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _GripperCommand__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_GripperCommand(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _GripperCommand__callbacks = {
  "robotiq_gripper::msg",
  "GripperCommand",
  _GripperCommand__cdr_serialize,
  _GripperCommand__cdr_deserialize,
  _GripperCommand__get_serialized_size,
  _GripperCommand__max_serialized_size
};

static rosidl_message_type_support_t _GripperCommand__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_GripperCommand__callbacks,
  get_message_typesupport_handle_function,
  &robotiq_gripper__msg__GripperCommand__get_type_hash,
  &robotiq_gripper__msg__GripperCommand__get_type_description,
  &robotiq_gripper__msg__GripperCommand__get_type_description_sources,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace robotiq_gripper

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_robotiq_gripper
const rosidl_message_type_support_t *
get_message_type_support_handle<robotiq_gripper::msg::GripperCommand>()
{
  return &robotiq_gripper::msg::typesupport_fastrtps_cpp::_GripperCommand__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robotiq_gripper, msg, GripperCommand)() {
  return &robotiq_gripper::msg::typesupport_fastrtps_cpp::_GripperCommand__handle;
}

#ifdef __cplusplus
}
#endif
