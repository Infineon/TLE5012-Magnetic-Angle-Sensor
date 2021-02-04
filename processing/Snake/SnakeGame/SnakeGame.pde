/**
 * You can play snake use the TLE5012 Magnet Sensor. In order to play,
 * please change the delay(10) to delay(100) 
 * in the readAngleValueProcessing and run it.
 *
 * needs: readAngleValueProcessing.ino
 */

import processing.serial.*;

class BorderLib
{
  private Border border;
  BorderLib (int i)
  {
    init(i);
  }

  public int [] [] getBorder ()
  {
    return (border.getBorder());
  }

  private void init (int n)
  {
    int x = 0, y = 0;
    if (n == 1)
    {
      int [] [] b = new int [XRES*2 + 2*(YRES-2)] [2];
      for (int i = 0; i < b.length; i++)
      {
        if (i == 0) {
          x = 0;
          y = 0;
        } else if (i == XRES) {
          x = 0; 
          y = YRES-1;
        } else if (i == XRES*2) {
          x = 0;
          y = 1;
        } else if (i == XRES*2 + YRES-2) {
          x = XRES-1;
          y = 1;
        }

        b [i] [0] = x;
        b [i] [1] = y;

        if (i < XRES*2) x++;
        else y++;
      }
      border = new Border (b);
    } else if (n == 2)
    {
      int [] [] b = new int [20] [2];
      int count = 0;
      for (int i = 0; i < XRES*YRES; i++)
      {
        if (x == (int) (XRES/3.0) && y > 5)
        {
          b [count] [0] = x;
          b [count] [1] = y;
          count++;
        } else if (x == (int) (XRES*2.0/3.0) && y < 10)
        {
          b [count] [0] = x;
          b [count] [1] = y;
          count++;
        }
        x++;
        if (x>=XRES) {
          x = 0;
          y++;
        }
      }
      border = new Border (b);
    }
  }
}

class Border
{
  private int [] [] b;
  Border (int [] [] b)
  {
    this.b = b;
    //this.b = new int [b.length] [2];
    //arrayCopy (this.b, b);
  }

  public int [] [] getBorder ()
  {
    return b;
  }
}

public class Food
{
  private int x, y;
  Food ()
  {
  }

  public int getX()
  {
    return x;
  }

  public int getY()
  {
    return y;
  }

  public void createPos (int [] [] empty)
  {
    int index = (int) random (empty.length);
    x = empty [index] [0];
    y = empty [index] [1];
  }
}

class Letters
{
  private HashMap presets;

  Letters ()
  {
    init();
  }

  private void init()
  {
    Letter n0, n1, n2, n3, n4, n5, n6, n7, n8, n9, g, a, m, e, e_s, o, v, r, s, n, k, b, p, t, doubleDot, wordSpace, letterSpace;

    // write letters --------------------------------------------------------------
    // 0
    int w = 3, h = 5;
    n0 = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1}), w, h);

    // 1
    w = 1;
    n1 = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 1, 1}), w, h);

    // 2
    w = 3;
    n2 = new Letter (twoDimenstions(w, h, new int [] {1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1}), w, h);

    // 3
    n3 = new Letter (twoDimenstions(w, h, new int [] {1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0}), w, h);

    // 4
    n4 = new Letter (twoDimenstions(w, h, new int [] {1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1}), w, h);

    // 5
    n5 = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0}), w, h);

    // 6
    n6 = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1}), w, h);

    // 7
    n7 = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0}), w, h);

    // 8
    n8 = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}), w, h);

    // 9
    n9 = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0}), w, h);

    // s
    s = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1}), w, h);

    // n
    w = 4;
    n = new Letter (twoDimenstions(w, h, new int [] {1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1}), w, h);

    // a
    w = 3;
    a = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1}), w, h);

    // k
    k = new Letter (twoDimenstions(w, h, new  int [] {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1}), w, h);

    // e
    e = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1}), w, h);

    // e thin
    w = 2;
    e_s = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 0, 1, 1, 1, 0, 1, 1}), w, h);

    // g
    w = 3;
    g = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1}), w, h);

    // m
    w = 5;
    m = new Letter (twoDimenstions(w, h, new int [] {1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1}), w, h);

    // o
    w = 3;
    o = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1}), w, h);

    // v
    v = new Letter (twoDimenstions(w, h, new int [] {1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0}), w, h);

    // r
    r = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1}), w, h);

    // p
    p = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0}), w, h);

    // b
    b = new Letter (twoDimenstions(w, h, new int [] {1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1}), w, h);

    // t
    t = new Letter (twoDimenstions(w, h, new int [] {1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}), w, h);

    // :
    w = 1;
    doubleDot = new Letter (twoDimenstions(w, h, new int [] {0, 1, 0, 1, 0}), w, h);

    // wordSpace
    w = 2;
    wordSpace = new Letter (twoDimenstions(w, h, new int [] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}), w, h);

    //letterSpace
    w = 1;

    letterSpace = new Letter (twoDimenstions(w, h, new int [] {0, 0, 0, 0, 0}), w, h);

    // save letters to hashmap ---------------------------------------------------------
    presets = new HashMap();

    Letter [] snake = {
      s, letterSpace, n, letterSpace, a, letterSpace, k, letterSpace, e
    };
    presets.put ("snake", snake);

    Letter [] start = {
      s, letterSpace, t, letterSpace, a, letterSpace, r, letterSpace, t
    };
    presets.put ("start", start);

    Letter [] gameOver = {
      g, letterSpace, a, letterSpace, m, letterSpace, e_s, wordSpace, o, letterSpace, v, letterSpace, e_s, letterSpace, r
    };
    presets.put ("gameover", gameOver);

    Letter [] bDoubleDot = {
      b, letterSpace, doubleDot
    };
    presets.put ("b:", bDoubleDot);

    Letter [] sDoubleDot = {
      s, letterSpace, doubleDot
    };
    presets.put ("s:", sDoubleDot);

    Letter [] pDoubleDot = {
      p, letterSpace, doubleDot
    };
    presets.put ("p:", pDoubleDot);

    presets.put ("space", new Letter[] {
      letterSpace
      }
      );
    presets.put ("0", new Letter[] {
      n0
      }
      );
    presets.put ("1", new Letter[] {
      n1
      }
      );
    presets.put ("2", new Letter[] {
      n2
      }
      );
    presets.put ("3", new Letter[] {
      n3
      }
      );
    presets.put ("4", new Letter[] {
      n4
      }
      );
    presets.put ("5", new Letter[] {
      n5
      }
      );
    presets.put ("6", new Letter[] {
      n6
      }
      );
    presets.put ("7", new Letter[] {
      n7
      }
      );
    presets.put ("8", new Letter[] {
      n8
      }
      );
    presets.put ("9", new Letter[] {
      n9
      }
      );
  }

  public Letter [] getLetters (String ss)
  {
    if (presets.containsKey(ss)) return  (Letter[]) presets.get (ss);
    else return (Letter[]) presets.get ("space");
  }

  public Letter [] getLetters (int ii)
  {
    String intToString = str (ii);
    char [] cArray = new char [intToString.length()];
    for (int i = 0; i < cArray.length; i++) cArray [i] = intToString.charAt (i);
    Letter [] numbers = new Letter [cArray.length*2];
    int count = 0;

    Letter [] tempSpace = (Letter [] ) presets.get ("space");

    for (int i = 0; i < cArray.length; i++) 
    {
      Letter [] temp = (Letter [] ) presets.get (str (cArray[i]));
      numbers [count] = temp [0];
      count++;
      numbers [count] = tempSpace [0];
      count++;
    }
    return numbers;
  }

  private int [] [] twoDimenstions (int w, int h, int [] temp)
  {

    int [] [] ttemp = new int [w] [h];
    int count = 0;


    for (int i = 0; i < h; i++)
    {
      for (int j = 0; j < w; j++)
      {
        ttemp [j] [i] = temp [count];
        count++;
      }
    }

    return ttemp;
  }
}

class Letter 
{
  private int [] [] l;
  private int w, h;
  Letter (int [] [] l)
  {
    this.l = l;
    this.w = l.length;
  }

  Letter (int [] [] l, int w, int h)
  {
    this.l = l;
    this.w = w;
    this.h = h;
  }

  public int getWidth ()
  {
    return w;
  }

  public int getHeight ()
  {
    return h;
  }

  public int [] [] getPos ()
  {
    return l;
  }
}

public class Points
{
  int p;

  Points ()
  {
    init();
  }

  private void init ()
  {
    p = 0;
  }

  public int getIntPoints ()
  {
    return p;
  }

  public String getPoints ()
  {
    return str (p);
  }

  public void finalize (int m)
  {
    p = m;
  }
}

public class Snake 
{
  private int [] [] pos;
  private int xdir = 1, ydir = 0, n;

  Snake (int x, int y, int n )
  {
    this.n = n;
    init(x, y, n);
  }

  public int getInitLength ()
  {
    return n;
  }

  public int getHeadX ()
  {
    return pos [0] [0];
  }

  public int getHeadY ()
  {
    return pos [0] [1];
  }

  public int getSnakeLength ()
  {
    return pos.length;
  }

  public int [] [] getSnakePos ()
  {
    return pos;
  }

  public void setDirX (int dir)
  {
    if (xdir == 0 && dir != xdir*-1)
    {
      xdir = dir;
      ydir = 0;
    }
  }

  public void setDirY (int dir)
  {
    if (ydir == 0 && dir != ydir*-1)
    {
      ydir = dir;
      xdir = 0;
    }
  }

  public void appendSnake ()
  {
    int [] [] temp = new int [pos.length+1] [2];
    arrayCopy (pos, temp);
    //int tempX =  pos [pos.length-1] [0];
    //int tempY = 
    temp [temp.length-1] [0] = pos [pos.length-1] [0]-xdir; 
    temp [temp.length-1] [1] = pos [pos.length-1] [1]-ydir;

    if (temp [temp.length-1] [0] < 0) temp [temp.length-1] [0] = XRES-1;
    else if (temp [temp.length-1] [0] >= XRES) temp [temp.length-1] [0] = 0;

    if (temp [temp.length-1] [1] < 0) temp [temp.length-1] [1] = YRES-1;
    else if (temp [temp.length-1] [1] >= YRES) temp [temp.length-1] [1] = 0;

    pos = new int [temp.length] [2];
    arrayCopy (temp, pos);
  }

  private void init (int x, int y, int n)
  {
    x = constrain (x, 0, XRES);
    y = constrain (y, 0, YRES);

    pos = new int [n] [2];
    pos [0] [0] = x;
    pos [0] [1] = y;

    for (int i = 1; i < n; i++)
    {
      pos [i] [0] = x;
      pos [i] [1] = y;
    }

    for (int i = 0; i < pos.length; i++) move();
  }

  public void move ()
  {

    int x = pos [0] [0];
    int y = pos [0] [1];

    x+=xdir;
    y+=ydir;

    //edges
    if (x == XRES) x = 0;
    else if (x < 0) x = XRES-1;
    if (y == YRES) y = 0;
    else if (y < 0) y = YRES-1;

    for (int i = pos.length-1; i > 0; i--)
    {
      pos [i] [0] = pos [i-1] [0];
      pos [i] [1] = pos [i-1] [1];
    }

    pos [0] [0] = x;
    pos [0] [1] = y;
  }
}

public class Game
{
  private BorderLib bl;
  private Snake snake;
  private Food food;
  private Letters l;
  private Points p;
  private int [] img;
  private int startStat = 0, endCount = 0, n, blinkCount, borders = 0, mode = 0; // 0 = start // 1 = play // 2 = end
  //private int [] [] b, b2; 
  private boolean startBlink = true;

  Game (int n)
  {
    l = new Letters();
    this.n = n;
    img = new int [XRES*YRES];
    initGame();
  }

  public void saveImg (String path)
  {
    String words = "";
    String [] list = new String [1];
    for (int i = 0; i < img.length; i++)
    {
      words += str(img[i]);
      if (i != img.length-1) words += ",";
    }

    list [0] = words;
    saveStrings(path + ".txt", list);
    println ("done saveing " + path + ".txt");
  }

  private void toogleBorderMode ()
  {
    borders++;
    if (borders > 2) borders = 0;
    initBorder();
  }

  private void initGame()
  {
    blinkCount = 0;
    snake = new Snake (16, 8, n);
    food = new Food();
    p = new Points ();
    if (borders != 0) initBorder();
    initFood();
  }

  private void initBorder ()
  {
    if (borders == 0) bl = null;
    else bl = new BorderLib (borders);
    /*
    b = new int [XRES*2 + 2*(YRES-2)] [2];
     int x = 0, y = 0;
     
     for (int i = 0; i < b.length; i++)
     {
     if (i == 0) {
     x = 0;
     y = 0;
     }
     else if (i == XRES) {
     x = 0; 
     y = YRES-1;
     }
     else if (i == XRES*2) {
     x = 0;
     y = 1;
     }
     else if (i == XRES*2 + YRES-2) {
     x = XRES-1;
     y = 1;
     }
     
     b [i] [0] = x;
     b [i] [1] = y;
     
     if (i < XRES*2) x++;
     else y++;
     }
     */
  }

  private void initFood ()
  {
    /*
    if (b != null && b.length == 0)food.createPos(snake.getSnakePos(), null);
     else food.createPos(snake.getSnakePos(), b);*/
    food.createPos (getEmptySpace());
  }

  public int [] getColorArray ()
  {
    return img;
  }

  private int [] []getEmptySpace ()
  {
    int emptySpaceLength = (XRES*YRES) - snake.getSnakeLength();
    if (borders > 0) emptySpaceLength-= bl.getBorder().length;
    int [] [] empty = new int [1+emptySpaceLength] [2];
    boolean [] full = new boolean [XRES*YRES];
    for (int i = 0; i < full.length; i++) full[i] = true;

    int [] [] snakePos = snake.getSnakePos();

    //println ("-----------------------");

    for (int i = 0; i < snakePos.length; i++)
    {
      int snakeX = snakePos[i] [0], snakeY = snakePos [i] [1];
      int index = snakeY*XRES+snakeX;
      //println ("index: " + index + ", snakeX: " + snakeX + ", snakeY: " + snakeY);
      try {
        full[index] = false;
      }
      catch (ArrayIndexOutOfBoundsException e)
      {
        println ("----------------");
        //println ("index: " + index + ", snakeX: " + snakeX + ", snakeY: " + snakeY);
      }
    }

    if (borders > 0)
    {
      int [] [] b = bl.getBorder();
      for (int i = 0; i < b.length; i++)
      {
        int bX = b[i] [0], bY = b[i] [1];
        int index = bY*XRES+bX;
        full[index] = false;
      }
    } 

    int count = 0;
    for (int i = 0; i < full.length; i++)
    {
      if (full[i])
      {
        int emptyX = i % XRES;
        int emptyY = i / XRES;
        try {
          empty [count] [0] = emptyX;
          empty [count] [1] = emptyY;
        }
        catch (ArrayIndexOutOfBoundsException e)
        {
          println ("----------------");
          //println ("Full res: " + (XRES*YRES) + ", SnakeLength: " + snake.getSnakeLength() + ", Detected empty room: " + emptySpaceLength);
          //println ("Count: " + count + ", Index: " + i);
          //println ("x: " + emptyX + ", y: " + emptyY);
        }
        count++;
      }
    }

    return empty;
  }

  public void input (char c)
  {
    if (mode == 1) // game
    {
      if (c  == 's')
      {
        p.finalize(getPoints());
        mode = 2;
      }
      if (c  == 'u') snake.setDirY(-1);
      if (c  == 'd') snake.setDirY(1);
      if (c  == 'l') snake.setDirX(-1);
      if (c  == 'r') snake.setDirX(1);
    }
    if (mode == 0) // start screen
    {
      if (c == 'd') startStat++;
      if (c == 'u') startStat--;
      if (startStat > 1) startStat = 0;
      else if (startStat < 0) startStat = 1;

      if (c == 's' || startStat == 0 && c == 'r') {
        mode = 1;
        initGame();
      }

      if (startStat == 1)
      {
        if (c == 'r' || c == 'l') {
          toogleBorderMode();
          //if (borders == 0) bl = null;
        }
      }
    }
    if (mode == 2) // end screen
    {
      if (endCount > 20 && c  == 'r' || endCount > 20 && c  == 's') {
        mode = 0;
        startStat = 0;
      }
    }
  }

  private int getPoints ()
  {
    int m = snake.getSnakePos().length-snake.getInitLength();
    if (borders == 1) m = (int) ((float) m * 1.5);
    else if (borders == 2) m = (int) ((float) m * 1.7);
    return m;
  }

  private void checkSnakeSelfIntersection ()
  {
    int [] [] snakePos = snake.getSnakePos();
    boolean intersection = false;

    for (int i = 0; i < snakePos.length; i++)
    {
      for (int j = 0; j < snakePos.length; j++)
      {
        if (i == j) continue;
        if (snakePos [i] [0] == snakePos [j] [0] && snakePos [i] [1] == snakePos [j] [1])
        {
          intersection = true;
          i = snakePos.length; 
          j = snakePos.length;
        }
      }
    }
    if (intersection)
    {
      mode = 2;

      p.finalize(getPoints());
      //initGame();
    }
  }

  private void checkSnakeFoodIntersection ()
  {
    int [] [] snakePos = snake.getSnakePos();
    int foodX = food.getX(), foodY = food.getY();

    boolean intersection = false;
    for (int i = 0; i < snakePos.length; i++)
    {
      if (snakePos [i] [0] == foodX && snakePos [i] [1] == foodY)
      {
        intersection = true;
        i = snakePos.length;
      }
    }

    if (intersection)
    {
      snake.appendSnake();
      initFood();
    }
  }

  private void checkSnakeBorderIntersection ()
  {
    boolean intersection = false;
    int [] [] b = bl.getBorder();

    for (int i = 0; i < b.length; i++)
    {
      if (b[i] [0] == snake.getHeadX() && b[i] [1] == snake.getHeadY())
      {
        intersection = true;
        i = b.length;
      }
    }

    if (intersection)
    {
      mode = 2;
      p.finalize(getPoints());
    }
  }

  public void draw ()
  {
    if (mode == 0) display (startScreen ());
    else if (mode == 1) {
      play ();
      endCount = 0;
    } else if (mode == 2) {
      display (endScreen ());
      endCount++;
    }
  }

  private void fillLetters (int x, int y, Letter [] letters, int fillColor, int [] c)
  {
    for (int i = 0; i < letters.length; i++)
    {
      int [] [] letterPos = letters[i].getPos();
      for (int j = 0; j < letterPos.length; j++)
      {
        int letterX = x + j;
        for (int k = 0; k < letterPos[j].length; k++)
        {
          int letterY = y+k;
          if (letterPos [j] [k] != 0)
          {
            int index = letterY*XRES+letterX;
            c[index] = fillColor;
          }
        }
      }
      x+= letters [i].getWidth();
    }
  }

  private int getWordWidth (Letter [] letters)
  {
    int wordWidth = 0;
    for (int i = 0; i < letters.length; i++)
    {
      wordWidth+= letters [i].getWidth();
    }
    return wordWidth;
  }

  private int [] startScreen ()
  {
    int [] c = new int [XRES*YRES];
    // 0 = yellow // 1 = red // 2 = orange // 3 = black

    // alles mit schwarz füllen
    for (int i = 0; i < c.length; i++) c [i] = 3; 

    // inhalt füllen
    int x = 6, y =  2;
    if (startStat == 0 && !startBlink) fillLetters(x, y, l.getLetters("start"), 2, c);
    else fillLetters (x, y, l.getLetters("snake"), (startStat == 0 ? 2 : 0), c);
    x = 6;
    y = 9;
    fillLetters (x, y, l.getLetters("b:"), (startStat == 1 ? 2 : 0), c );
    x+= 1 + getWordWidth(l.getLetters("b:"));
    fillLetters (x, y, l.getLetters(borders), (startStat == 1 ? 2 : 0), c );

    if (blinkCount == 10) {
      startBlink = !startBlink;
      blinkCount = 0;
    }
    blinkCount++;
    return c;
  }

  private int [] endScreen ()
  {
    int [] c = new int [XRES*YRES];
    // 0 = yellow // 1 = red // 2 = orange // 3 = black

    // alles mit schwarz füllen
    for (int i = 0; i < c.length; i++) c [i] = 3; 

    // inhalt füllen
    int x = 0, y = 2;
    fillLetters (x, y, l.getLetters("gameover"), 1, c);
    x = 4;
    y = 9;
    fillLetters (x, y, l.getLetters("p:"), 0, c);
    x+=1 + getWordWidth(l.getLetters("p:"));
    fillLetters (x, y, l.getLetters(p.getIntPoints()), 0, c);
    return c;
  }

  private int [] createColorArray ()
  {
    int [] c = new int [XRES*YRES];

    // alles mit schwarz füllen
    for (int i = 0; i < c.length; i++) c [i] = 3; 

    // schlange einfärben
    int [] [] snakePos = snake.getSnakePos();
    for (int i = 0; i < snakePos.length; i++)
    {
      int snakeX = snakePos[i] [0], snakeY = snakePos [i] [1];
      int index = snakeY*XRES+snakeX;
      c [index] = 0;
    }

    // essen einfärben
    c[food.getY()*XRES+food.getX()] = 2;

    // border einfärben
    if (borders > 0)
    {
      int [] [] b = bl.getBorder();
      for (int i = 0; i < b.length; i++)
      {
        int bX = b[i] [0], bY = b [i] [1];
        int index = bY*XRES+bX;
        c [index] = 1;
      }
    }

    return c;
  }

  private void display(int [] c)
  {
    int x = 0, y = 0;
    noStroke();
    arrayCopy (c, img);
    for (int i = 0; i < c.length; i++)
    {
      x = i % XRES;
      y = i / XRES;

      switch (c[i])
      {
      case 0:
        fill (YELLOW);
        rect (x, y, 1, 1);
        break;
      case 1:
        fill(RED);
        rect (x, y, 1, 1);
        break;
      case 2:
        fill(ORANGE);
        rect (x, y, 1, 1);
        break;
      default:
        //black
        break;
      }
    }
  }

  private void play ()
  {
    snake.move();
    if (borders > 0) checkSnakeBorderIntersection();
    checkSnakeSelfIntersection();
    checkSnakeFoodIntersection();
    display (createColorArray());
  }
}

final int GAMEWIDTH = 640;
final int XRES = 32;
final int YRES = 16;
final float ZOOM = ((float) GAMEWIDTH / (float) XRES);
final float PADDING = 4.5;
final color OFF = color (124, 87, 39);
final color ON = color (255, 234, 113);
final color YELLOW = color (255, 234, 113);
final color ORANGE = color(209, 149, 72);
final color RED = color(103, 39, 16);

Game game;
Serial myPort;
int move = 0;

void setup ()
{
  size (640, 320);

  //
  frameRate (10);

  game = new Game (8);

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

void draw ()
{ 
  background (OFF);
  scale (ZOOM);
  game.draw();
  String val = myPort.readStringUntil('\n');
  if (val != null)
  {
    move = parseVal(val);
    myPort.clear();
  }

  if (move == 0) game.input('u');
  if (move == 1) game.input('d');
  if (move == 2) game.input('l');
  if (move == 3) game.input('r');
}

void keyPressed ()
{
  if (keyCode == ENTER) game.input ('s');
  if (keyCode == UP) game.input('u');
  if (keyCode == DOWN) game.input('d');
  if (keyCode == LEFT) game.input('l');
  if (keyCode == RIGHT) game.input('r');

  if (keyCode == BACKSPACE) game.saveImg("text/" + timestamp());
}

String timestamp()
{
  String time, year, month, day, hour, minute, second;

  year = nf( year(), 4 );
  month = nf( month(), 2 );
  day = nf( day(), 2 );
  hour = nf( hour(), 2 );
  minute = nf( minute(), 2 );
  second = nf( second(), 2 );

  time = year + "_" + month + "_" + day + "_" + hour + "_" + minute + "_" + second;

  return time;
}


float pos;

int parseVal(String val)
{
  try
  {
    pos = Float.parseFloat(val);
    if (pos < 0)
    {
      pos = 360.0 + pos;
    }
    println(pos);
    if (pos >= 0 && pos < 90) return 0;
    else if (pos >= 90 && pos < 180) return 1;
    else if (pos >= 180 && pos < 270) return 2;
    else if (pos >= 270 && pos < 360) return 3;
    else return -1;
  }
  catch (Exception e)
  {
    println("could not parse");
    return -1;
  }
}
