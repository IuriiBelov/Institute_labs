#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "graphics.h"

#define LEFT 72
#define RIGHT 80
#define UP 75
#define DOWN 77
#define ENTER 13
#define SPACE 32
#define ESCAPE 27
#define QUANTITY 20
#define ALIVE 1
#define DEAD 0
#define NEIGHBOURS 8
#define ACTIVE 1
#define PASSIVE 0

typedef struct tag_bacteria
  {
    int alive;
    int x1Coordinate;
    int y1Coordinate;
    int x2Coordinate;
    int y2Coordinate;
  };
//struct that consists condition of bacteria and its coordinates

void startConditions(struct tag_bacteria *(*massiveOfBacteries)[QUANTITY]);
//function that sets start conditions of bacteries (dead)
void setCoordinates(int xmax, int ymax, struct tag_bacteria *(*massiveOfBacteries)[QUANTITY]);
//function that sets coordinates of bacteries
void drawCoordinateScale(int xmax, int ymax, struct tag_bacteria *(*massiveOfBacteries)[QUANTITY]);
//function that draws a coordinate scale
void cursor(int x1, int y1, int x2, int y2, int status);
//function that draws a cursor
void drawBacteria(int x1, int y1, int x2, int y2, int status);
//function that draws alive or dead bacteria
void moveCursor(int *i, int *j, struct tag_bacteria *(*massiveOfBacteries)[QUANTITY], int key);
//function that moves cursor to one position left, right, up or down
void auxiliaryFunction(int *x1, int *y1, int *x2, int *y2, struct tag_bacteria *element);
//auxiliary function that sets coordinates of bacteria to variables x1, y1, x2, y2
void putBacteria(struct tag_bacteria *element);
//function that draws a bacteria after ENTER was pressed
void setMassiveOfCurrentConfiguration(struct tag_bacteria *(*massiveOfBacteries)[QUANTITY], struct tag_bacteria *(*massiveOfBacteries2)[QUANTITY]);
//function that sets help massive of current configuration of bacteries
void nextConfiguration(struct tag_bacteria *(*massiveOfBacteries)[QUANTITY], struct tag_bacteria *(*massiveOfBacteries2)[QUANTITY]);
//function that sets next configuration of bacteries
void setMassiveOfNeighbours(int *massiveOfNeighbours, struct tag_bacteria *(*massiveOfBacteries2)[QUANTITY], int i, int j);
//function that sets massive of neighbours for current bacteria
int aliveNeighbours(int *massiveOfNeighbours);
//function that counts alive neighbours of bacteria

void main(void)
{
  int gd = DETECT, gm;
  //variables using to inizialize graphics regime
  int xmax, ymax;
  //maximum coordinates of X and Y axises
  int i, j;
  //meters
  int key = 1;
  //code of pressed button
  int x1, y1, x2, y2;
  //coordinates of start position of cursor
  struct tag_bacteria bacteries[QUANTITY][QUANTITY], bacteries2[QUANTITY][QUANTITY];
  struct tag_bacteria *massiveOfBacteries[QUANTITY][QUANTITY], *massiveOfBacteries2[QUANTITY][QUANTITY];
  for (i = 0; i < QUANTITY; i++)
      for(j = 0; j < QUANTITY; j++)
          massiveOfBacteries[i][j] = &bacteries[i][j];
  for (i = 0; i < QUANTITY; i++)
      for(j = 0; j < QUANTITY; j++)
          massiveOfBacteries2[i][j] = &bacteries2[i][j];
  startConditions(massiveOfBacteries);
  initgraph(&gd, &gm, "");
  xmax = getmaxx();
  ymax = getmaxy();
  setCoordinates(xmax, ymax, massiveOfBacteries);
  drawCoordinateScale(xmax, ymax, massiveOfBacteries);
  auxiliaryFunction(&x1, &y1, &x2, &y2, massiveOfBacteries[0][0]);
  cursor(x1, y1, x2, y2, ACTIVE);
  i = 0;
  j = 0;
  do
  {
    if (anykeypressed())
    {
      key = readkey();
      switch (key)
      {
      case (0):
        key = readkey();
        switch (key)
        {
        case LEFT:
          moveCursor(&i, &j, massiveOfBacteries, LEFT);
          break;
        case RIGHT:
          moveCursor(&i, &j, massiveOfBacteries, RIGHT);
          break;
        case UP:
          moveCursor(&i, &j, massiveOfBacteries, UP);
          break;
        case DOWN:
          moveCursor(&i, &j, massiveOfBacteries, DOWN);
          break;
        }
        break;
      case ENTER:
        putBacteria(massiveOfBacteries[i][j]);
        break;
      case SPACE:
        setMassiveOfCurrentConfiguration(massiveOfBacteries, massiveOfBacteries2);
        nextConfiguration(massiveOfBacteries, massiveOfBacteries2);
        setMassiveOfCurrentConfiguration(massiveOfBacteries, massiveOfBacteries2);
        break;
      }
    }
  } while (key != ESCAPE);
  closegraph();
}

void startConditions(struct tag_bacteria *(*massiveOfBacteries)[QUANTITY])
{
  int i, j;
  //meters
  for (i = 0; i < QUANTITY; i++)
    for (j = 0; j < QUANTITY; j++)
      massiveOfBacteries[i][j]->alive = DEAD;
  return;
}

void setCoordinates(int xmax, int ymax, struct tag_bacteria *(*massiveOfBacteries)[QUANTITY])
{
  int xSize, ySize;
  //normal size of bacteries
  int numberXLarge, numberYLarge;
  //number of bacteries of (normal + 1) size
  /*maybee (xmax / OUANTITY * xmax) or/and (ymax / QUANTITY * ymax) will be bigger than xmax 
    or/and ymax, so some bacteries may have (normal + 1) size*/
  int i, j;
  //meters
  xSize = xmax / QUANTITY;
  ySize = ymax / QUANTITY;
  numberXLarge = xmax - xSize * QUANTITY;
  numberYLarge = ymax - ySize * QUANTITY;
  for (i = 0; i < numberXLarge; i++)
    for (j = 0; j < QUANTITY; j++)
    {
      massiveOfBacteries[i][j]->x1Coordinate = xSize * i + i;
      massiveOfBacteries[i][j]->x2Coordinate = xSize * (i + 1) + i + 1;
    }
  for (i = numberXLarge; i < QUANTITY; i++)
    for (j = 0; j < QUANTITY; j++)
    {
      massiveOfBacteries[i][j]->x1Coordinate = xSize * i + i;
      massiveOfBacteries[i][j]->x2Coordinate = xSize * (i + 1) + i;
    }
  for (j = 0; j < numberYLarge; j++)
    for (i = 0; i < QUANTITY; i++)
    {
      massiveOfBacteries[i][j]->y1Coordinate = ySize * j + j;
      massiveOfBacteries[i][j]->y2Coordinate = ySize * (j + 1) + j + 1;
    }
  for (j = numberYLarge; j < QUANTITY; j++)
    for (i = 0; i < QUANTITY; i++)
    {
      massiveOfBacteries[i][j]->y1Coordinate = ySize * j + j;
      massiveOfBacteries[i][j]->y2Coordinate = ySize * (j + 1) + j;
    }
  return;
}

void drawCoordinateScale(int xmax, int ymax, struct tag_bacteria *(*massiveOfBacteries)[QUANTITY])
{
  int i;
  //meter
  for (i = 0; i < QUANTITY; i++)
    line(massiveOfBacteries[i][0]->x1Coordinate, 0, massiveOfBacteries[i][0]->x1Coordinate, ymax);
  for (i = 0; i < QUANTITY; i++)
    line(0, massiveOfBacteries[0][i]->y1Coordinate, xmax, massiveOfBacteries[0][i]->y1Coordinate);
  return;
}

void cursor(int x1, int y1, int x2, int y2, int status)
{
  if (status == ACTIVE)
    setcolor(RED);
  if (status == PASSIVE)
    setcolor(WHITE);
  line(x1, y1, x1, y2);
  line(x1, y2, x2, y2);
  line(x2, y2, x2, y1);
  line(x2, y1, x1, y1);
  return;
}

void drawBacteria(int x1, int y1, int x2, int y2, int status)
{
  int i;
  //meter
  if (status == ALIVE)
    setcolor(BLUE);
  if (status == DEAD)
    setcolor(BLACK);
  for (i = (x1 + 1); i < x2; i++)
    line(i, (y1 + 1), i, (y2 - 1));
  return;
}

void moveCursor(int *i, int *j, struct tag_bacteria *(*massiveOfBacteries)[QUANTITY], int key)
{
  int x1, y1, x2, y2;
  auxiliaryFunction(&x1, &y1, &x2, &y2, massiveOfBacteries[*i][*j]);
  cursor(x1, y1, x2, y2, PASSIVE);
  switch (key)
  {
  case LEFT:
    if (*j == 0)
      *j = QUANTITY - 1;
    else
      *j = *j - 1;
    break;
  case RIGHT:
    if (*j == (QUANTITY - 1))
      *j = 0;
    else
      *j = *j + 1;
    break;
  case UP:
    if (*i == 0)
      *i = QUANTITY - 1;
    else
      *i = *i - 1;
    break;
  case DOWN:
    if (*i == (QUANTITY - 1))
      *i = 0;
    else
      *i = *i + 1;
    break;
  }
  auxiliaryFunction(&x1, &y1, &x2, &y2, massiveOfBacteries[*i][*j]);
  cursor(x1, y1, x2, y2, ACTIVE);
  return;
}

void auxiliaryFunction(int *x1, int *y1, int *x2, int *y2, struct tag_bacteria *element)
{
  *x1 = element->x1Coordinate;
  *y1 = element->y1Coordinate;
  *x2 = element->x2Coordinate;
  *y2 = element->y2Coordinate;
  return;
}

void putBacteria(struct tag_bacteria *element)
{
  int x1, y1, x2, y2;
  //coordinates of bacteria
  auxiliaryFunction(&x1, &y1, &x2, &y2, element);
  if (element->alive == DEAD)
    element->alive = ALIVE;
  else
    element->alive = DEAD;
  drawBacteria(x1, y1, x2, y2, element->alive);
  return;
}

void setMassiveOfCurrentConfiguration(struct tag_bacteria *(*massiveOfBacteries)[QUANTITY], struct tag_bacteria *(*massiveOfBacteries2)[QUANTITY])
{
  int i, j;
  //meters
  for (i = 0; i < QUANTITY; i++)
    for (j = 0; j < QUANTITY; j++)
    {
      massiveOfBacteries2[i][j]->alive = massiveOfBacteries[i][j]->alive;
      auxiliaryFunction(&(massiveOfBacteries2[i][j]->x1Coordinate),
          &(massiveOfBacteries2[i][j]->y1Coordinate),
          &(massiveOfBacteries2[i][j]->x2Coordinate),
          &(massiveOfBacteries2[i][j]->y2Coordinate), massiveOfBacteries[i][j]);
    }
  return;
}

void nextConfiguration(struct tag_bacteria *(*massiveOfBacteries)[QUANTITY], struct tag_bacteria *(*massiveOfBacteries2)[QUANTITY])
{
  int i, j;
  //meters
  int aliveBacteries;
  //number of alive neighbours of bacteria
  int x1, y1, x2, y2;
  //coordinates of bacteria
  int massiveOfNeighbours[NEIGHBOURS];
  for (j = 0; j < QUANTITY; j++)
  {
    for (i = 0; i < QUANTITY; i++)
    {
      setMassiveOfNeighbours(massiveOfNeighbours, massiveOfBacteries2, i, j);
      aliveBacteries = aliveNeighbours(massiveOfNeighbours);
      auxiliaryFunction(&x1, &y1, &x2, &y2, massiveOfBacteries[i][j]);
      if (massiveOfBacteries2[i][j]->alive == ALIVE)
      {
        if ((aliveBacteries == 2) || (aliveBacteries == 3))
          massiveOfBacteries[i][j]->alive = ALIVE;
        else
          massiveOfBacteries[i][j]->alive = DEAD;
      }
      else
      {
        if (aliveBacteries == 3)
          massiveOfBacteries[i][j]->alive = ALIVE;
        else
          massiveOfBacteries[i][j]->alive = DEAD;
      }
      drawBacteria(x1, y1, x2, y2, massiveOfBacteries[i][j]->alive);
    }
  }
  return;
}

void setMassiveOfNeighbours(int *massiveOfNeighbours, struct tag_bacteria *(*massiveOfBacteries2)[QUANTITY], int i, int j)
{
  int iPlus, iMinus, jPlus, jMinus;
  //indexes of neighbours
  if (i == QUANTITY - 1)
    iPlus = 0;
  else
    iPlus = i + 1;
  if (i == 0)
    iMinus = QUANTITY - 1;
  else
    iMinus = i - 1;
  if (j == QUANTITY - 1)
    jPlus = 0;
  else
    jPlus = j + 1;
  if (j == 0)
    jMinus = QUANTITY - 1;
  else
    jMinus = j - 1;
  massiveOfNeighbours[0] = massiveOfBacteries2[iMinus][jMinus]->alive;
  massiveOfNeighbours[1] = massiveOfBacteries2[iMinus][jPlus]->alive;
  massiveOfNeighbours[2] = massiveOfBacteries2[iPlus][jMinus]->alive;
  massiveOfNeighbours[3] = massiveOfBacteries2[iPlus][jPlus]->alive;
  massiveOfNeighbours[4] = massiveOfBacteries2[iPlus][j]->alive;
  massiveOfNeighbours[5] = massiveOfBacteries2[iMinus][j]->alive;
  massiveOfNeighbours[6] = massiveOfBacteries2[i][jPlus]->alive;
  massiveOfNeighbours[7] = massiveOfBacteries2[i][jMinus]->alive;
  return;
}

int aliveNeighbours(int *massiveOfNeighbours)
{
  int alive = 0;
  //number of alive neighbours
  int i;
  //meter
  for (i = 0; i < NEIGHBOURS; i++)
    if (massiveOfNeighbours[i] == ALIVE)
      alive++;
  return alive;
}