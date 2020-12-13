#include "InsertionSort.h"

void insertionSort(int *massiv, int size)
{
  int i, j, k;
  int value;
  //value of the first element of the unsort part of massive
  for (i = 1; i < size; i++)
  {
    for (j = 0; j < i; j++)
      if (massiv[i] < massiv[j])
      {
        value = massiv[i];
        for (k = i; k > j; k--)
          massiv[k] = massiv[k - 1];
        massiv[j] = value;
      }
    }
  return;
}