#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "work.h"

#define MAX_COMMAND_LENGTH 23
#define MAX_NUMBER 10
#define ASCII_CODE 48

#define COMMAND_H 1
#define COMMAND_U 2
#define COMMAND_A 3
#define COMMAND_P 4
#define COMMAND_C 5
#define COMMAND_S 6
#define COMMAND_B 7
#define COMMAND_Q 8

#define ERROR 1

void countNumber2(unsigned long *res, unsigned long (*f)(unsigned long, unsigned long, int *), 
    unsigned long m, unsigned long n, int *error, char operation);
void countNumber1(unsigned long *res, unsigned long (*f)(unsigned long, int *), unsigned long n, 
    int *error, char operation);

int checkCommand(char *command, unsigned long *n, unsigned long *m);

int getNumbers(char *command, unsigned long *n, unsigned long *m);
int getNumber(char *command, unsigned long *n, int k);

int readNumber(char *command, char *str, int *i, int n);
int checkDiapasone(char *str);
void converse(char *str, unsigned long *n);
int checkNumber(char number);

int main(void)
{
  int end, error;
  unsigned long m, n, res;
  char command[MAX_COMMAND_LENGTH];
  end = 0;
  do
  {
    gets(command);
    error = 0;
    res = 0;
    switch (checkCommand(command, &m, &n))
    {
      case COMMAND_H :
        commandH();
        break;
      case COMMAND_U :
        countNumber2(&res, &commandU, m, n, &error, 'U');
        break;
      case COMMAND_A :
        countNumber2(&res, &commandA, m, n, &error, 'A');
        break;
      case COMMAND_P :
        countNumber1(&res, &commandP, m, &error, 'P');
        break;
      case COMMAND_C :
        countNumber2(&res, &commandC, m, n, &error, 'C');
        break;
      case COMMAND_S :
        countNumber2(&res, &commandS, m, n, &error, 'S');
        break;
      case COMMAND_B :
        countNumber1(&res, &commandB, m, &error, 'B');
        break;
      case COMMAND_Q :
        end = 1;
        break;
      default :
        break;
    }
  } while (end == 0);
  return 1;
}

void countNumber2(unsigned long *res, unsigned long (*f)(unsigned long, unsigned long, int *), 
    unsigned long m, unsigned long n, int *error, char operation)
{
  assert(res != NULL && f != NULL && error != NULL);
  *res = (*f)(m, n, error);
  if (*error != ERROR)
    printf("%c(%u,%u) = %u\n", operation, m, n, *res);
  return;
}

void countNumber1(unsigned long *res, unsigned long (*f)(unsigned long, int *), unsigned long n, 
    int *error, char operation)
{
  assert(res != NULL && f != NULL && error != NULL);
  *res = (*f)(n, error);
  if (*error != ERROR)
    printf("%c(%u) = %u\n", operation, n, *res);
  return;
}

int checkCommand(char *command, unsigned long *n, unsigned long *m)
{
  assert(command != NULL && n != NULL && m != NULL);
  switch (command[0])
  {
    case 'H' :
      if (command[1] == '\0')
        return COMMAND_H;
      break;
    case 'U' :
      if (command[1] == ' ')
        if (!getNumbers(command, n, m))
          return COMMAND_U;
      break;
    case 'A' :
      if (command[1] == ' ')
        if (!getNumbers(command, n, m))
          return COMMAND_A;
      break;
    case 'P' :
      if (command[1] == ' ')
        if (!getNumber(command, n, 2))
          return COMMAND_P;
      break;
    case 'C' :
      if (command[1] == ' ')
        if (!getNumbers(command, n, m))
          return COMMAND_C;
      break;
    case 'S' :
      if (command[1] == ' ')
        if (!getNumbers(command, n, m))
          return COMMAND_S;
      break;
    case 'B' :
      if (command[1] == ' ')
        if (!getNumber(command, n, 2))
          return COMMAND_B;
      break;
    case 'Q' :
      if (command[1] == '\0')
        return COMMAND_Q;
      break;
    default :
      printf("ERROR: wrong command\n");
      return 0;
  }
  printf("ERROR: wrong command\n");
  return 0;
}

int getNumbers(char *command, unsigned long *n, unsigned long *m)
{
  int k;
  assert(command != NULL && n != NULL && m != NULL);
  k = 2;
  if (getNumber(command, n, k))
    return 1;
  while (!checkNumber(command[k]))
    k++;
  if (getNumber(command, m, k + 1))
    return 1;
  return 0;
}

int getNumber(char *command, unsigned long *n, int k)
{
  int i;
  char number[MAX_NUMBER + 1];
  assert(command != NULL && n != NULL && k > 0);
  i = k;
  if (readNumber(command, number, &i, k))
    return 1;
  if (i == k)
  {
    printf("ERROR: wrong command\n");
    return 1;
  }
  if (checkDiapasone(number))
    return 1;
  converse(number, n);
  return 0;
}

int readNumber(char *command, char *str, int *i, int k)
{
  assert(command != NULL && str != NULL && i != NULL && k > 0);
  if (*i < k)
  {
    printf("ERROR: wrong command\n");
    return 1;
  }
  while (!checkNumber(command[*i]))
  {
    if (*i > k + MAX_NUMBER)
    {
      printf("ERROR: too big number\n");
      return 1;
    }
    str[*i - k] = command[*i];
    (*i)++;
  }
  str[*i - k] = '\0';
  return 0;
}

int checkDiapasone(char *str)
{
  int l;
  assert(str != NULL);
  l = strlen(str);
  if (l > MAX_NUMBER)
  {
    printf("ERROR: too big number\n");
    return 1;
  }
  if (l == MAX_NUMBER)
  {
    if (str[0] > '4')
    {
      printf("ERROR: too big number\n");
      return 1;
    }
    if (str[0] == '4')
      if (str[1] > '2' || str[2] > '9' || str[3] > '4' || str[4] > '9' || 
          str[5] > '6' || str[6] > '7' || str[7] > '2' || str[8] > '9' || 
          str[9] > '5')
        {
          printf("ERROR: too big number\n");
          return 1;
        }
  }
  return 0;
}

void converse(char *str, unsigned long *n)
{
  int i, j, l;
  unsigned long a, b;
  assert(str != NULL && n != NULL);
  l = strlen(str);
  if (l > MAX_NUMBER)
  {
    printf("ERROR: too big number\n");
    return;
  }
  *n = 0;
  for (i = 0; i < l; i++)
  {
    a = (unsigned long)(str[i] - ASCII_CODE);
    b = (unsigned long)pow(10, l - i - 1);
    for (j = 0; j < a; j++)
      (*n) += b;
  }
  return;
}

int checkNumber(char number)
{
  if (number >= ASCII_CODE && number <= ASCII_CODE + 9)
    return 0;
  return 1;
}