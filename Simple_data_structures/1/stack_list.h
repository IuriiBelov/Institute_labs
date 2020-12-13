#ifndef __PROJECT_LAB_A1_H_FILE_STACK_LIST__
#define __PROJECT_LAB_A1_H_FILE_STACK_LIST__

typedef struct stackList_t
{
  struct stackList_t *prev;
  int data;
} t_stackList;

void pushElemStackList(t_stackList **s, int elem, int *err);
int popElemStackList(t_stackList **s, int *err);
int topElemStackList(t_stackList *s, int *err);
void outputStackList(t_stackList *s);

#endif