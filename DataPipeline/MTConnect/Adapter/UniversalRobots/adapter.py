#!/usr/bin/env python3

import rtde_receive as rtde
import sys,os, time, math
from threading import Thread
from json import loads, dumps
from datetime import datetime

from mtconnect_adapter import Adapter
from data_item import DataItem, Event, SimpleCondition, Sample, ThreeDSample, MappedDataItem, MappedDataSet, Variable

from pyModbusTCP.client import ModbusClient

class Device:
    def __init__(self, adapter, api, modbus_client):
        self._dataitems = dict()
        self._adapter = adapter
        self._api = api
        self._adapter.start()
        self._is_available = False
        self.create_dataitems()
        self._modbus_client = modbus_client
        
        Thread(target = self.gather_forever).start()

    def create_dataitems(self):
        self.add_dataitem("AVAILABILITY","avail")
        self.add_dataitem("ACCUMULATED_TIME","start_time")
        self.add_dataitem("ACCUMULATED_TIME","exec_time")
        self.add_dataitem("ANGLE","angle_j1")
        self.add_dataitem("ANGLE","angle_j2")
        self.add_dataitem("ANGLE","angle_j3")
        self.add_dataitem("ANGLE","angle_j4")
        self.add_dataitem("ANGLE","angle_j5")
        self.add_dataitem("ANGLE","angle_j6")
        self.add_dataitem("ANGULAR_VELOCITY","vel_j1")
        self.add_dataitem("ANGULAR_VELOCITY","vel_j2")
        self.add_dataitem("ANGULAR_VELOCITY","vel_j3")
        self.add_dataitem("ANGULAR_VELOCITY","vel_j4")
        self.add_dataitem("ANGULAR_VELOCITY","vel_j5")
        self.add_dataitem("ANGULAR_VELOCITY","vel_j6")
        self.add_dataitem("ANGULAR_ACCELERATION","acc_j1")
        self.add_dataitem("ANGULAR_ACCELERATION","acc_j2")
        self.add_dataitem("ANGULAR_ACCELERATION","acc_j3")
        self.add_dataitem("ANGULAR_ACCELERATION","acc_j4")
        self.add_dataitem("ANGULAR_ACCELERATION","acc_j5")
        self.add_dataitem("ANGULAR_ACCELERATION","acc_j6")
        self.add_dataitem("TORQUE","tor_j1")
        self.add_dataitem("TORQUE","tor_j2")
        self.add_dataitem("TORQUE","tor_j3")
        self.add_dataitem("TORQUE","tor_j4")
        self.add_dataitem("TORQUE","tor_j5")
        self.add_dataitem("TORQUE","tor_j6")
        self.add_dataitem("TORQUE","tor_j6")
        self.add_dataitem("POSITION_CARTESIAN","posit_tcp")
        self.add_dataitem("ORIENTATION","orient_tcp")
        self.add_dataitem("VELOCITY","vel_x")
        self.add_dataitem("VELOCITY","vel_y")
        self.add_dataitem("VELOCITY","vel_z")
        self.add_dataitem("ANGULAR_VELOCITY","ang_vel_rx")
        self.add_dataitem("ANGULAR_VELOCITY","ang_vel_ry")
        self.add_dataitem("ANGULAR_VELOCITY","ang_vel_rz")
        self.add_dataitem("EMERGENCY_STOP","estop")
        #add data item for gripper position
        self.add_dataitem("OPENNESS", "gripper_pos")
       
    def add_dataitem(self, dataitem_type, dataitem_name):
        self._dataitems[dataitem_name] = DataItem(dataitem_name)
        self._adapter.add_data_item(self._dataitems[dataitem_name])

    def joint_angles(self):
        actual_q = [rad*180/math.pi for rad in self._api.getActualQ()]
        self._dataitems["angle_j1"].set_value(actual_q[0])
        self._dataitems["angle_j2"].set_value(actual_q[1])
        self._dataitems["angle_j3"].set_value(actual_q[2])
        self._dataitems["angle_j4"].set_value(actual_q[3])
        self._dataitems["angle_j5"].set_value(actual_q[4])
        self._dataitems["angle_j6"].set_value(actual_q[5])

    def joint_velocities(self):
        actual_qd = [rad*180/math.pi for rad in self._api.getActualQd()]
        self._dataitems["vel_j1"].set_value(actual_qd[0])
        self._dataitems["vel_j2"].set_value(actual_qd[1])
        self._dataitems["vel_j3"].set_value(actual_qd[2])
        self._dataitems["vel_j4"].set_value(actual_qd[3])
        self._dataitems["vel_j5"].set_value(actual_qd[4])
        self._dataitems["vel_j6"].set_value(actual_qd[5])

    def joint_accelerations(self):
        target_qdd = [rad*180/math.pi for rad in self._api.getTargetQdd()]
        self._dataitems["acc_j1"].set_value(target_qdd[0])
        self._dataitems["acc_j2"].set_value(target_qdd[1])
        self._dataitems["acc_j3"].set_value(target_qdd[2])
        self._dataitems["acc_j4"].set_value(target_qdd[3])
        self._dataitems["acc_j5"].set_value(target_qdd[4])
        self._dataitems["acc_j6"].set_value(target_qdd[5])

    def joint_torque(self):
        target_moment = self._api.getTargetMoment()
        self._dataitems["tor_j1"].set_value(target_moment[0])
        self._dataitems["tor_j2"].set_value(target_moment[1])
        self._dataitems["tor_j3"].set_value(target_moment[2])
        self._dataitems["tor_j4"].set_value(target_moment[3])
        self._dataitems["tor_j5"].set_value(target_moment[4])
        self._dataitems["tor_j6"].set_value(target_moment[5])

    def tcp_pose(self):
        actual_tcp_pose = self._api.getActualTCPPose()
        self._dataitems["posit_tcp"].set_value(" ".join(str(x*1000) for x in actual_tcp_pose[0:3]))
        self._dataitems["orient_tcp"].set_value(" ".join(str(x*180/math.pi) for x in actual_tcp_pose[3:6]))

    def tcp_speed(self):
        actual_tcp_speed = self._api.getActualTCPSpeed()
        self._dataitems["vel_x"].set_value(actual_tcp_speed[0])
        self._dataitems["vel_y"].set_value(actual_tcp_speed[1])
        self._dataitems["vel_z"].set_value(actual_tcp_speed[2])
        self._dataitems["ang_vel_rx"].set_value(actual_tcp_speed[3]*180/math.pi)
        self._dataitems["ang_vel_ry"].set_value(actual_tcp_speed[4]*180/math.pi)
        self._dataitems["ang_vel_rz"].set_value(actual_tcp_speed[5]*180/math.pi)

    def gripper_pos(self):
        pos = self._modbus_client.read_holding_registers(169)
        self._dataitems["gripper_pos"].set_value(1.0-(pos[0]-1.0)/89.0) # normalize to 0-1
        #print("Gripper data: ", pos)
        #self._dataitems["gripper_pos"].set_value(pos[0])

    def emergency_stop(self):
        if self._api.isEmergencyStopped():
            self._dataitems["estop"].set_value("TRIGGERED")
        else:
            self._dataitems["estop"].set_value("ARMED")
        
    def timestamps(self):
        self._dataitems["start_time"].set_value(self._api.getTimestamp())
        self._dataitems["exec_time"].set_value(self._api.getActualExecutionTime())

    def availability(self):
        if not self._is_available and self._api.isConnected():
            self._dataitems["avail"].set_value("AVAILABLE")
            self._is_available = True
        elif self._is_available and not self._api.isConnected():
            self._dataitems["avail"].set_value("UNAVAILABLE")
            self._is_available = False
            while not self._api.isConnected():
                try:
                    self._api.reconnect()
                except Exception as e:
                    print ("Error:", e)
                    print ("Reconnecting in 10 sec.")
                    time.sleep(10)
            self._dataitems["avail"].set_value("AVAILABLE")
            self._is_available = True

    def gather_data(self):
        self._adapter.begin_gather()
        self.availability()
        self.timestamps()
        self.emergency_stop()
        self.joint_angles()
        self.joint_velocities()
        self.joint_accelerations()
        self.joint_torque()
        self.tcp_pose()
        self.tcp_speed()
        self.gripper_pos()
        self._adapter.complete_gather()

    def gather_forever(self):
        while self._adapter.is_running():
            self.gather_data()
            time.sleep(0.100)

if __name__ == '__main__':

    variables = [
        "timestamp",
        "actual_q",
        "actual_qd", 
        "target_qdd", 
        "target_moment", 
        "actual_TCP_pose",
        "actual_TCP_speed",
        "actual_execution_time",
        "elbow_position",
        "elbow_velocity",
        "safety_status_bits"
        ]
    UR_IP = "192.168.50.25"
    ur5e_api = rtde.RTDEReceiveInterface(UR_IP, 500, variables, True, False, -1)
    adapter = Adapter(('0.0.0.0', 7878))
    modbus = ModbusClient(UR_IP)
    ur5e = Device(adapter, ur5e_api, modbus)
    
