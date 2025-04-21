# generated from rosidl_generator_py/resource/_idl.py.em
# with input from robotiq_gripper:msg/GripperCommand.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GripperCommand(type):
    """Metaclass of message 'GripperCommand'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('robotiq_gripper')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'robotiq_gripper.msg.GripperCommand')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__gripper_command
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__gripper_command
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__gripper_command
            cls._TYPE_SUPPORT = module.type_support_msg__msg__gripper_command
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__gripper_command

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GripperCommand(metaclass=Metaclass_GripperCommand):
    """Message class 'GripperCommand'."""

    __slots__ = [
        '_act',
        '_gto',
        '_atr',
        '_ard',
        '_pr',
        '_sp',
        '_fr',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'act': 'uint8',
        'gto': 'uint8',
        'atr': 'uint8',
        'ard': 'uint8',
        'pr': 'uint8',
        'sp': 'uint8',
        'fr': 'uint8',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.act = kwargs.get('act', int())
        self.gto = kwargs.get('gto', int())
        self.atr = kwargs.get('atr', int())
        self.ard = kwargs.get('ard', int())
        self.pr = kwargs.get('pr', int())
        self.sp = kwargs.get('sp', int())
        self.fr = kwargs.get('fr', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.act != other.act:
            return False
        if self.gto != other.gto:
            return False
        if self.atr != other.atr:
            return False
        if self.ard != other.ard:
            return False
        if self.pr != other.pr:
            return False
        if self.sp != other.sp:
            return False
        if self.fr != other.fr:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def act(self):
        """Message field 'act'."""
        return self._act

    @act.setter
    def act(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'act' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'act' field must be an unsigned integer in [0, 255]"
        self._act = value

    @builtins.property
    def gto(self):
        """Message field 'gto'."""
        return self._gto

    @gto.setter
    def gto(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'gto' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'gto' field must be an unsigned integer in [0, 255]"
        self._gto = value

    @builtins.property
    def atr(self):
        """Message field 'atr'."""
        return self._atr

    @atr.setter
    def atr(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'atr' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'atr' field must be an unsigned integer in [0, 255]"
        self._atr = value

    @builtins.property
    def ard(self):
        """Message field 'ard'."""
        return self._ard

    @ard.setter
    def ard(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'ard' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'ard' field must be an unsigned integer in [0, 255]"
        self._ard = value

    @builtins.property
    def pr(self):
        """Message field 'pr'."""
        return self._pr

    @pr.setter
    def pr(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'pr' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'pr' field must be an unsigned integer in [0, 255]"
        self._pr = value

    @builtins.property
    def sp(self):
        """Message field 'sp'."""
        return self._sp

    @sp.setter
    def sp(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'sp' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'sp' field must be an unsigned integer in [0, 255]"
        self._sp = value

    @builtins.property
    def fr(self):
        """Message field 'fr'."""
        return self._fr

    @fr.setter
    def fr(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'fr' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'fr' field must be an unsigned integer in [0, 255]"
        self._fr = value
