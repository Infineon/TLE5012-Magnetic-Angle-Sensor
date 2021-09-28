/**
 * Run Arduino file readAngleValueProcessing before running this file.
 * Using the Angle Value received from the TLE5012, you can control the small
 * white circle. Collect the blue circles and avoid being touched by the black ones.
 *
 * needs: readAngleValueProcessing.ino
 */
import processing.serial.*;

boolean GameOver = false;

int maxNumberEnemy = 4;

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

int boardSizeX = 600;
int boardSizeY = 600;

float ballPosX = 10.0;
float ballPosY = 10.0;

float vBallY = 2;

int score = 0;
int veloCityIncrement = 2;
int whenToInc = 4;

float homeX = boardSizeX/2;
float homeY = boardSizeY/2;

float theta = HALF_PI / 2;
void setup()
{
  size(600,600, P2D);
  f = createFont("Arial",16,true);
  String portName = Serial.list()[0];
  //frameRate(55);
  myPort = new Serial(this, portName, 1000000);
  if (myPort.available() > 0)
  {
    while(val == null) {val = myPort.readStringUntil('\n');}
  }
  println(val);
  if (val != null)
  {
   parseVal();
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
      parseVal();
      makeBoard();
      myPort.clear();
    }
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
   }
  catch (Exception e)
  {
    println("could not parse");
  }
  
}

void moveBall()
{
  if (ballPosY <= 0 || ballPosY >= boardSizeY)
  {
    vBallY *= (-1);
  }
  
  ballPosY += vBallY;
  ballPosX = (boardSizeX / 360.0) * floatVal;
  strokeWeight(0);
  fill(230,0,0);
  ellipse(ballPosX,ballPosY,radius,radius);
}

void makeBoard()
{
  displayScore();
  makeHome();
  moveBall();
  drawEnemy();
  gameWon();
}

void makeHome()
{
  fill(0,0,230);
  ellipse(homeX,homeY,radius*factorHome,radius*factorHome);
}

void gameWon()
{
  float x = ballPosX - homeX;
  float y = ballPosY - homeY;
  x = x*x;
  y = y*y;
  float leng = x + y;
  float radiusSq = radius * radius;
  if (leng < radiusSq) 
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
   score = score + 1;
   if (((score-1) % whenToInc) == 0)
   {
     if (vBallY < 0) vBallY = vBallY - veloCityIncrement;
     else vBallY = vBallY + veloCityIncrement;
   }
  }
}

void drawEnemy()
{
  int num = score;
  if (score > maxNumberEnemy) num = maxNumberEnemy;
  for (int i = 0; i < num; i++)
  {
    
    xCoord[i] = xCoord[i] + xVel[i];
    yCoord[i] = yCoord[i] + yVel[i];
    if (xCoord[i] <= 0 || xCoord[i] >= boardSizeX) xVel[i] = xVel[i] * (-1);
    if (yCoord[i] <= 0 || yCoord[i] >= boardSizeY) yVel[i] = yVel[i] * (-1);
    fill(0);
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
  float leng = x + y;
  float radiusSq = (radius*(factorEnemy/2)) * (radius*(factorEnemy/2));
  if (leng < radiusSq) return true;
  else return false;
}

void displayEnd()
{
  background(0);
  fill(255);
  textSize(20);
  text("GAMEOVER", boardSizeX/2,boardSizeY/2);
  text("Final Score", boardSizeX/2,boardSizeY/2 + 20);
   text(score, boardSizeX/2,boardSizeY/2 + 40);
}

void displayScore()
{
  textSize(20);
  text(score, 10,20);
}
