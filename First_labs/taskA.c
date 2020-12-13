#include "graphics.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ESCAPE 27
#define SPACE 32
#define ENTER 13
#define BACKSPACE 8
#define MIN_NUMBER 3
#define MAX_NUMBER 10
#define MAX_COLOR 15
#define MIN_COLOR 1
#define MIN_COORDINATE 1
#define BOTTOM 40
#define PI 3.1415926535897932384626433832795

void parameters(int*n, int*c, int*x, int*y, int*r, int maxx, int maxy);
//function that sets values to the paramethers
void mnogougolnick(int n, int c, int x, int y, int r);
//function that draws a polygon
int round(double d);
//function that rounds double argument into int
int random(int minimum, int maximum);
//function that returns a random value in given interval
int integerPart(double d);
//function that returns integer part of double argument
void clrscr(int maxx, int maxy);
//function that cleans the screen

void main(void)
{
  int gd = DETECT, gm;
  //variables using to inizialize graphcs regime
  int k = 0;
  //meter
  int n, c, x, y, r;
  //variables that sets a polygon
  int maxx, maxy;
  //maximum coordinates of X and Y axises
  int key = 1;
  //code of pressed button
  initgraph(&gd, &gm, "");
  maxx = getmaxx();
  maxy = getmaxy();
  do
  {
    if (!k)
	{
	  parameters(&n, &c, &x, &y, &r, maxx, maxy);
      mnogougolnick(n, c, x, y, r);
	}
    if (anykeypressed())
	{
	  key = readkey();
	  if (!k)
		  if (key == SPACE)
		  {
		    k = 1;
			key = BOTTOM;
		  }
	  if (k)
	  {
	    if (key == ENTER)
	    {
	      parameters(&n, &c, &x, &y, &r, maxx, maxy);
          mnogougolnick(n, c, x, y, r);
	    }
	    if (key == SPACE) 
			k = 0;
	  }
	  if (key == BACKSPACE)
		  clrscr(maxx, maxy);
	}
  } while (key != ESCAPE);
  closegraph();
}

void parameters(int*n, int*c, int*x, int*y, int*r, int maxx, int maxy)
{
  int dx, dy;
  /*interval between coordinats of center of the polygon and 
  maximum coordinates of X and Y axises*/
  int min;
  /*minimum interval between coordinats of center of the polygon 
  and minimum and maximum coordinats of X and Y axises*/
  *n = random(MIN_NUMBER, MAX_NUMBER);
  *c = random(MIN_COLOR, MAX_COLOR);
  *x = random(MIN_COORDINATE, (maxx - 1));
  *y = random(MIN_COORDINATE, (maxy - 1));
  dx = maxx - *x;
  dy = maxy - *y;
  if (dx >= dy) 
	  min = dy;
  else 
	  min = dx;
  if (*x < min) 
	  min = *x;
  if (*y < min) 
	  min = *y;
  *r = rand() % min;
  return;
}

void mnogougolnick(int n, int c, int x, int y, int r)
{
  int x1, y1, x2, y2;
  //coordinats of start and finish pixels of the line
  int i;
  //meter
  double length;
  //length of the side of the polygon
  double lengthX, lengthY;
  //length`s proections on X and Y axises
  int lengthXInt, lengthYInt;
  //rounded length`s proections on X and Y axises
  setcolor(c);
  x1 = x - r;
  y1 = y;
  length = 2 * r * sin(PI / n);
  for (i = 1; i <= n; i++)
 {
    lengthX = -length * cos(PI / 2 - PI / n + 2 * i * PI / n);
    lengthY = -length * sin(PI / 2 - PI / n + 2 * i * PI / n);
    lengthXInt = (int)(lengthX);
    lengthYInt = (int)(lengthY);
    x2 = x1 + lengthXInt;
    y2 = y1 + lengthYInt;
    line(x1, y1, x2, y2);
    x1 = x2;
    y1 = y2;
 }
 return;
}

int round(double d)
{
  int rounded;
  //rounded argument
  int integer;
  //integer part of the argument
  double fractional;
  //fractional part of the argument
  integer = (int)d;
  fractional = d - integer;
  if (fractional >= 0.5)
      rounded = integer + 1;
  else
	  rounded = integer;
  return(rounded);
}

int random(int minimum, int maximum)
{
  int v;
  //random value
  v = rand() % (maximum - minimum);
  v = v + minimum;
  return v;
}

int integerPart(double d)
{
  int i = 0;
  //meter
  double d1 = d;
  //copy of argument that will be changed
  do
  {
    d1 = d1 / 10;
	i++;
  } while (d1 >= 1);
}

void clrscr(int maxx, int maxy)
{
  int i;
  //meter
  setcolor(0);
  //function covers screen with black lines to clean it
  for (i = 0; i <= maxx; i++)
	  line(i, 0, i, maxy);
  return;
}