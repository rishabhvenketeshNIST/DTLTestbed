
class UR_State {
  public double tcp_x, tcp_y, tcp_z;
  //public double tcp_rot_ax, tcp_rot_ay, tcp_rot_az, tcp_rot_angle;
  public double[] tcp_rot = new double[4]; // x, y, z, w
  public double[] q = new double[6]; // joint positions
  public double[] w = new double[6]; // joint velocities
  public double[] a = new double[6]; // joint accelerations
  public double[] t = new double[6]; // joint torques
  public double gq;
  public UR_State() {}
  
  public UR_State(UR_State src) {
    tcp_x = src.tcp_x;
    tcp_y = src.tcp_y;
    tcp_z = src.tcp_z;
    System.arraycopy(src.tcp_rot, 0, tcp_rot, 0, tcp_rot.length);
    System.arraycopy(src.q, 0, q, 0, q.length);
    System.arraycopy(src.w, 0, w, 0, w.length);
    System.arraycopy(src.a, 0, a, 0, a.length);
    System.arraycopy(src.t, 0, t, 0, t.length);
    gq = src.gq;
  }
}

UR_State extractStateFromPlayback(SamplePlayback pb, UR_State s) {
  if (pb == null) return s;
  if (s == null) s = new UR_State();
  for(int i = 0; i < s.q.length; i++) {
    s.q[i] = pb.state[i+0]*Math.PI/180.0;
  }
  for(int i = 0; i < s.w.length; i++) {
    s.w[i] = pb.state[i+6]*Math.PI/180.0;
  }
  for(int i = 0; i < s.a.length; i++) {
    s.a[i] = pb.state[i+12]*Math.PI/180.0;
  }
  for(int i = 0; i < s.t.length; i++) {
    s.t[i] = pb.state[i+19];
  }
  // Gripper states
  // pb.state[24]
  // pb.state[25]
  s.tcp_x = pb.state[25]*0.001;
  s.tcp_y = pb.state[26]*0.001;
  s.tcp_z = pb.state[27]*0.001;
  // convert rotation format
  // create quaternion from axis-angle:
  double ax = 0, ay = 0, az = 0;
  ax = pb.state[31];
  ay = pb.state[32];
  az = pb.state[33];
  double a_len = Math.sqrt(ax*ax + ay*ay + az*az);
  if (a_len > 0.0) {
    ax /= a_len;
    ay /= a_len;
    az /= a_len;
  }
  double[] quat = quat_from_axis_angle(ax, ay, az, a_len*Math.PI/180.0);
  //PMatrix3D rot = new PMatrix3D();
  //rot.rotateZ((float) (pb.state[34]*Math.PI/180.0));
  //rot.rotateY((float) (pb.state[33]*Math.PI/180.0));
  //rot.rotateX((float) (pb.state[32]*Math.PI/180.0));
  //double[] quat = quat_from_mat(rot);
  System.arraycopy(quat, 0, s.tcp_rot, 0, quat.length);
  s.gq = (1-pb.state[18])*0.8248668046333418;
  return s;
}

SampleSequence extractUR5eSamples(XML[] components, String componentId, String sampleType, String sampleId) {
  XML component = findElementWithAttributeValue(components, "componentId", componentId);
  if (component == null) {
    return new SampleSequence(null, sampleType, sampleId); // sequence contains no data but retains metadata
  };
  XML samples = component.getChild("Samples");
  return new SampleSequence(samples, sampleType, sampleId);
}

SampleSequence[] extractUR5e3DSamples(XML[] components, String componentId, String sampleType, String sampleId) {
  XML component = findElementWithAttributeValue(components, "componentId", componentId);
  if (component == null) {
    return flatten3DSampleSequence(null, sampleType, sampleId);
  };
  XML samples = component.getChild("Samples");
  return flatten3DSampleSequence(samples, sampleType, sampleId);
}

// extracts UR5e sequence data from an MTConnect XML document.
// returns null if the document does not have a device matching devicename.
SampleSequence[] extractUR5eData(XML doc, String devicename) {
  // Find ur5e device stream
  XML streams_parent = doc.getChild("Streams");
  if (streams_parent == null) return null;
  XML[] streams = streams_parent.getChildren("DeviceStream");
  XML ur5e_device = findElementWithAttributeValue(streams, "uuid", devicename);
  if (ur5e_device == null) return null;
  // Extract data for each joint position. Do not fail if any data is missing.
  XML[] components = ur5e_device.getChildren("ComponentStream");
  ArrayList<SampleSequence> ur_seq = new ArrayList<SampleSequence>();
  // 0
  ur_seq.add(extractUR5eSamples(components, "a01", "Angle", "angle_j1"));
  ur_seq.add(extractUR5eSamples(components, "a02", "Angle", "angle_j2"));
  ur_seq.add(extractUR5eSamples(components, "a03", "Angle", "angle_j3"));
  ur_seq.add(extractUR5eSamples(components, "a04", "Angle", "angle_j4"));
  ur_seq.add(extractUR5eSamples(components, "a05", "Angle", "angle_j5"));
  ur_seq.add(extractUR5eSamples(components, "a06", "Angle", "angle_j6"));
  // 6
  ur_seq.add(extractUR5eSamples(components, "a01", "AngularVelocity", "vel_j1"));
  ur_seq.add(extractUR5eSamples(components, "a02", "AngularVelocity", "vel_j2"));
  ur_seq.add(extractUR5eSamples(components, "a03", "AngularVelocity", "vel_j3"));
  ur_seq.add(extractUR5eSamples(components, "a04", "AngularVelocity", "vel_j4"));
  ur_seq.add(extractUR5eSamples(components, "a05", "AngularVelocity", "vel_j5"));
  ur_seq.add(extractUR5eSamples(components, "a06", "AngularVelocity", "vel_j6"));
  // 12
  ur_seq.add(extractUR5eSamples(components, "a01", "AngularAcceleration", "acc_j1"));
  ur_seq.add(extractUR5eSamples(components, "a02", "AngularAcceleration", "acc_j2"));
  ur_seq.add(extractUR5eSamples(components, "a03", "AngularAcceleration", "acc_j3"));
  ur_seq.add(extractUR5eSamples(components, "a04", "AngularAcceleration", "acc_j4"));
  ur_seq.add(extractUR5eSamples(components, "a05", "AngularAcceleration", "acc_j5"));
  ur_seq.add(extractUR5eSamples(components, "a06", "AngularAcceleration", "acc_j6"));
  // 18
  ur_seq.add(extractUR5eSamples(components, "g_1", "Openness", "gripper_pos"));
  // 19
  ur_seq.add(extractUR5eSamples(components, "a01", "Torque", "tor_j1"));
  ur_seq.add(extractUR5eSamples(components, "a02", "Torque", "tor_j2"));
  ur_seq.add(extractUR5eSamples(components, "a03", "Torque", "tor_j3"));
  ur_seq.add(extractUR5eSamples(components, "a04", "Torque", "tor_j4"));
  ur_seq.add(extractUR5eSamples(components, "a05", "Torque", "tor_j5"));
  ur_seq.add(extractUR5eSamples(components, "a06", "Torque", "tor_j6"));
  // 25
  ur_seq.addAll(Arrays.asList(extractUR5e3DSamples(components, "g_1", "PositionCartesian", "posit_tcp")));
  ur_seq.add(extractUR5eSamples(components, "g_1", "Velocity", "vel_x"));
  ur_seq.add(extractUR5eSamples(components, "g_1", "Velocity", "vel_y"));
  ur_seq.add(extractUR5eSamples(components, "g_1", "Velocity", "vel_z"));
  // 31
  ur_seq.addAll(Arrays.asList(extractUR5e3DSamples(components, "g_1", "Orientation", "orient_tcp")));
  ur_seq.add(extractUR5eSamples(components, "g_1", "AngularVelocity", "ang_vel_rx"));
  ur_seq.add(extractUR5eSamples(components, "g_1", "AngularVelocity", "ang_vel_ry"));
  ur_seq.add(extractUR5eSamples(components, "g_1", "AngularVelocity", "ang_vel_rz"));
  
  SampleSequence[] seq_arr = new SampleSequence[ur_seq.size()];
  ur_seq.toArray(seq_arr);
  return seq_arr;
}
