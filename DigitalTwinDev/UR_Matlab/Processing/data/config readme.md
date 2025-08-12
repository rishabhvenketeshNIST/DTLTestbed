# MTC to Simulink Adapter Options

Options are in JSON format with the following keys:

- MTC_ip (string): The ip address of the MTConnect agent
- MTC_port (int): The port of the MTConnect agent
- server_port (int): The port on which to host the local server
- send_hz (float): The rate at which data is sent through the local server
- query_interval (float): The interval between MTConnect queries
- timescale (float): Adjustment to how fast the incoming data is replayed
- autoplay (boolean): Whether to start playback when the program launches
- ur5e_uuid (string): The uuid of the ur5e robot in the MTConnect documents
- save_replay (boolean): Whether to save csv files containing raw replay data
- save_replay_interval (float): How often to flush the replay data to a file
- time_data_duration (float): How long data will be stored for analysis before being discarded
- tcp_pos_error_threshold (float): How large the TCP position error must be to register as problematic
- tcp_pos_error_duration (float): TCP position error is analyzed over this time period. Cannot exceed time_data_duration.
- tcp_rot_error_threshold (float): How large the TCP rotation error must be to register as problematic
- tcp_rot_error_duration (float): TCP rotation error is analyzed over this time period. Cannot exceed time_data_duration.
- tcp_joint_error_threshold (float): Etc.
- tcp_joint_error_duration (float): Etc.


- dummy (boolean): Replay the dummy file instead of queries from the agent
- dummy_files (array of strings): Files containing valid MTConnect xml to use instead of querying the agent
- MTC_dump (boolean): Whether to dump all incoming MTConnect queries to files