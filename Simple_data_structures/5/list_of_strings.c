#include <stdlib.h>

#include "list_of_strings.h"

void addElem(t_listOfStrings **l, char *elem, int elemSize, int *err)
{
  t_listOfStrings *newElem, *l1;
  int i;
  *err = 0;
  if (l == NULL)
  {
    *err = 1;
    return;
  }
  newElem = malloc(sizeof(t_listOfStrings));
  if (newElem == NULL)
  {
    *err = 1;
    return;
  }
  newElem->elem = malloc(elemSize * sizeof(char));
  if (newElem->elem == NULL)
  {
    free(newElem);
    *err = 1;
    return;
  }
  for (i = 0; i < elemSize; i++)
    (newElem->elem)[i] = elem[i];
  printf("%s\n", newElem->elem);
  newElem->elemSize = elemSize;
  newElem->next = NULL;
  if (*l == NULL)
  {
    *l = newElem;
    return;
  }
  l1 = *l;
  while (l1->next != NULL)
    l1 = l1->next;
  l1->next = newElem;
  return;
}

void deleteElem(t_listOfStrings **l, int *err)
{
  t_listOfStrings *l1, *l2;
  *err = 0;
  if (l == NULL)
  {
    *err = 1;
    return;
  }
  if (*l == NULL)
    return;
  l1 = l2 = *l;
  while (l1->next != NULL)
  {
    l2 = l1;
    l1 = l1->next;
  }
  free (l1->elem);
  if (l2 == l1)
    *l = NULL;
  else
    l2->next = NULL;
  free(l1);
  return;
}

void outputList(t_listOfStrings *l)
{
  while (l != NULL)
  {
    printf("%s\n", l->elem);
    l = l->next;
  }
  return;
}