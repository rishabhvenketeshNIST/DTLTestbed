// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robotiq_gripper:msg/GripperCommand.idl
// generated code does not contain a copyright notice
#include "robotiq_gripper/msg/detail/gripper_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
robotiq_gripper__msg__GripperCommand__init(robotiq_gripper__msg__GripperCommand * msg)
{
  if (!msg) {
    return false;
  }
  // act
  // gto
  // atr
  // ard
  // pr
  // sp
  // fr
  return true;
}

void
robotiq_gripper__msg__GripperCommand__fini(robotiq_gripper__msg__GripperCommand * msg)
{
  if (!msg) {
    return;
  }
  // act
  // gto
  // atr
  // ard
  // pr
  // sp
  // fr
}

bool
robotiq_gripper__msg__GripperCommand__are_equal(const robotiq_gripper__msg__GripperCommand * lhs, const robotiq_gripper__msg__GripperCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // act
  if (lhs->act != rhs->act) {
    return false;
  }
  // gto
  if (lhs->gto != rhs->gto) {
    return false;
  }
  // atr
  if (lhs->atr != rhs->atr) {
    return false;
  }
  // ard
  if (lhs->ard != rhs->ard) {
    return false;
  }
  // pr
  if (lhs->pr != rhs->pr) {
    return false;
  }
  // sp
  if (lhs->sp != rhs->sp) {
    return false;
  }
  // fr
  if (lhs->fr != rhs->fr) {
    return false;
  }
  return true;
}

bool
robotiq_gripper__msg__GripperCommand__copy(
  const robotiq_gripper__msg__GripperCommand * input,
  robotiq_gripper__msg__GripperCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // act
  output->act = input->act;
  // gto
  output->gto = input->gto;
  // atr
  output->atr = input->atr;
  // ard
  output->ard = input->ard;
  // pr
  output->pr = input->pr;
  // sp
  output->sp = input->sp;
  // fr
  output->fr = input->fr;
  return true;
}

robotiq_gripper__msg__GripperCommand *
robotiq_gripper__msg__GripperCommand__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robotiq_gripper__msg__GripperCommand * msg = (robotiq_gripper__msg__GripperCommand *)allocator.allocate(sizeof(robotiq_gripper__msg__GripperCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robotiq_gripper__msg__GripperCommand));
  bool success = robotiq_gripper__msg__GripperCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robotiq_gripper__msg__GripperCommand__destroy(robotiq_gripper__msg__GripperCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robotiq_gripper__msg__GripperCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robotiq_gripper__msg__GripperCommand__Sequence__init(robotiq_gripper__msg__GripperCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robotiq_gripper__msg__GripperCommand * data = NULL;

  if (size) {
    data = (robotiq_gripper__msg__GripperCommand *)allocator.zero_allocate(size, sizeof(robotiq_gripper__msg__GripperCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robotiq_gripper__msg__GripperCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robotiq_gripper__msg__GripperCommand__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
robotiq_gripper__msg__GripperCommand__Sequence__fini(robotiq_gripper__msg__GripperCommand__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      robotiq_gripper__msg__GripperCommand__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

robotiq_gripper__msg__GripperCommand__Sequence *
robotiq_gripper__msg__GripperCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robotiq_gripper__msg__GripperCommand__Sequence * array = (robotiq_gripper__msg__GripperCommand__Sequence *)allocator.allocate(sizeof(robotiq_gripper__msg__GripperCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robotiq_gripper__msg__GripperCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robotiq_gripper__msg__GripperCommand__Sequence__destroy(robotiq_gripper__msg__GripperCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robotiq_gripper__msg__GripperCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robotiq_gripper__msg__GripperCommand__Sequence__are_equal(const robotiq_gripper__msg__GripperCommand__Sequence * lhs, const robotiq_gripper__msg__GripperCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robotiq_gripper__msg__GripperCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robotiq_gripper__msg__GripperCommand__Sequence__copy(
  const robotiq_gripper__msg__GripperCommand__Sequence * input,
  robotiq_gripper__msg__GripperCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robotiq_gripper__msg__GripperCommand);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robotiq_gripper__msg__GripperCommand * data =
      (robotiq_gripper__msg__GripperCommand *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robotiq_gripper__msg__GripperCommand__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robotiq_gripper__msg__GripperCommand__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robotiq_gripper__msg__GripperCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
