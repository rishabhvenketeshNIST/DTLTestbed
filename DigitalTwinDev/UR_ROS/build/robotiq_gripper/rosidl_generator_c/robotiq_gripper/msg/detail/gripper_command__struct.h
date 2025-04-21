// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robotiq_gripper:msg/GripperCommand.idl
// generated code does not contain a copyright notice

#ifndef ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_COMMAND__STRUCT_H_
#define ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/GripperCommand in the package robotiq_gripper.
typedef struct robotiq_gripper__msg__GripperCommand
{
  /// Activate (0 or 1)
  uint8_t act;
  /// Go to (0 or 1)
  uint8_t gto;
  /// Automatic release (0 or 1)
  uint8_t atr;
  /// Auto release direction (0 = closing, 1 = opening)
  uint8_t ard;
  /// Position request (0-255) (0=open, 255=close)
  uint8_t pr;
  /// Speed request (0-255) (0=slowest, 255=fastest)
  uint8_t sp;
  /// Force request (0-255) (0=fragile mode, 1=weakest, 255=strongest)
  uint8_t fr;
} robotiq_gripper__msg__GripperCommand;

// Struct for a sequence of robotiq_gripper__msg__GripperCommand.
typedef struct robotiq_gripper__msg__GripperCommand__Sequence
{
  robotiq_gripper__msg__GripperCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robotiq_gripper__msg__GripperCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_COMMAND__STRUCT_H_
