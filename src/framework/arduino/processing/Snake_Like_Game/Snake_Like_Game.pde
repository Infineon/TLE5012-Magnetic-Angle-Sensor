/**
 * Run Arduino file readAngleValueProcessing before running this file.
 * Using the Angle Value received from the TLE5012, you can control the small white circle.
 * Collect the blue circles and avoid being touched by the black ones.
 * If you are moving up then clockwise you turn right, counterclockwise left
 * If you are moving down then clockwise ypi turn
 *
 * needs: readAngleValueProcessing.ino
 */
import processing.serial.*;

boolean GameOver = false;

int maxNumberEnemy = 10;

int angleForMovement = 30;

float prevValue = 0;

float[] xCoord = new float[maxNumberEnemy]; 
float[] yCoord = new float[maxNumberEnemy];

float[] xVel = new float[maxNumberEnemy]; 
float[] yVel = new float[maxNumberEnemy];

int radius = 10;
float factorHome = 2;
float factorEnemy = 3;
int maxSpd = 7;

Serial myPort;
String val;
PFont f;
float floatVal = 0.0;

int boardSizeX = 1000;
int boardSizeY = 1000;

float ballPosX = 400.0;
float ballPosY = 400.0;

int velocity = 2;

float vBallY = 0;
float vBallX = velocity;

int score = 0;
int veloCityIncrement = 1;
int whenToInc = 4;

float homeX = boardSizeX/2;
float homeY = boardSizeY / 2;

float theta = HALF_PI / 2;

void setup()
{
  size(1000, 1000);
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
    funcDouble(val, true);
  }
}

void draw()
{
  if (GameOver) displayEnd();
  else
  {
    background(190);
    val = myPort.readStringUntil('\n');
    if (val != null)
    {
      funcDouble(val, false);
      myPort.clear();
    }
  }
}

void funcDouble(String val2, boolean firstTime)
{
  try
  {
    floatVal = Float.parseFloat(val2) ;
    if (floatVal < 0)
    {
      floatVal = 360.0 + floatVal;
    }

    if (firstTime) prevValue = floatVal;
    makeBoard();
  }
  catch (Exception e)
  {
    println("could not parse");
  }
}

void moveBall()
{
  if (ballPosY <= 0 || ballPosY >= boardSizeY || ballPosX <= 0 || ballPosX >= boardSizeX)
  {
    ballPosY = random(boardSizeY);
    ballPosX = random(boardSizeX);
  }

  if (floatVal >= 0 && floatVal < 90)
  {
    vBallX = 0;
    vBallY = velocity * (-1);
  } else if (floatVal >= 90 && floatVal < 180)
  {
    vBallX = velocity * (-1);
    vBallY = 0;
  } else if (floatVal >= 180 && floatVal < 270)
  {
    vBallX = 0;
    vBallY = velocity;
  } else if (floatVal >= 270 && floatVal < 360)
  {
    vBallX = velocity;
    vBallY = 0;
  }

  strokeWeight(0);
  fill(230, 0, 0);

  if (vBallX == 0) 
  {
    ballPosY += vBallY;
    ellipse(ballPosX, ballPosY, radius, radius);
  } else if (vBallY == 0) 
  {
    ballPosX += vBallX;
    ellipse(ballPosX, ballPosY, radius, radius);
  }
}

void makeBoard()
{

  drawEnemy();

  moveBall();
  makeHome();
  gameWon();
  displayScore();
}

void makeHome()
{
  fill(0, 0, 230);
  ellipse(homeX, homeY, radius*factorHome, radius*factorHome);
}

void gameWon()
{
  float x = ballPosX - homeX;
  float y = ballPosY - homeY;
  x = x*x;
  y = y*y;
  float leng = sqrt(x + y);
  if (leng < radius) 
  {
    homeX = random(boardSizeX);
    homeY = random(boardSizeY);

    if (score < maxNumberEnemy)
    {
      xCoord[score] = random(boardSizeX);
      yCoord[score] = random(boardSizeY);

      xVel[score] = random(maxSpd);
      yVel[score] = random(maxSpd);
    }
    score++;
    if (((score-1) % whenToInc) == 0)
    {
      velocity++;
    }
  }
}

void drawEnemy()
{
  int num = score;
  if (score > maxNumberEnemy) num = maxNumberEnemy;
  for (int i = 0; i < num; i++)
  {
    fill(0);
    xCoord[i] = xCoord[i] + xVel[i];
    yCoord[i] = yCoord[i] + yVel[i];
    if (xCoord[i] <= 0 || xCoord[i] >= boardSizeX) xVel[i] = xVel[i] * (-1);
    if (yCoord[i] <= 0 || yCoord[i] >= boardSizeY) yVel[i] = yVel[i] * (-1);
    ellipse(xCoord[i], yCoord[i], radius*factorEnemy, radius*factorEnemy);
    if (checkGameOver(xCoord[i], yCoord[i])) 
    {
      GameOver = true;
      displayEnd();
      break;
    }
  }
}

boolean checkGameOver(float xC, float yC)
{
  float x = ballPosX - xC;
  float y = ballPosY - yC;
  x = x*x;
  y = y*y;
  float leng = sqrt(x + y);
  if (leng < (radius*(factorEnemy/2))) return true;

  return false;
}

void displayEnd()
{
  background(0);
  textSize(50);
  fill(255);
  text("GAMEOVER", boardSizeX/2 - 100, boardSizeY/2 - 100);
}

void displayScore()
{
  textSize(20);
  text(score, 10, 20);
}
