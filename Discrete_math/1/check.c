#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "check.h"

#define CHAR_A 65
#define CHAR_Z 90

#define CHAR_0 48
#define CHAR_9 57

#define MIN_SYMBOL 32
#define MAX_SYMBOL 126
#define NON_SYMBOL 34

int checkPointer(void *pointer)
{
  if (pointer == NULL)
  {
    printf("ERROR: not enough dynamic memory\n");
    return 1;
  }
  return 0;
}

int checkSymbol(char symbol)
{
  if (symbol >= MIN_SYMBOL && symbol <= MAX_SYMBOL && symbol != NON_SYMBOL)
    return 0;
  return 1;
}

int checkElement(char *nameOfElement)
{
  int i, j;
  assert(nameOfElement != NULL);
  j = 0;
  for (i = 0; i < (int)strlen(nameOfElement); i++)
    if (!checkSymbol(nameOfElement[i]))
      j++;
  if (j < i)
  {
    printf("The element is not acceptable\n");
    return 1;
  }
  return 0;
}