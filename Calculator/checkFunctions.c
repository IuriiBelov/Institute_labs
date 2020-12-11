#include <stdio.h>
#include <assert.h>
#include "checkFunctions.h"
#include "error.h"

#define OK 0
#define MISTAKE 1
#define ADMISSIBLE_PREVIOUS_SYMBOLS 7

int checkFunctionsS(char const *str, int const l, int *mistake);
//function that checks functions begins on "s"
int checkFunctionsF(char const *str, int const l, int *mistake);
//function that checks functions begins on "f"
int checkFunctionsT(char const *str, int const l, int *mistake);
//function that checks functions begins on "t"
int checkFunctionsL(char const *str, int const l, int *mistake);
//function that checks functions begins on "l"
int checkFunctionsC(char const *str, int const l, int *mistake);
//function that checks functions begins on "c"
int checkFunctionsA(char const *str, int const l, int *mistake);
//function that checks functions begins on "a"
int previousFunctionSymbol(char const c);
//function that returns OK if previous symbol is admissible and MISTAKE if not
int nextFunctionSymbol(char const c);
//function that returns OK if next symbol is admissible and MISTAKE if not

int checkFunctions(char const *str, int const l, int *mistake)
{
  assert(str != NULL);
  assert(l >= 0);
  if (checkFunctionsS(str, l, mistake) == MISTAKE)
    return MISTAKE;
  assert(str != NULL);
  assert(l >= 0);
  if (checkFunctionsF(str, l, mistake) == MISTAKE)
    return MISTAKE;
  assert(str != NULL);
  assert(l >= 0);
  if (checkFunctionsT(str, l, mistake) == MISTAKE)
    return MISTAKE;
  assert(str != NULL);
  assert(l >= 0);
  if (checkFunctionsL(str, l, mistake) == MISTAKE)
    return MISTAKE;
  assert(str != NULL);
  assert(l >= 0);
  if (checkFunctionsC(str, l, mistake) == MISTAKE)
    return MISTAKE;
  assert(str != NULL);
  assert(l >= 0);
  if (checkFunctionsA(str, l, mistake) == MISTAKE)
    return MISTAKE;
  assert(str != NULL);
  assert(l >= 0);
  return OK;
}

int checkFunctionsS(char const *str, int const l, int *mistake)
{
  int meter;
  int wrongFunction = OK;
  //variable that has MISTAKE value if the function is wrong
  assert(str != NULL);
  assert(l >= 0);
  for (meter = 0; meter < l; meter++)
  {
    assert(meter >= 0);
    if ((str[meter] == 's') && ((meter == 0) || ((meter > 0) && (str[meter - 1] != 'o') && 
        (str[meter - 1] != 'c'))))
    {
      if ((meter > 0) && (previousFunctionSymbol(str[meter - 1]) == MISTAKE) && (str[meter - 
          1] != 'o'))
        wrongFunction = MISTAKE;
      meter++;
      assert(meter >= 0);
      if ((str[meter] != 'q') && (str[meter] != 'i'))
        wrongFunction = MISTAKE;
      assert(meter >= 0);
      if (str[meter] == 'q')
      {
        meter++;
        if (str[meter] != 'r')
          wrongFunction = MISTAKE;
        meter++;
        if (str[meter] != 't')
          wrongFunction = MISTAKE;
        meter++;
        if (nextFunctionSymbol(str[meter]) == MISTAKE)
          wrongFunction = MISTAKE;
        meter++;
      }
      assert(meter >= 0);
      if (str[meter] == 'i')
      {
        meter++;
        if (str[meter] != 'n')
          wrongFunction = MISTAKE;
        meter++;
        if (nextFunctionSymbol(str[meter]) == MISTAKE)
          wrongFunction = MISTAKE;
        meter++;
      }
      if (wrongFunction == MISTAKE)
      {
        if ((*mistake) == OK)
          (*mistake) = WRONG_FUNCTION;
        assert(str != NULL);
        assert(l >= 0);
        return MISTAKE;
      }
    }
  }
  assert(str != NULL);
  assert(l >= 0);
  return OK;
}

int checkFunctionsF(char const *str, int const l, int *mistake)
{
  int meter;
  int wrongFunction = OK;
  //variable that has MISTAKE value if the function is wrong
  assert(str != NULL);
  assert(l >= 0);
  for (meter = 0; meter < l; meter++)
  {
    assert(meter >= 0);
    if (str[meter] == 'f')
    {
      assert(meter >= 0);
      if ((meter > 0) && (previousFunctionSymbol(str[meter - 1]) == MISTAKE))
        wrongFunction = MISTAKE;
      meter++;
      assert(meter >= 0);
      if (str[meter] != 'l')
        wrongFunction = MISTAKE;
      meter++;
      assert(meter >= 0);
      if (str[meter] != 'o')
        wrongFunction = MISTAKE;
      meter++;
      assert(meter >= 0);
      if (str[meter] != 'o')
        wrongFunction = MISTAKE;
      meter++;
      assert(meter >= 0);
      if (str[meter] != 'r')
        wrongFunction = MISTAKE;
      meter++;
      assert(meter >= 0);
      if (nextFunctionSymbol(str[meter]) == MISTAKE)
        wrongFunction = MISTAKE;
      meter++;
      if (wrongFunction == MISTAKE)
      {
        if ((*mistake) == OK)
          (*mistake) = WRONG_FUNCTION;
        assert(str != NULL);
        assert(l >= 0);
        return MISTAKE;
      }
    }
  }
  assert(str != NULL);
  assert(l >= 0);
  return OK;
}

int checkFunctionsT(char const *str, int const l, int *mistake)
{
  int meter;
  int wrongFunction = OK;
  //variable that has MISTAKE value if the function is wrong
  assert(str != NULL);
  assert(l >= 0);
  for (meter = 0; meter < l; meter++)
  {
    assert(meter >= 0);
    if ((str[meter] == 't') && ((meter == 0) || ((meter > 0) && (str[meter - 1] != 'r') && 
        (str[meter - 1] != 'c'))))
    {
      assert(meter >= 0);
      if ((meter == 0) || (str[meter - 1] != 'r') || (str[meter - 1] != 'c'))
      {
        assert(meter >= 0);
        if ((meter > 0) && (previousFunctionSymbol(str[meter - 1]) == MISTAKE))
          wrongFunction = MISTAKE;
        meter++;
        if (str[meter] != 'g')
          wrongFunction = MISTAKE;
        meter++;
        if (nextFunctionSymbol(str[meter]) == MISTAKE)
          wrongFunction = MISTAKE;
        meter++;
      }
    }
    if (wrongFunction == MISTAKE)
    {
      if ((*mistake) == OK)
          (*mistake) = WRONG_FUNCTION;
      assert(str != NULL);
      assert(l >= 0);
      return MISTAKE;
    }
  }
  assert(str != NULL);
  assert(l >= 0);
  return OK;
}

int checkFunctionsL(char const *str, int const l, int *mistake)
{
  int meter;
  int wrongFunction = OK;
  //variable that has MISTAKE value if the function is wrong
  assert(str != NULL);
  assert(l >= 0);
  for (meter = 0; meter < l; meter++)
  {
    assert(meter >= 0);
    if ((str[meter] == 'l') && ((meter == 0) || ((meter > 0) && (str[meter - 1] != 'f') && 
        (str[meter - 1] != 'i'))))
    {
      if ((meter == 0) || (str[meter - 1] != 'f'))
      {
        assert(meter >= 0);
        if ((meter > 0) && (previousFunctionSymbol(str[meter - 1]) == MISTAKE))
          wrongFunction = MISTAKE;
        meter++;
        if (str[meter] != 'n')
          wrongFunction = MISTAKE;
        meter++;
        if (nextFunctionSymbol(str[meter]) == MISTAKE)
          wrongFunction = MISTAKE;
      }
      if (wrongFunction == MISTAKE)
      {
        if ((*mistake) == OK)
          (*mistake) = WRONG_FUNCTION;
        assert(str != NULL);
        assert(l >= 0);
        return MISTAKE;
      }
    }
  }
  assert(str != NULL);
  assert(l >= 0);
  return OK;
}

int checkFunctionsC(char const *str, int const l, int *mistake)
{
  int meter;
  int wrongFunction = OK;
  //variable that has MISTAKE value if the function is wrong
  assert(str != NULL);
  assert(l >= 0);
  for (meter = 0; meter < l; meter++)
  {
    assert(meter >= 0);
    if ((str[meter] == 'c') && ((meter == 0) || ((meter > 0) && (str[meter - 1] != 'r') && 
        (str[meter - 1] != 'c'))))
    {
      if ((meter > 0) && (previousFunctionSymbol(str[meter - 1]) == MISTAKE))
        wrongFunction = MISTAKE;
      meter++;
      assert(meter >= 0);
      if (str[meter] == 'o')
      {
        meter++;
        if (str[meter] != 's')
          wrongFunction = MISTAKE;
        meter++;
        if (nextFunctionSymbol(str[meter]) == MISTAKE)
          wrongFunction = MISTAKE;
      }
      assert(meter >= 0);
      if (str[meter] == 't')
      {
        meter++;
        if (str[meter] != 'g')
          wrongFunction = MISTAKE;
        meter++;
        if (nextFunctionSymbol(str[meter]) == MISTAKE)
          wrongFunction = MISTAKE;
      }
      assert(meter >= 0);
      if (str[meter] == 'e')
      {
        meter++;
        if (str[meter] != 'i')
          wrongFunction = MISTAKE;
        meter++;
        if (str[meter] != 'l')
          wrongFunction = MISTAKE;
        meter++;
        if (nextFunctionSymbol(str[meter]) == MISTAKE)
          wrongFunction = MISTAKE;
      }
      if (wrongFunction == MISTAKE)
      {
        if ((*mistake) == OK)
          (*mistake) = WRONG_FUNCTION;
        assert(str != NULL);
        assert(l >= 0);
        return MISTAKE;
      }
    }
  }
  assert(str != NULL);
  assert(l >= 0);
  return OK;
}

int checkFunctionsA(char const *str, int const l, int *mistake)
{
  int meter;
  int wrongFunction = OK;
  //variable that has MISTAKE value if the function is wrong
  assert(str != NULL);
  assert(l >= 0);
  for (meter = 0; meter < l; meter++)
  {
    assert(meter >= 0);
    if (str[meter] == 'a')
    {
      if ((meter > 0) && (previousFunctionSymbol(str[meter - 1]) == MISTAKE))
        wrongFunction = MISTAKE;
      meter++;
      assert(meter >= 0);
      if (str[meter] != 'r')
        wrongFunction = MISTAKE;
      meter++;
      assert(meter >= 0);
      if (str[meter] != 'c')
        wrongFunction = MISTAKE;
      meter++;
      assert(meter >= 0);
      if ((str[meter] != 's') && (str[meter] != 'c') && (str[meter] != 't'))
        wrongFunction = MISTAKE;
      if (str[meter] == 's')
      {
        meter++;
        assert(meter >= 0);
        if (str[meter] != 'i')
          wrongFunction = MISTAKE;
        meter++;
        assert(meter >= 0);
        if (str[meter] != 'n')
          wrongFunction = MISTAKE;
        meter++;
        assert(meter >= 0);
        if (nextFunctionSymbol(str[meter]) == MISTAKE)
          wrongFunction = MISTAKE;
      }
      assert(meter >= 0);
      if (str[meter] == 'c')
      {
        meter++;
        assert(meter >= 0);
        if (str[meter] != 'o')
          wrongFunction = MISTAKE;
        meter++;
        assert(meter >= 0);
        if (str[meter] != 's')
          wrongFunction = MISTAKE;
        meter++;
        assert(meter >= 0);
        if (nextFunctionSymbol(str[meter]) == MISTAKE)
          wrongFunction = MISTAKE;
      }
      assert(meter >= 0);
      if (str[meter] == 't')
      {
        meter++;
        assert(meter >= 0);
        if (str[meter] != 'g')
          wrongFunction = MISTAKE;
        meter++;
        assert(meter >= 0);
        if (nextFunctionSymbol(str[meter]) == MISTAKE)
          wrongFunction = MISTAKE;
      }
    }
    if (wrongFunction == MISTAKE)
    {
      if ((*mistake) == OK)
          (*mistake) = WRONG_FUNCTION;
      assert(str != NULL);
      assert(l >= 0);
      return MISTAKE;
    }
  }
  assert(str != NULL);
  assert(l >= 0);
  return OK;
}

int previousFunctionSymbol(char const c)
{
  char admissiblePreviousSymbols[ADMISSIBLE_PREVIOUS_SYMBOLS] = "+-*/^(";
  //string of admissible previous symbols
  int meter, counter = 0;
  for (meter = 0; meter < (ADMISSIBLE_PREVIOUS_SYMBOLS - 1); meter++)
  {
    assert(meter >= 0);
    if (c == admissiblePreviousSymbols[meter])
      counter++;
  }
  if (counter == 0)
    return MISTAKE;
  return OK;
}

int nextFunctionSymbol(char const c)
{
  if (c == '(')
    return OK;
  return MISTAKE;
}