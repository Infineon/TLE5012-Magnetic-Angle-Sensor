/** //<>// //<>// //<>// //<>// //<>//
 * Run Arduino file readSpeedProcessing before running this file.
 * This program gives a visual of the angle speed of the magnet sensor as a speedometer.
 * Every time you get to the target speed, you click on the screen or press any button
 * to start again with a higher target speed.
 *
 * needs: readSpeedProcessing.ino
 */
import processing.serial.*;

boolean gameEnd = false;
int radius = 200;
Serial myPort;
String val;
int revolutions = 0;
PFont f;
float floatVal = 0.0;
float prevPosition = 0;
float speedToGet = 1000;
int addSpeed = 200;

float endPosX = 0;
float endPosY = 0;

void setup()
{
  size(800, 800);
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

void draw() //<>//
{
  background(190);
  val = myPort.readStringUntil('\n');
  if (val != null)
  {
    parseValue();
    myPort.clear(); //<>//
  }
}

void visualize()
{
  displaySpeed();
  strokeWeight(3);
  line(400, 400, 200, 400);
  float degree = PI + (floatVal / speedToGet) * PI;

  endPosX = cos(degree);
  endPosY = sin(degree);

  println(floatVal);
  if (floatVal > speedToGet)
  { 
    background(190);
    line(400, 400, 600, 400); 
    text("" + floatVal + "°/s", 650, 400);
    speedToGet = speedToGet+addSpeed;
    displaySpeed();
  } else {
    background(190); 
    line(400, 400, 400+(200 * endPosX), 400+(200 * endPosY));
    text("" + floatVal + "°/s", 400+(300 * endPosX), 400+(300 * endPosY));
    displaySpeed();
  }
}

void parseValue()
{
  try
  {
    floatVal = abs(Float.parseFloat(val)); 
    visualize();
  }
  catch (Exception e)
  {
    println("could not parse");
  }
}

void displaySpeed()
{
  textSize(20);
  text(speedToGet, 10, 20);
  text("°/s", 120, 20);
}
