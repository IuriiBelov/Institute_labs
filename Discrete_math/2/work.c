#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "work.h"

#define MAX_NUMBER 4294967295

int allocMassive(unsigned long **massive, unsigned long size);
void divide(unsigned long *massive, unsigned long size);
int countRes(unsigned long *massive, unsigned long size, unsigned long *res);
int initArray(unsigned long *array1, unsigned long *array2, unsigned long size, unsigned long n);
void freeArrays(unsigned long *array1, unsigned long *array2, int *error);
int checkError(int error);

void commandH(void)
{
  printf("\n");
  printf("HELP:\n");
  printf("This program calculates the main combinatorial numbers.\n");
  printf("U m n == U(m,n) - menage number\n");
  printf("A m n == A(m,n) - menage number without repeating\n");
  printf("P n   == P(n)   - permutation number\n");
  printf("C m n == C(m,n) - combination number\n");
  printf("S m n == S(m,n) - Stirling II number\n");
  printf("B n   == B(n)   - Bell`s number\n");
  printf("\n");
  return;
}

unsigned long commandU(unsigned long m, unsigned long n, int *error)
{
  unsigned long i;
  unsigned long res, prevRes;
  assert(error != NULL);
  res = 1;
  for (i = 0; i < n; i++)
  {
    prevRes = res;
    res *= m;
    if ((unsigned long)(res / m) != prevRes)
    {
      printf("ERROR: overflow\n");
      *error = 1;
      return 0;
    }
  }
  return res;
}

unsigned long commandA(unsigned long m, unsigned long n, int *error)
{
  unsigned long i;
  unsigned long res, prevRes;
  assert(error != NULL);
  if (n > m)
    return 0;
  res = 1;
  for (i = 0; i < n; i++)
  {
    prevRes = res;
    res *= m - n + i + 1;
    if ((unsigned long)(res / (m - n + i + 1)) != prevRes)
    {
      printf("ERROR: overflow\n");
      *error = 1;
      return 0;
    }
  }
  return res;
}

unsigned long commandP(unsigned long n, int *error)
{
  unsigned long i;
  unsigned long res;
  assert(error != NULL);
  if (n > 12)
  {
    printf("overflow\n");
    *error = 1;
    return 0;
  }
  if (n == 0)
    return 1;
  res = 1;
  for (i = 0; i < n; i++)
    res *= i + 1;
  return res;
}

unsigned long commandC(unsigned long m, unsigned long n, int *error)
{
  unsigned long i, res, *massive;
  assert(error != NULL);
  if (n > m)
    return 0;
  if (m == n || n == 0)
    return 1;
  if (m == n + 1 || n == 1)
    return m;
  massive = NULL;
  res = 1;
  if (n >= m - n)
  {
    if (allocMassive(&massive, m - n))
    {
      *error = 1;
      return 0;
    }
    for (i = 0; i < m - n; i++)
      massive[i] = n + 1 + i;
    divide(massive, m - n);
    if (countRes(massive, m - n, &res))
    {
      free(massive);
      *error = 1;
      return 0;
    }
    free(massive);
  }
  else
  {
    if (allocMassive(&massive, n))
    {
      *error = 1;
      return 0;
    }
    for (i = 0; i < n; i++)
      massive[i] = m - n + 1 + i;
    divide(massive, n);
    if (countRes(massive, n, &res))
    {
      free(massive);
      *error = 1;
      return 0;
    }
    free(massive);
  }
  return res;
}

unsigned long commandS(unsigned long m, unsigned long n, int *error)
{
  unsigned long i, j, *array1, *array2, res;
  assert(error != NULL);
  if (m == n)
    return 1;
  if ((n == 0 && m != 0) || (n > m))
    return 0;
  if (allocMassive(&array1, m))
  {
    *error = 1;
    return 0;
  }
  if (allocMassive(&array2, m))
  {
    free(array1);
    *error = 1;
    return 0;
  }
  for (i = 0; i < m; i++)
    array1[i] = 1;
  if ((n / 2) * 2 == n)
    i = n / 2 - 1;
  else
    i = n / 2;
  for (j = 0; j < i; j++)
  {
    if (initArray(array2, array1, m, 2 * j + 2))
    {
      freeArrays(array1, array2, error);
      return 0;
    }
    if (initArray(array1, array2, m, 2 * j + 3))
    {
      freeArrays(array1, array2, error);
      return 0;
    }
  }
  if ((n / 2) * 2 == n)
  {
    if (initArray(array2, array1, m, n))
    {
      freeArrays(array1, array2, error);
      return 0;
    }
    res = array2[m - 1];
  }
  else
    res = array1[m - 1];
  free(array1);
  free(array2);
  return res;
}

unsigned long commandB(unsigned long n, int *error)
{
  unsigned long res, *arrayB, i, j, currentC;
  assert(error != NULL);
  if (n == 0)
    return 1;
  arrayB = NULL;
  if (allocMassive(&arrayB, n + 1))
  {
    *error = 1;
    return 0;
  }
  res = 0;
  arrayB[0] = arrayB[1] = 1;
  for (i = 2; i <= n; i++)
  {
    arrayB[i] = 0;
    for (j = 0; j < i; j++)
    {
      currentC = commandC(i - 1, j, error);
      if (*error == 1)
      {
        free(arrayB);
        return 0;
      }
      if ((currentC * arrayB[j]) / arrayB[j] != currentC)
      {
        printf("ERROR: overflow\n");
        *error = 1;
        free(arrayB);
        return 0;
      }
      if (MAX_NUMBER - currentC * arrayB[j] < arrayB[i])
      {
        printf("ERROR: overflow\n");
        *error = 1;
        free(arrayB);
        return 0;
      }
      arrayB[i] += currentC * arrayB[j];
    }
  }
  res = arrayB[n];
  free(arrayB);
  return res;
}

int allocMassive(unsigned long **massive, unsigned long size)
{
  assert(massive != NULL && size > 0);
  *massive = malloc(size * sizeof(unsigned long));
  if (*massive == NULL)
  {
    printf("ERROR: not enough dynamic memory\n");
    return 1;
  }
  return 0;
}

void divide(unsigned long *massive, unsigned long size)
{
  unsigned long i, j, k, *divideMassive;
  assert(massive != NULL && size > 0);
  if (allocMassive(&divideMassive, size - 1))
    return;
  for (i = 0; i < size - 1; i++)
    divideMassive[i] = i + 2;
  for (i = 0; i < size - 1; i++)
    for (j = 0; j < size; j++)
    {
      for (k = 2; k <= divideMassive[i]; k++)
      {
        if ((divideMassive[i] / k) * k == divideMassive[i] && (massive[j] / k) * k == massive[j])
        {
          divideMassive[i] /= k;
          massive[j] /= k;
          k--;
        }
        if (divideMassive[i] == 1)
          break;
      }
      if (divideMassive[i] == 1)
        break;
    }
  free(divideMassive);
  return;
}

int countRes(unsigned long *massive, unsigned long size, unsigned long *res)
{
  unsigned long i, prevRes;
  assert(massive != NULL && size > 0 && res != NULL);
  for (i = 0; i < size; i++)
  {
    prevRes = *res;
    *res *= massive[i];
    if ((unsigned long)(*res / massive[i]) != prevRes)
    {
      printf("ERROR: overflow\n");
      return 1;
    }
  }
  return 0;
}

int initArray(unsigned long *array1, unsigned long *array2, unsigned long size, unsigned long n)
{
  unsigned long i, j, prev;
  assert(array1 != NULL && array2 != NULL && size > 0 && n > 0);
  for (i = 0; i < size; i++)
  {
    if (i < n - 1)
      array1[i] = 0;
    else
    {
      array1[i] = array2[i - 1];
      for (j = 0; j < n; j++)
      {
        prev = array1[i];
        array1[i] += array1[i - 1];
        if (array1[i] - array1[i - 1] != prev)
        {
          printf("ERROR: overflow\n");
          return 1;
        }
      }
    }
  }
  return 0;
}

void freeArrays(unsigned long *array1, unsigned long *array2, int *error)
{
  assert(array1 != NULL && array1 != NULL && error != NULL);
  free(array1);
  free(array2);
  *error = 1;
  return;
}

int checkError(int error)
{
  if (error == 1)
  {
    printf("ERROR: overflow\n");
    return 1;
  }
  return 0;
}