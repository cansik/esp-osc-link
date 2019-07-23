import processing.serial.*;

class MicroController implements Runnable
{
  final int baudRate = 9600;

  String portName;
  Serial port;

  PApplet parent;

  // thread
  volatile boolean running = false;
  Thread thread;
  int mcFrameRate = 1000 / 60;

  // mcu controls
  volatile boolean publishDataRequested = false;
  volatile boolean pollRequested = false;

  public MicroController(PApplet parent, String portName)
  {
    this.portName = portName;
    this.parent = parent;
  }

  public boolean isAttached()
  {
    return mcu.port != null;
  }

  public void attach()
  {
    try
    {
      port = new Serial(parent, portName, baudRate);
    }
    catch(Exception ex)
    {
      println("Serial Error: " + ex.getMessage());
    }
  }

  public String readData()
  {
    if ( port.available() > 0) 
      return port.readStringUntil('\n');
    return null;
  }

  public void detach()
  {
    port.stop();
    port = null;
  }

  void start()
  {
    running = true;

    thread = new Thread(this);
    thread.setDaemon(true);
    thread.start();
  }

  void stop()
  {
    running = false;

    try
    {
      thread.join(5000);
    }
    catch(Exception ex) 
    {
      ex.printStackTrace();
    }
  }

  void run()
  {
    while (running)
    {
      try
      {
        Thread.sleep(mcFrameRate);
        handleProtocol();
      }
      catch(Exception ex) 
      {
        ex.printStackTrace();
      }
    }
  }

  void handleProtocol()
  {
    if (!isAttached())
      return;

    // check if poll requested
    if (pollRequested) {
      pollRequested = false;
      // todo: do something
    }

    // sending data
    if (publishDataRequested) {
      publishDataRequested = false;
      port.write("OD /pos 3 " + cube.x +  " " + cube.y + " " + cube.z + "\n");
      port.write("OD /michelsuperdings 1 233\n");
    }
  }
}
