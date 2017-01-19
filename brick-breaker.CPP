
#include<graphics.h>
#include<conio.h>
#include<dos.h>

void testRebound(int &x,int &y);
void move();


struct coordinates
{
    int x;
    int y;
};

coordinates ball;                                    // Coordinates of ball
//coordinates bar;

int testX=1,testY=0;  //Test the rebound
float diff = 20 ; //the difficulty level


void main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm, "c://tc/bgi");
    clrscr();
    int maxX = getmaxx()-10;
    int maxY = getmaxy()-10;
    for( ball.x = maxX/2 , ball.y = maxY ;  ; )
    {
	move();
	setcolor(RED);
	circle(ball.x,ball.y,10);
	testRebound(maxX,maxY);
	delay(diff);
	clrscr();
	if (ball.y == 0)
	    break;
    }
    getch();
    closegraph();
}


void testRebound(int &x,int &y)
{
    if (ball.x == x)
	testY=1;
    else if (ball.y == 0)
	testX=0;
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