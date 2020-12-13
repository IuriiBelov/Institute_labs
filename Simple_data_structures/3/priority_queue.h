#ifndef __PROJECT_LAB_A110_H_FILE_LIST_OF_STRINGS__
#define __PROJECT_LAB_A110_H_FILE_lIST_OF_STRINGS__

typedef struct priorityQueueElem_t
{
  char *data;
  int dataSize;
  int priority;
  struct priorityQueueElem_t *prev;
  struct priorityQueueElem_t *next;
} t_priorityQueueElem;

typedef struct priorityQueue_t
{
  t_priorityQueueElem *first;
  t_priorityQueueElem *last;
} t_priorityQueue;

void insertElem(t_priorityQueue **q, t_priorityQueueElem *elem, int *err);
t_priorityQueueElem *extractMaximumAndDelete(t_priorityQueue **q, int *err);
t_priorityQueueElem *extractMaximumNoDelete(t_priorityQueue *q, int *err);
void changePriority(t_priorityQueue **q, t_priorityQueueElem *elem, int newPriority, int *err);
void deleteElem(t_priorityQueue **q, t_priorityQueueElem *elem, int *err);
void printQueue(t_priorityQueue *q);

t_priorityQueueElem *findElem(t_priorityQueue *q, t_priorityQueueElem *elem);

#endif