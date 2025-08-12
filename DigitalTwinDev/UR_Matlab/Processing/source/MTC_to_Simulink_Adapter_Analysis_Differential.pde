import java.time.*;
import java.util.*;
import java.io.*;
import java.nio.*;
import processing.net.*;

final PApplet APP = this;
ArrayList<Mode> modes = new ArrayList<Mode>();

// Options
boolean DUMMY = false;
long MAX_MTC_SAMPLES = 10000;
int SERVER_PORT = 16385;
String MTC_IP = "127.0.0.1";
int MTC_port = 5000;
//String MTC_UR5e_NAME = "UR5e";
String MTC_UR5e_UUID = "ur5e";
double MTC_QUERY_INTERVAL = 5; // seconds
boolean SAVE_REPLAY = true;
double SAVE_REPLAY_INTERVAL = 30; // seconds
boolean SAVE_MTC = false;
boolean AUTOPLAY = false;
float TIME_DATA_DURATION = 10; // seconds
float TCP_POS_ERROR_THRESHOLD = 0.01; // meters
float TCP_POS_ERROR_DURATION = 10; // seconds
float TCP_ROT_ERROR_THRESHOLD = 0.01; // radians
float TCP_ROT_ERROR_DURATION = 10; // seconds
float JOINT_ERROR_THRESHOLD = 0.01; // radians
float JOINT_ERROR_DURATION = 10; // seconds

// Timekeeping
long pTime;
double deltaTime;
double timeScale = 1;
double mtc_query_timer = 0;
double save_replay_timer = 0;

// Networking
Server server;
Client mtc_client;

// Robot control and analysis
long MTC_lastSequenceNum = -1; // the last processed sequence number
SamplePlayback playback;
boolean playing = false, step = false;
LocalDateTime ur_sim_time = LocalDateTime.MIN;
UR_State simstate = new UR_State();
UR_State realstate = new UR_State();

Table dataTable;

void init_MTC() {
  String command = String.format("curl %s:%d/%s/current", MTC_IP, MTC_port, MTC_UR5e_UUID);
  XML doc = null;

  try {
    Process process = Runtime.getRuntime().exec(command);
    BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
    StringBuilder sb = new StringBuilder();
    String line;
    while ((line = reader.readLine()) != null) {
      sb.append(line);
      sb.append('\n');
    }
    reader.close();
    doc = XML.parse(sb.toString());
  }
  catch (Exception e) {
    e.printStackTrace();
  }
  if (doc == null) {
    throw new RuntimeException("Could not initialize MTConnect adapter, no connection. Make sure curl is installed and on the PATH.");
  }
  XML header = doc.getChild("Header");
  long last = header.getLong("lastSequence", -1);
  if (last >= 0) {
    MTC_lastSequenceNum = last;
    println("Most recent sequence number: " + MTC_lastSequenceNum);
  } else {
    throw new RuntimeException("Error in MTConnect query");
  }
}

void query_UR_data() {
  String command = String.format(
    "curl %s:%d/%s/sample?from=%d&count=%d",
    MTC_IP,
    MTC_port,
    MTC_UR5e_UUID,
    Math.max(MTC_lastSequenceNum-100, 0), // minus 100 to have buffer
    MAX_MTC_SAMPLES);
  XML doc = null;

  try {
    Process process = Runtime.getRuntime().exec(command);
    BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
    StringBuilder sb = new StringBuilder();
    String line;
    while ((line = reader.readLine()) != null) {
      sb.append(line);
      sb.append('\n');
    }
    reader.close();
    //println(sb.toString());
    doc = XML.parse(sb.toString());
  }
  catch (Exception e) {
    e.printStackTrace();
  }
  
  if (doc == null) return;
  
  XML header = doc.getChild("Header");
  if (header != null) {
    long last = header.getLong("lastSequence", -1);
    if (last >= 0) {
      MTC_lastSequenceNum = Math.min(last, MTC_lastSequenceNum+MAX_MTC_SAMPLES);
    } else {
      XML error_parent = doc.getChild("Errors");
      if (error_parent != null) {
        XML[] errors = error_parent.getChildren("Error");
        for(XML x : errors) {
          String errcode = x.getString("errorCode");
          if (("OUT_OF_RANGE").equals(errcode)) {
            // Reset the last sample time and the playback time to re-synchronize
            playback.time = LocalDateTime.MIN;
            init_MTC();
          }
        }
      }
    }
  }
  append_UR_data(doc);
}

void save_data_table() {
  if (dataTable != null) {
    synchronized(dataTable) {
      if (dataTable.getRowCount() > 0) {
        String filename = String.format("Data_%d-%d-%d_%d-%d-%d.csv", year(), month(), day(), hour(), minute(), second());
        println("Saving data in file: " + filename);
        saveTable(dataTable, filename);
        dataTable.clearRows();
      }
    }
  }
}

void append_UR_data(XML doc) {
  SampleSequence[] seq = extractUR5eData(doc, MTC_UR5e_UUID);
  if (seq == null) return;
  
  //println("Loaded UR5e data:");
  //for (SampleSequence s : seq) {
  //  print(s.dataItemId);
  //  print(" (");
  //  if (s.data.isEmpty()) {
  //    print("no data");
  //  } else {
  //    print(s.data.firstKey());
  //  }
  //  print(") : ");
  //  println(s.data.size());
  //}
  

  playback.enqueue(seq);
  if (AUTOPLAY) {
    AUTOPLAY = false; // only do this for the first time
    // Start playing one query interval after launch
    // so we have some buffer time and aren't left without data.
    Thread t = new Thread(() -> {
      try {
        Thread.sleep((long)(1000L*MTC_QUERY_INTERVAL));
      }
      catch (Exception e) {
      }
      playing = true;
    }
    );
    t.start();
  }
  if (SAVE_MTC) {
    saveXML(doc, dataPath(String.format("MTC_%d-%d-%d_%d-%d-%d.xml", year(), month(), day(), hour(), minute(), second())));
  }
}

void setup() {
  size(800, 750, P2D);
  registerMethod("mouseEvent", this);
  JSONObject config = loadJSONObject("config.json");
  float sendRate = config.getFloat("send_hz", 50);
  timeScale = config.getFloat("timescale", 1);
  MTC_IP = config.getString("MTC_ip", "127.0.0.1");
  MTC_port = config.getInt("MTC_port", 5000);
  MTC_QUERY_INTERVAL = config.getDouble("query_interval", 5);
  //MTC_UR5e_NAME = config.getString("ur5e_name", "UR5e");
  MTC_UR5e_UUID = config.getString("ur5e_uuid", "ur5e");
  SERVER_PORT = config.getInt("server_port", 16385);
  SAVE_REPLAY = config.getBoolean("save_replay", true);
  SAVE_REPLAY_INTERVAL = config.getDouble("save_replay_interval", 30);
  DUMMY = config.getBoolean("dummy", false);
  //DUMMY_FILE = config.getString("dummy_file", "ur_data.xml");
  JSONArray dummy_files_array = config.getJSONArray("dummy_files");
  String[] dummy_files = dummy_files_array.toStringArray();
  SAVE_MTC = config.getBoolean("MTC_dump", false);
  AUTOPLAY = config.getBoolean("autoplay", false);
  MAX_MTC_SAMPLES = Math.min(100000, (long) (500.0 * MTC_QUERY_INTERVAL) * 37); // Max UR sample rate in Hz * the number of seconds between MTC queries * number of dataitem samples
  TIME_DATA_DURATION = config.getFloat("time_data_duration", 10);
  TCP_POS_ERROR_THRESHOLD = config.getFloat("tcp_pos_error_threshold", 0.01);
  TCP_POS_ERROR_DURATION = config.getFloat("tcp_pos_error_duration", 10);
  TCP_ROT_ERROR_THRESHOLD = config.getFloat("tcp_rot_error_threshold", 0.01);
  TCP_ROT_ERROR_DURATION = config.getFloat("tcp_rot_error_duration", 10);
  JOINT_ERROR_THRESHOLD = config.getFloat("joint_error_threshold", 0.01);
  JOINT_ERROR_DURATION = config.getFloat("joint_error_duration", 10);
  timedata = new TemporalData(ceil(sendRate*TIME_DATA_DURATION));
  frameRate(sendRate);
  surface.setResizable(true);
  surface.setTitle("MTConnect to Simulink Adapter");
  
  for(Mode m : modes) {
    m.setup();
  }
  switchMode(menu);
  
  textSize(14);
  textAlign(LEFT, TOP);

  if (SAVE_REPLAY) {
    dataTable = createDataTable();
  }
  playback = new SamplePlayback(37);
  if (DUMMY && dummy_files != null) {
    for(String dummy_filename: dummy_files) {
      XML dummy_data = loadXML(dummy_filename);
      if (dummy_data != null) {
        append_UR_data(dummy_data);
      }
    }
  } else {
    init_MTC();
  }

  println(String.format("Starting server on %s:%d...", Server.ip(), SERVER_PORT));
  server = new Server(this, SERVER_PORT);
  
  pTime = System.nanoTime();
}

void draw() {
  long curTime = System.nanoTime();
  deltaTime = (curTime - pTime) * 0.000000001;
  pTime = curTime;

  mtc_query_timer += deltaTime;
  if (mtc_query_timer > MTC_QUERY_INTERVAL) {
    mtc_query_timer = 0;
    if (!DUMMY)
      thread("query_UR_data");
  }
  save_replay_timer += deltaTime;
  if (save_replay_timer > SAVE_REPLAY_INTERVAL) {
    save_replay_timer = 0;
    thread("save_data_table");
  }

  // Compare current state to sim state
  extractStateFromPlayback(playback, realstate);
  real_states.put(playback.time, new UR_State(realstate));

  // Update state
  if (playing || step) {
    analyzeData();
    step = false;
    playback.step(deltaTime*timeScale);
  }

  // Send Joint Targets
  byte[] msg = createSimulinkMessage(playback.time, playback.state);
  server.write(msg);

  // Display Information
  background(0);
  mode.update();
  mode.draw();
  
  mode.drawUI();
}

void exit() {
  save_data_table();
  mode.onEnd();
  super.exit();
}

void mouseEvent(MouseEvent e) {
  mode.mouseEvent(e);
}

void keyPressed() {
  if (key == ' ') {
    playing = !playing;
  }
  if (keyCode == RIGHT) {
    step = true;
  }
  int FKeyStart = g.isGL() ? 96 : 111; // F1 keyCode - 1
  // F1-F12 are keyCodes 97-108 inclusive
  if (keyCode == FKeyStart+1) {
    switchMode(menu);
  }
  if (keyCode == FKeyStart+2) {
    switchMode(infodump);
  }
  mode.keyPressed();
}

void keyReleased() {
  mode.keyReleased();
}

void keyTyped() {
  mode.keyTyped();
}

void stepTimeScale(int step) {
  timeScale = constrain(timeScale*pow(0.75, -step*0.1), 1e-2, 1e2);
}

void clientEvent(Client c) {
  if (c == mtc_client) {
    String xml_src = c.readString();
    //println("Recieved MTC XML:");
    //println(xml_src);
    int first_line_idx = xml_src.indexOf("<?xml");
    if (first_line_idx >= 0) {
      xml_src = xml_src.substring(first_line_idx);
      try {
        XML src = XML.parse(xml_src);
        append_UR_data(src);
      }
      catch (Exception e) {
        System.err.println("Error reading MTConnect XML");
      }
    }
  } else { // Assume that the client is one of the server connections, which we expect to be Simulink.
    readSimulinkResponse(c);
  }
}

void serverEvent(Server s, Client c) {
  println("Client at " + c.ip() + " connected to server.");
  s.active();
}

double lerp(double a, double b, double t) {
  return a + (b-a)*t;
}

double invlerp(double a, double b, double v) {
  return (v-a)/(b-a);
}

double map(double v, double a1, double b1, double a2, double b2) {
  return lerp(a2, b2, invlerp(a1, b1, v));
}

double constrain(double v, double lo, double hi) {
  return Math.max(Math.min(v, hi), lo);
}
