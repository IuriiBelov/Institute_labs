#ifndef __PROJECT_LAB_A11_H_FILE_QUEUE_LIST__
#define __PROJECT_LAB_A11_H_FILE_QUEUE_LIST__

typedef struct queueListElem_t
{
  int data;
  struct queueListElem_t *prev;
  struct queueListElem_t *next;
} t_queueListElem;

typedef struct
{
  t_queueListElem *first;
  t_queueListElem *last;
} t_queueList;

void enqueueList(t_queueList **q, int elem, int *err);
int dequeueList(t_queueList **q, int *err);
void outputQueueList(t_queueList *q);

#endif