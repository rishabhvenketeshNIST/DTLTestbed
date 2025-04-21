// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robotiq_gripper:msg/GripperStatus.idl
// generated code does not contain a copyright notice

#ifndef ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_STATUS__STRUCT_H_
#define ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/GripperStatus in the package robotiq_gripper.
typedef struct robotiq_gripper__msg__GripperStatus
{
  /// Activated? (0 or 1)
  uint8_t act;
  /// Going or stopped? (0 or 1)
  uint8_t gto;
  /// Status (0=deactivated, 1=in progress activation, 2=N/A, 3=activated)
  uint8_t sta;
  /// Object detection (0=moving with no object detected, 1=stopped by object when opening, 2=stopped by object when closing, 3=stopped successfully)
  uint8_t obj;
  /// Fault status (see manual)
  uint8_t flt;
  /// Requested position
  uint8_t pr;
  /// Measured position
  uint8_t po;
} robotiq_gripper__msg__GripperStatus;

// Struct for a sequence of robotiq_gripper__msg__GripperStatus.
typedef struct robotiq_gripper__msg__GripperStatus__Sequence
{
  robotiq_gripper__msg__GripperStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robotiq_gripper__msg__GripperStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOTIQ_GRIPPER__MSG__DETAIL__GRIPPER_STATUS__STRUCT_H_
