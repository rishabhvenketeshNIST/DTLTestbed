# Ur5e adapter
An implementation of the Universal Robot adapter.

Introduction
------------
A python adapter "adapter.py" for the UR5e is shared which provides an interface for the UR5e to become MTConnect compliant. The adapter allows the use of MTConnect agent to make the UR5e compliant. The steps to install and implement MTConnect agent can be found at https://github.com/mtconnect/cppagent

Implementation
--------------
Download the files in an external host (e.g. Raspberry Pi) that is connected to the UR5e robot due to the inability to install third party software on the UR5e controller. update the port information in the "adapter.py" to the port number available on your device.

`PORT = 7878`

Once the information in the "adapter.py" file is updated, this python script needs to be used as a service so that the adapter is active everytime the PocketNC is powered on. In order to enable this enter the following code in the Raspberry Pi terminal:

`sudo nano .\bashrc`

In the .bashrc shell script, goto the end of the file and add the following line:

`nohup python /home/pocketnc/adapter.py > /dev/null 2>&1 &`

assuming that the location of the "adapter.py" file is "/home/pocketnc/adapter.py". Edit this line appropriately.

Next time when the PocketNC is restarted, the adapter will be running as a service behind the scenes.

For implementation of the MTConnect agent, the steps are clearly defined on the MTConnect agent github repository (https://github.com/mtconnect/cppagent). The "ur5e.xml" can be used as device file for the MTConnect agent.

DataItems
---------
Following Data Items have been included in the adapter:

1. Accumulated Time : Start Time
2. Accumulated Time : Exec Time
3. Angle : Joint 1
4. Angle : Joint 2
5. Angle : Joint 3
6. Angle : Joint 4
7. Angle : Joint 5
8. Angle : Joint 6
9. Angular Velocity : Joint 1
10. Angular Velocity : Joint 2
11. Angular Velocity : Joint 3
12. Angular Velocity : Joint 4
13. Angular Velocity : Joint 5
14. Angular Velocity : Joint 6
15. Angular Acceleration : Joint 1
16. Angular Acceleration : Joint 2
17. Angular Acceleration : Joint 3
18. Angular Acceleration : Joint 4
19. Angular Acceleration : Joint 5
20. Angular Acceleration : Joint 6
21. Torque : Joint 1
22. Torque : Joint 2
23. Torque : Joint 3
24. Torque : Joint 4
25. Torque : Joint 5
26. Torque : Joint 6
27. TCP (Tool Center Position) Position Cartesian
28. Orientation of TCP
29. Velocity (X - Cartesian)
30. Velocity (Y - Cartesian)
31. Velocity (Z - Cartesian)
32. Angular Velocity (rx)
30. Angular Velocity (ry)
31. Angular Velocity (rz)
32. Emergency Stop
33. Gripper Openness Position

MTConnect
---------
For more information on the MTConnect standard and the dataitems included within the standard please visit
http://www.mtconnect.org/

Universal Robot 5e
---------
The UR5e is a 6-DOF industrial collaborative robot. This project is not affiliated with Universal Robots. Please visit
[http://www.pocketnc.com/](https://www.universal-robots.com/products/ur5e/)
