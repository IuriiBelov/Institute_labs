#include <stdlib.h>
#include <assert.h>
#include "memory.h"
#include "check.h"

#define N 10000
#define DESKRIPTOR 16

static block_t *s = NULL;
static block_t *startOfTheHeap = NULL;

void defragmentation(block_t *s);

int initSystem(void)
{
  assert(s == NULL);
  s = malloc(N);
  if (checkPointer(s))
    return 1;
  s->size = N - sizeof(block_t) - sizeof(int);
  s->prev = s->next = NULL;
  *(int *)((char *)s + sizeof(block_t) + s->size) = -(s->size);
  startOfTheHeap = s;
  return 0;
}

void *myMalloc(int size)
{
  void *p = NULL;
  block_t *next, *prev, *start, *q;
  assert(size >= 0);
  if (s == NULL)
    return NULL;
  start = s;
  while (s->size < size)
  {
    s = s->next;
    if (s == NULL)
      return NULL;
  }
  p = (void *)((char *)s + sizeof(block_t));
  if (s->size >= size && s->size <= (int)(size + sizeof(int) + sizeof(block_t)))
  {
    next = s->next;
    prev = s->prev;
    if (next == NULL && prev == NULL)
      s = NULL;
    if (next == NULL && prev != NULL)
    {
      (s->prev)->next = NULL;
      s->prev = NULL;
      s = start;
    }
    if (next != NULL && prev == NULL)
    {
      q = s->next;
      s->next = NULL;
      s = q;
      s->prev = NULL;
    }
    if (next != NULL && prev != NULL)
    {
      (s->next)->prev = prev;
      (s->prev)->next = next;
      s->prev = s->next = NULL;
      s = start;
    }
  }
  else
  {
    *(int *)((char *)p + size) = size;
    q = (block_t *)((char *)p + size + sizeof(int));
    q->next = s->next;
    q->prev = s->prev;
    if (s->prev != NULL)
      (s->prev)->next = q;
    if (s->next != NULL)
      (s->next)->prev = q;
    q->size = s->size - size - sizeof(int) - sizeof(block_t);
    s->size = size;
    s->prev = s->next = NULL;
    *(int *)((char *)q + sizeof(block_t) + q->size) = -(q->size);
    if (q->prev == NULL)
      s = q;
    else
      s = start;
  }
  return p;
}

void myFree(void *p)
{
  block_t *q;
  int size;
  if (p == NULL)
    return;
  size = *(int *)((char *)p - sizeof(int));
  q = (block_t *)((char *)p - sizeof(block_t));
  q->prev = NULL;
  if (s == NULL)
    q->next = NULL;
  else
  {
    q->next = s;
    s->prev = q;
  }
  q->size = size;
  s = q;
  *(int *)((char *)s + sizeof(block_t) + size) = -size;
  defragmentation(s);
  return;
}

void defragmentation(block_t *s)
{
  block_t *q;
  /*right defragmentation*/
  int a;
  assert(s != NULL);
  a = 2 * sizeof(block_t) + s->size + sizeof(int) + *(int *)((char *)s + 2 * sizeof(block_t) 
      + s->size);
  if (s < (block_t *)((char *)startOfTheHeap + a) && *(int *)((char *)s + a) < 0)
  {
    q = (block_t *)((char *)s + sizeof(block_t) + s->size + sizeof(int));
    if (q->next != NULL)
      (q->next)->prev = q->prev;
    if (q->prev != NULL)
      (q->prev)->next = q->next;
    q->prev = q->next = NULL;
    s->size = s->size + sizeof(int) + sizeof(block_t) - *(int *)((char *)s + 2 * 
        sizeof(block_t) + s->size);
    *(int *)((char *)q + sizeof(block_t) + q->size) = -(s->size);
  }
  /*left defragmentation*/
  if (s > (block_t *)((char *)startOfTheHeap + sizeof(int)) && *(int *)((char *)s - 
      sizeof(int)) < 0)
  {
    q = (block_t *)((char *)s - sizeof(int) + *(int *)((char *)s - sizeof(int)) - 
        sizeof(block_t));
    if (q->next != NULL)
      (q->next)->prev = q->prev;
    if (q->prev != NULL)
      (q->prev)->next = q->next;
    q->next = s->next;
    q->prev = NULL;
    (s->next)->prev = q;
    q->size = *(int *)((char *)q + sizeof(block_t) - sizeof(int)) + sizeof(int) + 
        sizeof(block_t) + s->size;
    *(int *)((char *)s + sizeof(block_t) + s->size) = -(q->size);
    s = q;
  }
  return;
}

void closeSystem(void)
{
  free(startOfTheHeap);
  return;
}