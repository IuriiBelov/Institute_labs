#include <stdio.h>
#include <stdlib.h>

#include "queue_array.h"

void createQueueArray(t_queueArray **q, int size, int *err)
{
  *err = 0;
  if (q == NULL)
  {
    *err = 1;
    return;
  }
  *q = malloc(sizeof(t_queueArray));
  if (*q == NULL)
  {
    *err = 1;
    return;
  }
  (*q)->queue = malloc(size * sizeof(int));
  if ((*q)->queue == NULL)
  {
    *err = 1;
    free(*q);
    return;
  }
  (*q)->size = size;
  (*q)->first = (*q)->last = -1;
  return;
}

void deleteQueueArray(t_queueArray **q)
{
  if (q == NULL)
    return;
  if (*q == NULL)
    return;
  if ((*q)->queue != NULL)
    free((*q)->queue);
  free(*q);
  *q = NULL;
  return;
}

void enqueueArray(t_queueArray *q, int elem, int *err)
{
  *err = 0;
  if (q == NULL || q->queue == NULL)
  {
    *err = 1;
    return;
  }
  if (q->last == q->size - 1 && q->first == 0 || q->last == q->first - 1)
  {
    printf("Queue is full\n");
    *err = 1;
    return;
  }
  if (q->last == q->size - 1)
    q->last = 0;
  else
  {
    (q->last)++;
    if ((q->last) == 0)
      (q->first)++;
  }
  (q->queue)[q->last] = elem;
  return;
}

int dequeueArray(t_queueArray *q, int *err)
{
  int result;
  *err = 0;
  if (q == NULL || q->queue == NULL)
  {
    *err = 1;
    return 0;
  }
  if (q->first == -1)
  {
    printf("Queue is empty\n");
    *err = 1;
    return 0;
  }
  result = (q->queue)[q->first];
  if (q->first == q->last)
    q->first = q->last = -1;
  else
  {
    if (q->first == q->size - 1)
      q->first = 0;
    else
      (q->first)++;
  }
  return result;
}

void outputQueueArray(t_queueArray *q)
{
  int i;
  printf("The queue:\n");
  if (q == NULL || q->queue == NULL)
    return;
  if (q->last < q->first)
  {
    for (i = q->first; i < q->size; i++)
      printf("%i\n", (q->queue)[i]);
    for (i = 0; i <= q->last; i++)
      printf("%i\n", (q->queue)[i]);
    return;
  }
  for (i = q->first; i <= q->last; i++)
    printf("%i\n", (q->queue)[i]);
  return;
}