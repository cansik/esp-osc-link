class Cube
{
  // const
  final int rotationResolution = (int)pow(2, 10);

  int x = 0;
  int y = 0;
  int z = 0;

  // render
  float cubeSize = 100;

  public Cube() {
  }

  public void render() {
    push();

    // rotate
    rotateX(getRadiansAngle(x));
    rotateY(getRadiansAngle(y));
    rotateZ(getRadiansAngle(z));

    // render spehere
    push();
    fill(0, 255, 255);
    noStroke();
    sphereDetail(30);
    sphere(cubeSize * 0.6);
    pop();

    // render cube
    push();
    fill(70);
    noStroke();
    box(cubeSize);
    pop();

    pop();
  }

  private float getRadiansAngle(int rawValue) {
    return map(rawValue, 0, rotationResolution, 0, PI * 2);
  }
}
