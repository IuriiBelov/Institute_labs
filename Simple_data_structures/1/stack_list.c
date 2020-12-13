#include <stdio.h>
#include <stdlib.h>

#include "stack_list.h"

void pushElemStackList(t_stackList **s, int elem, int *err)
{
  t_stackList *newS = NULL;
  *err = 0;
  newS = malloc(sizeof(t_stackList));
  if (newS == NULL)
  {
    *err = 1;
    return;
  }
  newS->data = elem;
  newS->prev = *s;
  *s = newS;
  return;
}

int popElemStackList(t_stackList **s, int *err)
{
  t_stackList *newS;
  int elem;
  *err = 0;
  if (*s == NULL)
  {
    *err = 1;
    return 0;
  }
  elem = (*s)->data;
  newS = (*s)->prev;
  free(*s);
  *s = newS;
  return elem;
}

int topElemStackList(t_stackList *s, int *err)
{
  *err = 0;
  if (s == NULL)
  {
    *err = 1;
    return 0;
  }
  return s->data;
}

void outputStackList(t_stackList *s)
{
  printf("The stack:\n");
  while (s != NULL)
  {
    printf("%i\n", s->data);
    s = s->prev;
  }
  return;
}