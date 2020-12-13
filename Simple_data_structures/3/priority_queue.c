#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"

void insertElem(t_priorityQueue **q, t_priorityQueueElem *elem, int *err)
{
  t_priorityQueueElem *newElem, *elem1, *prevElem;
  int i;
  *err = 0;
  if (q == NULL || elem == NULL)
  {
    *err = 1;
    return;
  }
  newElem = malloc(sizeof(t_priorityQueueElem));
  newElem->data = malloc(elem->dataSize * sizeof(char));
  for (i = 0; i < elem->dataSize; i++)
    (newElem->data)[i] = (elem->data)[i];
  newElem->dataSize = elem->dataSize;
  newElem->priority = elem->priority;
  if (*q == NULL)
  {
    *q = malloc(sizeof(t_priorityQueue));
    (*q)->first = (*q)->last = newElem;
    newElem->prev = newElem->next = NULL;
    return;
  }
  elem1 = (*q)->first;
  while (elem1->priority >= newElem->priority)
  {
    prevElem = elem1;
    elem1 = elem1->next;
  }
  newElem->next = elem1;
  if (elem1 == NULL)
  {
    newElem->prev = prevElem;
    (*q)->last = newElem;
    return;
  }
  newElem->prev = elem1->prev;
  if (elem1->prev != NULL)
    (elem1->prev)->next = newElem;
  else
    (*q)->first = newElem;
  elem1->prev = newElem;
  return;
}

t_priorityQueueElem *extractMaximumAndDelete(t_priorityQueue **q, int *err)
{
  t_priorityQueueElem *result;
  *err = 0;
  if (q == NULL || *q == NULL)
  {
    *err = 1;
    return NULL;
  }
  result = (*q)->first;
  if ((*q)->first == (*q)->last)
  {
    free(*q);
    *q = NULL;
  }
  else
    (*q)->first = ((*q)->first)->next;
  return result;
}

t_priorityQueueElem *extractMaximumNoDelete(t_priorityQueue *q, int *err)
{
  t_priorityQueueElem *result;
  int i;
  *err = 0;
  if (q == NULL)
  {
    *err = 1;
    return NULL;
  }
  result = malloc(sizeof(t_priorityQueueElem));
  result->data = malloc((q->first)->dataSize * sizeof(char));
  for (i = 0; i < (q->first)->dataSize; i++)
    (result->data)[i] = ((q->first)->data)[i];
  result->dataSize = (q->first)->dataSize;
  result->priority = (q->first)->priority;
  result->prev = result->next = NULL;
  return result;
}

void changePriority(t_priorityQueue **q, t_priorityQueueElem *elem, int newPriority, int *err)
{
  t_priorityQueueElem *neededElem, *newElem;
  int i;
  *err = 0;
  neededElem = findElem(*q, elem);
  if (neededElem == NULL)
  {
    *err = 1;
    return;
  }
  neededElem->priority = newPriority;
  newElem = malloc(sizeof(t_priorityQueueElem));
  newElem->data = malloc(neededElem->dataSize * sizeof(char));
  for (i = 0; i < neededElem->dataSize; i++)
    (newElem->data)[i] = (neededElem->data)[i];
  newElem->dataSize = neededElem->dataSize;
  newElem->priority = neededElem->priority;
  newElem->prev = newElem->next = NULL;
  deleteElem(q, neededElem, err);
  if (*err == 1)
    return;
  insertElem(q, newElem, err);
  return;
}

void deleteElem(t_priorityQueue **q, t_priorityQueueElem *elem, int *err)
{
  t_priorityQueueElem *neededElem;
  *err = 0;
  neededElem = findElem(*q, elem);
  if (neededElem == NULL)
  {
    *err = 1;
    return;
  }
  if (neededElem->prev == NULL)
    (*q)->first = neededElem->next;
  else
    (neededElem->prev)->next = neededElem->next;
  if (neededElem->next == NULL)
    (*q)->last = neededElem->prev;
  else
    (neededElem->next)->prev = neededElem->prev;
  free(neededElem->data);
  free(neededElem);
  if ((*q)->first == NULL && (*q)->last == NULL)
  {
    free(*q);
    *q = NULL;
  }
  return;
}

void printQueue(t_priorityQueue *q)
{
  t_priorityQueueElem *elem;
  if (q == NULL || q->first == NULL)
    return;
  elem = q->first;
  while (elem != NULL)
  {
    printf("%i %s\n", elem->priority, elem->data);
    elem = elem->next;
  }
  return;
}

t_priorityQueueElem *findElem(t_priorityQueue *q, t_priorityQueueElem *elem)
{
  t_priorityQueueElem *result;
  int i;
  if (q == NULL || elem == NULL)
    return NULL;
  result = q->first;
  while (result != NULL)
  {
    if (result->priority != elem->priority || result->dataSize != elem->dataSize)
    {
      result = result->next;
      continue;
    }
    for (i = 0; i < result->dataSize; i++)
      if ((result->data)[i] != (elem->data)[i])
      {
        result = result->next;
        continue;
      }
    break;
  }
  return result;
}