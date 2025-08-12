ArrayList<Double> analysis = new ArrayList<>();
TreeMap<LocalDateTime, UR_State> real_states = new TreeMap<>();
TreeMap<LocalDateTime, UR_State> sim_states = new TreeMap<>();
LocalDateTime analysis_time = LocalDateTime.MIN;
Event tcp_pos_error_event = new Event();
Event tcp_rot_error_event = new Event();
Event[] joint_error_events = new Event[6];
{
  for (int i = 0; i < joint_error_events.length; i++) {
    joint_error_events[i] = new Event();
  }
}

class TemporalData {
  final int capacity;

  List<LocalDateTime> times = new LinkedList<>();
  List<Double> q1_errs = new LinkedList<>();
  List<Double> q2_errs = new LinkedList<>();
  List<Double> q3_errs = new LinkedList<>();
  List<Double> q4_errs = new LinkedList<>();
  List<Double> q5_errs = new LinkedList<>();
  List<Double> q6_errs = new LinkedList<>();
  List<Double> tcp_dist_errs = new LinkedList<>();
  List<Double> tcp_angle_errs = new LinkedList<>();
  List<Double> gripper_angle_errs = new LinkedList<>();

  TemporalData(int capacity) {
    this.capacity = capacity;
  }

  void push(LocalDateTime time, UR_State real, UR_State sim, double tcp_dist_err, double tcp_angle_err, double gripper_angle_err) {
    while (times.size() >= capacity) {
      pop();
    }
    times.add(time);
    q1_errs.add(Math.abs(real.q[0] - sim.q[0]));
    q2_errs.add(Math.abs(real.q[1] - sim.q[1]));
    q3_errs.add(Math.abs(real.q[2] - sim.q[2]));
    q4_errs.add(Math.abs(real.q[3] - sim.q[3]));
    q5_errs.add(Math.abs(real.q[4] - sim.q[4]));
    q6_errs.add(Math.abs(real.q[5] - sim.q[5]));
    tcp_dist_errs.add(tcp_dist_err);
    tcp_angle_errs.add(tcp_angle_err);
    gripper_angle_errs.add(gripper_angle_err);
  }

  void pop() {
    if (times.size() == 0) return;
    times.remove(0);
    q1_errs.remove(0);
    q2_errs.remove(0);
    q3_errs.remove(0);
    q4_errs.remove(0);
    q5_errs.remove(0);
    q6_errs.remove(0);
    tcp_dist_errs.remove(0);
    tcp_angle_errs.remove(0);
    gripper_angle_errs.remove(0);
  }
}

TemporalData timedata;

int getIndexAfterTime(List<LocalDateTime> times, LocalDateTime target) {
  int i = 0;
  for (LocalDateTime t : times) {
    if (target.compareTo(t) <= 0) {
      break;
    }
    i++;
  }
  return i;
}

void detectErrorOverThresholdForTime(List<LocalDateTime> times, List<Double> data, double threshold, double duration, Event errorEvent) {
  LocalDateTime backwardsInTime = analysis_time.minusNanos((long) (1e9*duration));
  int startIndex = getIndexAfterTime(times, backwardsInTime);
  int endIndex = times.size();
  int dataLength = endIndex-startIndex;
  LocalDateTime dataStartTime = times.get(startIndex);
  // Make sure that we aren't measuring for too short of a duration to be statistically significant
  float secondsBetweenStartAndTargetTime = 1000f * Math.abs(toEpochMillis(backwardsInTime) - toEpochMillis(dataStartTime));
  if (startIndex < endIndex) {
    double err = 0.0;
    if (secondsBetweenStartAndTargetTime < 0.05*duration) {
      ArrayList<Double> temporal_error = new ArrayList<>(dataLength);
      Iterator<Double> err_iter = data.iterator();
      for (int i = 0; i < startIndex; i++) err_iter.next();
      err_iter.forEachRemaining((val) -> {
        temporal_error.add(val);
      }
      );
      err = median(temporal_error);
    }
    if (err > Math.abs(threshold)) {
      errorEvent.call();
    }
  }
}

void analyzeData() {
  while (true) {
    UR_State real = null, sim = null;
    if (!(real_states.isEmpty() || sim_states.isEmpty())) {
      Map.Entry<LocalDateTime, UR_State> real_first = real_states.firstEntry();
      Map.Entry<LocalDateTime, UR_State> sim_first = sim_states.firstEntry();
      real = real_first.getValue();
      sim = sim_first.getValue();
      // Convert time to millisecond precision to better detect overlapping timesteps
      LocalDateTime real_time = fromEpochMillis(toEpochMillis(real_first.getKey()));
      LocalDateTime sim_time = fromEpochMillis(toEpochMillis(sim_first.getKey()));
      analysis_time = min(real_time, sim_time);
      if (analysis_time.compareTo(real_time) >= 0) {
        synchronized(real_states) {
          real_states.remove(real_first.getKey());
        }
      }
      if (analysis_time.compareTo(sim_time) >= 0) {
        synchronized(sim_states) {
          sim_states.remove(sim_first.getKey());
        }
      }
    }
    if (real == null || sim == null) {
      break;
    }
    PVector real_tcp = new PVector((float) real.tcp_x, (float)  real.tcp_y, (float)  real.tcp_z);
    PVector sim_tcp = new PVector((float) sim.tcp_x, (float)  sim.tcp_y, (float)  sim.tcp_z);
    double dist = PVector.dist(real_tcp, sim_tcp);
    double angle = quat_angle_between(real.tcp_rot, sim.tcp_rot);
    //println(angle);
    //double[] real_aa = quat_to_axis_angle(real.tcp_rot);
    //double[] sim_aa = quat_to_axis_angle(sim.tcp_rot);
    //println(String.format("Real axis-angle: %.2f, %.2f, %.2f; %.2f | Sim axis-angle: %.2f, %.2f, %.2f; %.2f", real_aa[0], real_aa[1], real_aa[2], real_aa[3], sim_aa[0], sim_aa[1], sim_aa[2], sim_aa[3]));
    double g_angle = Math.abs(real.gq - sim.gq);
    analysis.clear();
    analysis.add(dist);
    analysis.add(angle);
    for (int i = 0; i < real.t.length; i++) {
      analysis.add(Math.abs(real.t[i] - sim.t[i]));
    }
    analysis.add(g_angle);

    timedata.push(analysis_time, real, sim, dist, angle, g_angle);

    detectErrorOverThresholdForTime(timedata.times, timedata.tcp_dist_errs, TCP_POS_ERROR_THRESHOLD, TCP_POS_ERROR_DURATION, tcp_pos_error_event);
    detectErrorOverThresholdForTime(timedata.times, timedata.tcp_angle_errs, TCP_ROT_ERROR_THRESHOLD, TCP_ROT_ERROR_DURATION, tcp_rot_error_event);
    detectErrorOverThresholdForTime(timedata.times, timedata.q1_errs, JOINT_ERROR_THRESHOLD, JOINT_ERROR_DURATION, joint_error_events[0]);
    detectErrorOverThresholdForTime(timedata.times, timedata.q2_errs, JOINT_ERROR_THRESHOLD, JOINT_ERROR_DURATION, joint_error_events[1]);
    detectErrorOverThresholdForTime(timedata.times, timedata.q3_errs, JOINT_ERROR_THRESHOLD, JOINT_ERROR_DURATION, joint_error_events[2]);
    detectErrorOverThresholdForTime(timedata.times, timedata.q4_errs, JOINT_ERROR_THRESHOLD, JOINT_ERROR_DURATION, joint_error_events[3]);
    detectErrorOverThresholdForTime(timedata.times, timedata.q5_errs, JOINT_ERROR_THRESHOLD, JOINT_ERROR_DURATION, joint_error_events[4]);
    detectErrorOverThresholdForTime(timedata.times, timedata.q6_errs, JOINT_ERROR_THRESHOLD, JOINT_ERROR_DURATION, joint_error_events[5]);

    if (dataTable != null) {
      synchronized(dataTable) {
        writeDataRow(dataTable, analysis_time, real, sim, analysis);
      }
    }
  } // while(true)
}

class ErrorReporter implements Runnable {
  private float threshold, duration, cooldown = 0;
  private String error_name, units;
  public final Queue<String> errors;
  public ErrorReporter(String errname, float thresh, float duration, String units) {
    error_name = errname;
    threshold = thresh;
    this.duration = duration;
    this.units = units;
    errors = new LinkedList<String>();
  }
  public void cooldown(float dt) {
    cooldown -= dt;
  }
  public void run() {
    if (cooldown <= 0) {
      cooldown = duration;
      StringBuilder sb = new StringBuilder();
      sb.append(analysis_time);
      sb.append(": ");
      sb.append(error_name);
      sb.append(" median has been over ");
      sb.append(threshold);
      sb.append(" ");
      sb.append(units);
      sb.append(" for ");
      sb.append(duration);
      sb.append(" seconds.");
      errors.offer(sb.toString());
    }
  }
}

Table createDataTable() {
  Table t = new Table();
  t.addColumn("time", Table.STRING);
  t.addColumn("q1", Table.DOUBLE);
  t.addColumn("q2", Table.DOUBLE);
  t.addColumn("q3", Table.DOUBLE);
  t.addColumn("q4", Table.DOUBLE);
  t.addColumn("q5", Table.DOUBLE);
  t.addColumn("q6", Table.DOUBLE);
  t.addColumn("w1", Table.DOUBLE);
  t.addColumn("w2", Table.DOUBLE);
  t.addColumn("w3", Table.DOUBLE);
  t.addColumn("w4", Table.DOUBLE);
  t.addColumn("w5", Table.DOUBLE);
  t.addColumn("w6", Table.DOUBLE);
  t.addColumn("a1", Table.DOUBLE);
  t.addColumn("a2", Table.DOUBLE);
  t.addColumn("a3", Table.DOUBLE);
  t.addColumn("a4", Table.DOUBLE);
  t.addColumn("a5", Table.DOUBLE);
  t.addColumn("a6", Table.DOUBLE);
  t.addColumn("t1", Table.DOUBLE);
  t.addColumn("t2", Table.DOUBLE);
  t.addColumn("t3", Table.DOUBLE);
  t.addColumn("t4", Table.DOUBLE);
  t.addColumn("t5", Table.DOUBLE);
  t.addColumn("t6", Table.DOUBLE);
  t.addColumn("gq", Table.DOUBLE);
  t.addColumn("tcp_x", Table.DOUBLE);
  t.addColumn("tcp_y", Table.DOUBLE);
  t.addColumn("tcp_z", Table.DOUBLE);
  t.addColumn("tcp_rot_x", Table.DOUBLE);
  t.addColumn("tcp_rot_y", Table.DOUBLE);
  t.addColumn("tcp_rot_z", Table.DOUBLE);
  t.addColumn("tcp_rot_w", Table.DOUBLE);
  t.addColumn("s_q1", Table.DOUBLE);
  t.addColumn("s_q2", Table.DOUBLE);
  t.addColumn("s_q3", Table.DOUBLE);
  t.addColumn("s_q4", Table.DOUBLE);
  t.addColumn("s_q5", Table.DOUBLE);
  t.addColumn("s_q6", Table.DOUBLE);
  t.addColumn("s_w1", Table.DOUBLE);
  t.addColumn("s_w2", Table.DOUBLE);
  t.addColumn("s_w3", Table.DOUBLE);
  t.addColumn("s_w4", Table.DOUBLE);
  t.addColumn("s_w5", Table.DOUBLE);
  t.addColumn("s_w6", Table.DOUBLE);
  t.addColumn("s_a1", Table.DOUBLE);
  t.addColumn("s_a2", Table.DOUBLE);
  t.addColumn("s_a3", Table.DOUBLE);
  t.addColumn("s_a4", Table.DOUBLE);
  t.addColumn("s_a5", Table.DOUBLE);
  t.addColumn("s_a6", Table.DOUBLE);
  t.addColumn("s_t1", Table.DOUBLE);
  t.addColumn("s_t2", Table.DOUBLE);
  t.addColumn("s_t3", Table.DOUBLE);
  t.addColumn("s_t4", Table.DOUBLE);
  t.addColumn("s_t5", Table.DOUBLE);
  t.addColumn("s_t6", Table.DOUBLE);
  t.addColumn("s_gq", Table.DOUBLE);
  t.addColumn("s_tcp_x", Table.DOUBLE);
  t.addColumn("s_tcp_y", Table.DOUBLE);
  t.addColumn("s_tcp_z", Table.DOUBLE);
  t.addColumn("s_tcp_rot_x", Table.DOUBLE);
  t.addColumn("s_tcp_rot_y", Table.DOUBLE);
  t.addColumn("s_tcp_rot_z", Table.DOUBLE);
  t.addColumn("s_tcp_rot_w", Table.DOUBLE);
  t.addColumn("tcp_dist_err", Table.DOUBLE);
  t.addColumn("tcp_angle_err", Table.DOUBLE);
  t.addColumn("t1_err", Table.DOUBLE);
  t.addColumn("t2_err", Table.DOUBLE);
  t.addColumn("t3_err", Table.DOUBLE);
  t.addColumn("t4_err", Table.DOUBLE);
  t.addColumn("t5_err", Table.DOUBLE);
  t.addColumn("t6_err", Table.DOUBLE);
  return t;
}

void writeDataRow(Table t, LocalDateTime timestamp, UR_State real, UR_State sim, ArrayList<Double> analysis) {
  TableRow r = t.addRow();
  r.setString("time", timestamp.toString());
  for (int i = 0; i < real.q.length; i++) {
    r.setDouble("q" + (i+1), real.q[i]);
  }
  for (int i = 0; i < real.w.length; i++) {
    r.setDouble("w" + (i+1), real.w[i]);
  }
  for (int i = 0; i < real.a.length; i++) {
    r.setDouble("a" + (i+1), real.a[i]);
  }
  for (int i = 0; i < real.t.length; i++) {
    r.setDouble("t" + (i+1), real.t[i]);
  }
  r.setDouble("gq", real.gq);
  r.setDouble("tcp_x", real.tcp_x);
  r.setDouble("tcp_y", real.tcp_y);
  r.setDouble("tcp_z", real.tcp_z);
  r.setDouble("tcp_rot_x", real.tcp_rot[0]);
  r.setDouble("tcp_rot_y", real.tcp_rot[1]);
  r.setDouble("tcp_rot_z", real.tcp_rot[2]);
  r.setDouble("tcp_rot_w", real.tcp_rot[3]);

  for (int i = 0; i < sim.q.length; i++) {
    r.setDouble("s_q" + (i+1), sim.q[i]);
  }
  for (int i = 0; i < sim.w.length; i++) {
    r.setDouble("s_w" + (i+1), sim.w[i]);
  }
  for (int i = 0; i < sim.a.length; i++) {
    r.setDouble("s_a" + (i+1), sim.a[i]);
  }
  for (int i = 0; i < sim.t.length; i++) {
    r.setDouble("s_t" + (i+1), sim.t[i]);
  }
  r.setDouble("s_gq", sim.gq);
  r.setDouble("s_tcp_x", sim.tcp_x);
  r.setDouble("s_tcp_y", sim.tcp_y);
  r.setDouble("s_tcp_z", sim.tcp_z);
  r.setDouble("s_tcp_rot_x", sim.tcp_rot[0]);
  r.setDouble("s_tcp_rot_y", sim.tcp_rot[1]);
  r.setDouble("s_tcp_rot_z", sim.tcp_rot[2]);
  r.setDouble("s_tcp_rot_w", sim.tcp_rot[3]);

  r.setDouble("tcp_dist_err", analysis.get(0));
  r.setDouble("tcp_angle_err", analysis.get(1));
  for (int i = 0; i < 6; i++) {
    r.setDouble("t" + (i+1) + "_err", analysis.get(i+2));
  }
}
