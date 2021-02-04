/**
 * Run readAngleValueProcessing before running this. This program runs the game Pong.
 * You can control your paddle with the TLE5012.
 *
 * needs: readAngleValueProcessing.ino
 */

import processing.serial.*;


class Ball {

  float posX, posY, movX, movY, speedX, speedY, size;
  int stickOn;
  boolean sticky;
  float pos;


  Ball(float _posX, float _posY) {
    posX = _posX;
    posY = _posY;
    movX = 0;
    movY = 0;
    speedX = 0;
    speedY = 0;
    sticky = true;
    stickOn = 1;
    size = 6;
  }

  void setPos(float _posX, float _posY) {
    posX = _posX;
    posY = _posY;
  }

  void update() {
    if (sticky) {
      if (stickOn == 1) {
        posX = player1.posX + player1.thickness/2 + ball.size/2;
        posY = player1.posY;
      } else if (stickOn == 2) {  
        posX = player2.posX - player2.thickness/2 - ball.size/2;
        posY = player2.posY;
      }
    } else {
      posX = posX + movX;
      posY = posY + movY;
    }


    if (posY < size) movY = -movY;        // top bounce
    if (posY > height-size) movY = -movY; // bottom bounce

    if (posX < 0) { // out left side
      player2.scorePlus();
      sticky = true;
      stickOn = 1;
    } else if (posX > width) { // out right side
      player1.scorePlus();
      sticky = true;
      stickOn = 2;
    } else if (posX < (player1.posX + (player1.thickness / 2) + (size / 2))) {
      if (player1.testRacketCollision(posX, posY, size)) {
        movX = -movX;
        movY += player1.getMovY() / 5;
      }
    } else if (posX > player2.posX) {  
      if (player2.testRacketCollision(posX, posY, size)) {
        movX = -movX;
        movY += player2.getMovY() / 5;
      }
    }
  }

  void stickRelease(int idplayer) {
    sticky = false;
    if ((stickOn == 1) && (idplayer == 1)) {
      movY = player1.getMovY(); 
      movX = 5;
      stickOn = 0;
    } else if ((stickOn == 2) && (idplayer == 2)) {
      movY = player2.getMovY(); 
      movX = -5;
      stickOn = 0;
    }
  }

  void setSticky(int _playerId) {
    sticky = true;
    stickOn = _playerId;
  }

  float getPosY() {
    return posY;
  }

  void draw() {
    update();
    ellipse(posX, posY, size, size);
  }
}

class Ground {

  int scoreP1, scoreP2;

  Ground() {
    scoreP1 = 0;
    scoreP2 = 0;
  }

  void draw() {
    line(width/2, 0, width/2, height); // net
    text(player1.getScore(), width/3, 50); 
    text(player2.getScore(), width/1.6, 50);
  }
}

class Message {
  String say;
  int time;
  int maxTime = 50;

  Message() {
    say = "";
    time = 0;
  }

  void set(String _say) {
    time = maxTime;
    say = _say;
  }

  void draw() {
    if ((say != "") && (time > 0)) {
      float a = 255 - ((maxTime - time) * 5);
      stroke(255, 255, 255, a); 
      fill(255, 255, 255, a);
      text(say, width/2 - (say.length() * 18)/2, height/2);
      time--;
    } else {
      say = "";
    }
    stroke(255, 255, 255, 255); 
    fill(255, 255, 255, 255);
  }
}
class Player {
  float posX, posY, movX, movY;
  int id, size, thickness, score;
  boolean computerDriven;
  int difficulty, pause, pauseTime, movPause, dir;

  Player(int _id, float _posX, float _posY, boolean _computerDriven) {
    id = _id;
    posX = _posX;
    posY = _posY;
    computerDriven = _computerDriven;
    size = 80;
    thickness = 5;
    score = 0;
    difficulty = 2;
    pause = 75;
    pauseTime = pause;
    movPause = 0;
    dir = 0;
  }

  void draw() {
    update();
    rect(posX - (size/16), posY - (size/2), thickness, size);
  }

  void up() {
    if (!computerDriven) movY = constrain (movY -= 12, -10, 10);
  }

  void down() {
    if (!computerDriven) movY = constrain (movY += 12, -10, 10);
  }

  void move(float pos)
  {
    if (!computerDriven) movY = constrain (posY = (pos * (600.0 / 360.0)), -10, 10);
  }

  void update() {
    if (computerDriven) {
      if (ball.sticky && (ball.stickOn == 2)) pausePlayer(); 
      else movY = constrain(ball.getPosY() - posY, -2 - difficulty, 2 + difficulty);
    }
    posY = constrain (posY+movY, 0, height);
    movY *= .7;
  }

  float getMovY() {
    return movY;
  }

  void pausePlayer() {
    if (computerDriven) {
      if (pause == pauseTime) {
        movPause = 5;
        dir = 1;
      }
      movY = constrain (movPause * dir, -5, 5);
      if ((posY < (size/2)) && (dir < 0)) dir = 1;
      else if ((posY > (height - (size/2))) && (dir > 0)) {
        println(height - (size/2));
        dir = -1;
      }
      pause--;
      if (pause < 1) {
        pause = 75;
        releaseBall();
      }
    }
  }

  void releaseBall() {
    ball.stickRelease(id);
  }

  void scorePlus() {
    score ++;
  }

  int getScore() {
    return score;
  }

  void resetScore() {
    score = 0;
  }

  void setDifficulty(int _d) {
    difficulty = constrain (difficulty += _d, 0, 10);
  }

  float getDifficulty() {
    return difficulty;
  }
  void switchComputerDriven() {
    if (computerDriven) computerDriven = false;
    else computerDriven = true;
  }

  void setPos(int _posX, int _posY) {
    posX = _posX;
    posY = _posY;
  }

  boolean testRacketCollision(float x, float y, float s) {
    if ((y - (s / 2) > posY - (size / 2)) && (y + (s / 2) < posY + (size / 2))) {
      return true;
    } else return false;
  }
}

PFont scoreFont;
Ground ground;
Player player1;
Player player2;
Ball ball;
Message message;
boolean start = true;

Serial myPort;

void setup() {
  size(600, 450);
  ground = new Ground();
  player1 = new Player(1, 20, height/2, false);
  player2 = new Player(2, width - 20, height/2, true);
  ball = new Ball(0, 0);
  ball.setPos(player1.posX + player1.size/9 + ball.size/2, player1.posY);
  message = new Message();
  scoreFont = createFont("Arial", 40);
  textFont(scoreFont);
  ellipseMode(CENTER);
  //frameRate(50);
  String portName = Serial.list()[0];
  String val = null;  
  myPort = new Serial(this, portName, 1000000);
  if (myPort.available() > 0)
  {
    while (val == null) {
      val = myPort.readStringUntil('\n');
    }
  }
  if (val != null)
  {
    parseVal(val);
  }
}

void draw() {
  background(0);
  stroke(255); 
  fill(255);
  ground.draw();
  player1.draw();
  player2.draw();
  ball.draw();
  message.draw();
  String val = myPort.readStringUntil('\n');
  if (val != null)
  {
    parseVal(val);
    myPort.clear();
  }


  if (start) {
    player1.movY = 4;
    ball.stickRelease(1);
    start = false;
  }
}

void keyPressed() {
  if (key == 'r' || key == 'R') {
    resetGame();
  }
  if (key == 'p' || key == 'P') {
    player2.switchComputerDriven();
  }
  if (key == 'e' || key == 'E') {
    player1.up();
  }
  if (key == 'd' || key == 'D') {
    player1.down();
  }  
  if (key == 'c' || key == 'C') {
    player1.releaseBall();
  }
  if (key == '+') {
    player2.setDifficulty(1);
    message.set("computer level " + (int)player2.getDifficulty());
  }
  if (key == '-') {
    player2.setDifficulty(-1);
    message.set("computer level " + (int)player2.getDifficulty());
  }
  if (key == CODED) {
    if (keyCode == UP) {
      player2.up();
    }
    if (keyCode == DOWN) {
      player2.down();
    }
    if (keyCode == LEFT) {
      player2.releaseBall();
    }
  }
}

void resetGame() {
  player1.setPos(20, height/2);
  player2.setPos(width - 20, height/2);
  player1.resetScore();
  player2.resetScore();
  ball.setSticky(1);
  player1.movY = 4;
  ball.stickRelease(1);
  message.set("new game");
}

float pos;

void parseVal(String val)
{
  try
  {
    pos = Float.parseFloat(val);
    if (pos < 0)
    {
      pos = 360.0 + pos;
    }
    if (pos > 120 && pos < 240) start =true;
    moveP1();
  }
  catch (Exception e)
  {
    println("could not parse");
  }
}

void moveP1()
{
  player1.move(pos);
}
