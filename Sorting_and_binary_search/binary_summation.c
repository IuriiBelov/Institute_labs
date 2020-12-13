#include "binary_summation.h"

void binarySummation(int *A, int *B, int *C, int n)
{
  int i, key, summ;
  key = 0;
  for (i = n - 1; i >= 0; i--)
  {
    summ = A[i] + B[i] + key;
    switch (summ)
    {
    case 3:
      C[i + 1] = 1;
      break;
    case 2:
      C[i + 1] = 0;
      if (key == 0)
        key = 1;
      break;
    case 1:
      C[i + 1] = 1;
      if (key == 1)
        key = 0;
      break;
    default:
      C[i + 1] = 0;
    }
  }
  C[0] = key;
  return;
}