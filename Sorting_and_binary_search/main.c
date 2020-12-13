#include <stdio.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "insertion_sort.h"
#include "binary_summation.h"
#include "merge_sort.h"
#include "binary_search.h"
#include "summ_x.h"

#define N 11

int main()
{
  int *arr, *A, *B, *C;
  int i;
  summands_t resSummX;
  _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  /*
  arr = malloc(N * sizeof(int));
  //arr[0] = 5; arr[1] = 2; arr[2] = 4; arr[3] = 6; arr[4] = 1; arr[5] = 3;
  arr[0] = 31; arr[1] = 41; arr[2] = 59; arr[3] = 26; arr[4] = 41; arr[5] = 58;
  for (i = 0; i < N; i++)
    printf("%i ", arr[i]);
  printf("\n");
  insertionSort(arr, N);
  for (i = 0; i < N; i++)
    printf("%i ", arr[i]);
  printf("\n");
  free(arr);
  */
  /*
  A = malloc(N * sizeof(int));
  B = malloc(N * sizeof(int));
  C = malloc((N + 1) * sizeof(int));
  A[0] = 1; A[1] = 1; A[2] = 1; A[3] = 1;
  B[0] = 1; B[1] = 1; B[2] = 1; B[3] = 1;
  binarySummation(A, B, C, N);
  for (i = 0; i <= N; i++)
    printf("%i", C[i]);
  printf("\n");
  free(A);
  free(B);
  free(C);
  */
  
  arr = malloc(N * sizeof(int));
  arr[0] = 5; arr[1] = 2; arr[2] = 4; arr[3] = 7; arr[4] = 1; arr[5] = 3; arr[6] = 2; arr[7] = 6; arr[8] = 4; arr[9] = -2; arr[10] = 0;
  for (i = 0; i < N; i++)
    printf("%i ", arr[i]);
  printf("\n");
  mergeSort(arr, N);
  for (i = 0; i < N; i++)
    printf("%i ", arr[i]);
  printf("\n");
  printf("%i\n", binarySearch(arr, N, 3));
  resSummX = summX(arr, N, -1);
  printf("%i %i\n", resSummX.firstIndex, resSummX.secondIndex);
  free(arr);
  
  return 0;
}