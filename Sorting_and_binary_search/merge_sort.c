#include <stdlib.h>

#include "merge_sort.h"

#define MAX_LONG_INT 2147483647

void mergeSortReal(int *arr, int first, int last);
void merge(int *arr, int first, int middle, int last);
void anotherMerge(int *arr, int first, int middle, int last);
void copyTail(int *arr, int *M, int k, int i, int n);

void mergeSort(int *arr, int n)
{
  mergeSortReal(arr, 0, n - 1);
  return;
}

void mergeSortReal(int *arr, int first, int last)
{
  int middle;
  if (first >= last)
    return;
  middle = (first + last) / 2;
  mergeSortReal(arr, first, middle);
  mergeSortReal(arr, middle + 1, last);
  anotherMerge(arr, first, middle, last);
  return;
}

void merge(int *arr, int first, int middle, int last)
{
  int n1, n2, i, j, k;
  long int *L, *R;
  n1 = middle - first + 1;
  n2 = last - middle;
  L = malloc((n1 + 1) * sizeof(long int));
  R = malloc((n2 + 1) * sizeof(long int));
  for (i = 0; i < n1; i++)
    L[i] = (long int)arr[first + i];
  for (j = 0; j < n2; j++)
    R[j] = (long int)arr[middle + j + 1];
  L[n1] = R[n2] = MAX_LONG_INT;
  i = j = 0;
  for (k = first; k <= last; k++)
    if (L[i] <= R[j])
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }
  free(L);
  free(R);
  return;
}

void anotherMerge(int *arr, int first, int middle, int last)
{
  int n1, n2, i, j, k;
  long int *L, *R;
  n1 = middle - first + 1;
  n2 = last - middle;
  L = malloc(n1 * sizeof(long int));
  R = malloc(n2 * sizeof(long int));
  for (i = 0; i < n1; i++)
    L[i] = (long int)arr[first + i];
  for (j = 0; j < n2; j++)
    R[j] = (long int)arr[middle + j + 1];
  i = j = 0;
  for (k = first; k <= last; k++)
    if (L[i] <= R[j])
    {
      arr[k] = L[i];
      i++;
      if (i == n1)
      {
        copyTail(arr, R, k + 1, j, n2);
        break;
      }
    }
    else
    {
      arr[k] = R[j];
      j++;
      if (j == n2)
      {
        copyTail(arr, L, k + 1, i, n1);
        break;
      }
    }
  free(L);
  free(R);
  return;
}

void copyTail(int *arr, int *M, int k, int i, int n)
{
  while (i != n)
  {
    arr[k] = M[i];
    k++;
    i++;
  }
  return;
}