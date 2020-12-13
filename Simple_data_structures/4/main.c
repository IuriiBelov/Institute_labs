#include <stdio.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "list_of_words.h"

int main()
{
  t_listOfWords *l;
  char *word;
  char c;
  int err, i, size;
  FILE *fp;

  _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  // Filling the list
  fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    printf("Error: file not opened\n");
    return 0;
  }
  fseek(fp, 0 ,SEEK_END);  
  size = ftell(fp);
  fseek(fp, 0 ,SEEK_SET);
  word = malloc(size * sizeof(char));
  if (word == NULL)
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
      word[i] = '\0';
      err = 0;
      addElem(&l, word, i + 1, &err);
      showList(l);
      i = 0;
      break;
    default:
      word[i] = c;
      i++;
    }
  } while (c != EOF);
  fclose(fp);
  free(word);
  // Working with the list
  showAllWordsLongerThenN(l, 4);
  showAllWordsOfNLengthAlphabetically(l, 4);
  return 0;
}