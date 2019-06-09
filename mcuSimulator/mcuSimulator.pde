import peasy.PeasyCam;

String mcuPath = "/dev/tty.SLAB_USBtoUART";
boolean isMcuAvailable = false;

MicroController mcu = new MicroController(this, mcuPath);

boolean debug = true;

PeasyCam cam;

Cube cube = new Cube();

void setup()
{
  frameRate(60);
  size(600, 600, P3D);
  pixelDensity(2);
  surface.setTitle("MCU Simulator");

  cam = new PeasyCam(this, 0, 0, 0, 400);

  // try to attach
  checkDevices();
  mcu.attach();

  mcu.start();
  setupUI();
}

void draw()
{
  checkDevices();

  background(0);

  showAxisMarker();

  cube.render();

  showInfo();
}

void showInfo()
{
  cam.beginHUD();
  cp5.draw();

  fill(255);
  textSize(14);
  text("MCU detected: " + isMcuAvailable 
    + "\nattached: " + (mcu.isAttached()) 
    + "\nFPS: " + round(frameRate), 20, height - 50);
  cam.endHUD();
}

void showAxisMarker()
{
  int axisLength = 100;
  strokeWeight(3);

  // x
  stroke(236, 32, 73);
  line(0, 0, 0, axisLength, 0, 0);

  // y
  stroke(47, 149, 153);
  line(0, 0, 0, 0, axisLength, 0);

  // z
  stroke(247, 219, 79);
  line(0, 0, 0, 0, 0, axisLength);
}

void keyPressed()
{
  if (key == ' ')
  {
    // try to connect
    if (isMcuAvailable)
      mcu.attach();
    else
      println("No MCU detected!");
  }

  if (key == 'i')
  {
    int seed = (int)random(0, 10000);
    randomSeed(seed);

    println("Seed: " + seed);
  }
}

void checkDevices()
{
  isMcuAvailable = new File(mcuPath).exists();
}
