#include <stdio.h>
#include <stdlib.h>

#include "list_of_words.h"

int compareWordsAlphabetically(char *word1, char *word2, int length);

void addElem(t_listOfWords **l, char *word, int length, int *err)
{
  t_listOfWords *newElem, *l1, *prevElem;
  int i;
  *err = 0;
  newElem = malloc(sizeof(t_listOfWords));
  if (newElem == NULL)
  {
    *err = 1;
    return;
  }
  newElem->word = malloc(length * sizeof(char));
  if (newElem->word == NULL)
  {
    free(newElem);
    *err = 1;
    return;
  }
  newElem->length = length;
  for (i = 0; i < length; i++)
    (newElem->word)[i] = word[i];
  if (*l == NULL)
  {
    newElem->next = NULL;
    *l = newElem;
    return;
  }
  l1 = *l;
  prevElem = NULL;
  while (l1 != NULL && l1->length > length)
  {
    prevElem = l1;
    l1 = l1->next;
  }
  while (l1 != NULL && l1->length == length && compareWordsAlphabetically(l1->word, word, length) == 1)
  {
    prevElem = l1;
    l1 = l1->next;
  }
  newElem->next = l1;
  if (prevElem == NULL)
    *l = newElem;
  else
    prevElem->next = newElem;
  return;
}

void showAllWordsLongerThenN(t_listOfWords *l, int n)
{
  t_listOfWords *l1;
  if (l == NULL)
    return;
  printf("All words longer then %i:\n", n);
  l1 = l;
  while (l1 != NULL)
  {
    if (l1->length > n + 1)
      printf("%s\n", l1->word);
    l1 = l1->next;
  }
  printf("\n");
  return;
}

void showAllWordsOfNLengthAlphabetically(t_listOfWords *l, int n)
{
  t_listOfWords *l1;
  if (l == NULL)
    return;
  printf("All words of %i length:\n", n);
  l1 = l;
  while (l1 != NULL)
  {
    if (l1->length < n + 1)
      break;
    if (l1->length == n + 1)
      printf("%s\n", l1->word);
    l1 = l1->next;
  }
  printf("\n");
  return;
}

void showList(t_listOfWords *l)
{
  t_listOfWords *l1;
  if (l == NULL)
    return;
  l1 = l;
  while (l1 != NULL)
  {
    printf("%s\n", l1->word);
    l1 = l1->next;
  }
  printf("\n");
  return;
}

void deleteList(t_listOfWords **l)
{
  t_listOfWords *l1;
  while(*l != NULL)
  {
    l1 = (*l)->next;
    free(*l);
    *l = l1;
  }
  return;
}

int compareWordsAlphabetically(char *word1, char *word2, int length)
{
  int i;
  for (i = 0; i < length - 1; i++)
  {
    if (word1[i] == word2[i] - 32 || word1[i] == word2[i] + 32)
    {
      if (word1[i] < word2[i])
        return 1;
      if (word1[i] > word2[i])
        return 2;
      continue;
    }
    if (word1[i] <= 90 && word2[i] <= 90 || word1[i] >= 97 && word2[i] >= 97)
    {
      if (word1[i] < word2[i])
        return 1;
      if (word1[i] > word2[i])
        return 2;
      continue;
    }
    if (word1[i] < word2[i] - 32)
      return 1;
    if (word1[i] < word2[i] && word1[i] > word2[i] - 32)
      return 2;
    if (word2[i] < word1[i] - 32)
      return 2;
    if (word2[i] < word1[i] && word2[i] > word1[i] - 32)
      return 1;
  }
  return 0;
}