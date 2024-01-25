/**
 * Run Arduino file readAngleValueProcessing before running this file.
 * This is a an example of using the Angle Value that we get from the TLE5012,
 * to show the angle that is measured in a unit circle.
 * If angle measured is greater than 180Â° then it is represented as a negative degree.
 * For example 210Â° will be represented as -150Â°.
 * Using the visual, you can set the angle of the magnetic sensor to (more or less) exactly the value you want.
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
float prevPosition = 200;

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

  float xCoord = sin(floatVal); 
  float yCoord = cos(floatVal);

  float checkRev = (floatVal * (360/TWO_PI));
  if (checkRev<0) checkRev = 360+checkRev;
  float diff = prevPosition - checkRev;

  if (diff >= 20 || diff < -20)
  {
    if (prevPosition <= 20 && checkRev >= 340) revolutions--;
    else if (prevPosition >= 340 && checkRev <= 20) revolutions++;
    prevPosition = checkRev;
  }

  float newcheckRev = checkRev * (TWO_PI / 360);

  float r = (TWO_PI*revolutions) + (newcheckRev);

  fill(255);

  point(300+(r*xCoord), 300+(r*yCoord));

  textFont(f, 16);

  rect(10, 10, 140, 60);
  fill(0);
  text("revolutions", 30, 30);
  text(revolutions, 70, 50);

  prevPosition = checkRev;
}

void parseValue()
{
  try
  {
    floatVal = Float.parseFloat(val);
    floatVal = floatVal * (TWO_PI / 360);

    visualize();
  }
  catch (Exception e)
  {
    println("could not parse");
  }
}
