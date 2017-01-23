#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>

void testRebound(int &x,int &y);
void move();


struct coordinates
{
    int x;
    int y;
};

struct dabbe
{
    int lx;
    int ly;
    int rx;
    int ry;
};

struct block
{
    dabbe coordinates_block;
    int hitCounter;
};

dabbe platform;                                      //Coordinates of bar

coordinates ball;                                    // Coordinates of ball


int testX=1,testY=0,c=0;  			//Test the rebound
char ch; 				//input interprettor
float diff = 5; 			//the difficulty level
void main()
{
    randomize();
    int gd=DETECT,gm;
    initgraph(&gd,&gm, "c://tc/bgi");
    clrscr();
    int maxX = getmaxx()-10;
    int maxY = getmaxy()-10;
    int x = random(maxX-20)+10;
    for( ball.x = x , ball.y = maxY-150, platform.lx=(maxX/2)-50, platform.ly=maxY-90, platform.rx=(maxX/2)+50, platform.ry=maxY-80 ;  ; )
    {
	ch='h';
	setbkcolor(GREEN);
	move();
	setcolor(RED);
	setfillstyle(SOLID_FILL,RED);
	fillellipse(ball.x,ball.y,10,10);
	testRebound(maxX,maxY);
	delay(diff);
	clrscr();
	setcolor(BLUE);
	setfillstyle(SOLID_FILL,BLUE);
	bar3d(platform.lx,platform.ly, platform.rx, platform.ry,5,1);
	if(kbhit())
	ch=getch();

	if(ch=='e')
	  break;

	else if(ch==100)
	{
	 platform.lx+=5;
	 platform.rx+=5;
	}

	else if(ch==97)
	{
	 platform.lx-=5;
	 platform.rx-=5;
	}

	if(ball.x<=platform.rx+9 && ball.x>=platform.lx-9 && ball.y>=maxY-100)
	  testX=1;
	if(c==1)
	    break;

    }
    if(c==1)
    {
       circle(50,50,20) ;
    }
    getch();
    closegraph();
}


void testRebound(int &x,int &y)
{
    if (ball.x == x)
	testY=1;
    else if(ball.x== 10)
	testY=0;
    if (ball.y == 10)
	testX=0;
    if(ball.y == y - 81)
	c = 1;
 }


void move()
{
    if (testX == 0) //if ball touches the top
	ball.y++;
    else if (testX == 1) //if ball touches bottom/bar
	ball.y--;
   if (testY == 0) //if ball touches left
	ball.x++;
    else if (testY == 1) //if ball touches right
	ball.x--;
}
