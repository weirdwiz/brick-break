#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>

 void testRebound(int & x, int & y);
void move();

struct coordinates {
  int x;
  int y;
};

struct dabbe {
  int lx;
  int ly;
  int rx;
  int ry;
  int hitCounter;
};

dabbe platform; //coordinates of bar


coordinates ball; // Coordinates of ball

int testX = 1, testY = 0; //Test the rebound
char ch; //input interprettor
int diff = 5; //the difficulty level

dabbe b[5] = {
	      { 50,50,150,100,2},{160,50,260,100,2},{270,50,370,100,2},{380,50,480,100,2},{490,50,590,100,2}
	     };

void main() {
  randomize();

  int gd = DETECT, gm;
  initgraph( & gd, & gm, "c://turboc3/bgi");
  clrscr();

  int maxX = getmaxx() - 10;
  int maxY = getmaxy() - 10;
  int x = random(maxX - 20) + 10;

  for (ball.x = x, ball.y = maxY - 150, platform.lx = (maxX/2)-50, platform.ly = maxY - 20, platform.rx = (maxX / 2) + 50, platform.ry = maxY - 10;;) {
    ch = 'h';

    setbkcolor(GREEN);

    move();
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    fillellipse(ball.x, ball.y, 10, 10);

    testRebound(maxX, maxY);
    delay(diff);
    cleardevice();
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(platform.lx, platform.ly, platform.rx, platform.ry);


    for (int i = 0; i < 5; i++)
    {
     if(b[i].hitCounter==2)
     {
      setcolor(RED);
      setfillstyle(SOLID_FILL, RED);
     }
     if(b[i].hitCounter==1)
     {
       setcolor(BLUE);
       setfillstyle(SOLID_FILL, BLUE);
     }
      if (b[i].hitCounter > 0)
	bar(b[i].lx, b[i].ly, b[i].rx, b[i].ry);
    }

     if (ball.x <= platform.rx + 5 && ball.x >= platform.lx - 5 && ball.y >= maxY - 30)
    testX = 1;
    if(ball.y==maxY+10)
     break;

    if (kbhit())
      ch = getch();
    if (ch == 'e')
      break;

    else if (ch == 100) {
      platform.lx += 5;
      platform.rx += 5;
    } else if (ch == 97) {
      platform.lx -= 5;
      platform.rx -= 5;
    }

  }

  closegraph();
}

void testRebound(int & x, int & y) {
  if (ball.x == x)
    testY = 1;
  else if (ball.x == 10)
    testY = 0;
  if (ball.y == 10)
    testX = 0;

  for (int i = 0; i < 5; i++) {
    if (b[i].hitCounter > 0)
     {
      if ((ball.x == b[i].lx - 10) && (ball.y >= b[i].ly-5) && (ball.y <= b[i].ry+5))
      {
	testY = 1;       //ball touches left side
	b[i].hitCounter--;
      }
      if ((ball.y == b[i].ry + 10) && (ball.x >= b[i].lx-5) && (ball.x <= b[i].rx+5))
      {
	testX = 0;   //ball touches the bottom side
	b[i].hitCounter--;
      }
      if ((ball.x == b[i].rx + 10) && (ball.y >= b[i].ly-5) && (ball.y <= b[i].ry+5))
      {
	testY = 0; //ball touches right side
	b[i].hitCounter--;
      }

      if ((ball.y == b[i].ly - 10) && (ball.x >= b[i].lx-5) && (ball.x <= b[i].rx+5))
      {
	testX = 1; //ball touches upper side
	b[i].hitCounter--;
      }
    }
  }


}
void move() {
  if (testX == 0) //if ball touches the top
    ball.y++;
  else if (testX == 1) //if ball touches bottom/bar
    ball.y--;
  if (testY == 0) //if ball touches left
    ball.x++;
  else if (testY == 1) //if ball touches right
    ball.x--;
}
