#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stringSet.h"
#include "check.h"

#define MAX_LENGTH 80

setList *findSet(char *nameOfSet, setList *listOfSets);
int findSets(char *nameOfSet1, char *nameOfSet2, elemSet **set1, elemSet **set2, setList 
    *listOfSets);
setList *createNewSet(setList **listOfSets);
int checkSet(char *nameOfSet, setList *listOfSets);
int initSets(elemSet **set1, elemSet **set2, setList **newSet, setList **listOfSets, char 
    *nameOfSet1, char *nameOfSet2);
void addElem2(setList *list, elemSet **set, char *nameOfElement);

setList *createSet(char *nameOfSet, setList **listOfSets)
{
  int i;
  setList *newSet, *prevSet, *listOfSets2;
  assert(nameOfSet != NULL && listOfSets != NULL);
  /* Find the place to insert the new set */
  listOfSets2 = *listOfSets;
  prevSet = NULL;
  while (listOfSets2 != NULL)
  {
    if (strcmp(listOfSets2->nameOfSet, nameOfSet) == 0)
    {
      printf("A set with such name already exists\n");
      return NULL;
    }
    else if (strcmp(listOfSets2->nameOfSet, nameOfSet) < 0)
    {
      prevSet = listOfSets2;
      listOfSets2 = listOfSets2->next;
    }
    else
      break;
  }
  /* Create new set */
  newSet = malloc(sizeof(setList));
  if (checkPointer(newSet))
    return NULL;
  newSet->set = NULL;
  newSet->nameOfSet = malloc((strlen(nameOfSet) + 1) * sizeof(char));
  if (checkPointer(newSet->nameOfSet))
  {
    free(newSet);
    return NULL;
  }
  for (i = 0; i < (int)strlen(nameOfSet); i++)
    (newSet->nameOfSet)[i] = nameOfSet[i];
  (newSet->nameOfSet)[strlen(nameOfSet)] = '\0';
  /* Add new set to the list of sets */
  newSet->next = listOfSets2;
  if (prevSet != NULL)
    prevSet->next = newSet;
  else
    *listOfSets = newSet;
  return newSet;
}

void deleteSet(char *nameOfSet, setList **listOfSets)
{
  setList *listOfSets2, *prevSet, *delSet;
  elemSet *nextElem;
  assert(nameOfSet != NULL && listOfSets != NULL);
  /* Find the set we need to delete */
  listOfSets2 = *listOfSets;
  prevSet = NULL;
  delSet = NULL;
  while (listOfSets2 != NULL)
  {
    if (strcmp(listOfSets2->nameOfSet, nameOfSet) == 0)
    {
      delSet = listOfSets2;
      break;
    }
    else if (strcmp(listOfSets2->nameOfSet, nameOfSet) < 0)
    {
      prevSet = listOfSets2;
      listOfSets2 = listOfSets2->next;
    }
    else
      break;
  }
  if (delSet == NULL)
  {
    printf("There isn`t a set with such name\n");
    return;
  }
  /* Delete all elements of the set */
  if (delSet->set != NULL)
  {
    do
    {
      nextElem = (delSet->set)->next;
      free((delSet->set)->data);
      free(delSet->set);
      delSet->set = nextElem;
    } while (delSet->set != NULL);
  }
  /* Delete the set from the list of sets */
  if (prevSet != NULL)
    prevSet->next = delSet->next;
  else
    *listOfSets = delSet->next;
  free(delSet->nameOfSet);
  free(delSet);
  return;
}

void powerSet(char *nameOfSet, setList *listOfSets)
{
  int power;
  elemSet *set;
  setList *list;
  assert(nameOfSet != NULL);
  list = findSet(nameOfSet, listOfSets);
  if (list == NULL)
    return;
  set = list->set;
  power = 0;
  while (set != NULL)
  {
    power++;
    set = set->next;
  }
  printf("Power of the set is: %i\n", power);
  return;
}

void addElem(char *nameOfSet, char *nameOfElement, setList *listOfSets)
{
  int i;
  setList *list;
  elemSet *set, *prevElem, *newElem;
  assert(nameOfSet != NULL && nameOfElement != NULL);
  /* Check if the element is acceptable */
  if (checkElement(nameOfSet) || strlen(nameOfSet) > MAX_LENGTH)
    return;
  list = findSet(nameOfSet, listOfSets);
  if (list == NULL)
    return;
  set = list->set;
  prevElem = NULL;
  /* Find the place to insert the new element */
  while (set != NULL)
  {
    if (strcmp(set->data, nameOfElement) == 0)
    {
      printf("Such element already exists in this set\n");
      return;
    }
    if (strcmp(set->data, nameOfElement) < 0)
    {
      prevElem = set;
      set = set->next;
    }
    else
      break;
  }
  /* Create new element */
  newElem = malloc(sizeof(elemSet));
  if (checkPointer(newElem))
    return;
  newElem->data = malloc((strlen(nameOfElement) + 1) * sizeof(char));
  if (checkPointer(newElem->data))
  {
    free(newElem);
    return;
  }
  for (i = 0; i < (int)strlen(nameOfElement); i++)
    (newElem->data)[i] = nameOfElement[i];
  (newElem->data)[strlen(nameOfElement)] = '\0';
  /* Add new elem to the set */
  newElem->next = set;
  if (prevElem != NULL)
    prevElem->next = newElem;
  else
    list->set = newElem;
  return;
}

void deleteElem(char *nameOfSet, char *nameOfElement, setList *listOfSets)
{
  setList *list;
  elemSet *set, *prevElem, *delElem;
  assert(nameOfSet != NULL && nameOfElement != NULL);
  list = findSet(nameOfSet, listOfSets);
  if (list == NULL)
    return;
  set = list->set;
  /* Find the element we need to delete */
  prevElem = NULL;
  delElem = NULL;
  while (set != NULL)
  {
    if (strcmp(set->data, nameOfElement) == 0)
    {
      delElem = set;
      break;
    }
    else if (strcmp(set->data, nameOfElement) < 0)
    {
      prevElem = set;
      set = set->next;
    }
    else
      return;
  }
  if (delElem == NULL)
  {
    printf("There isn`t such element in this set\n");
    return;
  }
  /* Delete the element from the list of elements */
  if (prevElem != NULL)
    prevElem->next = delElem->next;
  else
    list->set = delElem->next;
  free(delElem->data);
  free(delElem);
  return;
}

void checkElem(char *nameOfSet, char *nameOfElement, setList *listOfSets)
{
  setList *list;
  elemSet *set;
  assert(nameOfSet != NULL && nameOfElement != NULL);
  list = findSet(nameOfSet, listOfSets);
  if (list == NULL)
    return;
  set = list->set;
  while (set != NULL)
  {
    /* The element is founded */
    if (strcmp(set->data, nameOfElement) == 0)
    {
      printf("YES\n");
      return;
    }
    set = set->next;
  }
  printf("NO\n");
  return;
}

void unificationSet(char *nameOfSet1, char *nameOfSet2, setList **listOfSets)
{
  elemSet *set1, *set2, *newSet;
  setList *list;
  assert(nameOfSet1 != NULL && nameOfSet2 != NULL && listOfSets != NULL);
  set1 = set2 = newSet = NULL;
  if (initSets(&set1, &set2, &list, listOfSets, nameOfSet1, nameOfSet2))
    return;
  newSet = NULL;
  while (set1 != NULL || set2 != NULL)
  {
    if (set1 != NULL && set2 != NULL)
    {
      if (strcmp(set1->data, set2->data) == 0)
      {
        addElem2(list, &newSet, set1->data);
        set1 = set1->next;
        set2 = set2->next;
      }
      else
      {
        if (strcmp(set1->data, set2->data) < 0)
        {
          addElem2(list, &newSet, set1->data);
          set1 = set1->next;
        }
        else
        {
          addElem2(list, &newSet, set2->data);
          set2 = set2->next;
        }
      }
    }
    else
    {
      if (set1 == NULL)
      {
        addElem2(list, &newSet, set2->data);
        set2 = set2->next;
      }
      else
      {
        addElem2(list, &newSet, set1->data);
        set1 = set1->next;
      }
    }
  }
  return;
}

void intersectionSet(char *nameOfSet1, char *nameOfSet2, setList **listOfSets)
{
  elemSet *set1, *set2, *newSet;
  setList *list;
  assert(nameOfSet1 != NULL && nameOfSet2 != NULL && listOfSets != NULL);
  set1 = set2 = newSet = NULL;
  if (initSets(&set1, &set2, &list, listOfSets, nameOfSet1, nameOfSet2))
    return;
  newSet = NULL;
  while (set1 != NULL && set2 != NULL)
  {
    if (strcmp(set1->data, set2->data) == 0)
    {
      addElem2(list, &newSet, set1->data);
      set1 = set1->next;
      set2 = set2->next;
    }
    else
    {
      if (strcmp(set1->data, set2->data) < 0)
        set1 = set1->next;
      else
        set2 = set2->next;
    }
  }
  return;
}

void differenceSet(char *nameOfSet1, char *nameOfSet2, setList **listOfSets)
{
  elemSet *set1, *set2, *newSet;
  setList *list;
  assert(nameOfSet1 != NULL && nameOfSet2 != NULL && listOfSets != NULL);
  set1 = set2 = newSet = NULL;
  if (initSets(&set1, &set2, &list, listOfSets, nameOfSet1, nameOfSet2))
    return;
  newSet = NULL;
  while (set1 != NULL)
  {
    if (set2 == NULL)
    {
      addElem2(list, &newSet, set1->data);
      set1 = set1->next;
    }
    else
    {
      if (strcmp(set1->data, set2->data) == 0)
      {
        set1 = set1->next;
        set2 = set2->next;
      }
      else
      {
        if (strcmp(set1->data, set2->data) < 0)
        {
          addElem2(list, &newSet, set1->data);
          set1 = set1->next;
        }
        else
          set2 = set2->next;
      }
    }
  }
  return;
}

void symmetricDifferenceSet(char *nameOfSet1, char *nameOfSet2, setList **listOfSets)
{
  elemSet *set1, *set2, *newSet;
  setList *list;
  assert(nameOfSet1 != NULL && nameOfSet2 != NULL && listOfSets != NULL);
  set1 = set2 = newSet = NULL;
  if (initSets(&set1, &set2, &list, listOfSets, nameOfSet1, nameOfSet2))
    return;
  newSet = NULL;
  while (set1 != NULL || set2 != NULL)
  {
    if (set1 != NULL && set2 != NULL)
    {
      if (strcmp(set1->data, set2->data) == 0)
      {
        set1 = set1->next;
        set2 = set2->next;
      }
      else
      {
        if (strcmp(set1->data, set2->data) < 0)
        {
          addElem2(list, &newSet, set1->data);
          set1 = set1->next;
        }
        else
        {
          addElem2(list, &newSet, set2->data);
          set2 = set2->next;
        }
      }
    }
    else
    {
      if (set1 == NULL)
      {
        addElem2(list, &newSet, set2->data);
        set2 = set2->next;
      }
      else
      {
        addElem2(list, &newSet, set1->data);
        set1 = set1->next;
      }
    }
  }
  return;
}

void checkInclusion(char *nameOfSet1, char *nameOfSet2, setList **listOfSets)
{
  elemSet *set1, *set2;
  assert(nameOfSet1 != NULL && nameOfSet2 != NULL && listOfSets != NULL);
  set1 = set2 = NULL;
  if (findSets(nameOfSet1, nameOfSet2, &set1, &set2, *listOfSets))
    return;
  while (set1 != NULL)
  {
    if (strcmp(set1->data, set2->data) == 0)
    {
      set1 = set1->next;
      set2 = set2->next;
    }
    else
    {
      if (strcmp(set1->data, set2->data) < 0)
      {
        printf("NO\n");
        return;
      }
      else
        set2 = set2->next;
    }
    if (set2 == NULL)
    {
      printf("NO\n");
      return;
    }
  }
  printf("YES\n");
  return;
}

void showList(setList *listOfSets)
{
  setList *listOfSets2;
  listOfSets2 = listOfSets;
  printf("List of legacy sets: \n");
  /* Print all elements from list of sets */
  while (listOfSets2 != NULL)
  {
    printf("%s\n", listOfSets2->nameOfSet);
    listOfSets2 = listOfSets2->next;
  }
  return;
}

void showSet(char *nameOfSet, setList *listOfSets)
{
  setList *list;
  elemSet *set;
  assert(nameOfSet != NULL);
  list = findSet(nameOfSet, listOfSets);
  if (list == NULL)
    return;
  set = list->set;
  printf("Elements of the set %s: \n", nameOfSet);
  printf("{");
  while (set != NULL)
  {
    printf("%s", set->data);
    if (set->next != NULL && (set->next)->data != NULL)
      printf(",");
    printf(" ");
    set = set->next;
  }
  printf("}\n");
  return;
}

void help(void)
{
  printf("\n");
  printf("HELP:\n");
  printf("This program operates with sets of strings. Maximum length of the string is 80\n");
  printf("    symbols. You can do these operations:\n");
  printf("'create_<name_of_the_set>' - to create a set\n");
  printf("'delete_<name_of_the_set>' - to delete the set\n");
  printf("'power_<name_of_the_set>' - to withdraw power of the set\n");
  printf("'add_<name_of_the_set>_<name_of_the_element>' - to add the element to the set\n");
  printf("'delete_<name_of_the_set>_<name_of_the_element>' - to delete the element from\n");
  printf("    the set\n");
  printf("'check_<name_of_the_set>_<name_of_the_element>' - to check if the set contains\n");
  printf("    the element\n");
  printf("'unification_<name_of_the_set_1>_<name_of_the_set_2>' - to count an\n");
  printf("    unification of the two sets and to put it in a new set\n");
  printf("'intersection_<name_of_the_set_1>_<name_of_the_set_2>' - to count an\n");
  printf("    untersection of the two sets and to put it in a new set\n");
  printf("'difference_<name_of_the_set_1>_<name_of_the_set_2>' - to count a difference\n");
  printf("    of the two sets and to put it in a new set\n");
  printf("'symmetric_<name_of_the_set_1>_<name_of_the_set_2>' - to count a symmetric\n");
  printf("    difference of the two sets and to put it in a new set\n");
  printf("'inclusion_<name_of_the_set_1>_<name_of_the_set_2>' - to check if the set 1\n");
  printf("    contains the set 2\n");
  printf("'show' - to show the list of existing sets\n");
  printf("'show_<name_of_the_set>' - to show elements of the set\n");
  printf("'end' - to finish the program\n");
  printf("'help' - to cause the reference\n");
  printf("\n");
  return;
}

void freeListOfSets(setList *listOfSets)
{
  elemSet *set;
  setList *listOfSets2;
  while (listOfSets != NULL)
  {
    while (listOfSets->set != NULL)
    {
      set = (listOfSets->set)->next;
      free((listOfSets->set)->data);
      free(listOfSets->set);
      listOfSets->set = set;
    }
    listOfSets2 = listOfSets->next;
    free(listOfSets->nameOfSet);
    free(listOfSets);
    listOfSets = listOfSets2;
  }
}

setList *findSet(char *nameOfSet, setList *listOfSets)
{
  setList *listOfSets2;
  assert(nameOfSet != NULL);
  listOfSets2 = listOfSets;
  while(listOfSets2 != NULL)
  {
    if (strcmp(listOfSets2->nameOfSet, nameOfSet) == 0)
      return listOfSets2;
    listOfSets2 = listOfSets2->next;
  }
  printf("There isn`t a set with such name\n");
  return NULL;
}

int findSets(char *nameOfSet1, char *nameOfSet2, elemSet **set1, elemSet **set2, setList 
    *listOfSets)
{
  setList *list1, *list2;
  assert(nameOfSet1 != NULL && nameOfSet2 != NULL && set1 != NULL && set2 != NULL);
  list1 = findSet(nameOfSet1, listOfSets);
  list2 = findSet(nameOfSet2, listOfSets);
  if (list1 == NULL || list2 == NULL)
    return 1;
  *set1 = list1->set;
  *set2 = list2->set;
  return 0;
}

setList *createNewSet(setList **listOfSets)
{
  setList *list;
  char nameOfNewSet[MAX_LENGTH];
  assert(listOfSets != NULL);
  do
  {
    printf("Enter the name of the new set\n");
    gets(nameOfNewSet);
    if (!checkSet(nameOfNewSet, *listOfSets))
      break;
    printf("Set with such name already exists. Try again\n");
  } while (1);
  list = createSet(nameOfNewSet, listOfSets);
  return list;
}

int checkSet(char *nameOfSet, setList *listOfSets)
{
  setList *listOfSets2;
  assert(nameOfSet != NULL);
  listOfSets2 = listOfSets;
  while (listOfSets2 != NULL)
  {
    if (strcmp(nameOfSet, listOfSets2->nameOfSet) == 0)
      return 1;
    listOfSets2 = listOfSets2->next;
  }
  return 0;
}

int initSets(elemSet **set1, elemSet **set2, setList **newSet, setList **listOfSets, char 
    *nameOfSet1, char *nameOfSet2)
{
  assert(set1 != NULL && set2 != NULL && newSet != NULL && listOfSets != NULL && 
      nameOfSet1 != NULL && nameOfSet2 != NULL);
  if (findSets(nameOfSet1, nameOfSet2, set1, set2, *listOfSets))
    return 1;
  *newSet = createNewSet(listOfSets);
  if (*newSet == NULL)
    return 1;
  return 0;
}

void addElem2(setList *list, elemSet **set, char *nameOfElement)
{
  int i;
  elemSet *newElem;
  assert(list != NULL && set != NULL && nameOfElement != NULL);
  newElem = malloc(sizeof(elemSet));
  if (checkPointer(newElem))
    return;
  newElem->data = malloc((strlen(nameOfElement) + 1) * sizeof(char));
  if (checkPointer(newElem->data))
  {
    free(newElem);
    return;
  }
  for (i = 0; i < (int)strlen(nameOfElement); i++)
    (newElem->data)[i] = nameOfElement[i];
  (newElem->data)[strlen(nameOfElement)] = '\0';
  newElem->next = NULL;
  if (*set == NULL)
    list->set = newElem;
  else
    (*set)->next = newElem;
  *set = newElem;
  return;
}