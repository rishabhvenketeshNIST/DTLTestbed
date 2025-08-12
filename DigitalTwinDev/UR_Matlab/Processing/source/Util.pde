public class Event {
  HashSet<Runnable> listeners = new HashSet<>();
  
  public void add(Runnable r) {
    listeners.add(r);
  }
  
  public void remove(Runnable r) {
    listeners.remove(r);
  }
  
  public void call() {
    for(Runnable r : listeners) {
      r.run();
    }
  }
}

public class ArrayIndexComparator<T> implements Comparator<Integer>
{
    private final List<T> list;
    private final Comparator<T> comp;

    public ArrayIndexComparator(List<T> data, Comparator<T> comp)
    {
        list = data;
        if(comp == null) {
          this.comp = (a, b) -> {
            Comparable ca = (Comparable) a;
            Comparable cb = (Comparable) b;
            return ca.compareTo(cb);
          };
        } else {
          this.comp = comp;
        }
    }
    
    public ArrayIndexComparator(List<T> data) {
      this(data, null);
    }

    public Integer[] createIndexArray()
    {
        Integer[] indexes = new Integer[list.size()];
        for (int i = 0; i < list.size(); i++)
        {
            indexes[i] = i;
        }
        return indexes;
    }

    public int compare(Integer index1, Integer index2)
    {
      return comp.compare(list.get(index1), list.get(index2));
    }
}

public <T extends Comparable> Integer[] getSortedIndices(List<T> list) {
  ArrayIndexComparator<T> comp = new ArrayIndexComparator<>(list);
  Integer[] sorted_indices = comp.createIndexArray();
  Arrays.sort(sorted_indices, comp);
  return sorted_indices;
}

public <T> Integer[] getSortedIndices(List<T> list, Comparator<T> comparator) {
  ArrayIndexComparator<T> comp = new ArrayIndexComparator<>(list, comparator);
  Integer[] sorted_indices = comp.createIndexArray();
  Arrays.sort(sorted_indices, comp);
  return sorted_indices;
}

public <T> List<T> reorderedList(List<T> list, Integer[] indices) {
  List<T> sorted = new ArrayList(list.size());
  for(int i : indices) {
    sorted.add(list.get(i));
  }
  return sorted;
}

LocalDateTime fromEpochMillis(long millis) {
  try {
    Instant inst = Instant.ofEpochMilli(millis);
    return LocalDateTime.ofInstant(inst, ZoneOffset.UTC);
  }
  catch(Exception e) {
    return LocalDateTime.MIN;
  }
}

LocalDateTime min(LocalDateTime a, LocalDateTime b) {
  return a.compareTo(b) <= 0 ? a : b; 
}

LocalDateTime max(LocalDateTime a, LocalDateTime b) {
  return a.compareTo(b) >= 0 ? a : b; 
}

LocalDateTime parseUTC(String datestring) {
  Instant inst = Instant.parse(datestring);
  return LocalDateTime.ofInstant(inst, UTC_ZONE_ID);
}

final ZoneId UTC_ZONE_ID = ZoneId.of("Etc/UTC");

long toEpochMillis(LocalDateTime time) {
  Instant inst = time.toInstant(ZoneOffset.UTC);
  try {
    return inst.toEpochMilli();
  }
  catch(Exception e) {
    return -1L;
  }
}

double goodMod(double a, double b) {
  if (b == 0.0) return 0.0;
  return (a % b + b) % b;
}

import java.awt.Toolkit;
import java.awt.datatransfer.*;

public String getClipboardContents() {
  String result = "";
  Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
  // odd: the Object param of getContents is not currently used
  Transferable contents = clipboard.getContents(null);
  boolean hasTransferableText = (contents != null) && contents.isDataFlavorSupported(DataFlavor.stringFlavor);
  if (hasTransferableText && contents != null) {
    try {
      result = (String) contents.getTransferData(DataFlavor.stringFlavor);
    } 
    catch (Exception ex) {
      //System.out.println(ex);
      //ex.printStackTrace();
    }
  }
  return result;
}

public void setClipboardContents(String str) {
  StringSelection stringSelection = new StringSelection(str);
  Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
  clipboard.setContents(stringSelection, null);
}
