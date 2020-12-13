#include "binary_search.h"

int binarySearchReal(int *arr, int first, int last, int v);

int binarySearch(int *arr, int n, int v)
{
  return binarySearchReal(arr, 0, n - 1, v);
}

int binarySearchReal(int *arr, int first, int last, int v)
{
  int middle;
  if (first == last && v != arr[first])
    return -1;
  middle = (first + last) / 2;
  if (v == arr[middle])
    return middle;
  else if (v < arr[middle])
    return binarySearchReal(arr, first, middle - 1, v);
  else
    return binarySearchReal(arr, middle + 1, last, v);
}