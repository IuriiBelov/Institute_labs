#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "length.h"

#define ENTER 10

int length(char const *str)
{
  int l = 0;
  //length of the string
  assert(str != NULL);
  while ((str[l] != ENTER) && (str[l] != EOF))
    l++;
  assert(l >= 0);
  return l;
}