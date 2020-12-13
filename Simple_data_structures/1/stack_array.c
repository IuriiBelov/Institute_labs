#include <stdio.h>
#include <stdlib.h>

#include "stack_array.h"

void createStackArray(t_stackArray **s, int size, int *err)
{
  *err = 0;
  *s = malloc(sizeof(t_stackArray));
  if (*s == NULL)
  {
    *err = 1;
    return;
  }
  (*s)->stack = malloc(size * sizeof(int));
  if ((*s)->stack == NULL)
  {
    *err = 1;
    return;
  }
  (*s)->size = size;
  (*s)->i = -1;
  return;
}

void deleteStackArray(t_stackArray **s)
{
  free((*s)->stack);
  free(*s);
  *s = NULL;
  return;
}

void pushElemStackArray(t_stackArray *s, int elem, int *err)
{
  *err = 0;
  if (s == NULL || s->i == s->size - 1)
  {
    *err = 1;
    return;
  }
  (s->i)++;
  (s->stack)[s->i] = elem;
  return;
}

int popElemStackArray(t_stackArray *s, int *err)
{
  *err = 0;
  if (s == NULL || s->i == -1)
  {
    *err = 1;
    return 0;
  }
  (s->i)--;
  return (s->stack)[s->i + 1];
}

int topElemStackArray(t_stackArray *s, int *err)
{
  *err = 0;
  if (s == NULL || s->i == -1)
  {
    *err = 1;
    return 0;
  }
  return (s->stack)[s->i];
}

void outputStackArray(t_stackArray *s)
{
  int i;
  printf("The stack:\n");
  if (s == NULL)
    return;
  i = s->i;
  while (i >= 0)
  {
    printf("%i\n", (s->stack)[i]);
    i--;
  }
  return;
}