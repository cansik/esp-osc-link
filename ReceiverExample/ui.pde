import controlP5.*;

ControlP5 cp5;

int uiHeight;

boolean isUIInitialized = false;

Slider rSlider;
Slider gSlider;
Slider bSlider;

void setupUI()
{
  isUIInitialized = false;
  PFont font = createFont("Helvetica", 100f);

  cp5 = new ControlP5(this);
  cp5.setAutoDraw(false);

  // change the original colors
  cp5.setColorForeground(color(59, 59, 152));
  cp5.setColorBackground(color(24, 44, 97));
  cp5.setFont(font, 14);
  cp5.setColorActive(color(59, 59, 152));

  int h = 20;
  cp5.addLabel("OSC RECEIVER")
    .setPosition(10, h);

  h += 30;
  cp5.addButton("sendTestData")
    .setValue(100)
    .setPosition(10, h)
    .setSize(150, 22)
    .setCaptionLabel("Send Test")
    ;

  uiHeight = h + 500;

  isUIInitialized = true;
}

void r() {
  if (!isUIInitialized) return;
  publishTestData();
}

void g() {
  if (!isUIInitialized) return;
  publishTestData();
}

void b() {
  if (!isUIInitialized) return;
  publishTestData();
}

void sendTestData() {
  if (!isUIInitialized) return;
  
  publishTestData();
}

public String formatTime(long millis)
{
  long second = (millis / 1000) % 60;
  long minute = (millis / (1000 * 60)) % 60;
  long hour = (millis / (1000 * 60 * 60)) % 24;

  if (minute == 0 && hour == 0 && second == 0)
    return String.format("%02dms", millis);

  if (minute == 0 && hour == 0)
    return String.format("%02ds", second);

  if (hour == 0)
    return String.format("%02dm %02ds", minute, second);

  return String.format("%02dh %02dm %02ds", hour, minute, second);
}

void mousePressed() {

  // suppress cam on UI
  if (mouseX > 0 && mouseX < 250 && mouseY > 0 && mouseY < uiHeight) {
    cam.setActive(false);
  } else {
    cam.setActive(true);
  }
}
