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

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <assert.h>
#include "expression.h"
#include "error.h"

#define OK 0
#define MISTAKE 1
#define E 2.71828182845904523536028747135266
#define PI 3.141592653589793238462643383279

int checkOperand(char c);
//function that returns "OK" if the symbol is an operand and "MISTAKE" if the symbol is an operator
int strOperator(char c, double *stack, int *meterStack, int *mistake);
//function that treats operators
void strOperand(char const *polishStr, int *meterPolishStr, double *stack, int *meterStack, 
    int *mistake, int const l);
//function that treats operands

double calcExpression(char const *polishStr, int const l, int *mistake)
{
  double *stack;
  //auxiliary string of values
  //char *operand;
  //string of an operand
  double result;
  //result of expression
  int meterPolishStr = 0, meterStack = 0;//, meterOperand = 0;
  assert(polishStr != NULL);
  assert(mistake != NULL);
  assert(l >= 0);
  stack = malloc((l + 1) * sizeof(double));
  if (stack == NULL)
  {
    if ((*mistake) == OK)
      (*mistake) = NOT_ENOUGH_DYNAMIC_MEMORY;
    assert(polishStr != NULL);
    assert(mistake != NULL);
    assert(l >= 0);
    return MISTAKE;
  }
  while (meterPolishStr < l)
  {
    assert(meterPolishStr < l);
    if (checkOperand(polishStr[meterPolishStr]) == OK)
      strOperand(polishStr, &meterPolishStr, stack, &meterStack, mistake, l);
    else
    {
      if (strOperator(polishStr[meterPolishStr], stack, &meterStack, mistake) == MISTAKE)
      {
        free(stack);
        assert(polishStr != NULL);
        assert(mistake != NULL);
        assert(l >= 0);
        return MISTAKE;
      }
      meterPolishStr++;
    }
  }
  result = stack[meterStack - 1];
  free(stack);
  assert(polishStr != NULL);
  assert(mistake != NULL);
  assert(l >= 0);
  return result;
}

void strOperand(char const *polishStr, int *meterPolishStr, double *stack, int *meterStack, 
    int *mistake, int const l)
{
  char *operand;
  //string of an operand
  int meterOperand = 0;
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert((*meterPolishStr) >= 0);
  assert(stack != NULL);
  assert(meterStack != NULL);
  assert((*meterStack) >= 0);
  assert(mistake != NULL);
  assert(l >= 0);
  operand = malloc(l * sizeof(char));
  if (operand == NULL)
  {
    if ((*mistake) == OK)
      (*mistake) = NOT_ENOUGH_DYNAMIC_MEMORY;
  }
  else
  {
    while(checkOperand(polishStr[*meterPolishStr]) == OK)
    {
      assert(meterOperand >= 0);
      operand[meterOperand] = polishStr[*meterPolishStr];
      (*meterPolishStr)++;
      meterOperand++;
    }
    if (operand[0] == 'p')
    {
      stack[*meterStack] = PI;
      (*meterStack)++;
    }
    if (operand[0] == 'e')
    {
      stack[*meterStack] = E;
      (*meterStack)++;
    }
    if ((operand[0] != 'p') && (operand[0] != 'e'))
    {
      stack[*meterStack] = atof(operand);
      (*meterStack)++;
    }
    free(operand);
  }
  assert(polishStr != NULL);
  assert(meterPolishStr != NULL);
  assert((*meterPolishStr) >= 0);
  assert(stack != NULL);
  assert(meterStack != NULL);
  assert((*meterStack) >= 0);
  assert(mistake != NULL);
  assert(l >= 0);
  return;
}

int strOperator(char c, double *stack, int *meterStack, int *mistake)
{
  assert(stack != NULL);
  assert(meterStack != NULL);
  assert((*meterStack) >= 0);
  switch (c)
  {
  case '+':
    stack[*meterStack - 2] = stack[*meterStack - 2] + stack[*meterStack - 1];
    (*meterStack)--;
    break;
  case '-':
    stack[*meterStack - 2] = stack[*meterStack - 2] - stack[*meterStack - 1];
    (*meterStack)--;
    break;
  case '*':
    stack[*meterStack - 2] = stack[*meterStack - 2] * stack[*meterStack - 1];
    (*meterStack)--;
    break;
  case '/':
    if (stack[*meterStack - 1] == 0)
    {
      if ((*mistake) == OK)
        (*mistake) = DIVISION_BY_ZERO;
      assert(stack != NULL);
      assert(meterStack != NULL);
      assert((*meterStack) >= 0);
      return MISTAKE;
    }
    stack[*meterStack - 2] = stack[*meterStack - 2] / stack[*meterStack - 1];
    (*meterStack)--;
    break;
  case '^':
    stack[*meterStack - 2] = pow(stack[*meterStack - 2], stack[*meterStack - 1]);
    (*meterStack)--;
    break;
  case 'a':
    if (stack[*meterStack - 1] < 0)
    {
      if ((*mistake) == OK)
        (*mistake) = SQRT_BY_NEGATIVE_NUMBER;
      assert(stack != NULL);
      assert(meterStack != NULL);
      assert((*meterStack) >= 0);
      return MISTAKE;
    }
    stack[*meterStack - 1] = sqrt(stack[*meterStack - 1]);
    break;
  case 'b':
    stack[*meterStack - 1] = sin(stack[*meterStack - 1]);
    break;
  case 'd':
    if ((int)(stack[*meterStack - 1] / PI * 2) == (stack[*meterStack - 1] / PI * 2))
      if ((int)(stack[*meterStack - 1] / PI) != (stack[*meterStack - 1] / PI))
      {
        if ((*mistake) == OK)
          (*mistake) = THE_VALUE_IS_INFINITY;
        assert(stack != NULL);
        assert(meterStack != NULL);
        assert((*meterStack) >= 0);
        return MISTAKE;
      }
    if ((stack[*meterStack - 1] == (3 * PI / 2)) || (stack[*meterStack - 1] == ((-3) * PI / 2)))
    {
      if ((*mistake) == OK)
        (*mistake) = THE_VALUE_IS_INFINITY;
      assert(stack != NULL);
      assert(meterStack != NULL);
      assert((*meterStack) >= 0);
      return MISTAKE;
    }
    stack[*meterStack - 1] = tan(stack[*meterStack - 1]);
    break;
  case 'm':
    stack[*meterStack - 1] = floor(stack[*meterStack - 1]);
    break;
  case 'l':
    if (stack[*meterStack - 1] <= 0)
    {
      if ((*mistake) == OK)
        (*mistake) = LN_BY_NEGATIVE_NUMBER;
      assert(stack != NULL);
      assert(meterStack != NULL);
      assert((*meterStack) >= 0);
      return MISTAKE;
    }
    stack[*meterStack - 1] = log(stack[*meterStack - 1]);
    break;
  case 'c':
    stack[*meterStack - 1] = cos(stack[*meterStack - 1]);
    break;
  case 'f':
    if ((int)(stack[*meterStack - 1] / PI) == (stack[*meterStack - 1] / PI))
    {
      if ((*mistake) == OK)
        (*mistake) = DIVISION_BY_ZERO;
      assert(stack != NULL);
      assert(meterStack != NULL);
      assert((*meterStack) >= 0);
      return MISTAKE;
    }
    stack[*meterStack - 1] = cos(stack[*meterStack - 1])/sin(stack[*meterStack - 1]);
    break;
  case 'n':
    stack[*meterStack - 1] = ceil(stack[*meterStack - 1]);
    break;
  case 'g':
    if ((stack[*meterStack - 1] < -1) || (stack[*meterStack - 1] > 1))
    {
      if ((*mistake) == OK)
        (*mistake) = INADMISSIBLE_ARGUMENT_FOR_ARCSIN;
      assert(stack != NULL);
      assert(meterStack != NULL);
      assert((*meterStack) >= 0);
      return MISTAKE;
    }
    stack[*meterStack - 1] = asin(stack[*meterStack - 1]);
    break;
  case 'h':
    if ((stack[*meterStack - 1] < -1) || (stack[*meterStack - 1] > 1))
    {
      if ((*mistake) == OK)
        (*mistake) = INADMISSIBLE_ARGUMENT_FOR_ARCCOS;
      assert(stack != NULL);
      assert(meterStack != NULL);
      assert((*meterStack) >= 0);
      return MISTAKE;
    }
    stack[*meterStack - 1] = acos(stack[*meterStack - 1]);
    break;
  case 'j':
    stack[*meterStack - 1] = atan(stack[*meterStack - 1]);
    break;
  }
  assert(stack != NULL);
  assert(meterStack != NULL);
  assert((*meterStack) >= 0);
  return OK;
}

int checkOperand(char c)
{
  if ((c == '0') || (c == '1') || (c == '2') || (c == '3') || (c == '4') || (c == '5') || 
      (c == '6') || (c == '7') || (c == '8') || (c == '9') || (c == 'p') || (c == 'e') || 
      (c == '.'))
    return OK;
  return MISTAKE;
}