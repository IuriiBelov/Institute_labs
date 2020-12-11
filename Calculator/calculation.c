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

#include <ctype.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <assert.h>
#include "calculation.h"
#include "check.h"
#include "checkFunctions.h"
#include "polishNotation.h"
#include "expression.h"
#include "length.h"
#include "error.h"

#define ENTER 10
#define MISTAKE 1
#define OK 0

double calculate(char const *str, int *mistake)
{
  char *polishStr;
  //string of expression in reverse polish notation
  double resultOfCalculation = 2;
  //rezult of the calculation
  int resultOfRewrite = 0;
  //result of rewriting the string of expression in reverse polish notation
  int l = 0;
  //length of the string
  while ((str[l] != ' ') && (str[l] != '\n') && (str[l] != '\0'))
    l++;
  assert(l >= 0);
  assert(str != NULL);
  polishStr = malloc((l + 1) * 16 * sizeof(char));
  if (polishStr == NULL)
  {
    if ((*mistake) == OK)
      (*mistake) = NOT_ENOUGH_DYNAMIC_MEMORY;
    free(polishStr);
    return MISTAKE;
  }
  assert(str != NULL);
  assert(polishStr != NULL);
  resultOfRewrite = rewritePolishNotation(str, polishStr, l, mistake);
  if (resultOfRewrite == MISTAKE)
  {
    free(polishStr);
    return MISTAKE;
  }
  assert(polishStr != NULL);
  l = length(polishStr);
  assert(l >= 0);
  resultOfCalculation = calcExpression(polishStr, l, mistake);
  free(polishStr);
  return resultOfCalculation;
}