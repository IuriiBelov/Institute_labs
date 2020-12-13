#ifndef __PROJECT_LAB_A110_H_FILE_LIST_OF_STRINGS__
#define __PROJECT_LAB_A110_H_FILE_lIST_OF_STRINGS__

typedef struct listOfStrings_t
{
  char *elem;
  int elemSize;
  struct listOfStrings_t *next;
} t_listOfStrings;

void addElem(t_listOfStrings **l, char *elem, int elemSize, int *err);
void deleteElem(t_listOfStrings **l, int *err);
void outputList(t_listOfStrings *l);

#endif