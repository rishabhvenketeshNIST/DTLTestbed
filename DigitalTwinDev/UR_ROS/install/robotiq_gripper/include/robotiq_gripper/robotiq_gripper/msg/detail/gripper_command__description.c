// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from robotiq_gripper:msg/GripperCommand.idl
// generated code does not contain a copyright notice

#include "robotiq_gripper/msg/detail/gripper_command__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_robotiq_gripper
const rosidl_type_hash_t *
robotiq_gripper__msg__GripperCommand__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xc6, 0x14, 0x76, 0x19, 0x83, 0x4e, 0x48, 0x63,
      0x7f, 0x88, 0x71, 0x7f, 0xde, 0xa6, 0x15, 0x30,
      0x21, 0xdd, 0x6f, 0x9e, 0x96, 0x9b, 0x68, 0x97,
      0x96, 0x5c, 0xad, 0x29, 0x0d, 0x3a, 0xf3, 0x29,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char robotiq_gripper__msg__GripperCommand__TYPE_NAME[] = "robotiq_gripper/msg/GripperCommand";

// Define type names, field names, and default values
static char robotiq_gripper__msg__GripperCommand__FIELD_NAME__act[] = "act";
static char robotiq_gripper__msg__GripperCommand__FIELD_NAME__gto[] = "gto";
static char robotiq_gripper__msg__GripperCommand__FIELD_NAME__atr[] = "atr";
static char robotiq_gripper__msg__GripperCommand__FIELD_NAME__ard[] = "ard";
static char robotiq_gripper__msg__GripperCommand__FIELD_NAME__pr[] = "pr";
static char robotiq_gripper__msg__GripperCommand__FIELD_NAME__sp[] = "sp";
static char robotiq_gripper__msg__GripperCommand__FIELD_NAME__fr[] = "fr";

static rosidl_runtime_c__type_description__Field robotiq_gripper__msg__GripperCommand__FIELDS[] = {
  {
    {robotiq_gripper__msg__GripperCommand__FIELD_NAME__act, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robotiq_gripper__msg__GripperCommand__FIELD_NAME__gto, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robotiq_gripper__msg__GripperCommand__FIELD_NAME__atr, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robotiq_gripper__msg__GripperCommand__FIELD_NAME__ard, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robotiq_gripper__msg__GripperCommand__FIELD_NAME__pr, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robotiq_gripper__msg__GripperCommand__FIELD_NAME__sp, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robotiq_gripper__msg__GripperCommand__FIELD_NAME__fr, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
robotiq_gripper__msg__GripperCommand__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {robotiq_gripper__msg__GripperCommand__TYPE_NAME, 34, 34},
      {robotiq_gripper__msg__GripperCommand__FIELDS, 7, 7},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "uint8 act # Activate (0 or 1)\n"
  "uint8 gto # Go to (0 or 1)\n"
  "uint8 atr # Automatic release (0 or 1)\n"
  "uint8 ard # Auto release direction (0 = closing, 1 = opening)\n"
  "uint8 pr # Position request (0-255) (0=open, 255=close)\n"
  "uint8 sp # Speed request (0-255) (0=slowest, 255=fastest)\n"
  "uint8 fr # Force request (0-255) (0=fragile mode, 1=weakest, 255=strongest)";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
robotiq_gripper__msg__GripperCommand__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {robotiq_gripper__msg__GripperCommand__TYPE_NAME, 34, 34},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 348, 348},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
robotiq_gripper__msg__GripperCommand__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *robotiq_gripper__msg__GripperCommand__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
