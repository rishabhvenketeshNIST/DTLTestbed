// UI
String[] views = {"Incoming Data", "Real State", "Sim State", "Analysis"};
int view = 0;

Mode infodump = new Mode() {
  void draw() {
    ArrayList<String> lines = new ArrayList<>();
    String viewtitles = "Press number to view: ";
    for (int i = 0; i < views.length; i++) {
      viewtitles += (i+1) + ". " + views[i];
      if (i < views.length - 1) viewtitles += ", ";
    }
    lines.add(viewtitles);
    lines.add("Local server IP: " + Server.ip());
    lines.add(String.format("Send rate: %.1f Hz, Time scale: %.2f", frameRate, timeScale));
    lines.add(playing ? "Playing" : "Paused");
    lines.add(String.format("Playback time: %s", playback.time.toString()));
    if (view == 0) {
      lines.add("Sync Data (id [index]: value):");
      SampleSequence[] seqs = playback.getCurrentSequences();
      for (int i = 0; i < playback.state.length; i++) {
        int time_i = playback.time_array_indices[i];
        double d = playback.state[i];
        String dataItemId = "unknown";
        if (seqs != null) {
          dataItemId = seqs[i].dataItemId;
        }
        lines.add(String.format("%s [%d]: %.2f", dataItemId, time_i, d));
      }
      lines.add("Queue size: " + playback.queue.size());
    } else if (view == 1) {
      lines.add("");
      //lines.add("Joint positions:");
      for (int i = 0; i < realstate.q.length; i++) {
        lines.add("q" + (i+1) + ": " + realstate.q[i]);
      }
      //lines.add("Joint velocities:");
      for (int i = 0; i < realstate.w.length; i++) {
        lines.add("w" + (i+1) + ": " + realstate.w[i]);
      }
      //lines.add("Joint accelerations:");
      for (int i = 0; i < realstate.a.length; i++) {
        lines.add("a" + (i+1) + ": " + realstate.a[i]);
      }
      //lines.add("Joint torques:");
      for (int i = 0; i < simstate.t.length; i++) {
        lines.add("t" + (i+1) + ": " + realstate.t[i]);
      }
      lines.add("Gripper servo: " + realstate.gq);
      lines.add("TCP x: " + realstate.tcp_x);
      lines.add("TCP y: " + realstate.tcp_y);
      lines.add("TCP z: " + realstate.tcp_z);
      lines.add("TCP rot qx: " + realstate.tcp_rot[0]);
      lines.add("TCP rot qy: " + realstate.tcp_rot[1]);
      lines.add("TCP rot qz: " + realstate.tcp_rot[2]);
      lines.add("TCP rot qw: " + realstate.tcp_rot[3]);
      //lines.add("TCP rot mag: " + quat_mag(realstate.tcp_rot));
    } else if (view == 2) {
      lines.add("Sim Timestamp: " + ur_sim_time);
      //lines.add("Joint positions:");
      for (int i = 0; i < simstate.q.length; i++) {
        lines.add("q" + (i+1) + ": " + simstate.q[i]);
      }
      //lines.add("Joint velocities:");
      for (int i = 0; i < simstate.w.length; i++) {
        lines.add("w" + (i+1) + ": " + simstate.w[i]);
      }
      //lines.add("Joint accelerations:");
      for (int i = 0; i < simstate.a.length; i++) {
        lines.add("a" + (i+1) + ": " + simstate.a[i]);
      }
      //lines.add("Joint torques:");
      for (int i = 0; i < simstate.t.length; i++) {
        lines.add("t" + (i+1) + ": " + simstate.t[i]);
      }
      lines.add("Gripper servo: " + simstate.gq);
      lines.add("TCP x: " + simstate.tcp_x);
      lines.add("TCP y: " + simstate.tcp_y);
      lines.add("TCP z: " + simstate.tcp_z);
      lines.add("TCP rot qx: " + simstate.tcp_rot[0]);
      lines.add("TCP rot qy: " + simstate.tcp_rot[1]);
      lines.add("TCP rot qz: " + simstate.tcp_rot[2]);
      lines.add("TCP rot qw: " + simstate.tcp_rot[3]);
      //lines.add("TCP rot mag: " + quat_mag(simstate.tcp_rot));
    } else if (view == 3) {
      lines.add("Sim Timestamp: " + ur_sim_time);
      lines.add("Analysis Timestamp: " + analysis_time);
      if (analysis.size() == 0) {
        lines.add("No data yet");
      } else {
        lines.add("TCP distance error: " + analysis.get(0));
        lines.add("TCP angle error: " + analysis.get(1)*180.0/Math.PI);
        lines.add("Gripper servo error: " + analysis.get(2)*180.0/Math.PI);
        for (int i = 0; i < 6; i++) {
          lines.add("t" + (i+1) + " err: " + analysis.get(i+3));
        }
      }
    }


    fill(255);
    float ly = 0;
    for (String s : lines) {
      text(s, 0, ly);
      ly += 15;
    }
    ly = 0;
  }
  
  void mouseEvent(MouseEvent e) {
    if(e.getAction() == MouseEvent.WHEEL) {
      stepTimeScale(-(e.isControlDown() ? e.getCount() : e.getCount()*10));
    }
    if(e.getAction() == MouseEvent.PRESS) {
      if (e.getButton() == CENTER) {
        timeScale = 1.0;
      }
    }
  }

  void keyPressed() {
    if (keyCode == UP) {
      stepTimeScale(1);
    }
    if (keyCode == DOWN) {
      stepTimeScale(-1);
    }
    if (key >= '1' && key <= '9') {
      int newview = Integer.parseInt(""+key)-1;
      if (newview >= 0 && newview < views.length) view = newview;
    }
  }
};
