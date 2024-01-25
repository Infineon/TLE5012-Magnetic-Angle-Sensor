/**
 * Run Arduino file readAngleValueProcessing before running this file.
 * This is a an example of using the Angle Value that we get from the TLE5012,
 * to show the angle that is measured in a unit circle.
 * If angle measured is greater than 180° then it is represented as a negative degree.
 * For example 210° will be represented as -150°.
 * Using the visual, you can set the angle of the magnetic sensor to (more or less)
 * exactly the value you want.
 *
 * needs: readAngleValueProcessing.ino
 */
import processing.serial.*;

int radius = 200;
Serial myPort;
String val;
int revolutions = 0;
PFont f;
float floatVal = 0.0;
float prevPosition = 0;

void setup()
{
  size(600, 600);
  f = createFont("Arial", 16, true);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 1000000);
  if (myPort.available() > 0)
  {
    while (val == null) {
      val = myPort.readStringUntil('\n');
    }
  }
  println(val);
  if (val != null)
  {
    parseValue();
  }
}

void draw()
{
  val = myPort.readStringUntil('\n');
  if (val != null)
  {
    parseValue();
    myPort.clear();
  }
}

void visualize()
{

  float checkRev = (floatVal * (360/TWO_PI));
  if (checkRev<0) checkRev = 360+checkRev;
  float diff = prevPosition - checkRev;
  if (diff >= 30 || diff < -30)
  {
    if (prevPosition <= 30 && checkRev >= 330) revolutions--;
    else if (prevPosition >= 330 && checkRev <= 30) revolutions++;
    prevPosition = checkRev;
  }
  float xCoord = sin(floatVal + HALF_PI); 
  float yCoord = cos(floatVal + HALF_PI);

  float pointCircleX = 300+((radius/2)*xCoord);
  float pointCircleY = 300+((radius / 2)*yCoord);

  fill(255);

  ellipse(300, 300, radius, radius);
  strokeWeight(3);
  line(300, 300, 300+((radius/2)*xCoord), 300+((radius / 2)*yCoord));
  strokeWeight(1);

  textFont(f, 16);

  float positionTextX = 300+((radius)*xCoord);
  float positionTextY = 300+((radius)*yCoord);
  float degrees = (floatVal) * (360 / TWO_PI);

  fill(255);

  rect(10, 10, 140, 70);
  fill(0);
  text("revolutions", 30, 30);
  text(revolutions, 70, 50);
  text(degrees, 50, 70);
}

void parseValue()
{
  try
  {
    floatVal = Float.parseFloat(val) * (TWO_PI / 360);
    background(190);
    visualize();
  }
  catch (Exception e)
  {
    println("could not parse");
  }
}
