#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>


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

dabbe platform;                                      //coordinates of bar

struct blocks
{
    dabbe blks; 				    //coordinate of rectangles
    int hitCounter;				    //Hit Counter
};
coordinates ball;                                    // Coordinates of ball

int testX=1,testY=0;  //Test the rebound
char ch; //input interprettor
float diff = 7 ; //the difficulty level

blocks b[5] = {{ { 50 , 50 , 150 , 100 } , 0 },{ { 160 , 50 , 260 , 100 } , 0 },{ { 270 , 50 , 370 , 100 }, 0 },{ { 380 , 50 , 480 , 100 }, 0 },{ { 490 , 50 , 590 , 100 }, 0 }};

//blocks  b1 = { { 50 , 50 , 150 , 100 } , 0 }
//	,b2 = { { 160 , 50 , 260 , 100 } , 0 }
//	,b3 = { { 270 , 50 , 370 , 100 }, 0 }
//	,b4 = { { 380 , 50 , 480 , 100 }, 0 }
//	,b5 = { { 490 , 50 , 590 , 100 }, 0 };

void main()
{
    randomize();

    int gd=DETECT,gm;
    initgraph(&gd,&gm, "c://tc/bgi");
    clrscr();

    int maxX = getmaxx()-10;
    int maxY = getmaxy()-10;
    int x = random(maxX-20)+10;
    
//    for (int i = 0 ; i < 5 ; i++)
//    {
//        b[i].blks = { 50 + 110*i , 50 , 150 + 110*i , 100 } ;
//    }
//    b[0] = { { 50 , 50 , 150 , 100 } , 0 };
//    b[1] = { { 160 , 50 , 260 , 100 } , 0 };
//    b[2] = { { 270 , 50 , 370 , 100 }, 0 };
//    b[3] = { { 380 , 50 , 480 , 100 }, 0 };
//    b[4] = { { 490 , 50 , 590 , 100 }, 0 };

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
	cleardevice();
        setcolor(BLUE);
        setfillstyle(SOLID_FILL,BLUE);
        bar(platform.lx,platform.ly, platform.rx, platform.ry);
        setcolor(RED);
        setfillstyle(SOLID_FILL,RED);
        
        for(int i=0;i<5;i++)
        {
            bar(b[i].blks.lx , b[i].blks.ly , b[i].blks.rx , b[i].blks.ry); 
        }

    //	bar(b1.blks.lx , b1.blks.ly , b1.blks.rx , b1.blks.ry);
    //
    //	bar( b2.blks.lx , b2.blks.ly , b2.blks.rx , b2.blks.ry);
    //
    //	bar ( b3.blks.lx , b3.blks.ly , b3.blks.rx , b3.blks.ry );
    //
    //	bar ( b4.blks.lx , b4.blks.ly , b4.blks.rx , b4.blks.ry );
    //
    //	bar ( b5.blks.lx , b5.blks.ly , b5.blks.rx , b5.blks.ry );

        if( kbhit() )
        ch = getch();
        if( ch == 'e')
          break;

        else if( ch==100 )
        {
         platform.lx += 5;
         platform.rx += 5;
        }

        else if( ch == 97 )
        {
         platform.lx -= 5;
         platform.rx -=5 ;
        }

        if(ball.x <= platform.rx + 9 && ball.x >= platform.lx - 9 && ball.y >= maxY - 100 )
          testX = 1;
    }
    getch();
    closegraph();
}


void testRebound(int &x,int &y)
{
    if (ball.x == x)
	testY = 1;
    else if(ball.x==10)
	testY = 0;
    if (ball.y == 10)
	testX = 0;
    
    for (int i = 0 ; i < 5 ; i ++ )
    {
          if ( (ball.x == b[i].blks.lx - 10) && (ball.y >= b[i].blks.ly) && (ball.y <= b[i].blks.ry))
            testY = 1;
        if ( (ball.y == b[i].blks.ry + 10) && (ball.x >= b[i].blks.lx) && (ball.x <= b[i].blks.rx ))
            testX = 0;
        if( (ball.x == b[i].blks.rx + 10) && (ball.y >= b[i].blks.ly) && (ball.y <= b[i].blks.ry))
            testY=0;
        if( (ball.y == b[i].blks.ly - 10) && (ball.x >= b[i].blks.lx) && (ball.x <= b[i].blks.rx ))
            testX=1;

    }
//    if ( (ball.x == b1.blks.lx - 10) && (ball.y >= b1.blks.ly) && (ball.y <= b1.blks.ry))
//	testY = 1;
//    if ( (ball.y == b1.blks.ry + 10) && (ball.x >= b1.blks.lx) && (ball.x <= b1.blks.rx ))
//	testX = 0;
//    if( (ball.x == b1.blks.rx + 10) && (ball.y >= b1.blks.ly) && (ball.y <= b1.blks.ry))
//	testY=0;
//    if( (ball.y == b1.blks.ly - 10) && (ball.x >= b1.blks.lx) && (ball.x <= b1.blks.rx ))
//	testX=1;
//    
//    
//    if ( (ball.x == b2.blks.lx - 10) && (ball.y >= b2.blks.ly) && (ball.y <= b2.blks.ry))
//	testY=1;
//    if ( (ball.y == b2.blks.ry + 10) && (ball.x >= b2.blks.lx) && (ball.x <= b2.blks.rx ))
//	testX=0;
//    if( (ball.x == b2.blks.rx + 10) && (ball.y >= b2.blks.ly) && (ball.y <= b2.blks.ry))
//	testY=0;
//    if( (ball.y == b2.blks.ly - 10) && (ball.x >= b2.blks.lx) && (ball.x <= b2.blks.rx ))
//	testX=1;
//    
//    
//    if ( (ball.x == b3.blks.lx - 10) && (ball.y >= b3.blks.ly) && (ball.y <= b3.blks.ry))
//	testY=1;
//    if ( (ball.y == b3.blks.ry + 10) && (ball.x >= b3.blks.lx) && (ball.x <= b3.blks.rx ))
//	testX=0;
//    if( (ball.x == b3.blks.rx + 10) && (ball.y >= b3.blks.ly) && (ball.y <= b3.blks.ry))
//	testY=0;
//    if( (ball.y == b3.blks.ly - 10) && (ball.x >= b3.blks.lx) && (ball.x <= b3.blks.rx ))
//	testX=1;
//    
//
//    if ( (ball.x == b4.blks.lx - 10) && (ball.y >= b4.blks.ly) && (ball.y <= b4.blks.ry))
//	testY=1;
//    if ( (ball.y == b4.blks.ry + 10) && (ball.x >= b4.blks.lx) && (ball.x <= b4.blks.rx ))
//	testX=0;
//    if( (ball.x == b4.blks.rx + 10) && (ball.y >= b4.blks.ly) && (ball.y <= b4.blks.ry))
//	testY=0;
//    if( (ball.y == b4.blks.ly - 10) && (ball.x >= b4.blks.lx) && (ball.x <= b4.blks.rx ))
//	testX=1;
//    
//    if ( (ball.x == b5.blks.lx - 10) && (ball.y >= b5.blks.ly) && (ball.y <= b5.blks.ry))
//	testY=1;
//    if ( (ball.y == b5.blks.ry + 10) && (ball.x >= b5.blks.lx) && (ball.x <= b5.blks.rx ))
//	testX=0;
//    if( (ball.x == b5.blks.rx + 10) && (ball.y >= b5.blks.ly) && (ball.y <= b5.blks.ry))
//	testY=0;
//    if( (ball.y == b5.blks.ly - 10) && (ball.x >= b5.blks.lx) && (ball.x <= b5.blks.rx ))
//	testX=1;
//

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
