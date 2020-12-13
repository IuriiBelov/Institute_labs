#include "BubbleSort.h"
#include "ChangeValues.h"

void bubbleSort(int *massiv, int size)
{
  int i, j;
  for (i = 1; i < size; i++)
    for (j = 1; j < (size - i + 1); j++)
      if (massiv[j] < massiv[j - 1])
        changeValues(&massiv[j], &massiv[j - 1]);
  return;
}