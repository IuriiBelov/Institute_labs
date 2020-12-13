#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

#define ONE 10
#define TEN 10
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define ESCAPE 27

void settingCoordinates(double *x, double *y, int maxx, int maxy);
//function that sets coordinates of x1, y1, x2 and y2
void kursor(double x, double y);
//function that draws a cursor
void moveKursor(double *x, double *y, int key, int maxx, int maxy);
//function that moves the cursor to one position
void drawFraktal(int n, double x1, double y1, double x2, double y2);
//function that draws the curve
double maximum(double a, double b);
//function that counts maximum of two arguments
double minimum(double a, double b);
//function that counts minimum of two arguments
double perestanovki(double a, double b, double c);
//auxiliary function
//void calculationOne(double x1, double y1, double *x, double *y);
//auxiliary function
//void calculationTwo(double x1, double x2, double y1, double y2, double *x, double *y);
//auxiliary function
//void calculationThree(double a, double b, double c, double *x, double *y);
//auxiliary function

typedef struct element
{
  double xCoordinate;
  double yCoordinate;
  element *previousElement, lastElement;
}

void makeList(double x1, double x2, double y1, double y2);
//function that makes a linked list of two elements
void addElement(element *previous, element *next, double xCoordinate, double yCoordinate);
//function that adds an element to the linked list
void deleteElement(element *elem);
//function that deletes an element from the list

void main(void)
{
  int gd = DETECT, gm;
  //variables used to inizialize graphics regime
  double x1, y1, x2, y2;
  //coordinates of two basic points
  int key = 1;
  //code of pressed button
  int maxx, maxy;
  //maximum coordinates of X and Y axises
  int n = 0;
  //number of interation
  initgraph(&gd, &gm, "");
  maxx = getmaxx();
  maxy = getmaxy();
  x1 = maxx / 2;
  y1 = maxy / 2;
  x2 = x1;
  y2 = y1;
  settingCoordinates(&x1, &y1, maxx, maxy);
  settingCoordinates(&x2, &y2, maxx, maxy);
  cleardevice();
  makeList(x1, y1, x2, y2);
  drawFraktal(n, x1, y1, x2, y2);
  do
  {
    if (anykeypressed())
    {
      key = readkey();
      if (key == LEFT)
      {
        cleardevice();
        if (n > 0)
          n = n - 1;
        drawFraktal(n, x1, y1, x2, y2);
      }
      if (key == RIGHT)
      {
        cleardevice();
        n = n + 1;
        drawFraktal(n, x1, y1, x2, y2);
      }
    }
  } while (key != ESCAPE);
  closegraph();
}

void settingCoordinates(double *x, double *y, int maxx, int maxy)
{
  int key = 1;
  //code of pressed button
  kursor((int)(*x), (int)(*y));
  do
  {
    if (anykeypressed())
    {
      key = readkey();
      moveKursor(x, y, key, maxx, maxy);
    }
  } while (key != ENTER);
  return;
}

void moveKursor(double *x, double *y, int key, int maxx, int maxy)
{
  setcolor(BLACK);
  kursor(*x, *y);
  setcolor(WHITE);
  switch (key)
  {
  case UP:
    if (*y > 0)
      *y = *y - ONE;
    break;
  case DOWN:
    if (*y < maxy)
      *y = *y + ONE;
    break;
  case LEFT:
    if (*x > 0)
      *x = *x - ONE;
    break;
  case RIGHT:
    if (*x < maxx)
      *x = *x + ONE;
    break;
  }
  kursor(*x, *y);
  return;
}

void kursor(double x, double y)
{
  line((int)(x), ((int)(y) - TEN), (int)(x), ((int)(y) + TEN));
  line(((int)(x) - TEN), (int)(y), ((int)(x) + TEN), (int)(y));
  return;
}

void drawFraktal(int n, double x1, double y1, double x2, double y2)
{
  /*double x, y;*/
  if (n == 0)
    line((int)(first->xCoordinate), (int)(first->yCoordinate), (int)(last->xCoordinate), 
        (int)(last->yCoordinate));
  /*if ((x2 - x1 == y2 - y1) || (x2 - x1 == y1 - y2))
  {
    if (((x2 > x1) && (y2 < y1)) || ((x2 < x1) && (y2 > y1)))
    calculationOne(x1, y2, &x, &y);
    if (((x2 > x1) && (y2 > y1)) || ((x2 < x1) && (y2 < y1)))
    calculationOne(x2, y1, &x, &y);
  }
  else
    calculationTwo(x1, y1, x2, y2, &x, &y);
  if (((x1 == x2) && (y1 > y2)) || ((x1 == x2) && (y1 < y2)))
    calculationThree(x1, y2, y1, &x, &y);
  if (((x1 < x2) && (y1 == y2)) || ((x1 > x2) && (y1 == y2)))
    calculationThree(y1, x1, x2, &y, &x);
  if (n == 1)
  {
    line((int)(x1), (int)(y1), (int)(x), (int)(y));
    line((int)(x), (int)(y), (int)(x2), (int)(y2));
  }
  if (n > 1)
  {
    drawFraktal((n - 1), x1, y1, x, y);
    drawFraktal((n - 1), x, y, x2, y2);
  }*/
  return;
}

double maximum(double a, double b)
{
  double max = 0;
  if (a >= b)
    max = a;
  if (a < b)
    max = b;
  return max;
}

double minimum(double a, double b)
{
  double min = 0;
  if (a >= b)
    min = b;
  if (a < b)
    min = a;
  return min;
}

double perestanovki(double a, double b, double c)
{
  double rez;
  rez = a * b - b * c - a * c;
  return rez;
}

/*void calculationOne(double x1, double y1, double *x, double *y)
{
  *x = x1;
  *y = y1;
  return;
}

void calculationTwo(double x1, double y1, double x2, double y2, double *x, double *y)
{
  double xmax, ymax;
  double xmin, ymin;
  xmax = maximum(x1, x2);
  ymax = maximum(y1, y2);
  xmin = minimum(x1, x2);
  ymin = minimum(y1, y2);
  if (((x2 > x1) && (y2 > y1)) || ((x2 > x1) && (y2 < y1)))
  {
    *y = (ymin * ymin - xmin * xmin - xmax * xmax - ymax * ymax - 2 * perestanovki(xmin, ymax, xmax)) / (2 * (xmax - xmin - ymax + ymin));
    if ((x2 > x1) && (y2 > y1))
    *x = xmin + ymax - *y;
  if ((x2 > x1) && (y2 < y1))
    *x = *y - ymax + xmax;
  }
  if (((x2 < x1) && (y2 > y1)) || ((x2 < x1) && (y2 < y1)))
  {
    *y = (ymax * ymax - xmin * xmin - ymin * ymin - xmax * xmax - 2 * perestanovki(xmax, ymin, xmin)) / (2 * (ymax + xmin - xmax - ymin));
    if ((x2 < x1) && (y2 > y1))
    *x = *y + xmin - ymin;
  if ((x2 < x1) && (y2 < y1))
    *x = xmax + ymin - *y;
  }
  return;
}

void calculationThree(double a, double b, double c, double *x, double *y)
{
  *x = a + (b - c) / 2;
  *y = (b + c) / 2;
  return;
}*/

void makeList(double x1, double x2, double y1, double y2)
{
  element *first = malloc(sizeof(element));
  element *last = malloc(sizeof(element));
  first->xCoordinate = x1;
  first->yCoordinate = y1;
  last->xCoordinate = x2;
  last->yCoordinate = y2;
  first->previousElement = NULL;
  first->nextElement = last;
  last->previousElement = first;
  last->lastElement = NULL;
  return;
}

void addElement(element *previous, element *next, double xCoordinate, double yCoordinate)
{
  element *current = malloc(sizeof(element));
  current->xCoordinate = xCoordinate;
  current->yCoordinate = yCoordinate;
  current->previousElement = previous;
  current->nextElement = next;
  previous->nextElement = current;
  next->previousElement = current;
  return;
}

void deleteElement(element *elem)
{
  element *elemPrevious = malloc(sizeof(element)), elemNext = malloc(sizeof(element));
  elemPrevious = elem->previousElement;
  elemNext = elem->nextElement;
  elem->previousElement = elemPrevious->previousElement;
  elem->nextElement = elemNext->nextElement;
  free(elemPrevious);
  free(elemNext);
  return;
}