final int PRIMARY_COL = color(220, 220, 255);
final int Q_COL = color(80, 208, 242);
final int W_COL = color(4, 216, 4);
final int A_COL = color(255, 255, 75);
final int T_COL = color(255, 169, 30);
final int GRIP_COL = color(200, 50, 50);
PImage ur5e_img;
boolean show_values = false;
boolean stats_mode = false;
Mode menu = new Mode() {
  UR_State ur_real_display_state, ur_sim_display_state;

  ModeGUI ui = new ModeGUI();

  int joint_value_type = 0; // 0 = q, 1 = w, 2 = a, 3 = t

  TextButton general_mode_button, stats_mode_button;
  TextButton info_label;
  Button real_display, sim_display, stats_display;
  Button graph_display;
  TextButton q_button, w_button, a_button, t_button;
  TextButton real_time_label, sim_time_label;
  TextButton show_values_button, play_button, reset_time_button;
  TextButton events_label;
  ArrayList<String> events = new ArrayList<>();
  int events_scroll = 0;
  ArrayList<ErrorReporter> reporters = new ArrayList<>();

  void setup() {
    ur5e_img = loadImage("UR5e.png");
    general_mode_button = new TextButton("General Info") {
      {
        align.setAnchor(0.25, 0).setAlign(CENTER, TOP).setScale(0.5, 0).setMinSize(0, 25);
      }
      void press(MouseEvent e) {
        stats_mode = false;
      }
      void draw(PGraphics c) {
        bgCol = stats_mode ? PRIMARY_COL : color(255);
        outlineCol = stats_mode ? color(0) : color(255, 0);
        super.draw(c);
      }
    };
    stats_mode_button = new TextButton("Statistics") {
      {
        align.setAnchor(0.75, 0).setAlign(CENTER, TOP).setScale(0.5, 0).setMinSize(0, 25);
      }
      void press(MouseEvent e) {
        stats_mode = true;
      }
      void draw(PGraphics c) {
        bgCol = !stats_mode ? PRIMARY_COL : color(255);
        outlineCol = !stats_mode ? color(0) : color(255, 0);
        super.draw(c);
      }
    };
    info_label = new TextButton() {
      {
        setTextAlign(LEFT, CENTER);
        outlineCol = color(255, 0);
        align.setAnchor(0, 0).setAlign(LEFT, TOP).setOffset(0, 25).setScale(1, 0).setMinSize(0, 25);
      }
      void draw(PGraphics c) {
        text = String.format("Server IP: %s, Timestamp: %s, Send rate: %.2f Hz, Data queue: %d", Server.ip(), analysis_time.toString(), frameRate, playback.queue.size());
        super.draw(c);
      }
    };

    real_display = new Button() {
      Rect r = new Rect();
      boolean enabled = true;
      boolean contains(float mx, float my) {
        return r.contains(mx, my);
      }
      boolean isEnabled() {
        return enabled;
      }
      void setEnabled(boolean e) {
        enabled = e;
      }
      void draw(PGraphics c) {
        r.x = 0;
        r.y = 50;
        r.w = c.width*0.5;
        r.h = c.height - r.y - 125;
        pushStyle();
        fill(255);
        stroke(0);
        rectMode(CORNER);
        //r.draw(c);
        textAlign(LEFT, TOP);
        fill(0);
        textSize(14);
        text("Real Robot", r.x+2, r.y, r.w-4, r.h);
        popStyle();
        UR_State state = ur_real_display_state != null ? ur_real_display_state : realstate;
        Rect centered = new Rect(r);
        centered.x += r.w*0.5;
        centered.y += r.h*0.5;
        double[] states;
        double minval = -PI, maxval = PI;
        int col = Q_COL;
        switch(joint_value_type) {
        case 0:
          states = state.q;
          break;
        case 1:
          states = state.w;
          col = W_COL;
          break;
        case 2:
          states = state.a;
          col = A_COL;
          break;
        case 3:
          states = state.t;
          minval = -100;
          maxval = 100;
          col = T_COL;
          break;
        default:
          joint_value_type = 0;
          states = state.q;
        }
        display_ur_joint_states(c, ur5e_img, centered, states, minval, maxval, state.gq, col);
      }
      void press(MouseEvent e) {
      }
      void release(MouseEvent e) {
      }
      void click(MouseEvent e) {
      }
    };
    sim_display = new Button() {
      Rect r = new Rect();
      boolean enabled = true;
      boolean contains(float mx, float my) {
        return r.contains(mx, my);
      }
      boolean isEnabled() {
        return enabled;
      }
      void setEnabled(boolean e) {
        enabled = e;
      }
      void draw(PGraphics c) {
        r.x = c.width*0.5;
        r.y = 50;
        r.w = c.width*0.5;
        r.h = c.height - r.y - 125;
        pushStyle();
        fill(255);
        stroke(0);
        rectMode(CORNER);
        //r.draw(c);
        textAlign(RIGHT, TOP);
        fill(0);
        textSize(14);
        text("Sim Robot", r.x+2, r.y, r.w-4, r.h);
        popStyle();
        UR_State state = ur_sim_display_state != null ? ur_sim_display_state : simstate;
        Rect centered = new Rect(r);
        centered.x += r.w*0.5;
        centered.y += r.h*0.5;
        double[] states;
        double minval = -PI, maxval = PI;
        int col = Q_COL;
        switch(joint_value_type) {
        case 0:
          states = state.q;
          break;
        case 1:
          states = state.w;
          col = W_COL;
          break;
        case 2:
          states = state.a;
          col = A_COL;
          break;
        case 3:
          states = state.t;
          minval = -100;
          maxval = 100;
          col = T_COL;
          break;
        default:
          joint_value_type = 0;
          states = state.q;
        }
        display_ur_joint_states(c, ur5e_img, centered, states, minval, maxval, state.gq, col);
      }
    };
    stats_display = new Button() {
      Rect r = new Rect();
      boolean enabled = true;
      boolean contains(float mx, float my) {
        return r.contains(mx, my);
      }
      boolean isEnabled() {
        return enabled;
      }
      void setEnabled(boolean e) {
        enabled = e;
      }
      void draw(PGraphics c) {
        r.x = 0;
        r.y = 50;
        r.w = c.width*0.5;
        r.h = c.height - r.y - 125;
        pushStyle();
        fill(255);
        stroke(0);
        rectMode(CORNER);
        //r.draw(c);
        textAlign(LEFT, TOP);
        fill(0);
        textSize(14);
        text("Joint Position Error", r.x+2, r.y, r.w-4, r.h);
        popStyle();
        UR_State m_realstate = ur_real_display_state; // != null ? ur_real_display_state : realstate;
        UR_State m_simstate = ur_sim_display_state; // != null ? ur_sim_display_state : simstate;
        Rect centered = new Rect(r);
        centered.x += r.w*0.5;
        centered.y += r.h*0.5;
        double[] states = new double[6];
        double minval = 0, maxval = TAU;
        int col = color(200, 69, 200);
        for (int i = 0; i < states.length; i++) {
          states[i] = Math.abs(m_realstate.q[i] - m_simstate.q[i]);
        }
        double g_err = Math.abs(m_realstate.gq - m_simstate.gq);

        display_ur_joint_states(c, ur5e_img, centered, states, minval, maxval, g_err, col);
      }
    };
    graph_display = new Button() {
      Rect r = new Rect();
      boolean enabled = true;
      boolean contains(float mx, float my) {
        return r.contains(mx, my);
      }
      boolean isEnabled() {
        return enabled;
      }
      void setEnabled(boolean e) {
        enabled = e;
      }
      void draw(PGraphics c) {
        r.x = c.width*0.5;
        r.y = 50;
        r.w = c.width*0.5;
        r.h = c.height - r.y - 125;
        pushStyle();
        fill(255);
        stroke(0);
        rectMode(CORNER);
        //r.draw(c);
        textAlign(RIGHT, TOP);
        fill(0);
        textSize(14);
        text("Error graphs", r.x+2, r.y, r.w-4, r.h);
        popStyle();
        Rect centered = new Rect(r);
        centered.x += r.w*0.5;
        centered.y += r.h*0.5;
        Rect joint_err_graph_bounds = new Rect(r.x+r.w*0.5, r.y+r.h*0.25, r.w, r.h*0.5);
        GraphInfo joint_err_graph_info = new GraphInfo().setTitle("Joint Error").setAxisLabels("Time Passed (s)", "Error (rad)")
          .setAxisLimits(-10, 0, -HALF_PI-0.001, HALF_PI+0.001).setAxisStep(1, PI/8.0).setAxisDecimals(0, 2);
        Rect joint_err_graph_data_bounds = draw_graph_body(c, joint_err_graph_bounds, joint_err_graph_info);

        ArrayList<Double> times = new ArrayList<Double>(timedata.times.size());
        for (LocalDateTime dt : timedata.times) {
          long millisdiff = toEpochMillis(dt)-toEpochMillis(analysis_time);
          double seconds = millisdiff / 1000.0d;
          times.add(seconds);
        }
        String[] axisNames = {"q1", "q2", "q3", "q4", "q5", "q6", "qg"};
        int[] colors = {
          color(255, 0, 0),
          color(255, 128, 0),
          color(255, 255, 0),
          color(0, 255, 0),
          color(0, 0, 255),
          color(255, 0, 255),
          GRIP_COL,
        };
        draw_graph_data(c, joint_err_graph_data_bounds, joint_err_graph_info, times, timedata.q1_errs, LINE, colors[0]);
        draw_graph_data(c, joint_err_graph_data_bounds, joint_err_graph_info, times, timedata.q2_errs, LINE, colors[1]);
        draw_graph_data(c, joint_err_graph_data_bounds, joint_err_graph_info, times, timedata.q3_errs, LINE, colors[2]);
        draw_graph_data(c, joint_err_graph_data_bounds, joint_err_graph_info, times, timedata.q4_errs, LINE, colors[3]);
        draw_graph_data(c, joint_err_graph_data_bounds, joint_err_graph_info, times, timedata.q5_errs, LINE, colors[4]);
        draw_graph_data(c, joint_err_graph_data_bounds, joint_err_graph_info, times, timedata.q6_errs, LINE, colors[5]);
        draw_graph_data(c, joint_err_graph_data_bounds, joint_err_graph_info, times, timedata.gripper_angle_errs, LINE, colors[6]);
        pushMatrix();
        translate(joint_err_graph_bounds.x+joint_err_graph_bounds.w*0.5-50, joint_err_graph_bounds.y-joint_err_graph_bounds.h*0.5+25);
        draw_graph_legend(c, axisNames, colors);
        popMatrix();
        
        float max_tcp_dist_err = max((float) max(timedata.tcp_dist_errs), 0.01);
        GraphInfo dist_err_info = new GraphInfo().setTitle("TCP Position Error").setAxisLabels("Time Passed (s)", "Error (m)")
          .setAxisLimits(-10, 0, 0, max_tcp_dist_err).setAxisStep(1, max_tcp_dist_err*0.1249).setAxisDecimals(0, 3);
        Rect dist_err_bounds = new Rect(r.x+r.w*0.25, r.y+r.h*0.75, r.w*0.5, r.h*0.5);
        draw_graph(c, dist_err_bounds, dist_err_info, times, timedata.tcp_dist_errs, LINE, color(255, 0, 0));
        
        float max_tcp_angle_err = max((float) max(timedata.tcp_angle_errs), PI/32.0);
        GraphInfo angle_err_info = new GraphInfo().setTitle("TCP Rotation Error").setAxisLabels("Time Passed (s)", "Error (rad)")
          .setAxisLimits(-10, 0, 0, max_tcp_angle_err).setAxisStep(1, max_tcp_angle_err*0.1249).setAxisDecimals(0, 2);
        Rect angle_err_bounds = new Rect(r.x+r.w*0.75, r.y+r.h*0.75, r.w*0.5, r.h*0.5);
        draw_graph(c, angle_err_bounds, angle_err_info, times, timedata.tcp_angle_errs, LINE, color(0, 0, 255));
      }
    };
    real_time_label = new TextButton() {
      {
        setTextAlign(LEFT, CENTER);
        align.setAnchor(0.175, 1).setOffset(0, -100).setAlign(CENTER, BOTTOM).setScale(0.35, 0).setMinSize(0, 25);
      }
      void draw(PGraphics c) {
        super.draw(c);
        Rect r = align.getCenterRect();
        pushStyle();
        fill(0);
        textAlign(textAlignX, textAlignY);
        text(" Latest: " + playback.time, r.x-r.w*0.5, r.y);
        popStyle();
      }
    };
    show_values_button = new TextButton("Show/Hide Values") {
      {
        bgCol = PRIMARY_COL;
        align.setAnchor(0.4, 1).setOffset(0, -100).setAlign(CENTER, BOTTOM).setScale(0.1, 0).setMinSize(0, 25);
      }
      void draw(PGraphics c) {
        text = show_values ? "Hide Values" : "Show Values";
        super.draw(c);
      }
      void click(MouseEvent e) {
        if (e.getButton() == LEFT) {
          show_values = !show_values;
        }
      }
    };
    play_button = new TextButton() {
      {
        bgCol = PRIMARY_COL;
        align.setAnchor(0.5, 1).setOffset(0, -100).setAlign(CENTER, BOTTOM).setScale(0.1, 0).setMinSize(0, 25);
      }
      void draw(PGraphics c) {
        text = playing ? "Pause" : "Play";
        super.draw(c);
      }
      void click(MouseEvent e) {
        if (e.getButton() == LEFT) {
          playing = !playing;
        }
      }
    };
    reset_time_button = new TextButton("Clear Queue") {
      {
        bgCol = PRIMARY_COL;
        align.setAnchor(0.6, 1).setOffset(0, -100).setAlign(CENTER, BOTTOM).setScale(0.1, 0).setMinSize(0, 25);
      }
      void click(MouseEvent e) {
        if (e.getButton() == LEFT) {
          playback.queue.clear();
          playback.time_arrays = null;
          playback.time = LocalDateTime.MIN;
        }
      }
    };
    sim_time_label = new TextButton() {
      {
        setTextAlign(LEFT, CENTER);
        align.setAnchor(0.825, 1).setOffset(0, -100).setAlign(CENTER, BOTTOM).setScale(0.35, 0).setMinSize(0, 25);
      }
      void draw(PGraphics c) {
        super.draw(c);
        Rect r = align.getCenterRect();
        pushStyle();
        fill(0);
        textAlign(textAlignX, textAlignY);
        text(" Latest: " + ur_sim_time, r.x-r.w*0.5, r.y);
        popStyle();
      }
    };

    events_label = new TextButton() {
      {
        setTextSize(14);
        setTextAlign(LEFT, TOP);
        align.setAnchor(0, 1).setAlign(LEFT, BOTTOM).setScale(1, 0).setMinSize(0, 100);
      }
      void draw(PGraphics c) {
        Rect r = align.getCenterRect();
        if(events.size() > 0) {
        final float lineheight = 14;
        int lines = floor(r.h/lineheight);
        int startidx = events.size()-1 - events_scroll;
        int endidx = max(0, startidx - lines);
        StringBuilder sb = new StringBuilder();
        for (int i = startidx; i >= endidx; i--) {
          sb.append(" ");
          sb.append(events.get(i));
          sb.append('\n');
        }
        text = sb.toString();
        } else {
          text = ""; 
        }
        super.draw(c);
      }
    };
    q_button = new TextButton("q\n(rad)") {
      {
        bgCol = Q_COL;
        align.setAnchor(0.5, 1).setOffset(-75, -125).setAlign(CENTER, BOTTOM).setMinSize(50, 50);
      }
      void click(MouseEvent e) {
        if (e.getButton() == LEFT) {
          joint_value_type = 0;
        }
      }
    };
    w_button = new TextButton("w\n(rad/s)") {
      {
        bgCol = W_COL;
        align.setAnchor(0.5, 1).setOffset(-25, -125).setAlign(CENTER, BOTTOM).setMinSize(50, 50);
      }
      void click(MouseEvent e) {
        if (e.getButton() == LEFT) {
          joint_value_type = 1;
        }
      }
    };
    a_button = new TextButton("a\n(rad/s²)") {
      {
        bgCol = A_COL;
        align.setAnchor(0.5, 1).setOffset(25, -125).setAlign(CENTER, BOTTOM).setMinSize(50, 50);
      }
      void click(MouseEvent e) {
        if (e.getButton() == LEFT) {
          joint_value_type = 2;
        }
      }
    };
    t_button = new TextButton("T\n(N-m)") {
      {
        bgCol = T_COL;
        align.setAnchor(0.5, 1).setOffset(75, -125).setAlign(CENTER, BOTTOM).setMinSize(50, 50);
      }
      void click(MouseEvent e) {
        if (e.getButton() == LEFT) {
          joint_value_type = 3;
        }
      }
    };

    ui.addButton(info_label);
    ui.addButton(real_display);
    ui.addButton(sim_display);
    ui.addButton(stats_display);
    ui.addButton(graph_display);
    ui.addButton(real_time_label);
    ui.addButton(show_values_button);
    ui.addButton(play_button);
    ui.addButton(reset_time_button);
    ui.addButton(sim_time_label);
    ui.addButton(events_label);
    ui.addButton(q_button);
    ui.addButton(w_button);
    ui.addButton(a_button);
    ui.addButton(t_button);

    ui.addButton(general_mode_button);
    ui.addButton(stats_mode_button);
    
    ErrorReporter er;
    
    er = new ErrorReporter("TCP position error", TCP_POS_ERROR_THRESHOLD, TCP_POS_ERROR_DURATION, "m");
    tcp_pos_error_event.add(er);
    reporters.add(er);
    er = new ErrorReporter("TCP rotation error", TCP_ROT_ERROR_THRESHOLD, TCP_ROT_ERROR_DURATION, "rad");
    tcp_rot_error_event.add(er);
    reporters.add(er);
    er = new ErrorReporter("joint 1 error", JOINT_ERROR_THRESHOLD, JOINT_ERROR_DURATION, "rad");
    joint_error_events[0].add(er);
    reporters.add(er);
    er = new ErrorReporter("joint 2 error", JOINT_ERROR_THRESHOLD, JOINT_ERROR_DURATION, "rad");
    joint_error_events[1].add(er);
    reporters.add(er);
    er = new ErrorReporter("joint 3 error", JOINT_ERROR_THRESHOLD, JOINT_ERROR_DURATION, "rad");
    joint_error_events[2].add(er);
    reporters.add(er);
    er = new ErrorReporter("joint 4 error", JOINT_ERROR_THRESHOLD, JOINT_ERROR_DURATION, "rad");
    joint_error_events[3].add(er);
    reporters.add(er);
    er = new ErrorReporter("joint 5 error", JOINT_ERROR_THRESHOLD, JOINT_ERROR_DURATION, "rad");
    joint_error_events[4].add(er);
    reporters.add(er);
    er = new ErrorReporter("joint 6 error", JOINT_ERROR_THRESHOLD, JOINT_ERROR_DURATION, "rad");
    joint_error_events[5].add(er);
    reporters.add(er);
  }


  void draw() {
    timeScale = 1.0;
    if (!(real_states.isEmpty() || sim_states.isEmpty())) {
      ur_real_display_state = real_states.firstEntry().getValue();
      ur_sim_display_state = sim_states.firstEntry().getValue();
    } else {
      ur_real_display_state = realstate;
      ur_sim_display_state = simstate;
    }

    real_display.setEnabled(!stats_mode);
    sim_display.setEnabled(!stats_mode);
    q_button.setEnabled(!stats_mode);
    w_button.setEnabled(!stats_mode);
    a_button.setEnabled(!stats_mode);
    t_button.setEnabled(!stats_mode);

    stats_display.setEnabled(stats_mode);
    graph_display.setEnabled(stats_mode);

    for(ErrorReporter er : reporters) {
      er.cooldown((float) deltaTime);
      while(!er.errors.isEmpty()) {
        events.add(er.errors.poll());
      }
    }
    
    events_scroll = constrain(events_scroll, 0, events.size()-1);

    background(255);
    
  }

  void drawUI() {
    ui.draw(g);
  }
  void keyPressed() {
    ui.keyPress(key);
    if (ui.focus == null) {
      if (keyCode == 'Q') {
        joint_value_type = 0;
      }
      if (keyCode == 'W') {
        joint_value_type = 1;
      }
      if (keyCode == 'A') {
        joint_value_type = 2;
      }
      if (keyCode == 'T') {
        joint_value_type = 3;
      }
    }
    //events.add("Key press: " + key);
  }
  void keyReleased() {
    ui.keyRelease(key);
  }
  void keyTyped() {
    ui.keyType(key);
  }
  void mouseEvent(MouseEvent e) {
    if(e.getAction() == MouseEvent.WHEEL) {
      if(events_label.contains(mouseX, mouseY)) {
        events_scroll += e.getCount();
      }
    }
    ui.mouseEvent(e);
  }
};

void display_dial(PGraphics c, Rect r, float val, float minval, float maxval, int col) {
  fill(0);
  stroke(col);
  ellipse(r.x, r.y, r.w, r.h);
  noStroke();
  fill(col);
  arc(r.x, r.y, r.w, r.h, -HALF_PI, -HALF_PI+map(val, minval, maxval, 0, TAU), PIE);
  if (show_values || r.contains(mouseX, mouseY)) {
    c.push();
    c.translate(r.x, r.y-50);
    String valtext = String.format("%.10f", val);
    textSize(14);
    textAlign(LEFT, CENTER);
    float text_w = textWidth(valtext);
    float text_h = textAscent() + textDescent();
    c.fill(255);
    c.stroke(0);
    c.rect(-5, 0, text_w+10, text_h);
    c.fill(0);
    c.text(valtext, 0, 0, text_w, text_h);
    c.pop();
  }
}
// Points in relative positions from the top left of the view (like uv coordinates)
final float[][] state_points = {
  {0.8, 0.8},
  {0.6, 0.65},
  {0.65, 0.1},
  {0.525, 0.325},
  {0.4, 0.5},
  {0.25, 0.15},
  {0.1, 0.35}
};
// PGraphics c: used to display graphics
// PImage ur_img: square image of UR to display in the view
// Rect r: centered rectangle of the bounding area for this display
// double[] states: array of length 6, one value for each joint
// double minval, maxval: expected limits for the joint values
// double gripper: value for how open the gripper is, in radians (servo)
// int col: primary color of this joint state display
void display_ur_joint_states(PGraphics c, PImage ur_img, Rect r, double[] states, double minval, double maxval, double gripper, int col) {
  Rect square = new Rect(r);
  square.w = min(r.w, r.h);
  square.h = square.w;
  square.x = square.x-square.w*0.5;
  square.y = square.y-square.h*0.5;
  c.pushStyle();
  c.rectMode(CORNER);
  c.imageMode(CORNER);
  c.image(ur_img, square.x, square.y, square.w, square.h);
  Rect dial = new Rect(0, 0, 50, 50);
  double[] allstates = new double[state_points.length];
  System.arraycopy(states, 0, allstates, 0, states.length);
  allstates[state_points.length-1] = gripper;
  for (int i = 0; i < state_points.length; i++) {
    float[] uv = state_points[i];
    float val = (float) allstates[i];
    boolean is_gripper = i == state_points.length-1;
    float m_minval = is_gripper ? 0.0 : (float) minval;
    float m_maxval = is_gripper ? 0.8248668046333418 : (float) maxval;
    int m_col = is_gripper ? GRIP_COL : col;
    float x = square.x + uv[0]*square.w;
    float y = square.y + uv[1]*square.h;
    dial.x = x;
    dial.y = y;
    display_dial(c, dial, val, m_minval, m_maxval, m_col);
  }
  c.popStyle();
}
