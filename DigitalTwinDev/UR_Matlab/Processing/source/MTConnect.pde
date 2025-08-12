// A data structure for MTConnect samples which maintains timestamp data but discards sequence indices.
class SampleSequence {
  String sampleType, dataItemId;
  SortedMap<LocalDateTime, Double> data;

  SampleSequence() {
    data = new TreeMap<>();
  }

  SampleSequence(String sampleType, String dataItemId) {
    this();
    this.sampleType = sampleType;
    this.dataItemId = dataItemId;
  }

  SampleSequence(XML samplesXML, String sampleType, String dataItemId) {
    this(sampleType, dataItemId);
    if (samplesXML != null && sampleType != null && dataItemId != null) {
      XML[] xdata = samplesXML.getChildren(sampleType);
      for (XML x : xdata) {
        if (dataItemId.equals(x.getString("dataItemId"))) {
          LocalDateTime ldt = parseUTC(x.getString("timestamp"));
          Double d = Double.parseDouble(x.getContent());
          data.put(ldt, d);
        }
      }
    }
  }
}

// Constructs three SampleSequences for 3D sample data, such as cartesian position or velocity.
SampleSequence[] flatten3DSampleSequence(XML samplesXML, String sampleType, String dataItemId) {
  if (samplesXML == null || sampleType ==  null || dataItemId == null) return null;
  SampleSequence[] seqs = {
    new SampleSequence(sampleType+"_x", dataItemId+"_x"),
    new SampleSequence(sampleType+"_y", dataItemId+"_y"),
    new SampleSequence(sampleType+"_z", dataItemId+"_z"),
  };
  XML[] xdata = samplesXML.getChildren(sampleType);
  for (XML x : xdata) {
    if (dataItemId.equals(x.getString("dataItemId"))) {
      LocalDateTime ldt = parseUTC(x.getString("timestamp"));
      String[] tokens = splitTokens(x.getContent());
      for (int i = 0; i < seqs.length && i < tokens.length; i++) {
        Double d = Double.parseDouble(tokens[i]);
        seqs[i].data.put(ldt, d);
      }
    }
  }
  return seqs;
}

LocalDateTime getEarliestTime(SampleSequence[] samples) {
  LocalDateTime earliest = LocalDateTime.MAX;
  for (SampleSequence s : samples) {
    if (s.data.isEmpty()) continue;
    LocalDateTime contender = s.data.firstKey();
    if (earliest.compareTo(contender) > 0) {
      earliest = contender;
    }
  }
  return earliest;
}

class SamplePlayback {
  private LocalDateTime time;
  private double[] state;
  private Queue<SampleSequence[]> queue;
  private LocalDateTime[][] time_arrays;
  private int[] time_array_indices;

  SamplePlayback(int numVals, LocalDateTime startTime) {
    state = new double[numVals];
    time_array_indices = new int[numVals];
    time = startTime;
    queue = new LinkedList<SampleSequence[]>();
  }

  SamplePlayback(int numVals) {
    this(numVals, LocalDateTime.MIN);
  }

  public int getValueCount() {
    return state.length;
  }

  public SamplePlayback enqueue(SampleSequence[] seq) {
    if (seq == null) {
      return this;
    }
    if (seq.length != getValueCount()) {
      throw new RuntimeException(String.format(
        "Sample sequence array (length %d) provided contains %s values for this playback (state length %d)",
        seq.length, seq.length > getValueCount() ? "too many" : "too few", getValueCount()
        ));
    }
    //if (time == LocalDateTime.MIN) {
    //  time = getEarliestTime(seq);
    //}
    queue.offer(seq);
    return this;
  }

  public void clear() {
    queue.clear();
    time_arrays = null;
  }

  private SampleSequence[] getCurrentSequences() {
    if (queue.isEmpty()) return null;
    return queue.peek();
  }

  private LocalDateTime[][] getCurrentTimes() {
    if (time_arrays == null && !queue.isEmpty()) {
      int count = getValueCount();
      time_arrays = new LocalDateTime[count][];
      SampleSequence[] sequences = getCurrentSequences();
      if (sequences == null) return null;
      for (int i = 0; i < count; i++) {
        // sequences are guaranteed to have the same length as count
        SampleSequence seq = sequences[i];
        Set<LocalDateTime> set = seq.data.keySet();
        time_arrays[i] = new LocalDateTime[set.size()];
        set.toArray(time_arrays[i]);
        time_array_indices[i] = 0;
      }
    }
    return time_arrays;
  }

  SamplePlayback step(double timestep_seconds) {
    if (timestep_seconds < 0.0) throw new IllegalArgumentException("Timestep cannot be negative, only step playback forward.");

    SampleSequence[] sequences = getCurrentSequences();
    if (sequences != null && time == LocalDateTime.MIN) {
      time = getEarliestTime(sequences);
      time_arrays = null;
    }
    LocalDateTime[][] times = getCurrentTimes();
    if (sequences == null || times == null) return this; // there is no more data, so don't bother updating anything
    time = time.plusNanos((long) (timestep_seconds*1e9));
    int sequences_at_end = 0;
    for (int i = 0; i < times.length; i++) {
      int time_i = time_array_indices[i];
      // only try to iterate through time if the current sample timestamp is at or behind the current time
      if (time.compareTo(time_arrays[i][time_i]) >= 0) {
        // Step through the time arrays until the current time array timestamp is before the current time
        for (; time_i < time_arrays[i].length; time_i++) {
          boolean at_end = time_i >= time_arrays[i].length-1;
          if (at_end) {
            break;
          }
          if (time.compareTo(time_arrays[i][time_i]) >= 0 && time.compareTo(time_arrays[i][time_i+1]) < 0) {
            break;
          }
        }
      }
      if (time_arrays[i].length == 0 || time.compareTo(time_arrays[i][time_arrays[i].length - 1]) > 0) {
        sequences_at_end += 1;
      }
      // at this point, time_i should refer to the most recent data point
      SampleSequence seq = sequences[i];
      if (seq.data.isEmpty() || time_arrays[i].length == 0) {
        // no data
        //state[i] = 0;
      } else {
        time_array_indices[i] = time_i; // apply changes to the time index
        LocalDateTime data_time = time_arrays[i][time_i];
        Double datum = seq.data.get(data_time);
        state[i] = datum;
      }
    }
    if (sequences_at_end == times.length) {
      // then there is no more data in this sequence, so poll from the queue.
      queue.poll();
      time_arrays = null;
      Arrays.fill(time_array_indices, 0);
    }
    return this;
  }

  double[] getState() {
    double[] copy = new double[state.length];
    System.arraycopy(state, 0, copy, 0, state.length);
    return copy;
  }
}
