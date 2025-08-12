// 1 timestamp, 6 joint positions, 6 joint velocities, 6 joint accelerations, 1 gripper joint position state
final int MATLAB_PACKET_SIZE = 20; // all entries have a size of 8 bytes

byte[] createSimulinkMessage(LocalDateTime timestamp, double[] joint_states) {
  ByteBuffer packet = ByteBuffer.allocate(8*MATLAB_PACKET_SIZE);
  packet.order(ByteOrder.LITTLE_ENDIAN);
  // Use the epoch milliseconds as the data ID so the response from MATLAB is marked with a timestamp directly (useful for associating data between real and sim)
  packet.putLong(toEpochMillis(timestamp));
  // joint, velocities, accelerations
  for (int i = 0; i < 18; i++) {
    double target = joint_states[i];
    packet.putDouble(target*Math.PI/180.0);
  }
  packet.putDouble(joint_states[18]);
  return packet.array();
}

void readSimulinkResponse(Client c) {
  final int MSG_SIZE = 264;
  ByteBuffer buf = ByteBuffer.allocate(MSG_SIZE);
  buf.order(ByteOrder.LITTLE_ENDIAN);
  buf.put(c.readBytes(MSG_SIZE));
  long timestamp_millis = buf.getLong(0);
  // timestamp of -1 means data is not ready to publish
  if (timestamp_millis != -1) {
    simstate.tcp_x = buf.getDouble(8);
    simstate.tcp_y = buf.getDouble(16);
    simstate.tcp_z = buf.getDouble(24);
    // MATLAB has quaternions in w, x, y, z order, but we want x, y, z, w
    // But, now we recieve axis, angle
    //simstate.tcp_rot[3] = buf.getDouble(32);
    //simstate.tcp_rot[0] = buf.getDouble(40);
    //simstate.tcp_rot[1] = buf.getDouble(48);
    //simstate.tcp_rot[2] = buf.getDouble(56);
    double ax = buf.getDouble(32);
    double ay = buf.getDouble(40);
    double az = buf.getDouble(48);
    double angle = buf.getDouble(56);
    simstate.tcp_rot = quat_from_axis_angle(ax, ay, az, angle);
    
    int addr = 64;
    for (int i = 0; i < simstate.q.length; i++) {
      simstate.q[i] = buf.getDouble(addr);
      addr += 8;
    }
    for (int i = 0; i < simstate.w.length; i++) {
      simstate.w[i] = buf.getDouble(addr);
      addr += 8;
    }
    for (int i = 0; i < simstate.a.length; i++) {
      simstate.a[i] = buf.getDouble(addr);
      addr += 8;
    }
    for (int i = 0; i < simstate.t.length; i++) {
      simstate.t[i] = buf.getDouble(addr);
      addr += 8;
    }
    simstate.gq = buf.getDouble(addr);
    LocalDateTime timestamp = fromEpochMillis(timestamp_millis);
    //println("Recieved TCP [" + timestamp.toString() + "]: " + tcp_x + ", " + tcp_y + ", " + tcp_z + "; Axis-angle: " + tcp_rot_x + ", " + tcp_rot_y + ", " + tcp_rot_z + ", " + tcp_rot_angle);
    ur_sim_time = timestamp;
    synchronized(sim_states) {
      sim_states.put(ur_sim_time, new UR_State(simstate));
    }
    //ur_tcp_pos.set((float) tcp_x, (float)  tcp_y, (float) tcp_z);
    //ur_tcp_rot_axis.set((float) tcp_rot_x, (float) tcp_rot_y, (float) tcp_rot_z);
    //ur_tcp_rot_angle = tcp_rot_angle;
  }
}
