class Rect {
  public float x, y, w, h;
  public Rect() {
    this(0, 0, 0, 0);
  }
  public Rect(float x, float y, float w, float h) {
    set(x, y, w, h);
  }
  public Rect(Rect r) {
    this(r.x, r.y, r.w, r.h);
  }
  public void set(Rect r) {
    set(r.x, r.y, r.w, r.h);
  }
  public void set(float x, float y, float w, float h) {
    this.x = x; this.y = y; this.w = w; this.h = h;
  }
  public void draw(PGraphics c) {
    c.rect(x, y, w, h);
  }
  public boolean contains(float mx, float my) {
    return abs(mx - x) <= w*0.5 && abs(my - y) <= h*0.5;
  }
  public boolean cornerContains(float mx, float my) {
    return mx > x && mx <= x + w && my > y && my <= y + h;
  }
  public String toString() {
    return x + ", " + y + ", " + w + ", " + h;
  }
}

class Align {
  PGraphics canvas;
  float ax, ay;
  int alignX, alignY;
  float ox, oy;
  float sw, sh;
  float mw, mh, Mw, Mh;
  Align() {
    alignX = CENTER;
    alignY = CENTER;
    mw = 10;
    mh = 10;
    Mw = Float.MAX_VALUE;
    Mh = Float.MAX_VALUE;
  }
  Align copy(Align a) {
    canvas = a.canvas;
    ax = a.ax;
    ay = a.ay;
    alignX = a.alignX;
    alignY = a.alignY;
    ox = a.ox;
    oy = a.oy;
    sw = a.sw;
    sh = a.sh;
    mw = a.mw;
    mh = a.mh;
    Mw = a.Mw;
    Mh = a.Mh;
    return this;
  }
  Align setBounds(PGraphics c) {
    canvas = c;
    return this;
  }
  Align setAlign(int x, int y) {
    if (x == LEFT || x == CENTER || x == RIGHT)
      alignX = x;
    if (y == TOP || y == CENTER || y == BOTTOM)
      alignY = y;
    return this;
  }
  Align setAnchor(float ax, float ay) {
    this.ax = ax;
    this.ay = ay;
    return this;
  }
  Align setOffset(float ox, float oy) {
    this.ox = ox;
    this.oy = oy;
    return this;
  }
  Align setScale(float sw, float sh) {
    this.sw = sw;
    this.sh = sh;
    return this;
  }
  Align setMinSize(float w, float h) {
    this.mw = w;
    this.mh = h;
    return this;
  }
  Align setMaxSize(float w, float h) {
    this.Mw = w;
    this.Mh = h;
    return this;
  }
  float getX() {
    float w = canvas == null ? 0 : canvas.width;
    return w * ax + ox;
  }
  float getY() {
    float h = canvas == null ? 0 : canvas.height;
    return h * ay + oy;
  }
  float getW() {
    float w = canvas == null ? 0 : canvas.width;
    return constrain(w * sw, mw, Mw);
  }
  float getH() {
    float h = canvas == null ? 0 : canvas.height;
    return constrain(h * sh, mh, Mh);
  }
  Rect getCenterRect() {
    Rect r = new Rect(getX(), getY(), getW(), getH());
    switch(alignX) {
    case LEFT:
      r.x += r.w*0.5;
      break;
    case RIGHT:
      r.x -= r.w*0.5;
      break;
    }
    switch(alignY) {
    case TOP:
      r.y += r.h*0.5;
      break;
    case BOTTOM:
      r.y -= r.h*0.5;
      break;
    }
    return r;
  }
  boolean contains(float mx, float my) {
    Rect r = getCenterRect();
    return r.contains(mx, my);//abs(mx - r.x) <= r.w*0.5 && abs(my - r.y) <= r.h*0.5;
  }
}

public class TextButton implements TextEntry {
  boolean enabled = true;
  public String text;
  public int textAlignX, textAlignY;
  public float minTextSize, maxTextSize, textScale;
  public int bgCol, textCol, outlineCol;
  public float outlineWeight;
  public Align align = new Align();
  public TextButton() {
    this("");
  }
  public TextButton(String text) {
    textAlignX = CENTER;
    textAlignY = CENTER;
    textScale = 0;
    minTextSize = 14;
    maxTextSize = 14;
    bgCol = color(255);
    textCol = color(0);
    outlineCol = color(0);
    outlineWeight = 1;
    this.text = (text == null ? "" : text);
  }
  boolean contains(float mx, float my) {
    return align.contains(mx, my);
  }
  boolean isEnabled() {
    return enabled;
  }
  void setEnabled(boolean e) {
    enabled = e;
  }
  void draw(PGraphics c) {
    align.setBounds(c);
    c.pushStyle();
    c.rectMode(CENTER);
    Rect r = align.getCenterRect(); 
    c.strokeWeight(outlineWeight);
    c.stroke(outlineCol);
    c.fill(bgCol);
    r.draw(c);
    c.fill(textCol);
    c.textSize(getTextSize());
    c.textAlign(textAlignX, textAlignY);
    if (text != null)
      c.text(text, r.x, r.y, r.w, r.h);
    c.popStyle();
  }
  void press(MouseEvent e) {
  }
  void release(MouseEvent e) {
  }
  void click(MouseEvent e) {
  }
  void keyPress(int key) {
    if (key == CODED) return;
    text = enterText(text, key, true);
  }
  void keyRelease(int key) {
  }
  void keyType(int key) {
  }
  TextButton setTextAlign(int x, int y) {
    if (x == LEFT || x == CENTER || x == RIGHT)
      textAlignX = x;
    if (y == TOP || y == CENTER || y == BOTTOM)
      textAlignY = y;
    return this;
  }
  void setTextSize(float size) {
    minTextSize = size;
    maxTextSize = size;
  }
  float getTextSize() {
    return constrain(align.getH() * textScale, minTextSize, maxTextSize);
  }
  String getText() {
    return text;
  }
}

public class IntButton extends TextButton {
  int value;
  boolean negatable;
  public IntButton() {
    this(0);
  }
  public IntButton(int val) {
    super();
    value = val;
  }
  @Override
    void draw(PGraphics c) {
    text = getText();
    super.draw(c);
  }
  @Override
    void keyPress(int key) {
    if (key == CODED) return;
    value = enterInteger(value, key, negatable);
  }
  @Override
    String getText() {
    return String.valueOf(value);
  }
  int getValue() {
    return value;
  }
}

public class CheckBox implements Button {
  public int bgCol, trueCol, falseCol, outlineCol;
  public float outlineWeight;
  public boolean value, enabled = true;
  public Align align = new Align();
  public CheckBox(boolean val) {
    value = val;
    bgCol = color(255);
    trueCol = color(0, 255, 0);
    falseCol = color(255, 0, 0);
    outlineCol = color(0);
    outlineWeight = 2;
  }
  public CheckBox() {
    this(false);
  }
  boolean isEnabled() { 
    return enabled;
  }
  void setEnabled(boolean e) { 
    enabled = e;
  }
  void draw(PGraphics c) {
    align.setBounds(c);
    c.pushStyle();
    c.rectMode(CENTER);
    Rect r = align.getCenterRect();
    c.strokeWeight(outlineWeight);
    c.stroke(outlineCol);
    c.fill(bgCol);
    r.draw(c);
    c.fill(value ? trueCol : falseCol);
    c.textAlign(CENTER, CENTER);
    c.textSize(r.h * 0.8);
    c.text(value ? "y" : "n", r.x, r.y);
    c.popStyle();
  }
  boolean contains(float mx, float my) {
    return align.contains(mx, my);
  }
  void press(MouseEvent e) {
  }
  void release(MouseEvent e) {
  }
  void click(MouseEvent e) {
    value = !value;
  }
}
