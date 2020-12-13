#include "SheikerSort.h"
#include "ChangeValues.h"

extern void sheikerSort(int *massiv, int size);
//the main function that sorts the massiv by a sheiker sort

void sheikerSort(int *massiv, int size)
{
  int i, j;
  int unsortSize = size;
  //size of unsorted part of the massiv
  for (i = 0; i < (size - 1); i++)
  {
    for (j = (size - unsortSize); j < (unsortSize - 1); j++)
      if (massiv[j] > massiv[j + 1])
        changeValues(&massiv[j], &massiv[j + 1]);
    for (j = (unsortSize - 1); j > (size - unsortSize); j--)
      if (massiv[j] < massiv[j - 1])
        changeValues(&massiv[j], &massiv[j - 1]);
    unsortSize--;
  }
  return;
}