#include <stdio.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "list_of_strings.h"

int main()
{
  FILE *fp;
  int size, i, j, err, length;
  char c, *s;
  t_listOfStrings *l, *l1;
  _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    printf("Error: file not opened\n");
    return 0;
  }
  fseek(fp, 0 ,SEEK_END);  
  size = ftell(fp);
  fseek(fp, 0 ,SEEK_SET);
  s = malloc(size * sizeof(char));
  if (s == NULL)
  {
    printf("Error: not enough memory\n");
    fclose(fp);
    return 0;
  }
  i = 0;
  l = NULL;
  do
  {
    c = fgetc(fp);
    switch (c)
    {
    case '\n': case EOF:
      s[i] = '\0';
      err = 0;
      addElem(&l, s, i + 1, &err);
      i = 0;
      break;
    default:
      s[i] = c;
      i++;
    }
  } while (c != EOF);
  fclose(fp);
  free(s);
  length = 0;
  l1 = l;
  while (l1 != NULL)
  {
    length += l1->elemSize;
    length--;
    l1 = l1->next;
  }
  length++;
  s = malloc(length * sizeof(char));
  if (s == NULL)
  {
    printf("Error: not enough memory\n");
    while (l != NULL)
      deleteElem(&l, &err);
    return 0;
  }
  l1 = l;
  i = 0;
  while (l1 != NULL)
  {
    for (j = 0; j < l1->elemSize - 1; j++)
    {
      s[i] = (l1->elem)[j];
      i++;
    }
    l1 = l1->next;
  }
  s[i] = '\0';
  printf("%s\n", s);
  free(s);
  while (l != NULL)
    deleteElem(&l, &err);
  return 0;
}