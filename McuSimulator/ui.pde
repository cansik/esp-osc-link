import controlP5.*;

ControlP5 cp5;

int uiHeight;

boolean isUIInitialized = false;

Slider xSlider;
Slider ySlider;
Slider zSlider;

void setupUI()
{
  isUIInitialized = false;
  PFont font = createFont("Helvetica", 100f);

  cp5 = new ControlP5(this);
  cp5.setAutoDraw(false);

  // change the original colors
  cp5.setColorForeground(color(179, 55, 113));
  cp5.setColorBackground(color(109, 33, 79));
  cp5.setFont(font, 14);
  cp5.setColorActive(color(179, 55, 113));

  int h = 20;
  cp5.addLabel("MCU SIMULATOR")
    .setPosition(10, h);

  h += 30;
  cp5.addButton("setRandomRotation")
    .setValue(100)
    .setPosition(10, h)
    .setSize(150, 22)
    .setCaptionLabel("Random Rotation")
    ;

  h += 50;
  xSlider = cp5.addSlider("x", 10, 150, 10, h, 100, 20)
    .setRange(0, cube.rotationResolution)
    .setLabel("x-Rotaion")
    .setValue(cube.x)
    .plugTo(cube);

  h += 25;
  ySlider = cp5.addSlider("y", 10, 150, 10, h, 100, 20)
    .setRange(0, cube.rotationResolution)
    .setLabel("y-Rotaion")
    .setValue(cube.y)
    .plugTo(cube);

  h += 25;
  zSlider = cp5.addSlider("z", 10, 150, 10, h, 100, 20)
    .setRange(0, cube.rotationResolution)
    .setLabel("z-Rotaion")
    .setValue(cube.z)
    .plugTo(cube);

  h += 30;
  cp5.addButton("publishData")
    .setValue(100)
    .setPosition(10, h)
    .setSize(150, 22)
    .setCaptionLabel("Publish Data")
    ;

  h += 30;
  cp5.addButton("pollData")
    .setValue(100)
    .setPosition(10, h)
    .setSize(150, 22)
    .setCaptionLabel("Poll Data")
    ;


  uiHeight = h + 500;

  isUIInitialized = true;
}

void x() {
  if (!isUIInitialized) return;
  mcu.publishDataRequested = true;
}

void y() {
  if (!isUIInitialized) return;
  mcu.publishDataRequested = true;
}

void z() {
  if (!isUIInitialized) return;
  mcu.publishDataRequested = true;
}

void setRandomRotation()
{
  if (!isUIInitialized) return;

  cube.x = (int)random(0, cube.rotationResolution);
  cube.y = (int)random(0, cube.rotationResolution);
  cube.z = (int)random(0, cube.rotationResolution);

  xSlider.setValue(cube.x);
  ySlider.setValue(cube.y);
  zSlider.setValue(cube.z);


  mcu.publishDataRequested = true;
}

void pollData() {
  if (!isUIInitialized) return;
  println("polling data...");
  mcu.pollRequested = true;
}

void publishData() {
  if (!isUIInitialized) return;
  println("publishing data...");
  mcu.publishDataRequested = true;
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
