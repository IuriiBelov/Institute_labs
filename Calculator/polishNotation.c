/*
a == sqrt
b == sin
c == cos
d == tg
f == ctg
g == arcsin
h == arccos
j == arctg
l == ln
m == floor
n == ceil
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <assert.h>
#include "polishNotation.h"
#include "error.h"

#define OK 0
#define MISTAKE 1
#define OKE 10
#define OKPI 20

int number(char const c);
//function that checks if the symbol is a number
int constant(char const *str, int meterStr);
//function that checks if the symbol is a constant
int function(char const *str, int meterStr);
//function that checks if the symbol is a function
int functionSymbol(char const *str, int meterStr);
//function that checks if the symbol means function
void polishStrNumber(char const *str, char *polishStr, int *meterStr, int *meterPolishStr);
//function that treats numbers
void polishStrConstantPI(char const *str, char *polishStr, int *meterStr, int *meterPolishStr);
//function that treats constant "E"
void polishStrConstantE(char const *str, char *polishStr, int *meterStr, int *meterPolishStr);
//function that treats constant "PI"
void stackPlusMinus(char *stack, char *polishStr, int *meterStack, int *meterPolishStr);
//function that treats "+" and "-" operators
void stackMultiplyDivide(char *stack, char *polishStr, int *meterStack, int *meterPolishStr);
//function that treats "*" and "/" operators
void stackExponentiation(char *stack, char *polishStr, int *meterStack, int *meterPolishStr);
//function that treats "^" operator
void stackCloseBracket(char *stack, char *polishStr, int *meterStack, int *meterPolishStr);
//function that treats close bracket
void stackFunction(char *stack, char *polishStr, int *meterStack, int *meterPolishStr);
//function that treats functions

int rewritePolishNotation(char const *str, char *polishStr, int const l, int *mistake)
{
  int meterStr = 0, meterPolishStr = 0, meterStack = 0;
  int operand = 0;
  //auxiliary variable that has "1" value if str[meterStr] is an operand and "0" if not
  char *stack;
  //auxiliary string of operators
  assert(str != NULL);
  assert(polishStr != NULL);
  assert(l >= 0);
  stack = malloc(l * sizeof(char));
  if (stack == NULL)
  {
    if((*mistake) == OK)
      (*mistake) = NOT_ENOUGH_DYNAMIC_MEMORY;
    assert(str != NULL);
    assert(polishStr != NULL);
    assert(l >= 0);
    return MISTAKE;
  }
  while (meterStr < l)
  {
    assert(meterStr < l);
    if (isspace(str[meterStr]))
      meterStr++;
    else
    {
      operand = 0;
      if (number(str[meterStr]) == OK)
      {
        polishStrNumber(str, polishStr, &meterStr, &meterPolishStr);
        operand = 1;
      }
      switch (constant(str, meterStr))
      {
      case OKPI:
        polishStrConstantPI(str, polishStr, &meterStr, &meterPolishStr);
        operand = 1;
        break;
      case OKE:
        polishStrConstantE(str, polishStr, &meterStr, &meterPolishStr);
        operand = 1;
        break;
      }
      if (operand == 0)
      {
        if (functionSymbol(str, meterStr) == OK)
        {
          stackFunction(stack, polishStr, &meterStack, &meterPolishStr);
          stack[meterStack] = str[meterStr];
          meterStr++;
        }
        else
          switch (str[meterStr])
          {
          case '+':
            if ((meterStr == 1) || ((str[meterStr - 1] != 'e') || (number(str[meterStr - 2]) != 
                OK)))
            {
              stackPlusMinus(stack, polishStr, &meterStack, &meterPolishStr);
              stack[meterStack] = '+';
            }
            meterStr++;
            break;
          case '-':
            if ((meterStr == 1) || ((str[meterStr - 1] != 'e') || (number(str[meterStr - 2]) != 
                OK)))
            {
              stackPlusMinus(stack, polishStr, &meterStack, &meterPolishStr);
              stack[meterStack] = '-';
            }
            meterStr++;
            break;
          case '*':
            stackMultiplyDivide(stack, polishStr, &meterStack, &meterPolishStr);
            stack[meterStack] = '*';
            meterStr++;
            break;
          case '/':
            stackMultiplyDivide(stack, polishStr, &meterStack, &meterPolishStr);
            stack[meterStack] = '/';
            meterStr++;
            break;
          case '^':
            stackExponentiation(stack, polishStr, &meterStack, &meterPolishStr);
            stack[meterStack] = '^';
            meterStr++;
            break;
          case '(':
            meterStack++;
            stack[meterStack] = '(';
            meterStr++;
           break;
         case ')':
            stackCloseBracket(stack, polishStr, &meterStack, &meterPolishStr);
            meterStr++;
            break;
          }
      }
    }
  }
  while (meterStack > 0)
  {
    polishStr[meterPolishStr] = stack[meterStack];
    meterPolishStr++;
    polishStr[meterPolishStr] = ' ';
    meterPolishStr++;
    meterStack--;
  }
  polishStr[meterPolishStr] = '\n';
  free(stack);
  assert(str != NULL);
  assert(polishStr != NULL);
  assert(l >= 0);
  return OK;
}

void polishStrNumber(char const *str, char *polishStr, int *meterStr, int *meterPolishStr)
{
  assert(str != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStr != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStr) >= 0);
  polishStr[*meterPolishStr] = str[*meterStr];
  (*meterStr)++;
  (*meterPolishStr)++;
  if (number(str[*meterStr]) != OK)
  {
    polishStr[*meterPolishStr] = ' ';
    (*meterPolishStr)++;
  }
  assert(str != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStr != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStr) >= 0);
  return;
}

void polishStrConstantPI(char const *str, char *polishStr, int *meterStr, int *meterPolishStr)
{
  assert(str != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStr != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStr) >= 0);
  polishStr[*meterPolishStr] = str[*meterStr];
  (*meterStr)++;
  (*meterPolishStr)++;
  polishStr[*meterPolishStr] = str[*meterStr];
  (*meterStr)++;
  (*meterPolishStr)++;
  polishStr[*meterPolishStr] = ' ';
  (*meterPolishStr)++;
  assert(str != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStr != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStr) >= 0);
  return;
}

void polishStrConstantE(char const *str, char *polishStr, int *meterStr, int *meterPolishStr)
{
  assert(str != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStr != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStr) >= 0);
  polishStr[*meterPolishStr] = str[*meterStr];
  (*meterStr)++;
  (*meterPolishStr)++;
  polishStr[*meterPolishStr] = ' ';
  (*meterPolishStr)++;
  assert(str != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStr != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStr) >= 0);
  return;
}

int previousSymbol(char c)
{
  if ((c == '^') || (c == '*') || (c == '/') || (c == '+') || (c == '-'))
    return MISTAKE;
  return OK;
}

void stackPlusMinus(char *stack, char *polishStr, int *meterStack, int *meterPolishStr)
{
  assert(stack != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStack != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStack) >= 0);
  while ((stack[*meterStack] == '^') || (stack[*meterStack] == '*') || 
      (stack[*meterStack] == '/') || (stack[*meterStack] == '+') || 
      (stack[*meterStack] == '-') || (functionSymbol(stack, *meterStack) == OK))
    {
      polishStr[*meterPolishStr] = stack[*meterStack];
      (*meterPolishStr)++;
      polishStr[*meterPolishStr] = ' ';
      (*meterPolishStr)++;
      (*meterStack)--;
    }
  (*meterStack)++;
  assert(stack != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStack != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStack) >= 0);
  return;
}

void stackMultiplyDivide(char *stack, char *polishStr, int *meterStack, int *meterPolishStr)
{
  assert(stack != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStack != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStack) >= 0);
  while ((stack[*meterStack] == '^') || (stack[*meterStack] == '*') || 
      (stack[*meterStack] == '/') || (functionSymbol(stack, *meterStack) == OK))
  {
    polishStr[*meterPolishStr] = stack[*meterStack];
    (*meterPolishStr)++;
    polishStr[*meterPolishStr] = ' ';
    (*meterPolishStr)++;
    (*meterStack)--;
  }
  (*meterStack)++;
  assert(stack != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStack != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStack) >= 0);
  return;
}

void stackExponentiation(char *stack, char *polishStr, int *meterStack, int *meterPolishStr)
{
  assert(stack != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStack != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStack) >= 0);
  while (((stack[*meterStack] == '(') && ((*meterStack) >= 0)) || (functionSymbol(stack, 
      *meterStack) == OK))
  {
    if (stack[*meterStack] == '(')
    {
      (*meterStack)++;
      assert(stack != NULL);
      assert(polishStr != NULL);
      assert(meterPolishStr != NULL);
      assert(meterStack != NULL);
      assert((*meterPolishStr) >= 0);
      assert((*meterStack) >= 0);
      return;
    }
    polishStr[*meterPolishStr] = stack[*meterStack];
    (*meterPolishStr)++;
    polishStr[*meterPolishStr] = ' ';
    (*meterPolishStr)++;
    (*meterStack)--;
  }
  (*meterStack)++;
  assert(stack != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStack != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStack) >= 0);
  return;
}

void stackCloseBracket(char *stack, char *polishStr, int *meterStack, int *meterPolishStr)
{
  assert(stack != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStack != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStack) >= 0);
  while (stack[*meterStack] != '(')
  {
    polishStr[*meterPolishStr] = stack[*meterStack];
    (*meterPolishStr)++;
    polishStr[*meterPolishStr] = ' ';
    (*meterPolishStr)++;
    (*meterStack)--;
  }
  (*meterStack)--;
  assert(stack != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStack != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStack) >= 0);
  return;
}

void stackFunction(char *stack, char *polishStr, int *meterStack, int *meterPolishStr)
{
  assert(stack != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStack != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStack) >= 0);
  while (functionSymbol(stack, *meterStack) == OK)
  {
    polishStr[*meterPolishStr] = stack[*meterStack];
    (*meterPolishStr)++;
    polishStr[*meterPolishStr] = ' ';
    (*meterPolishStr)++;
    (*meterStack)--;
  }
  (*meterStack)++;
  assert(stack != NULL);
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert(meterStack != NULL);
  assert((*meterPolishStr) >= 0);
  assert((*meterStack) >= 0);
  return;
}

int number(char const c)
{
  char numbers[12] = "0123456789.";
  int i;
  for (i = 0; i < 11; i++)
    if (c == numbers[i])
      return OK;
  return MISTAKE;
}

int constant(char const *str, int meterStr)
{
  assert(str != NULL);
  assert(meterStr >= 0);
  if (str[meterStr] == 'e')
  {
    assert(str != NULL);
    assert(meterStr >= 0);
    return OKE;
  }
  if ((str[meterStr] == 'p') && (str[meterStr + 1] == 'i'))
  {
    assert(str != NULL);
    assert(meterStr >= 0);
    return OKPI;
  }
  assert(str != NULL);
  assert(meterStr >= 0);
  return MISTAKE;
}

int functionSymbol(char const *str, int meterStr)
{
  assert(str != NULL);
  assert(meterStr >= 0);
  if ((str[meterStr] == 'a') || (str[meterStr] == 'b') || (str[meterStr] == 'c') || 
      (str[meterStr] == 'd') || (str[meterStr] == 'f') || (str[meterStr] == 'g') || 
      (str[meterStr] == 'h') || (str[meterStr] == 'j') || (str[meterStr] == 'n') || 
      (str[meterStr] == 'l') || (str[meterStr] == 'm'))
  {
    assert(str != NULL);
    assert(meterStr >= 0);
    return OK;
  }
  assert(str != NULL);
  assert(meterStr >= 0);
  return MISTAKE;
}