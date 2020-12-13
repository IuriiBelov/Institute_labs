#include <stdio.h>
#include <stdlib.h>

#include "queue_list.h"

void enqueueList(t_queueList **q, int elem, int *err)
{
  t_queueListElem *newElem;
  *err = 0;
  if (q == NULL)
  {
    *err = 1;
    return;
  }
  newElem = malloc(sizeof(t_queueListElem));
  if (newElem == NULL)
  {
    *err = 1;
    return;
  }
  newElem->data = elem;
  newElem->next = NULL;
  if (*q == NULL)
  {
    *q = malloc(sizeof(t_queueList));
    if (*q == NULL)
    {
      *err = 1;
      free(newElem);
      return;
    }
    newElem->prev = NULL;
    (*q)->first = newElem;
  }
  else
    newElem->prev = (*q)->last;
  (*q)->last = newElem;
  return;
}

int dequeueList(t_queueList **q, int *err)
{
  int result;
  t_queueListElem *newFirst;
  *err = 0;
  if (q == NULL)
  {
    *err = 1;
    return 0;
  }
  if (*q == NULL)
  {
    printf("Queue is empty\n");
    *err = 1;
    return 0;
  }
  result = ((*q)->first)->data;
  if ((*q)->first == (*q)->last)
  {
    free((*q)->first);
    free(*q);
    *q = NULL;
    return result;
  }
  newFirst = ((*q)->first)->next;
  free((*q)->first);
  (*q)->first = newFirst;
  ((*q)->first)->prev = NULL;
  return result;
}

void outputQueueList(t_queueList *q)
{
  t_queueListElem *elem;
  printf("The queue:\n");
  if (q == NULL)
    return;
  elem = q->first;
  while (elem != NULL)
  {
    printf("%i\n", elem->data);
    elem = elem->next;
  }
  return;
}