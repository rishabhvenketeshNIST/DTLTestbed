from setuptools import find_packages
from setuptools import setup

setup(
    name='robotiq_gripper',
    version='0.0.0',
    packages=find_packages(
        include=('robotiq_gripper', 'robotiq_gripper.*')),
)
