/**
 * Run Arduino file readAngleValueProcessing before running this file.
 * Using the Angle Value received from the TLE5012, you can control the line
 * at the bottom of the screen to save the ball from falling.
 *
 * needs: readAngleValueProcessing.ino
 */
import processing.serial.*;

int radius = 10;
Serial myPort;
String val;
PFont f;
float floatVal = 0.0;
int prevPosition = 0;

int boardSizeX = 600;
int boardSizeY = 600;

float ballPosX = 10.0;
float ballPosY = 10.0;

float linePosX = boardSizeX / 2;
int linePosY = boardSizeY - 100;
int lineLen = 100;

float vX = 5.0;
float vY = 5.0; 

int score = 1;
int veloCityIncrement = 1;

int whenToIncrement = 5;

boolean inLine = true;
boolean increment = false;

float theta = HALF_PI / 2;
void setup()
{
  size(600, 600);
  f = createFont("Arial", 16, true);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  if (myPort.available() > 0)
  {
    while (val == null) {
      val = myPort.readStringUntil('\n');
    }
  }
  println(val);
  if (val != null)
  {
    parseVal();
  }
}

void draw()
{
  background(190);
  val = myPort.readStringUntil('\n');
  if (val != null)
  {
    parseVal();
  }
  makeBoard();

  if (gameOver())
  {
    background(255);
    text("GameOver", boardSizeX / 2, boardSizeY / 2);
  }
}

void parseVal()
{
  try
  {
    floatVal = Float.parseFloat(val);
    if (floatVal < 0)
    {
      floatVal = 360.0 + floatVal;
    }

    moveLine();
  }
  catch (Exception e)
  {
    println("could not parse");
  }
}

void makeBoard()
{
  displayScore();
  ellipse(ballPosX, ballPosY, radius, radius);
  fill(0);
  strokeWeight(4);
  if (linePosX < 0) linePosX = 0;
  else if ((linePosX+lineLen) > boardSizeX) linePosX = boardSizeX - lineLen;
  line(linePosX, linePosY, linePosX + lineLen, linePosY);
  fill(0);
  moveBall();
}

void moveBall()
{
  if ((score % whenToIncrement) == 0 && increment)
  {
    if (vX < 0) vX = vX - veloCityIncrement;
    else vX = vX + veloCityIncrement;
    if (vY < 0) vY = vY - veloCityIncrement;
    else vY = vY + veloCityIncrement;
    increment = false;
  }
  if (ballPosX >= boardSizeX)
  {
    inLine = true;
    vX *= (-1);
  } else if (ballPosX <= 0)
  {
    inLine = true;
    vX *= (-1);
  }

  if (ballPosY <= 0)
  {
    inLine = true;
    vY *= (-1);
  }

  if (
    (ballPosY >= (linePosY - vY))&& 
    (ballPosY <= (linePosY + vY))&&
    (ballPosX >= linePosX - vX)      &&
    (ballPosX <= (linePosX + lineLen + vX) &&
    (inLine))
    )
  {
    increment = true;
    inLine = false;
    score++;
    vY *= (-1);
    theta = ((ballPosX - linePosX - vX)/(lineLen + vX)) * (PI);

    if (theta > HALF_PI)
    {
      theta = 180 - theta;
    }  

    if (ballPosX > (linePosX + (lineLen/2)))
    {
      if (vX < 0) vX *= (-1);
    } else
    {
      if (vX > 0) vX *= (-1);
    }
  }



  ballPosX += vX * cos(theta);
  ballPosY += vY * sin(theta);
}

void moveLine()
{
  linePosX = -(lineLen/2) + (boardSizeX / 360.0) * floatVal;
}

boolean gameOver()
{
  return (ballPosY > (linePosY+vY+5));
}

void displayScore()
{
  textSize(20);
  text(score, 10, 20);
}
