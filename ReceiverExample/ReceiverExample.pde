import peasy.PeasyCam;

import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress uplinkAddress;

// osc settings
int inPort = 9000;
int outPort = 8000;
String address = "10.142.131.255"; //"192.168.1.255";

PeasyCam cam;

boolean debug = true;

Cube cube = new Cube();

void setup()
{
  frameRate(60);
  size(600, 600, P3D);
  pixelDensity(2);
  surface.setTitle("OSC Device Example");

  cam = new PeasyCam(this, 0, 0, 0, 400);
  setupUI();
}

void draw()
{
  if (oscP5 == null)
  {
    // osc
    oscP5 = new OscP5(this, inPort);
    uplinkAddress = new NetAddress(address, outPort);
  }

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
  text("FPS: " + round(frameRate), 20, height - 40);
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
    println("send test...");
  }
}

void publishTestData() {
  OscMessage msg = new OscMessage("/lnk/test");
  msg.add(1);
  oscP5.send(msg, uplinkAddress);
}

void oscEvent(OscMessage msg) {
  println("Message: " + msg.addrPattern());

  if (msg.checkAddrPattern("/lnk/pos"))
  {
    int x = msg.get(0).intValue();
    int y = msg.get(1).intValue();
    int z = msg.get(2).intValue();

    cube.x = x;
    cube.y = y;
    cube.z = z;
  }
}
