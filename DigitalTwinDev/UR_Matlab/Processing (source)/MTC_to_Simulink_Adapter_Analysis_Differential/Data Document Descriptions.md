# 2023-7-7_13-17-2
- Created after confirming that real-time data transfer is working
- Assumes angles from MTConnect were Euler angles
- Assumes angles from MATLAB were correct
- Compares data points with wildly different timestamps
	- Known because error decreases over time as MATLAB catches up to playback

# 2023-7-7_13-52-8
- Corrected angle measurement from MTConnect
	- Angles are actually angle-axis, but reported as Euler
- Still comparing data from different timestamps,
  but the simulation happened to not be delayed,
  so the additional error is not as pronounced.

# 2023-7-10_10-46-26
- Data points of timestamps similar to the millisecond are compared,
  but many data points are double-counted because of a bug.
- Showcases the effects of freezing the MATLAB simulation:
  MATLAB's reported values do not line up with their timestamps,
  causing large error spikes. However, the error returns to normal
  as MATLAB catches up.
- Uses a different method of measuring the angle between quaternions,
  which is the metric used for "angle error". This method returns a signed
  angle value with the smallest possible magnitude (for example, uses -1 instead of 359 degrees)
  instead of some angle value with varying magnitude.
  Upon reflection, this value should be unsigned for an absolute value of error.

# 2023-7-10_11-19-27
- Fixes a data race in the program. Tested to see if it impacted the data. It did not.

# 2023-7-10_12-25-53
- Fixes the bug where data points of the same timestamp are considered multiple times.
  This results in the included data points being only ones for which, at that timestamp,
  a data point exists for both the incoming real-life data and the simulation data.
- Angle error measurements are still signed, which needs to be fixed.

# 2023-7-10_12-59-8
- Fixes angle error measurements being signed.
  They are now reported as absolute values.
- I noticed a bug where the "at that timestamp, a data point exists for both" was too strict,
  leading to the analysis skipping a bunch of data points.

# 2023-7-10_13-10-52
- Attempts to fix the "data point must exist at both timestamps" bug
  by allowing comparisons between data points up to 10 ms apart in time.
  This increases the number of data points being compared, 
  but still has an issue of inconsistent sample rates,
  and of course compares data from differing timestamps to a degree.
  
# 2023-7-11_8-48-18
- Fixes the "data point must exist at both timestamps" bug
  by doing two things:
  - A master "analysis time" variable is used to filter out data points.
    Data points which occurred at or before the master time are discarded.
    After a round of data processing, the master time is updated to be the earliest time
    of the next data points from the real data and sim data.
    It's like a cursor that moves to the next closest data point of the two datasets in time,
    but compares the next data point of both data sets.
  - Retains only millisecond precision from datapoint timestamps to better detect when data is associated in time.
    This works especially well because MATLAB is sent timestamps in this form, so doing this conversion will make
    certain timestamps between MATLAB and real life exactly equal, and thus will be discarded in the same iteration.

# 2023-7-11_9-40-12
- Adds sending joint velocities and accelerations to MATLAB for smoother movement.
  The simulation looks smoother, and the error in the data also appears smoother (less spikes than usual).
  
# 2023-7-12_14-4-4
- Fixes bug where joint torques were not being read correctly from MTConnect
- Also modified the MATLAB simulation to include some arbitrary joint friction, to see if that would impact its accuracy
  - It impacted joint torque errors, but not any joint kinematic errors.

# 2023-7-12_14-11-0
- Removes joint friction to compare against the previous entry
- Has unusually low TCP position and rotation error