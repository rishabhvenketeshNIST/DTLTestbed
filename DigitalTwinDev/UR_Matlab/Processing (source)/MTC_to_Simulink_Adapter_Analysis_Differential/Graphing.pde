class GraphInfo {
  float minX = 0, maxX = 10, stepX = 1;
  float minY = 0, maxY = 10, stepY = 1;
  String title = "";
  String xlabel = "x axis";
  String ylabel = "y axis";
  int minorTicks = 0;
  int xdecimals = 0, ydecimals = 0;
  boolean showGrid = true;
  
  GraphInfo() {
  }
  
  GraphInfo(GraphInfo gi) {
    minX = gi.minX;
    maxX = gi.maxX;
    stepX = gi.stepX;
    minY = gi.minY;
    maxY = gi.maxY;
    stepY = gi.stepY;
    title = gi.title;
    xlabel = gi.xlabel;
    ylabel = gi.ylabel;
    minorTicks = gi.minorTicks;
    xdecimals = gi.xdecimals;
    ydecimals = gi.ydecimals;
    showGrid = gi.showGrid;
  }

  GraphInfo setTitle(String title) {
    this.title = title;
    return this;
  }

  GraphInfo setAxisLimits(float minX, float maxX, float minY, float maxY) {
    this.minX = minX;
    this.maxX = maxX;
    this.minY = minY;
    this.maxY = maxY;
    return this;
  }

  GraphInfo setAxisStep(float stepX, float stepY) {
    this.stepX = stepX;
    this.stepY = stepY;
    return this;
  }

  GraphInfo setAxisDecimals(int xdec, int ydec) {
    xdecimals = xdec;
    ydecimals = ydec;
    return this;
  }

  GraphInfo setAxisLabels(String x, String y) {
    xlabel = x;
    ylabel = y;
    return this;
  }
  
  GraphInfo setMinorTicks(int ticks) {
    minorTicks = ticks;
    return this;
  }
  
  GraphInfo showGrid(boolean showit) {
    showGrid = showit;
    return this;
  }
}

Rect draw_graph_body(PGraphics c, Rect bounds, GraphInfo info) {
  float axis_size = 30;
  float tick_size = 6;
  c.push();
  c.fill(0);
  // title
  c.textSize(14);
  c.textAlign(CENTER, TOP);
  c.text(info.title, bounds.x, bounds.y-bounds.h*0.5);
  //c.textSize(12);
  // x axis
  c.textAlign(CENTER, BOTTOM);
  c.text(info.xlabel, bounds.x, bounds.y+bounds.h*0.5 + 3);
  c.strokeWeight(1);
  c.pushMatrix();
  c.translate(bounds.x-bounds.w*0.5, bounds.y+bounds.h*0.5);
  c.line(axis_size, -axis_size, bounds.w, -axis_size);
  c.textAlign(CENTER, TOP);
  for (float xval = info.minX; xval <= info.maxX; xval += info.stepX) {
    if (info.minorTicks > 0) {
      float minor_step = info.stepX/(info.minorTicks + 1);
      int minor_ticks_count = 0;
      for (float x_minor = xval+minor_step; minor_ticks_count < info.minorTicks && x_minor <= info.maxX; x_minor += minor_step) {
        float x = map(x_minor, info.minX, info.maxX, axis_size, bounds.w-axis_size);
        c.stroke(169);
        c.line(x, -axis_size, x, tick_size*0.5-axis_size);
        if (info.showGrid) {
          c.line(x, -axis_size, x, axis_size-bounds.h);
        }
        minor_ticks_count++;
      }
    }
    float x = map(xval, info.minX, info.maxX, axis_size, bounds.w-axis_size);
    c.stroke(0);
    c.line(x, -axis_size, x, tick_size-axis_size);
    if (info.showGrid) {
      stroke(128);
      c.line(x, -axis_size, x, axis_size-bounds.h);
    }
    c.text(String.format("%."+info.xdecimals+"f", xval), x, 0.4*tick_size-axis_size);
  }
  c.popMatrix();
  // y axis
  c.pushMatrix();
  c.translate(bounds.x-bounds.w*0.5, bounds.y+bounds.h*0.5);
  c.rotate(-HALF_PI);
  c.fill(0);
  c.textAlign(CENTER, TOP);
  c.text(info.ylabel, bounds.h*0.5, 10-textWidth(String.format("%."+info.ydecimals+"f", 0.0)));
  c.strokeWeight(1);
  c.line(axis_size, axis_size, bounds.h, axis_size);
  c.textAlign(CENTER, BOTTOM);
  for (float yval = info.minY; yval <= info.maxY; yval += info.stepY) {
    if (info.minorTicks > 0) {
      float minor_step = info.stepY/(info.minorTicks + 1);
      int minor_ticks_count = 0;
      for (float y_minor = yval+minor_step; minor_ticks_count < info.minorTicks && y_minor <= info.maxY; y_minor += minor_step) {
        float y = map(y_minor, info.minY, info.maxY, axis_size, bounds.h-axis_size);
        c.stroke(169);
        c.line(y, axis_size, y, axis_size-tick_size*0.75);
        if (info.showGrid) {
          c.line(y, axis_size, y, bounds.w-axis_size);
        }
        minor_ticks_count++;
      }
    }
    float y = map(yval, info.minY, info.maxY, axis_size, bounds.h-axis_size);
    c.stroke(0);
    c.line(y, axis_size, y, axis_size-tick_size);
    if (info.showGrid) {
      stroke(128);
      c.line(y, axis_size, y, bounds.w-axis_size);
    }
    c.pushMatrix();
    c.translate(y, axis_size-0.4*tick_size);
    c.rotate(HALF_PI);
    c.textAlign(RIGHT, BOTTOM);
    c.text(String.format("%."+info.ydecimals+"f", yval), 0, 0);
    c.popMatrix();
  }
  c.popMatrix();
  c.pop();
  Rect data_area = new Rect(bounds);
  data_area.w -= axis_size*2;
  data_area.h -= axis_size*2;
  return data_area;
}

void draw_graph_data(PGraphics c, Rect bounds, GraphInfo info, List<Double> xdata, List<Double> ydata, int style, int col) {
  c.push();
  //c.clip(bounds.x-bounds.w*0.5, bounds.y-bounds.h*0.5, bounds.w, bounds.h);
  if (style == LINE) {
    //Integer[] sorted_indices = getSortedIndices(xdata);
    //List<Double> sorted_x_data = reorderedList(xdata, sorted_indices);
    //List<Double> sorted_y_data = reorderedList(ydata, sorted_indices);
    c.stroke(col);
    c.strokeWeight(3);
    c.strokeCap(ROUND);
    Float prevx = null, prevy = null;
    // Assume both have the same length, but if they don't just stop after the shortest finishes
    Iterator<Double> xiter = xdata.iterator();
    Iterator<Double> yiter = ydata.iterator();
    while (xiter.hasNext() && yiter.hasNext()) {
      double xval = xiter.next();
      double yval = yiter.next();
      float x = map((float) xval, info.minX, info.maxX, bounds.x-bounds.w*0.5, bounds.x+bounds.w*0.5);
      float y = map((float) yval, info.minY, info.maxY, bounds.y+bounds.h*0.5, bounds.y-bounds.h*0.5);
      boolean visible = true;
      if (prevx != null && prevy != null) {
        visible = dist(prevx, prevy, x, y) > 1;
        if (bounds.contains(prevx, prevy) && bounds.contains(x, y) && (visible || !xiter.hasNext() || !yiter.hasNext())) {
          c.line(prevx, prevy, x, y);
        }
      }
      if (visible) {
        prevx = x;
        prevy = y;
      }
    }
  } else { // points
    c.stroke(col);
    c.strokeWeight(5);
    c.strokeCap(ROUND);
    Iterator<Double> xiter = xdata.iterator();
    Iterator<Double> yiter = ydata.iterator();
    while (xiter.hasNext() && yiter.hasNext()) {
      double xval = xiter.next();
      double yval = yiter.next();
      float x = map((float) xval, info.minX, info.maxX, bounds.x-bounds.w*0.5, bounds.x+bounds.w*0.5);
      float y = map((float) yval, info.minY, info.maxY, bounds.y+bounds.h*0.5, bounds.y-bounds.h*0.5);
      if (bounds.contains(x,y)) {
        c.point(x, y);
      }
    }
  }
  //c.noClip();
  c.pop();
}

void draw_graph(PGraphics c, Rect bounds, GraphInfo info, List<Double> xdata, List<Double> ydata, int style, int col) {
  Rect r = draw_graph_body(c, bounds, info);
  draw_graph_data(c, r, info, xdata, ydata, style, col);
}

void draw_graph_legend(PGraphics c, String[] axisNames, int[] colors) {
  final float lineheight = 15;
  c.push();
  c.textSize(14);
  float totalheight = lineheight*axisNames.length;
  float maxwidth = 0;
  for(String s : axisNames) {
    maxwidth = max(maxwidth, c.textWidth(s));
  }
  c.rectMode(CORNER);
  c.fill(255);
  c.stroke(1);
  c.strokeWeight(2);
  c.rect(0, 0, maxwidth+25, totalheight+10);
  c.translate(5, 5);
  c.textAlign(LEFT, TOP);
  c.noStroke();
  for(int i = 0; i < axisNames.length; i++) {
    String name = axisNames[i];
    int col = colors[i];
    c.fill(col);
    c.text(name, 0, 0);
    c.circle(maxwidth+10, lineheight*0.5, 15);
    c.translate(0, lineheight);
  }
  
  
  c.pop();
}
