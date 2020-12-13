#ifndef __PROJECT_LAB_A1_H_FILE_STACK_ARRAY__
#define __PROJECT_LAB_A1_H_FILE_STACK_ARRAY__

typedef struct
{
  int *stack;
  int size;
  int i;
} t_stackArray;

void createStackArray(t_stackArray **s, int size, int *err);
void deleteStackArray(t_stackArray **s);
void pushElemStackArray(t_stackArray *s, int elem, int *err);
int popElemStackArray(t_stackArray *s, int *err);
int topElemStackArray(t_stackArray *s, int *err);
void outputStackArray(t_stackArray *s);

#endif