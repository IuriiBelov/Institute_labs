#include "ChangeValues.h"

void changeValues(int *a, int *b)
{
  int change;
  //auxiliary variable
  change = *a;
  *a = *b;
  *b = change;
  return;
}