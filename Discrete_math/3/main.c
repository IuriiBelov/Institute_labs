#include <stdio.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <assert.h>
#include "wayOut.h"
#include "check.h"

#define CELL 1
#define INT  2

/* ���������, ���������� ���������� � ������ ������� ��������� */
typedef struct tag_cell
{
  int value;/* �������� 0, ���� ������ - "������"; 1, ���� "�����" */
  int number;/* ����� ������, ���� ��� - "������" (�� ���������� "��������") */
} cell;

int readData(cell ***M, int *m, int *n, int *i, int *j, int *k);
/* �������, ������� ��������� �� ������ ������� ��������� � ���������� ���������� ��������� 
   ��������. 
   cell ***M - ��������� �� ������� 
   int *m    - ��������� �� ���������� ����� � ������� 
   int *n    - ��������� �� ���������� �������� � ������� 
   int *i    - ��������� �� ������, � ������� ���������� ��������� ������� 
   int *j    - ��������� �� �������, � ������� ���������� ��������� ������� 
   int *k    - ��������� �� ���������� "��������" � ��������� 
   ������� ���������� 0, ���� �� ������ �������, � 1, ���� ��� (�� �������� ���� ��� �� ������� 
   ������������ ������. */
void initGraph(cell **M, elem *V, int k, int m, int n);
/* �������, ������� �������������� ������ ������ �����, ��������� �������� �������� 
   "�������" � ���������. ������� ����� ������, ���� ������-"�������" �������. 
   cell **M - ������� ��������� 
   elem *V  - ������ ������ ����� 
   int k    - ���������� ������ � ����� 
   int m    - ���������� ����� � ������� ��������� 
   int n    - ���������� �������� � ������� ��������� 
   ������� ������ �� ����������. */
int allocMatrix(cell ***M, int m, int n);
/* �������, ������� �������� ������������ ������ ��� ������� ��������� 
   cell ***M - ��������� �� ������� ��������� 
   int m     - ���������� ����� � ������� 
   int n     - ���������� �������� � ������� 
   ������� ���������� 0, ���� ������� �������� ������, � 1, ���� �� �������. */
void freeMatrix(cell **M, int m);
/* �������, ������� ����������� ������������ ������, ���������� ��� ������� ��������� 
   cell **M - ������� ��������� 
   int m    - ���������� ����� � ������� 
   ������� ������ �� ����������. */

int main(void)
{
  cell **M = NULL;/* ������� ��������� */
  elem *V = NULL;/* ������ ������ ����� */
  int m = 0;/* ���������� ����� � ������� ��������� */
  int n = 0;/* ���������� �������� � ������� ��������� */
  int i = 0;/* ������, � ������� ���������� ��������� ������� */
  int j = 0;/* �������, � ������� ���������� ��������� ������� */
  int k = 0;/* ���������� ������-"��������" � ������� ��������� */
  int begin;/* ����� ������� �����, � ������� ���������� ��������� ������� */
  int *way;/* ������ ������, ������������ ���� */
  int h;/* ��������������� ���������� ����� */
  /* ������ �������� �� ������ ������ */
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
  /* ��������� ������ �� ����� */
  if (readData(&M, &m, &n, &i, &j, &k))
    return 1;
  /* �������� ������ ��� ������ ������ ����� */
  V = calloc(k, sizeof(elem));
  /* ���� ������ �������� �� ������� */
  if (checkPointer(V))
    /* ����������� ������ ��� ������� ��������� */
    freeMatrix(M, m);
  /* �������������� ������ ������ ����� */
  initGraph(M, V, k, m, n);
  /* ����� �������, ��� ���������� ��������� ������� */
  begin = (M[i - 1][j - 1]).number;
  way = wayOut(k, begin, V);
  if (way != NULL)
  {
    for (i = 0; i < k; i++)
      if (way[i] >= 0)
      {
        for (j = 0; j < m; j++)
          for (h = 0; h < n; h++)
            if ((M[j][h]).value == 0 && (M[j][h]).number == way[i])
              printf("(%i;%i) ", j + 1, h + 1);
      }
    printf("\n");
  }
  freeMatrix(M, m);
  free(V);
  return 0;
}

int readData(cell ***M, int *m, int *n, int *i, int *j, int *k)
{
  FILE *fp;/* ��������� �� ����, �� �������� ��������� ������ */
  int a, b;/* ��������������� ���������� ����� */
  assert(M != NULL && m != NULL && n != NULL && i != NULL && j != NULL && k != NULL);
  /* ��������� ���� ��� ������ */
  fp = fopen("data.txt", "r");
  if (fp == NULL)
  {
    printf("ERROR: file not found\n");
    return 1;
  }
  fscanf(fp, "%i %i %i %i", m, n, i, j);/* ������� ���������� ����� � �������� � ������� ��������� 
  � ������ � �������, � ������� ���������� ������������� �������*/
  /* �������� ������ ��� ������� ���������� ����� */
  if (allocMatrix(M, *m, *n))
  {
    fclose(fp);
    return 1;
  }
  /* ��������� ������� ��������� */
  for (a = 0; a < *m; a++)
    for (b = 0; b < *n; b++)
    {
      fscanf(fp, "%i", &(((*M)[a][b]).value));
      if (((*M)[a][b]).value == 0)/* ���� ��� ������-"������" */
      {
        ((*M)[a][b]).number = *k;/* �� ���������� ����� ���� ������ (�������� ������ � ����) */
        (*k)++;/* � ����������� ������� */
      }
    }
  fclose(fp);
  return 0;
}

void initGraph(cell **M, elem *V, int k, int m, int n)
{
  int a, b;/* ��������������� ���������� ����� */
  int z = 0;/* ������� ������-"��������" */
  assert(M != NULL && V != NULL && k > 0 && m > 0 && n > 0);
  /* ����������� �� ������� ������ ����� */
  for (a = 0; a < k; a++)
    /* ����������� �� ������� ������� ������ ������ ������� */
    for (b = 0; b < 4; b++)
      ((V[a]).adjacent)[b] = -1;/* ���������� �� � ����� ������� ��� ������� */
  /* ������������� ������� ��������� */
  for (a = 0; a < m; a++)
    for (b = 0; b < n; b++)
      if ((M[a][b]).value == 0)/* ���� ��� ������-"������" */
      {
        (V[z]).number = z;/* ������ ��� ������ ��������� �������� ����� */
        /* ���� ������-"������" �� ���� ��������� */
        if (a == 0 || a == m - 1 || b == 0 || b == n - 1)
          (V[z]).wayOut = 0;/* �� ��� ����� */
        else
          (V[z]).wayOut = 1;/* ����� ��� */
        if (a > 0)/* ������� �������� ������ */
          if ((M[a - 1][b]).value == 0)/* ���� ������� ����� - ���� "������" */
            ((V[z]).adjacent)[0] = (M[a - 1][b]).number;/* ������ ��� ����� � ������ ������� */
        if (a < m - 1)/* ������� ������� ������ */
          if ((M[a + 1][b]).value == 0)/* ���� ������ ����� - ���� "������" */
            ((V[z]).adjacent)[1] = (M[a + 1][b]).number;/* ������ ��� ����� � ������ ������� */
        if (b > 0)/* ������� ������ ������ */
          if ((M[a][b - 1]).value == 0)/* ���� ����� ����� - ���� "������" */
            ((V[z]).adjacent)[2] = (M[a][b - 1]).number;/* ������ ��� ����� � ������ ������� */
        if (b < n - 1)/* ������� ������� ������ */
          if ((M[a][b + 1]).value == 0)/* ���� ������ ����� - ���� "������" */
            ((V[z]).adjacent)[3] = (M[a][b + 1]).number;/* ������ ��� ����� � ������ ������� */
        z++;/* ����������� ������� ������ ����� */
      }
  return;
}

int allocMatrix(cell ***M, int m, int n)
{
  int a, b;
  assert(M != NULL && m > 0 && n > 0);
  /* �������� ������ ��� ������� */
  *M = calloc(m, sizeof(cell *));
  if (checkPointer(*M))
    return 1;
  /* ��������� ������ ��� ������ ������� */
  for (a = 0; a < m; a++)
  {
    (*M)[a] = calloc(n, sizeof(cell));
    /* ���� �� ������� �������� ������ ��� ��������� ������ */
    if (checkPointer((*M)[a]))
    {
      /* ����������� ��, ��� �������� ������, � ������� */
      for (b = 0; b < a; b++)
        free((*M)[b]);
      free(*M);
      return 1;
    }
  }
  return 0;
}

void freeMatrix(cell **M, int m)
{
  int a;
  assert(M != NULL && m > 0);
  /* ����������� ������ ��� ������ ������� */
  for (a = 0; a < m; a++)
    free(M[a]);
  /* ����������� ������ ��� ������� */
  free(M);
  return;
}