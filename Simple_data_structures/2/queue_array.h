#ifndef __PROJECT_LAB_A11_H_FILE_QUEUE_ARRAY__
#define __PROJECT_LAB_A11_H_FILE_QUEUE_ARRAY__

typedef struct
{
  int *queue;
  int size;
  int first;
  int last;
} t_queueArray;

void createQueueArray(t_queueArray **q, int size, int *err);
void deleteQueueArray(t_queueArray **q);
void enqueueArray(t_queueArray *q, int elem, int *err);
int dequeueArray(t_queueArray *q, int *err);
void outputQueueArray(t_queueArray *q);

#endif