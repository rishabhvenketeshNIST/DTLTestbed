// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from robotiq_gripper:msg/GripperStatus.idl
// generated code does not contain a copyright notice

#include "robotiq_gripper/msg/detail/gripper_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_robotiq_gripper
const rosidl_type_hash_t *
robotiq_gripper__msg__GripperStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xfc, 0xe0, 0x22, 0x6c, 0x21, 0x3f, 0x79, 0xb6,
      0xa8, 0x83, 0x73, 0xd1, 0x90, 0x07, 0xd4, 0x4a,
      0x19, 0xd7, 0x58, 0xa6, 0x58, 0x4e, 0x1b, 0xbe,
      0x2a, 0xe4, 0x10, 0x4f, 0xa0, 0x2e, 0x1e, 0x9c,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char robotiq_gripper__msg__GripperStatus__TYPE_NAME[] = "robotiq_gripper/msg/GripperStatus";

// Define type names, field names, and default values
static char robotiq_gripper__msg__GripperStatus__FIELD_NAME__act[] = "act";
static char robotiq_gripper__msg__GripperStatus__FIELD_NAME__gto[] = "gto";
static char robotiq_gripper__msg__GripperStatus__FIELD_NAME__sta[] = "sta";
static char robotiq_gripper__msg__GripperStatus__FIELD_NAME__obj[] = "obj";
static char robotiq_gripper__msg__GripperStatus__FIELD_NAME__flt[] = "flt";
static char robotiq_gripper__msg__GripperStatus__FIELD_NAME__pr[] = "pr";
static char robotiq_gripper__msg__GripperStatus__FIELD_NAME__po[] = "po";

static rosidl_runtime_c__type_description__Field robotiq_gripper__msg__GripperStatus__FIELDS[] = {
  {
    {robotiq_gripper__msg__GripperStatus__FIELD_NAME__act, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robotiq_gripper__msg__GripperStatus__FIELD_NAME__gto, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robotiq_gripper__msg__GripperStatus__FIELD_NAME__sta, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robotiq_gripper__msg__GripperStatus__FIELD_NAME__obj, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robotiq_gripper__msg__GripperStatus__FIELD_NAME__flt, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robotiq_gripper__msg__GripperStatus__FIELD_NAME__pr, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robotiq_gripper__msg__GripperStatus__FIELD_NAME__po, 2, 2},
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
robotiq_gripper__msg__GripperStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {robotiq_gripper__msg__GripperStatus__TYPE_NAME, 33, 33},
      {robotiq_gripper__msg__GripperStatus__FIELDS, 7, 7},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "uint8 act # Activated? (0 or 1)\n"
  "uint8 gto # Going or stopped? (0 or 1)\n"
  "uint8 sta # Status (0=deactivated, 1=in progress activation, 2=N/A, 3=activated)\n"
  "uint8 obj # Object detection (0=moving with no object detected, 1=stopped by object when opening, 2=stopped by object when closing, 3=stopped successfully)\n"
  "uint8 flt # Fault status (see manual)\n"
  "uint8 pr # Requested position\n"
  "uint8 po # Measured position";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
robotiq_gripper__msg__GripperStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {robotiq_gripper__msg__GripperStatus__TYPE_NAME, 33, 33},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 404, 404},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
robotiq_gripper__msg__GripperStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *robotiq_gripper__msg__GripperStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
