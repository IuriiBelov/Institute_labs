#ifndef H_FILE_STRINGSET__
#define H_FILE_STRINGSET__

typedef struct tag_elemSet
{
  char *data;
  struct tag_elemSet *next;
} elemSet;

typedef struct tag_setList
{
  elemSet *set;
  char *nameOfSet;
  struct tag_setList *next;
} setList;

setList *createSet(char *nameOfSet, setList **listOfSets);
void deleteSet(char *nameOfSet, setList **listOfSets);

void powerSet(char *nameOfSet, setList *listOfSets);
void addElem(char *nameOfSet, char *nameOfElement, setList *listOfSets);
void deleteElem(char *nameOfSet, char *nameOfElement, setList *listOfSets);
void checkElem(char *nameOfSet, char *nameOfElement, setList *listOfSets);

void unificationSet(char *nameOfSet1, char *nameOfSet2, setList **listOfSets);
void intersectionSet(char *nameOfSet1, char *nameOfSet2, setList **listOfSets);
void differenceSet(char *nameOfSet1, char *nameOfSet2, setList **listOfSets);
void symmetricDifferenceSet(char *nameOfSet1, char *nameOfSet2, setList **listOfSets);
void checkInclusion(char *nameOfSet1, char *nameOfSet2, setList **listOfSets);

void showList(setList *listOfSets);
void showSet(char *nameOfSet, setList *listOfSets);

void help(void);

void freeListOfSets(setList *listOfSets);

#endif