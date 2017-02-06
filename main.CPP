#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <time.h>

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
int size=0;
int testX = 1, testY = 0; //Test the rebound
char ch; //input interprettor
int diff = 20; //the difficulty level
const int len=21;
dabbe b[len] = {
	      { 0,0,124,20,2},{124,0,248,20,2},{248,0,392,20,2},{392,0,516,20,2},{516,0,640,20,2},
	      { 124,40,248,60,2},{ 248,60,392,80,2},{392,40,516,60,2},
	      { 0,60,124,80,2},{124,80,248,100,2},{248,100,392,120,2},{392,80,516,100,2},{516,60,640,80,2},
	      { 0,120,124,140,2},{124,140,248,160,2},{248,160,392,180,2},{392,140,516,160,2},{516,120,640,140,2},
	      { 124,60,248,80,3},{248,80,392,100,3},{392,60,516,80,3}
	      };

void main() {
  randomize();

  int gd = DETECT, gm;
  initgraph( & gd, & gm, "c://turboc3/bgi");
  clrscr();

  int check1=0,check2=0,check1_ball=0,check2_ball=0,diff_time,diff_ball_time,check1_bar=0,check2_bar=0,diff_bar_time,speed=0;
  time_t start_t,end_t,start_ball_t,end_ball_t,start_bar_t,end_bar_t;
  int maxX = getmaxx() - 10;
  int maxY = getmaxy() - 10;
  int x = random(maxX - 20) + 10;

  for (ball.x = x, ball.y = maxY - 150, platform.lx = (maxX/2)-(50), platform.ly = maxY - 20, platform.rx = (maxX / 2) + (50) , platform.ry = maxY - 10;;)
   {
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
    bar(platform.lx-size, platform.ly, platform.rx + size, platform.ry);


  for (int i = 0; i < len; i++)
   {
     if(i!=19&&i!=18&&i!=20)
     {

       if(b[i].hitCounter==2)
     {
      setcolor(BLACK);
      setfillstyle(SOLID_FILL, 8);
     }
     else if(b[i].hitCounter==1)
     {
       setcolor(BLACK);
       setfillstyle(SOLID_FILL, 7);
     }
      if (b[i].hitCounter > 0)
	bar(b[i].lx, b[i].ly, b[i].rx, b[i].ry);
    }
    else
     {
	if(b[i].hitCounter==3)
     {
      setcolor(BLACK);
      setfillstyle(SOLID_FILL, 12);
     }
     else if(b[i].hitCounter==2)
     {
       setcolor(BLACK);
       setfillstyle(SOLID_FILL, 13);
     }
     else if(b[i].hitCounter==1)
     {
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,13);
	 }
      if (b[i].hitCounter > 0)
	bar(b[i].lx, b[i].ly, b[i].rx, b[i].ry);
	 }
   }

     if (ball.x <= platform.rx + 10 + size && ball.x >= platform.lx - 10 - size && ball.y >= maxY - 30)
     testX = 1;

    if(ball.y>=maxY-15)
     break;

    if (kbhit())
      ch = getch();
    if (ch == 'e')
      break;

    else if (ch == 100) {
      platform.lx += (7+speed);
      platform.rx += (7+speed);
    } else if (ch == 97) {
      platform.lx -=(7+speed);
      platform.rx -=(7+speed);
    }

    if(b[18].hitCounter==0)
     check1++;

    if(check1==1)
     {
      check2=1;
      time(&start_t);
      size=50;
     }
    if(check2==1)
     {
      time(&end_t);
      diff_time=difftime(end_t,start_t);
       if(diff_time==15)
       {
	     check2=0;
	     size=0;
       }
     }

     if(b[19].hitCounter==0)
     check1_ball++;

    if(check1_ball==1)
     {
      check2_ball=1;
      time(&start_ball_t);
      diff+=10;
     }
    if(check2_ball==1)
     {
      time(&end_ball_t);
      diff_ball_time=difftime(end_ball_t,start_ball_t);
       if(diff_ball_time>=15)
       {
	     check2_ball=0;
	     diff-=10;
       }
     }

     if(b[20].hitCounter==0)
     check1_bar++;

    if(check1_bar==1)
     {
      check2_bar=1;
      time(&start_bar_t);
      speed=5;
     }
    if(check2_bar==1)
     {
      time(&end_bar_t);
      diff_bar_time=difftime(end_bar_t,start_bar_t);
       if(diff_bar_time==15)
       {
	     check2_bar=0;
	     speed=0;
       }
     }







  }

  closegraph();
}

void testRebound(int & x, int & y) {
  if (ball.x == x||ball.x==x-1||ball.x==x+1)
    testY = 1;
  else if (ball.x == 10||ball.x==11||ball.x==9)
    testY = 0;
  if (ball.y == 10||ball.y==11||ball.x==9)
    testX = 0;

  for (int i = 0; i < len; i++) {
    if (b[i].hitCounter > 0)
     {
      if ((ball.x == b[i].lx - 10||ball.x == b[i].lx - 11 ||ball.x == b[i].lx - 9) && (ball.y >= b[i].ly-10) && (ball.y <= b[i].ry+10))
      {
	testY = 1;       //ball touches left side
	b[i].hitCounter--;
      }
      if ((ball.y == b[i].ry + 10||ball.y == b[i].ry + 11 ||ball.y == b[i].ry + 9) && (ball.x >= b[i].lx-10) && (ball.x <= b[i].rx+10))
      {
	testX = 0;   //ball touches the bottom side
	b[i].hitCounter--;
      }
      if ((ball.x == b[i].rx + 10||ball.x == b[i].rx + 11 ||ball.x == b[i].rx + 9 ) && (ball.y >= b[i].ly-10) && (ball.y <= b[i].ry+10))
      {
	testY = 0; //ball touches right side
	b[i].hitCounter--;
      }

      if ((ball.y == b[i].ly - 10||ball.y == b[i].ly - 11 ||ball.y == b[i].ly - 9) && (ball.x >= b[i].lx-10) && (ball.x <= b[i].rx+10))
      {
	testX = 1; //ball touches upper side
	b[i].hitCounter--;
      }
    }
  }


}
void move() {
  if (testX == 0) //if ball touches the top
    ball.y+=3;
  else if (testX == 1) //if ball touches bottom/bar
    ball.y-=3;
  if (testY == 0) //if ball touches left
    ball.x+=3;
  else if (testY == 1) //if ball touches right
    ball.x-=3;
}
