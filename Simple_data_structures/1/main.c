#include <stdio.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "stack_list.h"
#include "stack_array.h"

int main()
{
  t_stackList *s1;
  t_stackArray *s2;
  int err;
  _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  //stackList
  s1 = NULL;
  err = 0;
  pushElemStackList(&s1, 2, &err);
  outputStackList(s1);
  pushElemStackList(&s1, 1, &err);
  outputStackList(s1);
  pushElemStackList(&s1, 3, &err);
  outputStackList(s1);
  popElemStackList(&s1, &err);
  outputStackList(s1);
  pushElemStackList(&s1, 4, &err);
  outputStackList(s1);
  pushElemStackList(&s1, 9, &err);
  outputStackList(s1);
  popElemStackList(&s1, &err);
  outputStackList(s1);
  popElemStackList(&s1, &err);
  outputStackList(s1);
  popElemStackList(&s1, &err);
  outputStackList(s1);
  popElemStackList(&s1, &err);
  outputStackList(s1);
  popElemStackList(&s1, &err);
  outputStackList(s1);
  pushElemStackList(&s1, 1, &err);
  outputStackList(s1);
  pushElemStackList(&s1, 2, &err);
  outputStackList(s1);

  printf("///\n");

  //stackArray
  s2 = NULL;
  err = 0;
  createStackArray(&s2, 3, &err);
  pushElemStackArray(s2, 2, &err);
  outputStackArray(s2);
  pushElemStackArray(s2, 1, &err);
  outputStackArray(s2);
  pushElemStackArray(s2, 3, &err);
  outputStackArray(s2);
  popElemStackArray(s2, &err);
  outputStackArray(s2);
  pushElemStackArray(s2, 4, &err);
  outputStackArray(s2);
  pushElemStackArray(s2, 9, &err);
  outputStackArray(s2);
  popElemStackArray(s2, &err);
  outputStackArray(s2);
  popElemStackArray(s2, &err);
  outputStackArray(s2);
  popElemStackArray(s2, &err);
  outputStackArray(s2);
  popElemStackArray(s2, &err);
  outputStackArray(s2);
  popElemStackArray(s2, &err);
  outputStackArray(s2);
  pushElemStackArray(s2, 1, &err);
  outputStackArray(s2);
  pushElemStackArray(s2, 2, &err);
  outputStackArray(s2);
  deleteStackArray(&s2);
  return 0;
}