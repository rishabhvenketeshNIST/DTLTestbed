// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from robotiq_gripper:msg/GripperCommand.idl
// generated code does not contain a copyright notice
#include "robotiq_gripper/msg/detail/gripper_command__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "robotiq_gripper/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "robotiq_gripper/msg/detail/gripper_command__struct.h"
#include "robotiq_gripper/msg/detail/gripper_command__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _GripperCommand__ros_msg_type = robotiq_gripper__msg__GripperCommand;

static bool _GripperCommand__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GripperCommand__ros_msg_type * ros_message = static_cast<const _GripperCommand__ros_msg_type *>(untyped_ros_message);
  // Field name: act
  {
    cdr << ros_message->act;
  }

  // Field name: gto
  {
    cdr << ros_message->gto;
  }

  // Field name: atr
  {
    cdr << ros_message->atr;
  }

  // Field name: ard
  {
    cdr << ros_message->ard;
  }

  // Field name: pr
  {
    cdr << ros_message->pr;
  }

  // Field name: sp
  {
    cdr << ros_message->sp;
  }

  // Field name: fr
  {
    cdr << ros_message->fr;
  }

  return true;
}

static bool _GripperCommand__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GripperCommand__ros_msg_type * ros_message = static_cast<_GripperCommand__ros_msg_type *>(untyped_ros_message);
  // Field name: act
  {
    cdr >> ros_message->act;
  }

  // Field name: gto
  {
    cdr >> ros_message->gto;
  }

  // Field name: atr
  {
    cdr >> ros_message->atr;
  }

  // Field name: ard
  {
    cdr >> ros_message->ard;
  }

  // Field name: pr
  {
    cdr >> ros_message->pr;
  }

  // Field name: sp
  {
    cdr >> ros_message->sp;
  }

  // Field name: fr
  {
    cdr >> ros_message->fr;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robotiq_gripper
size_t get_serialized_size_robotiq_gripper__msg__GripperCommand(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GripperCommand__ros_msg_type * ros_message = static_cast<const _GripperCommand__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name act
  {
    size_t item_size = sizeof(ros_message->act);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name gto
  {
    size_t item_size = sizeof(ros_message->gto);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name atr
  {
    size_t item_size = sizeof(ros_message->atr);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ard
  {
    size_t item_size = sizeof(ros_message->ard);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name pr
  {
    size_t item_size = sizeof(ros_message->pr);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name sp
  {
    size_t item_size = sizeof(ros_message->sp);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name fr
  {
    size_t item_size = sizeof(ros_message->fr);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _GripperCommand__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_robotiq_gripper__msg__GripperCommand(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robotiq_gripper
size_t max_serialized_size_robotiq_gripper__msg__GripperCommand(
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

  // member: act
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: gto
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: atr
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: ard
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: pr
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: sp
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: fr
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
    using DataType = robotiq_gripper__msg__GripperCommand;
    is_plain =
      (
      offsetof(DataType, fr) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _GripperCommand__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_robotiq_gripper__msg__GripperCommand(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_GripperCommand = {
  "robotiq_gripper::msg",
  "GripperCommand",
  _GripperCommand__cdr_serialize,
  _GripperCommand__cdr_deserialize,
  _GripperCommand__get_serialized_size,
  _GripperCommand__max_serialized_size
};

static rosidl_message_type_support_t _GripperCommand__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GripperCommand,
  get_message_typesupport_handle_function,
  &robotiq_gripper__msg__GripperCommand__get_type_hash,
  &robotiq_gripper__msg__GripperCommand__get_type_description,
  &robotiq_gripper__msg__GripperCommand__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robotiq_gripper, msg, GripperCommand)() {
  return &_GripperCommand__type_support;
}

#if defined(__cplusplus)
}
#endif
