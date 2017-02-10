#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream.h>
void testRebound(int& x, int& y);
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

dabbe platform;  // coordinates of bar

coordinates ball;  // Coordinates of ball
int score = 0;
int size = 0;
int balls = 10;
int testX = 1, testY = 0;  // Test the rebound
char ch;  // input interprettor
int diff = 20;  // the difficulty level
const int len = 21;
int endGame = len;
dabbe b[len] = {
    {0, 0, 124, 20, 2},      {124, 0, 248, 20, 2},    {248, 0, 392, 20, 2},
    {392, 0, 516, 20, 2},    {516, 0, 640, 20, 2},    {124, 40, 248, 60, 2},
    {248, 60, 392, 80, 2},   {392, 40, 516, 60, 2},   {0, 60, 124, 80, 2},
    {124, 80, 248, 100, 2},  {248, 100, 392, 120, 2}, {392, 80, 516, 100, 2},
    {516, 60, 640, 80, 2},   {0, 120, 124, 140, 2},   {124, 140, 248, 160, 2},
    {248, 160, 392, 180, 2}, {392, 140, 516, 160, 2}, {516, 120, 640, 140, 2},
    {124, 60, 248, 80, 3},   {248, 80, 392, 100, 3},  {392, 60, 516, 80, 3}};

int main() {
  randomize();

  int gd = DETECT, gm;
  initgraph(&gd, &gm, "c://turboc3/bgi");
  cleardevice();

  int inpu, inpu1, inpu2;
  int check1 = 0, check2 = 0, check1_ball = 0, check2_ball = 0, diff_time,
      diff_ball_time, check1_bar = 0, check2_bar = 0, diff_bar_time, speed = 0;
  time_t start_t, end_t, start_ball_t, end_ball_t, start_bar_t, end_bar_t;
  char scoreBoard[50];
  int maxX = getmaxx() - balls;
  int maxY = getmaxy() - balls;
  int x = random(maxX - 20) + 10;
  setbkcolor(BLACK);
  for (;;) {
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
    outtextxy((maxX / 2) - 300, (maxY / 2 - 100), "BRICK BREAKER");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy((maxX / 2) - 300, (maxY / 2 + 20),
              "Press Enter to start        Controls: A for left D for right ");
    outtextxy((maxX / 2) - 300, (maxY / 2 + 40), "Press Esc to exit");
    outtextxy((maxX / 2) - 300, (maxY / 2 + 60), "Press S for settings");
    if (kbhit())
      ch = getch();
    if (ch == 13)
      break;
    if (ch == 27)
      return 0;
    if (ch == 's') {
      cout << "1.    difficulty" << endl << "2.    ballsize\n";
      cin >> inpu;
      if (inpu == 1) {
        cout << "1.     easy" << endl
             << "2.     medium" << endl
             << "3.     pro" << endl
             << "4.   god\n";
        cin >> inpu1;
        if (inpu1 == 1)
          diff = 20;
        else if (inpu1 == 2)
          diff = 15;
        else if (inpu1 == 3)
          diff = 10;
        else
          diff = 3;
      } else {
        cout << "1.    big" << endl << "2.    mid" << endl << "3.     small\n";
        cin >> inpu2;
        if (inpu2 == 1)
          balls = 15;
        else if (inpu2 == 2)
          balls = 10;
        else
          balls = 5;
      }
      cleardevice();
    }
    ch = '0';
  }
  for (ball.x = x, ball.y = maxY - 150, platform.lx = (maxX / 2) - (50),
      platform.ly = maxY - 20, platform.rx = (maxX / 2) + (50),
      platform.ry = maxY - 10;
       ;) {
    ch = 'h';

    setbkcolor(GREEN);

    move();
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    fillellipse(ball.x, ball.y, balls, balls);

    testRebound(maxX, maxY);
    delay(diff);
    cleardevice();
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    platform.lx -= size;
    platform.rx += size;
    bar(platform.lx, platform.ly, platform.rx, platform.ry);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    sprintf(scoreBoard, "Score : %d", score);
    outtextxy(maxX - 200, maxY - 150, scoreBoard);

    for (int i = 0; i < len; i++) {
      if (i != 19 && i != 18 && i != 20) {
        if (b[i].hitCounter == 2) {
          setcolor(BLACK);
          setfillstyle(SOLID_FILL, 8);
        } else if (b[i].hitCounter == 1) {
          setcolor(BLACK);
          setfillstyle(SOLID_FILL, 7);
        }
        if (b[i].hitCounter > 0)
          bar(b[i].lx, b[i].ly, b[i].rx, b[i].ry);
      } else {
        if (b[i].hitCounter == 3) {
          setcolor(BLACK);
          setfillstyle(SOLID_FILL, 12);
        } else if (b[i].hitCounter == 2) {
          setcolor(BLACK);
          setfillstyle(SOLID_FILL, 13);
        } else if (b[i].hitCounter == 1) {
          setcolor(BLACK);
          setfillstyle(SOLID_FILL, 14);
        }
        if (b[i].hitCounter > 0)
          bar(b[i].lx, b[i].ly, b[i].rx, b[i].ry);
      }
    }

    if (ball.x <= platform.rx + balls + size &&
        ball.x >= platform.lx - balls - size && ball.y >= maxY - (20 + balls))
      testX = 1;

    if (ball.y >= maxY - 15)
      break;

    if (kbhit())
      ch = getch();
    if (ch == 27)
      break;

    else if (ch == 100) {
      platform.lx += (7 + speed);
      platform.rx += (7 + speed);
    } else if (ch == 97) {
      platform.lx -= (7 + speed);
      platform.rx -= (7 + speed);
    }

    if (b[18].hitCounter == 0)
      check1++;

    if (check1 == 1) {
      check2 = 1;
      time(&start_t);
      size = 50;
    }
    if (check2 == 1) {
      time(&end_t);
      diff_time = difftime(end_t, start_t);
      if (diff_time == 15) {
        check2 = 0;
        size = 0;
      }
    }

    if (b[19].hitCounter == 0)
      check1_ball++;

    if (check1_ball == 1) {
      check2_ball = 1;
      time(&start_ball_t);
      diff += 10;
    }
    if (check2_ball == 1) {
      time(&end_ball_t);
      diff_ball_time = difftime(end_ball_t, start_ball_t);
      if (diff_ball_time >= 15) {
        check2_ball = 0;
        diff -= 10;
      }
    }

    if (b[20].hitCounter == 0)
      check1_bar++;

    if (check1_bar == 1) {
      check2_bar = 1;
      time(&start_bar_t);
      speed = 5;
    }
    if (check2_bar == 1) {
      time(&end_bar_t);
      diff_bar_time = difftime(end_bar_t, start_bar_t);
      if (diff_bar_time == 15) {
        check2_bar = 0;
        speed = 0;
      }
    }

    if (endGame == 0)
      break;

    if (platform.lx <= 0 && platform.rx <= 0) {
      platform.lx = maxX + balls - 100;
      platform.rx = maxX + balls;
    }
    if (platform.rx >= maxX + balls && platform.lx >= maxX + balls) {
      platform.rx = 100;
      platform.lx = 0;
    }
  }
  clrscr();
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
  if (endGame == 0)
    outtextxy((maxX / 2) - 200, (maxY / 2), "You Win! :)");
  else
    outtextxy((maxX / 2) - 250, (maxY / 2), "You Lose! :(");
  outtextxy((maxX / 2) - 250, (maxY / 2) - 50, scoreBoard);
  getch();
  closegraph();
  return 0;
}

void testRebound(int& x, int& y) {
  if (ball.x == x || ball.x == x - 1 || ball.x == x + 1)
    testY = 1;
  else if (ball.x == balls || ball.x == balls + 1 || ball.x == balls - 1)
    testY = 0;
  if (ball.y == 10 || ball.y == balls + 1 || ball.x == balls - 1)
    testX = 0;

  for (int i = 0; i < len; i++) {
    if (b[i].hitCounter > 0) {
      if ((ball.x == b[i].lx - balls || ball.x == b[i].lx - (balls + 1) ||
           ball.x == b[i].lx - (balls - 1)) &&
          (ball.y >= b[i].ly - balls) && (ball.y <= b[i].ry + balls)) {
        testY = 1;  // ball touches left side
        b[i].hitCounter--;
        if (b[i].hitCounter == 0) {
          score += 50;
          endGame--;
        }
      }
      if ((ball.y == b[i].ry + balls || ball.y == b[i].ry + (balls + 1) ||
           ball.y == b[i].ry + (balls - 1)) &&
          (ball.x >= b[i].lx - balls) && (ball.x <= b[i].rx + balls)) {
        testX = 0;  // ball touches the bottom side
        b[i].hitCounter--;
        if (b[i].hitCounter == 0) {
          score += 50;
          endGame--;
        }
      }
      if ((ball.x == b[i].rx + balls || ball.x == b[i].rx + balls + 1 ||
           ball.x == b[i].rx + balls - 1) &&
          (ball.y >= b[i].ly - balls) && (ball.y <= b[i].ry + balls)) {
        testY = 0;  // ball touches right side
        b[i].hitCounter--;
        if (b[i].hitCounter == 0) {
          score += 50;
          endGame--;
        }
      }

      if ((ball.y == b[i].ly - balls || ball.y == b[i].ly - (balls + 1) ||
           ball.y == b[i].ly - (balls - 1)) &&
          (ball.x >= b[i].lx - balls) && (ball.x <= b[i].rx + balls)) {
        testX = 1;  // ball touches upper side
        b[i].hitCounter--;
        if (b[i].hitCounter == 0) {
          score += 50;
          endGame--;
        }
      }
    }
  }
}
void move() {
  if (testX == 0)  // if ball touches the top
    ball.y += 3;
  else if (testX == 1)  // if ball touches bottom/bar
    ball.y -= 3;
  if (testY == 0)  // if ball touches left
    ball.x += 3;
  else if (testY == 1)  // if ball touches right
    ball.x -= 3;
}
