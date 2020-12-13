#include <math.h>
#include "ChangeValues.h"
#include "SelectionSort.h"

void selectionSort(int *massiv, int size)
{
  int i, j;
  int min;
  //minimum element of the sorted part of the massive
  for (i = 0; i < size; i++)
  {
    min = massiv[i];
    for (j = i; j < size; j++)
      if (massiv[j] < min)
      {
        changeValues(&massiv[j], &massiv[i]);
        min = massiv[i];
      }
  }
  return;
}