#ifndef __PROJECT_LAB_A23_H_FILE_LIST_OF_WORDS__
#define __PROJECT_LAB_A23_H_FILE_lIST_OF_WORDS__

typedef struct listOfWords_t
{
  char *word;
  int length;
  struct listOfWords_t *next;
} t_listOfWords;

void addElem(t_listOfWords **l, char *word, int length, int *err);
void showAllWordsLongerThenN(t_listOfWords *l, int n);
void showAllWordsOfNLengthAlphabetically(t_listOfWords *l, int n);
void showList(t_listOfWords *l);
void deleteList(t_listOfWords **l);

#endif