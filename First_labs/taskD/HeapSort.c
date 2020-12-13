#include "HeapSort.h"
#include "ChangeValues.h"

void buildHeap(int *massiv, int size);
//function that builds a heap from the massiv
void repairHeap(int *massiv, int begin, int end);
//function that "repairs" the heap

void heapSort(int *massiv, int size)
{
  int i;
  buildHeap(massiv, size);
  for (i = (size - 1); i > 0; i--)
  {
    changeValues(&(massiv[0]), &(massiv[i]));
    repairHeap(massiv, 0, (i - 1));
  }
  return;
}

void buildHeap(int *massiv, int size)
{
  int i;
  for (i = (size / 2 - 1); i >= 0; i--)
    repairHeap(massiv, i, (size - 1));
  return;
}

void repairHeap(int *massiv, int begin, int end)
{
  int i = begin;
  //the head element of the heap
  while ((i < ((end - 1) / 2)) || (i == ((end - 1) / 2)) || (i == end / 2 - 1))
  {
    if ((i == ((end - 1) / 2)) && (end != 2) && ((2 * i + 2) != end))
    {
      if (massiv[i] < massiv[end])
        changeValues(&(massiv[i]), &(massiv[end]));
      return;
    }
    else
    {
      if ((massiv[i] < massiv[2 * i + 1]) && (massiv[i] < massiv[2 * i + 2]))
      {
        if (massiv[2 * i + 1] > massiv[2 * i + 2])
        {
          changeValues(&(massiv[i]), &(massiv[2 * i + 1]));
          i = 2 * i + 1;
        }
        else
        {
          changeValues(&(massiv[i]), &(massiv[2 * i + 2]));
          i = 2 * i + 2;
        }
        continue;
      }
      if ((massiv[i] < massiv[2 * i + 1]) && (massiv[i] >= massiv[2 * i + 2]))
      {
        changeValues(&(massiv[i]), &(massiv[2 * i + 1]));
        i = 2 * i + 1;
        continue;
      }
      if ((massiv[i] >= massiv[2 * i + 1]) && (massiv[i] < massiv[2 * i + 2]))
      {
        changeValues(&(massiv[i]), &(massiv[2 * i + 2]));
        i = 2 * i + 2;
        continue;
      }
      if ((massiv[i] >= massiv[2 * i + 1]) && (massiv[i] >= massiv[2 * i + 2]))
        return;
    }
  }
  return;
}