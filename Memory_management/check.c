#include <stdio.h>
#include "check.h"

int checkPointer(void *pointer)
{
  if (pointer == NULL)
  {
    printf("ERROR: not enough dynamic memory\n");
    return 1;
  }
  return 0;
}