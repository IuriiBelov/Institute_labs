#include <stdio.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "stringSet.h"
#include "check.h"

#define MAX_COMMAND_LENGTH 300/* Максимальная длина команды */
#define MAX_LENGTH 80/* Максимальная длина строки - элемента множества */

#define CREATE_SET 1
#define DELETE_SET 2

#define POWER_SET 11
#define ADD_ELEM 12
#define DELETE_ELEM 13
#define CHECK_ELEM 14

#define UNIFICATION_SET 21
#define INTERSECTION_SET 22
#define DIFFERENCE_SET 23
#define SYMMETRIC_DIFFERENCE_SET 24
#define CHECK_INCLUSION 25

#define SHOW_LIST 31
#define SHOW_SET 32

#define HELP 41

#define END 100

#define ERROR 1000

void getCommand(char command[MAX_COMMAND_LENGTH]);
int checkCommand(char *command, char **str1, char **str2);
int checkAddFunc(char *command, int *i);
int checkCheckFunc(char *command, int *i);
int checkCreateFunc(char *command, int *i);
int checkDeleteFunc(char *command, int *i);
int checkDifferenceFunc(char *command, int *i);
int checkEndFunc(char *command, int *i);
int checkHelpFunc(char *command, int *i);
int checkInclusionFunc(char *command, int *i);
int checkIntersectionFunc(char *command, int *i);
int checkPowerFunc(char *command, int *i);
int checkShowFunc(char *command, int *i);
int checkSymmetricFunc(char *command, int *i);
int checkUnificationFunc(char *command, int *i);
int readString(char *command, int *i, char **str);
int passSpace(char *command, int *i);

int readData(char *command, char *str1, char *str2, int n, int parameter);

int main(void)
{
  int end;
  setList *listOfSets;
  char command[MAX_COMMAND_LENGTH], *str1 = NULL, *str2 = NULL;
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
  end = 0;
  listOfSets = NULL;
  do
  {
    getCommand(command);
    switch (checkCommand(command, &str1, &str2))
    {
      case CREATE_SET :
        createSet(str1, &listOfSets);
        break;
      case DELETE_SET :
        deleteSet(str1, &listOfSets);
        break;
      case POWER_SET :
        powerSet(str1, listOfSets);
        break;
      case ADD_ELEM :
        addElem(str1, str2, listOfSets);
        break;
      case DELETE_ELEM :
        deleteElem(str1, str2, listOfSets);
        break;
      case CHECK_ELEM :
        checkElem(str1, str2, listOfSets);
        break;
      case UNIFICATION_SET :
        unificationSet(str1, str2, &listOfSets);
        break;
      case INTERSECTION_SET :
        intersectionSet(str1, str2, &listOfSets);
        break;
      case DIFFERENCE_SET :
        differenceSet(str1, str2, &listOfSets);
        break;
      case SYMMETRIC_DIFFERENCE_SET :
        symmetricDifferenceSet(str1, str2, &listOfSets);
        break;
      case CHECK_INCLUSION :
        checkInclusion(str1, str2, &listOfSets);
        break;
      case SHOW_LIST :
        showList(listOfSets);
        break;
      case SHOW_SET :
        showSet(str1, listOfSets);
        break;
      case HELP :
        help();
        break;
      case END :
        end = 1;
        break;
      default :
        printf("ERROR: wrong command\n");
    }
    if (str1 != NULL)
    {
      free(str1);
      str1 = NULL;
    }
    if (str2 != NULL)
    {
      free(str2);
      str2 = NULL;
    }
  } while (end == 0);
  freeListOfSets(listOfSets);
  listOfSets = NULL;
  return 0;
}

void getCommand(char command[MAX_COMMAND_LENGTH])
{
  int i;
  for (i = 0; i < MAX_COMMAND_LENGTH - 1; i++)
  {
    command[i] = getc(stdin);
    if (command[i] == '\n')
    {
      command[i] = '\0';
      return;
    }
  }
  command[MAX_COMMAND_LENGTH - 1] = '\0';
  return;
}

int checkCommand(char *command, char **str1, char **str2)
{
  int i;
  int space;
  assert(command != NULL && str1 != NULL && str2 != NULL);
  i = 0;
  passSpace(command, &i);
  switch (command[i])
  {
    case 'a' :
      if (checkAddFunc(command, &i))
        return ERROR;
      if (passSpace(command, &i))
        return ERROR;
      if (readString(command, &i, str1))
        return ERROR;
      if (passSpace(command, &i))
        return ERROR;
      if (readString(command, &i, str2))
        return ERROR;
      passSpace(command, &i);
      if (command[i] == '\0')
        return ADD_ELEM;
      break;
    case 'c' :
      i++;
      switch (command[i])
      {
        case 'h' :
          if (checkCheckFunc(command, &i))
            return ERROR;
          if (passSpace(command, &i))
            return ERROR;
          if (readString(command, &i, str1))
            return ERROR;
          if (passSpace(command, &i))
            return ERROR;
          if (readString(command, &i, str2))
            return ERROR;
          if (command[i] == '\0')
            return CHECK_ELEM;
          break;
        case 'r' :
          if (checkCreateFunc(command, &i))
            return ERROR;
          if (passSpace(command, &i))
            return ERROR;
          if (readString(command, &i, str1))
            return ERROR;
          passSpace(command, &i);
          if (command[i] == '\0')
            return CREATE_SET;
          break;
      }
      break;
    case 'd' :
      i++;
      switch (command[i])
      {
        case 'e' :
          if (checkDeleteFunc(command, &i))
            return ERROR;
          if (passSpace(command, &i))
            return ERROR;
          if (readString(command, &i, str1))
            return ERROR;
          space = passSpace(command, &i);
          if (command[i] == '\0')
            return DELETE_SET;
          if (!space)
          {
            if (readString(command, &i, str2))
              return ERROR;
            passSpace(command, &i);
            if (command[i] == '\0')
              return DELETE_ELEM;
          }
          break;
        case 'i' :
          if (checkDifferenceFunc(command, &i))
            return ERROR;
          if (passSpace(command, &i))
            return ERROR;
          if (readString(command, &i, str1))
            return ERROR;
          if (passSpace(command, &i))
            return ERROR;
          if (readString(command, &i, str2))
            return ERROR;
          passSpace(command, &i);
          if (command[i] == '\0')
            return DIFFERENCE_SET;
          break;
      }
      break;
    case 'e' :
      if (checkEndFunc(command, &i))
        return ERROR;
      passSpace(command, &i);
      if (command[i] == '\0')
        return END;
      break;
    case 'h' :
      if (checkHelpFunc(command, &i))
        return ERROR;
      passSpace(command, &i);
      if (command[i] == '\0')
        return HELP;
      break;
    case 'i' :
      i++;
      if (command[i] == 'n')
      {
        i++;
        switch (command[i])
        {
          case 'c' :
            if (checkInclusionFunc(command, &i))
              return ERROR;
            if (passSpace(command, &i))
              return ERROR;
            if (readString(command, &i, str1))
              return ERROR;
            if (passSpace(command, &i))
              return ERROR;
            if (readString(command, &i, str2))
              return ERROR;
            passSpace(command, &i);
            if (command[i] == '\0')
              return CHECK_INCLUSION;
            break;
          case 't' :
            if (checkIntersectionFunc(command, &i))
              return ERROR;
            if (passSpace(command, &i))
              return ERROR;
            if (readString(command, &i, str1))
              return ERROR;
            if (passSpace(command, &i))
              return ERROR;
            if (readString(command, &i, str2))
              return ERROR;
            passSpace(command, &i);
            if (command[i] == '\0')
              return INTERSECTION_SET;
            break;
        }
      }
      break;
    case 'p' :
      if (checkPowerFunc(command, &i))
        return ERROR;
      if (passSpace(command, &i))
        return ERROR;
      if (readString(command, &i, str1))
        return ERROR;
      passSpace(command, &i);
      if (command[i] == '\0')
        return POWER_SET;
      break;
    case 's' :
      i++;
      switch (command[i])
      {
        case 'h' :
          if (checkShowFunc(command, &i))
            return ERROR;
          space = passSpace(command, &i);
          if (command[i] == '\0')
            return SHOW_LIST;
          if (!space)
          {
            if (readString(command, &i, str1))
              return ERROR;
            passSpace(command, &i);
            if (command[i] == '\0')
              return SHOW_SET;
          }
          break;
        case 'y' :
          if (checkSymmetricFunc(command, &i))
            return ERROR;
          if (passSpace(command, &i))
            return ERROR;
          if (readString(command, &i, str1))
            return ERROR;
          if (passSpace(command, &i))
            return ERROR;
          if (readString(command, &i, str2))
            return ERROR;
          if (command[i] == '\0')
            return SYMMETRIC_DIFFERENCE_SET;
          break;
      }
      break;
    case 'u' :
      if (checkUnificationFunc(command, &i))
        return ERROR;
      if (passSpace(command, &i))
        return ERROR;
      if (readString(command, &i, str1))
        return ERROR;
      if (passSpace(command, &i))
        return ERROR;
      if (readString(command, &i, str2))
        return ERROR;
      if (command[i] == '\0')
        return UNIFICATION_SET;
      break;
  }
  return ERROR;
}

int checkAddFunc(char *command, int *i)
{
  assert(command != NULL && i != NULL && *i >= 0);
  if (command[*i + 1] == 'd' && command[*i + 2] == 'd')
  {
    (*i) += 3;
    return 0;
  }
  return 1;
}

int checkCheckFunc(char *command, int *i)
{
  assert(command != NULL && i != NULL && *i >= 0);
  if (command[*i + 1] == 'e' && command[*i + 2] == 'c' && command[*i + 3] == 'k')
  {
    (*i) += 4;
    return 0;
  }
  return 1;
}

int checkCreateFunc(char *command, int *i)
{
  assert(command != NULL && i != NULL && *i >= 0);
  if (command[*i + 1] == 'e' && command[*i + 2] == 'a' && command[*i + 3] == 't' && 
      command[*i + 4] == 'e')
  {
    (*i) += 5;
    return 0;
  }
  return 1;
}

int checkDeleteFunc(char *command, int *i)
{
  assert(command != NULL && i != NULL && *i >= 0);
  if (command[*i + 1] == 'l' && command[*i + 2] == 'e' && command[*i + 3] == 't' && 
      command[*i + 4] == 'e')
  {
    (*i) += 5;
    return 0;
  }
  return 1;
}

int checkDifferenceFunc(char *command, int *i)
{
  assert(command != NULL && i != NULL && *i >= 0);
  if (command[*i + 1] == 'f' && command[*i + 2] == 'f' && command[*i + 3] == 'e' && 
      command[*i + 4] == 'r' && command[*i + 5] == 'e' && command[*i + 6] == 'n' && 
      command[*i + 7] == 'c' && command[*i + 8] == 'e')
  {
    (*i) += 9;
    return 0;
  }
  return 1;
}

int checkEndFunc(char *command, int *i)
{
  assert(command != NULL && i != NULL && *i >= 0);
  if (command[*i + 1] == 'n' && command[*i + 2] == 'd')
  {
    (*i) += 3;
    return 0;
  }
  return 1;
}

int checkHelpFunc(char *command, int *i)
{
  assert(command != NULL && i != NULL && *i >= 0);
  if (command[*i + 1] == 'e' && command[*i + 2] == 'l' && command[*i + 3] == 'p')
  {
    (*i) += 4;
    return 0;
  }
  return 1;
}

int checkInclusionFunc(char *command, int *i)
{
  assert(command != NULL && i != NULL && *i >= 0);
  if (command[*i + 1] == 'l' && command[*i + 2] == 'u' && command[*i + 3] == 's' && 
      command[*i + 4] == 'i' && command[*i + 5] == 'o' && command[*i + 6] == 'n')
  {
    (*i) += 7;
    return 0;
  }
  return 1;
}

int checkIntersectionFunc(char *command, int *i)
{
  assert(command != NULL && i != NULL && *i >= 0);
  if (command[*i + 1] == 'e' && command[*i + 2] == 'r' && command[*i + 3] == 's' && 
      command[*i + 4] == 'e' && command[*i + 5] == 'c' && command[*i + 6] == 't' && 
      command[*i + 7] == 'i' && command[*i + 8] == 'o' && command[*i + 9] == 'n')
  {
    (*i) += 10;
    return 0;
  }
  return 1;
}

int checkPowerFunc(char *command, int *i)
{
  assert(command != NULL && i != NULL && *i >= 0);
  if (command[*i + 1] == 'o' && command[*i + 2] == 'w' && command[*i + 3] == 'e' && 
      command[*i + 4] == 'r')
  {
    (*i) += 5;
    return 0;
  }
  return 1;
}

int checkShowFunc(char *command, int *i)
{
  assert(command != NULL && i != NULL && *i >= 0);
  if (command[*i + 1] == 'o' && command[*i + 2] == 'w')
  {
    (*i) += 3;
    return 0;
  }
  return 1;
}

int checkSymmetricFunc(char *command, int *i)
{
  assert(command != NULL && i != NULL && *i >= 0);
  if (command[*i + 1] == 'm' && command[*i + 2] == 'm' && command[*i + 3] == 'e' && 
      command[*i + 4] == 't' && command[*i + 5] == 'r' && command[*i + 6] == 'i' && 
      command[*i + 7] == 'c')
  {
    (*i) += 8;
    return 0;
  }
  return 1;
}

int checkUnificationFunc(char *command, int *i)
{
  assert(command != NULL && i != NULL && *i >= 0);
  if (command[*i + 1] == 'n' && command[*i + 2] == 'i' && command[*i + 3] == 'f' && 
      command[*i + 4] == 'i' && command[*i + 5] == 'c' && command[*i + 6] == 'a' && 
      command[*i + 7] == 't' && command[*i + 8] == 'i' && command[*i + 9] == 'o' && 
      command[*i + 10] == 'n')
  {
    (*i) += 11;
    return 0;
  }
  return 1;
}

int readString(char *command, int *i, char **str)
{
  int strLength, j, space;
  assert(command != NULL && i != NULL);
  strLength = 0;
  /* Если строка заключена в двойные кавычки, в ней допустимы пробелы*/
  if (command[*i] == '"')
  {
    space = 1;
    (*i)++;
    /* Увеличиваем длину строки, пока не встретили символ двойных кавычек */
    while (command[*i + strLength] != '"')
    {
      /* Если встретили недопустимый символ, команда неверна */
      if (checkSymbol(command[*i + strLength]))
        return 1;
      strLength++;
    }
  }
  /* Если же нет, то пробелы не допустимы */
  else
  {
    space = 0;
    /* Увеличиваем длину строки, пока не встретили пробельный символ */
    while (!isspace(command[*i + strLength]))
    {
      /* Если встретили символ конца строки, больше считывать нечего */
      if (command[*i + strLength] == '\0')
        break;
      /* Если встретили недопустимый символ, команда неверна */
      if (checkSymbol(command[*i + strLength]))
        return 1;
      strLength++;
    }
  }
  if (strLength == 0)
  {
    printf("ERROR: empty name of set or element\n");
    return 1;
  }
  *str = calloc(strLength + 1, sizeof(char));
  if (checkPointer(*str))
    return 1;
  for (j = 0; j < strLength; j++)
    (*str)[j] = command[*i + j];
  (*str)[strLength] = '\0';
  (*i) += strLength;
  if (space == 1)
    (*i)++;
  return 0;
}

int passSpace(char *command, int *i)
{
  int j;
  assert(command != NULL && i != NULL && *i >= 0);
  j = *i;
  while (isspace(command[*i]))
    (*i)++;
  if (*i == j)
    return 1;
  return 0;
}