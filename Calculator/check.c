#include <stdio.h>
#include <assert.h>
#include "check.h"
#include "error.h"

#define OK 0
#define MISTAKE 1
#define ADMISSIBLE_SYMBOLS 36

int wrongSymbol(char const *str, int const l, int *mistake);
//function that checks if there is a wrong symbol in the string
int brackets(char const *str, int const l, int *mistake);
//function that checks the brackets
int constants(char const *str, int const l, int *mistake);
//function that checks the constants
int operators(char const *str, int const l, int *mistake);
//function that checks operators
int operands(char const *str, int const l, int *mistake);
//function that checks operands
int scienceNotation(char const *str, int const l, int *mistake);
//function that checks numbers in science notation
int numeral(char const c);
//function that returns "0" if the symbol is a numeral and "1" if not
int operand(char const c);
//function that returns "0" if the symbol is an operand and "1" if not
int firstFunctionSymbol (char const c);
//function that returns "0" if the symbol is a first symbol of function and "1" if not
int lastFunctionSymbol (char const c);
//function that returns "0" if the symbol is a last symbol of function and "1" if not

int check(char const *str, int const l, int *mistake)
{
  assert(str != NULL);
  assert(l >= 0);
  if (wrongSymbol(str, l, mistake) == MISTAKE)
    return MISTAKE;
  assert(str != NULL);
  assert(l >= 0);
  if (brackets(str, l, mistake) == MISTAKE)
    return MISTAKE;
  assert(str != NULL);
  assert(l >= 0);
  if (constants(str, l, mistake) == MISTAKE)
    return MISTAKE;
  assert(str != NULL);
  assert(l >= 0);
  if (operators(str, l, mistake) == MISTAKE)
    return MISTAKE;
  assert(str != NULL);
  assert(l >= 0);
  if (operands(str, l, mistake) == MISTAKE)
    return MISTAKE;
  assert(str != NULL);
  assert(l >= 0);
  if (scienceNotation(str, l, mistake) == MISTAKE)
    return MISTAKE;
  assert(str != NULL);
  assert(l >= 0);
  return OK;
}

int wrongSymbol(char const *str, int const l, int *mistake)
{
  char admissibleSymbols[ADMISSIBLE_SYMBOLS] = "0123456789+-*/^()pie. sqrtinfloagcE";
  int meterStr, meter;
  int counter;
  assert(str != NULL);
  assert(l >= 0);
  for (meterStr = 0; meterStr < l; meterStr++)
  {
    counter = 0;
    assert(ADMISSIBLE_SYMBOLS - 1 >= 0);
    for (meter = 0; meter < (ADMISSIBLE_SYMBOLS - 1); meter++)
      if (str[meterStr] != admissibleSymbols[meter])
        counter++;
    if (counter == (ADMISSIBLE_SYMBOLS - 1))
    {
      if ((*mistake) == OK)
        (*mistake) = INADMISSIBLE_SYMBOL_IN_THE_STRING;
      assert(str != NULL);
      assert(l >= 0);
      return MISTAKE;
    }
  }
  assert(str != NULL);
  assert(l >= 0);
  return OK;
}

int brackets(char const *str, int const l, int *mistake)
{
  int openBracket = 0, closeBracket = 0;
  //numbers of open and close brackets
  int wrongBracket = OK;
  //variable that has MISTAKE value if there is a wrong bracket in the string
  int meter;
  assert(str != NULL);
  assert(l >= 0);
  for (meter = 0; meter < l; meter++)
  {
    if (str[meter] == '(')
    {
      openBracket++;
      if (meter > 0)
      {
        assert(str != NULL);
        if ((operand(str[meter - 1]) == OK) && (lastFunctionSymbol(str[meter - 1]) == MISTAKE)
            && (str[meter - 1] != '('))
          wrongBracket = MISTAKE;
        if (str[meter - 1] == ')')
          wrongBracket = MISTAKE;
      }
      assert(l > 0);
      if (meter == (l - 1))
        wrongBracket = MISTAKE;
      if (meter < (l - 1))
      {
        assert(str != NULL);
        if ((operand(str[meter + 1]) == MISTAKE) && (str[meter + 1] != '-') && 
            (firstFunctionSymbol(str[meter + 1]) == MISTAKE))
          wrongBracket = MISTAKE;
        if (str[meter + 1] == ')')
          wrongBracket = MISTAKE;
      }
    }
    assert(str != NULL);
    assert(meter >= 0);
    if (str[meter] == ')')
    {
      closeBracket++;
      if (meter == 0)
        wrongBracket = MISTAKE;
      if (meter > 0)
      {
        if ((operand(str[meter - 1]) == MISTAKE) && (lastFunctionSymbol(str[meter - 1]) == 
            MISTAKE))
          wrongBracket = MISTAKE;
        if (str[meter - 1] == '(')
          wrongBracket = MISTAKE;
      }
      if (meter < (l - 1))
      {
        assert(str != NULL);
        if ((operand(str[meter + 1]) == OK) && (str[meter + 1] != ')') && (str[meter + 1] != 
            ' '))
          wrongBracket = MISTAKE;
        if (str[meter + 1] == '(')
          wrongBracket = MISTAKE;
      }
    }
    if (wrongBracket == MISTAKE)
    {
      if ((*mistake) == OK)
        (*mistake) = WRONG_BRACKET;
      assert(str != NULL);
      assert(l >= 0);
      return MISTAKE;
    }
  }
  if (openBracket != closeBracket)
  {
    if ((*mistake) == OK)
      (*mistake) = WRONG_BRACKET;
    assert(str != NULL);
    assert(l >= 0);
    return MISTAKE;
  }
  assert(str != NULL);
  assert(l >= 0);
  return OK;
}

int constants(char const *str, int const l, int *mistake)
{
  int meter;
  int wrongConstant = OK;
  //variable that has MISTAKE value if there is a wrong constant in the string
  assert(str != NULL);
  assert(l >= 0);
  for (meter = 0; meter < l; meter++)
  {
    assert(str != NULL);
    assert(meter >= 0);
    if (str[meter] == 'p')
    {
      if (meter == (l - 1))
        wrongConstant = MISTAKE;
      if (meter > 0)
      {
        if (str[meter - 1] == ')')
          wrongConstant = MISTAKE;
        if ((str[meter - 1] != '(') && (str[meter - 1] != ' ') && (operand(str[meter - 1]) 
            == OK))
          wrongConstant = MISTAKE;
      }
      if (str[meter + 1] != 'i')
        wrongConstant = MISTAKE;
      if (meter < (l - 2))
      {
        if ((str[meter + 2] != ')') && (str[meter + 2] != ' ') && (operand(str[meter + 2]) 
            == OK))
          wrongConstant = MISTAKE;
        if (str[meter + 2] == '(')
          wrongConstant = MISTAKE;
      }
    }
    if ((str[meter] == 'e') && ((meter == 0) || (meter == (l - 1)) || ((meter > 0) && (meter < 
        (l - 1)) && (str[meter - 1] != 'c') && (str[meter + 1] != 'i'))))
    {
      if (meter > 0)
      {
        if ((numeral(str[meter - 1]) == OK) && (str[meter + 1] != '+') && (str[meter + 1] != 
            '-') && (numeral(str[meter + 1]) == MISTAKE))
          wrongConstant = MISTAKE;
        if (numeral(str[meter - 1]) != OK)
        {
          if (str[meter - 1] == ')')
            wrongConstant = MISTAKE;
          if ((str[meter - 1] != '(') && (str[meter - 1] != ' ') && (operand(str[meter - 1]) 
              == OK))
            wrongConstant = MISTAKE;
        }
      }
      if ((meter > 0) && (meter < (l - 1)))
        if ((numeral(str[meter - 1]) == MISTAKE) && (numeral(str[meter + 1]) == OK))
          wrongConstant = MISTAKE;
      if (meter < (l - 1))
      {
        if ((meter == 0) && (numeral(str[meter + 1]) == OK))
          wrongConstant = MISTAKE;
        if ((str[meter + 1] != ')') && (str[meter + 1] != ' ') && (operand(str[meter + 1]) 
            == OK) && (numeral(str[meter + 1]) == MISTAKE))
          wrongConstant = MISTAKE;
        if (str[meter + 1] == '(')
          wrongConstant = MISTAKE;
      }
    }
    if (wrongConstant == MISTAKE)
    {
      if ((*mistake) == OK)
        (*mistake) = WRONG_CONSTANT;
      assert(str != NULL);
      assert(l >= 0);
      return MISTAKE;
    }
  }
  assert(str != NULL);
  assert(l >= 0);
  return OK;
}

int operators(char const *str, int const l, int *mistake)
{
  int meter, meter2;
  int wrongOperator = OK;
  //variable that has MISTAKE value if there is a wrong operator in the string
  int counter;
  //auxiliary variable
  assert(str != NULL);
  assert(l >= 0);
  for (meter = 0; meter < l; meter++)
  {
    assert(meter >= 0);
    if (operand(str[meter]) == MISTAKE)
    {
      counter = 0;
      for (meter2 = meter + 1; meter2 < l; meter2++)
        if (str[meter2] != ' ')
          counter++;
      if (counter == 0)
        wrongOperator = MISTAKE;
      if ((meter == 0) && (str[meter] != '-'))
        wrongOperator = MISTAKE;
      if ((str[meter] != '-') && (str[meter - 1] == '('))
        wrongOperator = MISTAKE;
      if (str[meter + 1] == ')')
        wrongOperator = MISTAKE;
      if ((meter > 0) && (operand(str[meter - 1]) == MISTAKE) && (str[meter] != '+') && 
          (str[meter] != '-'))
        wrongOperator = MISTAKE;
      if (wrongOperator == MISTAKE)
      {
        if ((*mistake) == OK)
          (*mistake) = WRONG_OPERATOR;
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

int operands(char const *str, int const l, int *mistake)
{
  int meter;
  int wrongOperand = OK;
  //variable that has MISTAKE value if there is a wrong operand in the string
  assert(str != NULL);
  assert(l >= 0);
  for(meter = 0; meter < l; meter++)
  {
    assert(meter >= 0);
    if ((operand(str[meter]) == OK) && (str[meter] != '(') && (str[meter] != ')') && 
        (firstFunctionSymbol(str[meter]) == MISTAKE) && (lastFunctionSymbol(str[meter]) ==
        MISTAKE))
    {
      if ((meter > 0) && (str[meter - 1] != 'e'))
      {
        if ((str[meter - 1] == 'i') || (str[meter - 1] == 'e'))
          wrongOperand = MISTAKE;
        if ((str[meter] != 'i') && (str[meter - 1] == 'p'))
          wrongOperand = MISTAKE;
      }
      if ((meter < (l - 1)) && (str[meter + 1] != 'l'))
        if (str[meter + 1] == 'p')
          wrongOperand = MISTAKE;
      if (str[meter] == '.')
      {
        if (meter == 0)
          wrongOperand = MISTAKE;
        if (numeral(str[meter - 1]) == MISTAKE)
          wrongOperand = MISTAKE;
        if (numeral(str[meter + 1]) == MISTAKE)
          wrongOperand = MISTAKE;
      }
      if (wrongOperand == MISTAKE)
      {
        if ((*mistake) == OK)
          (*mistake) = WRONG_OPERAND;
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

int scienceNotation(char const *str, int const l, int *mistake)
{
  int meter, meter2;
  int wrongNumber = OK;
  assert(str != NULL);
  assert(l >= 0);
  for (meter = 0; meter < l; meter++)
  {
    assert(meter >= 0);
    assert(str != NULL);
    if (((str[meter] == 'e') || (str[meter] == 'E')) && (meter > 0) && (numeral(str[meter - 1]) == OK))
    {
      meter2 = meter - 1;
      while (numeral(str[meter2]) == OK)
        meter2--;
      if (str[meter2] == '.')
      {
        meter2--;
        if (numeral(str[meter2]) == MISTAKE)
          wrongNumber = MISTAKE;
        else
          while (numeral(str[meter2]) == OK)
            meter2--;
      }
      if ((meter2 > 0) && (operand(str[meter2]) != MISTAKE) && (str[meter2] != '('))
        wrongNumber = MISTAKE;
      if ((str[meter + 1] != '+') && (str[meter + 1] != '-') && numeral(str[meter + 1]) != OK)
        wrongNumber = MISTAKE;
      if ((str[meter + 1] == '+') || (str[meter + 1] == '-'))
        meter++;
      meter++;
      while (numeral(str[meter]) == OK)
      {
        if ((meter < (l - 1)) && (numeral(str[meter + 1]) == MISTAKE) && (operand(str[meter + 
            1]) == OK) && (str[meter + 1] != ')'))
        {
          wrongNumber = MISTAKE;
          break;
        }
        meter++;
      }
    }
    if (wrongNumber == MISTAKE)
    {
      if ((*mistake) == OK)
        (*mistake) = WRONG_NUMBER_IN_SCIENCE_NOTATION;
      assert(str != NULL);
      assert(l >= 0);
      return MISTAKE;
    }
  }
  assert(str != NULL);
  assert(l >= 0);
  return OK;
}

int numeral(char const c)
{
  if ((c == '0') || (c == '1') || (c == '2') || (c == '3') || (c == '4') || (c == '5') || 
      (c == '6') || (c == '7') || (c == '8') || (c == '9'))
    return OK;
  return MISTAKE;
}

int operand(char const c)
{
  if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^'))
    return MISTAKE;
  return OK;
}

int firstFunctionSymbol (char const c)
{
  if ((c == 's') || (c == 'f') || (c == 't') || (c == 'l') || (c == 'c') || (c == 'a'))
    return OK;
  return MISTAKE;
}

int lastFunctionSymbol (char const c)
{
  if ((c == 't') || (c == 'n') || (c == 'r') || (c == 'g') || (c == 'l') || (c == 's'))
    return OK;
  return MISTAKE;
}