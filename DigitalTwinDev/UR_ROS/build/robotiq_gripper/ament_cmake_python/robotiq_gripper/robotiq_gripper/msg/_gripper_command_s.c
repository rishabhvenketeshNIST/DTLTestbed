// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from robotiq_gripper:msg/GripperCommand.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "robotiq_gripper/msg/detail/gripper_command__struct.h"
#include "robotiq_gripper/msg/detail/gripper_command__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool robotiq_gripper__msg__gripper_command__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[52];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("robotiq_gripper.msg._gripper_command.GripperCommand", full_classname_dest, 51) == 0);
  }
  robotiq_gripper__msg__GripperCommand * ros_message = _ros_message;
  {  // act
    PyObject * field = PyObject_GetAttrString(_pymsg, "act");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->act = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // gto
    PyObject * field = PyObject_GetAttrString(_pymsg, "gto");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->gto = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // atr
    PyObject * field = PyObject_GetAttrString(_pymsg, "atr");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->atr = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // ard
    PyObject * field = PyObject_GetAttrString(_pymsg, "ard");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->ard = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // pr
    PyObject * field = PyObject_GetAttrString(_pymsg, "pr");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->pr = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // sp
    PyObject * field = PyObject_GetAttrString(_pymsg, "sp");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->sp = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // fr
    PyObject * field = PyObject_GetAttrString(_pymsg, "fr");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->fr = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * robotiq_gripper__msg__gripper_command__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GripperCommand */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("robotiq_gripper.msg._gripper_command");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GripperCommand");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  robotiq_gripper__msg__GripperCommand * ros_message = (robotiq_gripper__msg__GripperCommand *)raw_ros_message;
  {  // act
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->act);
    {
      int rc = PyObject_SetAttrString(_pymessage, "act", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gto
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->gto);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gto", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // atr
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->atr);
    {
      int rc = PyObject_SetAttrString(_pymessage, "atr", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ard
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->ard);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ard", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pr
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->pr);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pr", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // sp
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->sp);
    {
      int rc = PyObject_SetAttrString(_pymessage, "sp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // fr
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->fr);
    {
      int rc = PyObject_SetAttrString(_pymessage, "fr", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
