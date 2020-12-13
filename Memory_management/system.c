#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "system.h"

static block_t *s/* The head element of the list of free blocks */, *startOfTheHeap;
static int memory;/* Size of the allocated heap */

block_t *findSuitableBlock(block_t *s, int size);
void removeBlock(block_t *block);
void addBlock(block_t *block);
void fractureBlock(block_t *s, int size);
block_t *checkLeftBlock(block_t *block);
block_t *checkRightBlock(block_t *block);
void mergeBlocks(block_t *block1, block_t *block2);
void changePointers(block_t *q1, block_t *q);

int initSystem(int size)
{
  assert(size >= 0);
  if (size <= sizeof(block_t) + sizeof(int))
    return 1;
  memory = size;
  s = malloc(size);
  if (s == NULL)
    return 1;
  startOfTheHeap = s;
  s->prev = s->next = NULL;
  s->size = size - sizeof(block_t) - sizeof(int);
  *(int *)((char *)s + memory - sizeof(int)) = -(s->size);/* The block is free */
  return 0;
}

void *myMalloc(int size)
{
  void *p;/* The pointer that we are going to return */
  block_t *startOfList, *block;
  assert(size >= 0);
  startOfList = s;
  if ((block = findSuitableBlock(startOfList, size)) == NULL)
    return NULL;
  if (block->size <= (int)(size + sizeof(int) + sizeof(block_t)))
  {
    p = (void *)((char *)block + sizeof(block_t));/* p == s + descriptor */
    *(int *)((char *)block + sizeof(block_t) + block->size) = block->size;
    if (s == block)
      s = s->next;
    removeBlock(block);
  }
  else
  {
    p = (void *)((char *)block + sizeof(block_t) + block->size - size);
    fractureBlock(block, size);
  }
  return p;
}

block_t *findSuitableBlock(block_t *s, int size)
{
  assert(size >= 0);
  if (s == NULL)/* There are not any free blocks */
    return NULL;
  while (s->size < size)
  {
    //printf("aaa\n");
    s = s->next;
    if (s == NULL)/* We have overlooked all free blocks and have not found any suitable */
      return NULL;
  }
  return s;
}

void removeBlock(block_t *block)
{
  assert(block != NULL);
  /* The block is occupated */
  if (s == block)
    s = s->next;
  if (block->prev != NULL)
    (block->prev)->next = block->next;
  if (block->next != NULL)
    (block->next)->prev = block->prev;
  block->prev = block->next = NULL;
  return;
}

void addBlock(block_t *block)/* We add block to the head of list of free blocks */
{
  assert(block != NULL);
  block->prev = NULL;
  block->next = s;
  *(int *)((char *)block + sizeof(block_t) + block->size) = -(block->size);
  if (s != NULL)
    s->prev = block;
  s = block;
  return;
}

void fractureBlock(block_t *s, int size)
{
  block_t *occupatedBlock;
  assert(s != NULL  && size > 0);
  *(int *)((char *)s + sizeof(block_t) + s->size) = size;/* The second block is occupated */
  s->size = s->size - sizeof(int) - sizeof(block_t) - size;
  /* s->size == s->size - sizeof(occupated block) */
  occupatedBlock = (block_t *)((char *)s + sizeof(block_t) + s->size + sizeof(int));
  *(int *)((char *)s + sizeof(block_t) + s->size) = -(s->size);/* The first block is free */
  occupatedBlock->size = size;
  /* We wrote size of the occupated block in his descriptor*/
  occupatedBlock->next = occupatedBlock->prev = NULL;
  return;
}

void myFree(void *p)
{
  block_t *q, *q1;
  if (p == NULL)/* We do not need to free anything */
    return;
  q = (block_t *)((char *)p - sizeof(block_t));
  /* q points on the block that we are going to free */
  mergeBlocks(q, checkRightBlock(q));
  if (q1 = checkLeftBlock(q))
  {
    mergeBlocks(q1, q);
    return;
  }
  *(int *)((char *)q + sizeof(block_t) + q->size) = -(q->size);
  addBlock(q);
  return;
}

block_t *checkLeftBlock(block_t *block)
{
  assert(block != NULL);
  if (block < (block_t *)((char *)startOfTheHeap + sizeof(block_t) + sizeof(int)))
  /* The block do not has a left neighbour */
    return NULL;
  if (*(int *)((char *)block - sizeof(int)) < 0)/* If the left neighbour is free */
    return (block_t *)((char *)block - sizeof(int) + *(int *)((char *)block - sizeof(int)) - 
        sizeof(block_t));
  return NULL;
}

block_t *checkRightBlock(block_t *block)
{
  block_t *rightBlock;
  assert(block != NULL);
  rightBlock = (block_t *)((char *)block + sizeof(block_t) + block->size + sizeof(int));
  if ((char *)rightBlock > (char *)startOfTheHeap + 
      memory - sizeof(block_t) - sizeof(int))/* The block do not has a right neighbour */
    return NULL;
  if (*(int *)((char *)rightBlock + sizeof(block_t) + rightBlock->size) < 0)
  /* If the right neighbour is free */
    return rightBlock;
  return NULL;
}

void mergeBlocks(block_t *block1, block_t *block2)
{
  if (block1 == NULL || block2 == NULL)
    return;
  block1->size = block1->size + sizeof(int) + sizeof(block_t) + block2->size;
  /* Size of merged block */
  *(int *)((char *)block2 + sizeof(block_t) + block2->size) = -(block1->size);
  /* The merged block is free */
  removeBlock(block2);
  return;
}

void changePointers(block_t *q1, block_t *q)
{
  block_t *p;
  assert(q1 != NULL && q != NULL);
  q->prev = q1->prev;
  q->next = q->next;
  if (q1->prev != NULL)
    (q1->prev)->next = q;
  if (q1->next != NULL)
    (q1->next)->prev = q;
  p = q;
  q = q1;
  q1 = p;
  return;
}

void closeSystem(void)
{
  free(startOfTheHeap);/* Free allocated heap */
  return;
}