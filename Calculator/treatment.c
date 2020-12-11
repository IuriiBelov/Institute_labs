#include <ctype.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <assert.h>
#include "check.h"
#include "checkFunctions.h"
#include "error.h"
#include "length.h"

#define MISTAKE 1
#define OK 0

void deleteSpace(char *str, int l);
//function that deletes space symbols in the string
int unarMinus(char *str, int *l, char *str3, int *mistake);
//function that treats unar minuses
void scienceNumber(char *str, int *l);
//function that treats numbers in science notation
void functions(char *str, int *l);
//function that replaces the functions to the symbols
void functionSqrtSin(char *str, int *meter, int *l);
//function that treats "sqrt" and "sin" functions
void functionFloor(char *str, int *meter, int *l);
//function that treats "floor" function
void functionTg(char *str, int *meter, int *l);
//function that treats "tg" function
void functionLnLog(char *str, int *meter, int *l);
//function that treats "ln"function
void functionCosCtgCeil(char *str, int *meter, int *l);
//function that treats "cos", "ctg" and "ceil" functions
void functionArcFunctions(char *str, int *meter, int *l);
//function that treats arcfunctions
int nextSymbol(char c);
//function that returns "0" if the symbol if an operand and "1" if not
int operatorss(char c);
//function that returns "0" if the symbol is an operator and "1" if not
int symbolFunction(char c);
//function that returns "0" if the symbol is a symbol of function and "1" if not

void treatment(char const *str, char *strr, int *mistake)
{
  char *str2, *str3;
  //copies of string of the expression
  int rez;
  //result of unarMinus
  int l;
  //length of the string
  int meter;
  assert(str != NULL);
  l = length(str);
  str2 = malloc((l + 1) * 4 * sizeof(char));
  str3 = malloc((l + 1) * 8 * sizeof(char));
  if ((str2 == NULL) || (str3 == NULL))
  {
    if ((*mistake) == OK)
      (*mistake) = NOT_ENOUGH_DYNAMIC_MEMORY;
    free(str2);
    free(str3);
    return;
  }
  assert(str2 != NULL);
  assert(str != NULL);
  assert(l >= 0);
  for (meter = 0; meter < l; meter++)
    str2[meter] = str[meter];
  assert(str2 != NULL);
  assert(l >= 0);
  deleteSpace(str2, l);
  if (check(str2, l, mistake) == MISTAKE)
  {
    free(str2);
    free(str3);
    return;
  }
  assert(str2 != NULL);
  assert(l >= 0);
  if (checkFunctions(str2, l, mistake) == MISTAKE)
  {
    free(str2);
    free(str3);
    return;
  }
  assert(l >= 0);
  for (meter = 0; meter < (l / 2); meter++)
  {
    assert(str2 != NULL);
    assert(str3 != NULL);
    assert((&l) != NULL);
    rez = unarMinus(str2, &l, str3, mistake);
    if (rez == MISTAKE)
    {
      free(str2);
      free(str3);
      return;
    }
    assert(str2 != NULL);
    assert(str3 != NULL);
    assert((&l) != NULL);
    rez = unarMinus(str3, &l, str2, mistake);
    if (rez == MISTAKE)
    {
      free(str2);
      free(str3);
      return;
    }
  }
  assert(str2 != NULL);
  assert((&l) != NULL);
  scienceNumber(str2, &l);
  functions(str2, &l);
  str2[l] = ' ';
  for (meter = 0; meter <= l; meter++)
    strr[meter] = str2[meter];
  free(str2);
  free(str3);
  return;
}

void deleteSpace(char *str, int l)
{
  int meterStr = 0, meterStr2;
  //meters
  int l1;
  //length of origin string
  assert(l >= 0);
  l1 = l;
  do
  {
    assert(str != NULL);
    assert(meterStr < l);
    if ((str[meterStr] >= 0) && (isspace(str[meterStr])))
    {
      for (meterStr2 = meterStr; meterStr2 < (l - 1); meterStr2++)
      {
        assert(meterStr2 < l);
        str[meterStr2] = str[meterStr2 + 1];
      }
      l--;
    }
    else
      meterStr++;
  } while (meterStr < l);
  assert(str != NULL);
  assert(l1 >= 0);
  assert(l >= 0);
  for (meterStr = l; meterStr < l1; meterStr++)
    str[meterStr] = ' ';
  return;
}

int unarMinus(char *str2, int *l, char *str3, int *mistake)
{
  int meterStr2 = 0, meterStr3 = 0, meter;
  int l2;
  int nBrackets;
  assert(str2 != NULL);
  assert(str3 != NULL);
  if ((meterStr2 == 0) && (str2[meterStr2] == '-'))
  {
    assert(l != NULL);
    (*l)++;
    for (meter = *l; meter > 0; meter--)
      *(str2 + meter) = *(str2 + meter - 1);
    str2[0] = '0';
  }
  assert(l != NULL);
  l2 = *l;
  while (meterStr2 < l2)
  {
    assert(str2 != NULL);
    if ((str2[meterStr2] == '-') && ((operatorss(str2[meterStr2 - 1]) == OK) || 
        (str2[meterStr2 - 1] == '(')))
    {
      assert(str3 != NULL);
      str3[meterStr3] = '(';
      meterStr3++;
      (*l)++;
      str3[meterStr3] = '0';
      meterStr3++;
      (*l)++;
      str3[meterStr3] = str2[meterStr2];
      meterStr3++;
      meterStr2++;
      if (str2[meterStr2] == '(')
      {
        str3[meterStr3] = str2[meterStr2];
        meterStr3++;
        meterStr2++;
        nBrackets = 1;
        while (nBrackets > 0)
        {
          str3[meterStr3] = str2[meterStr2];
          meterStr3++;
          meterStr2++;
          if (str2[meterStr2] == '(')
            nBrackets++;
          if (str2[meterStr2] == ')')
            nBrackets--;
        }
        str3[meterStr3] = ')';
        meterStr3++;
        (*l)++;
      }
      assert(str2 != NULL);
      if (nextSymbol(str2[meterStr2]) == OK)
      {
        if ((nextSymbol(str2[meterStr2]) == MISTAKE) && (str2[meterStr2] != '('))
        {
          if ((*mistake) == OK)
            (*mistake) = TWO_OPERANDS_EACH_AFTER_ANOTHER;
          assert(str2 != NULL);
          assert(str3 != NULL);
          assert(l != NULL);
          assert((*l) >= 0);
          return MISTAKE;
        }
        while ((nextSymbol(str2[meterStr2]) == OK) || (str2[meterStr2] == '('))
        {
          assert(str3 != NULL);
          str3[meterStr3] = str2[meterStr2];
          meterStr3++;
          meterStr2++;
        }
        str3[meterStr3] = ')';
        meterStr3++;
        (*l)++;
      }
      assert(str2 != NULL);
      if (symbolFunction(str2[meterStr2]) == OK)
      {
        while (str2[meterStr2] != '(')
        {
          assert(str3 != NULL);
          str3[meterStr3] = str2[meterStr2];
          meterStr3++;
          meterStr2++;
        }
        nBrackets = 1;
        while (nBrackets > 0)
        {
          assert(str2 != NULL);
          assert(str3 != NULL);
          str3[meterStr3] = str2[meterStr2];
          meterStr3++;
          meterStr2++;
          if (str2[meterStr2] == '(')
            nBrackets++;
          if (str2[meterStr2] == ')')
            nBrackets--;
        }
        str3[meterStr3] = ')';
        meterStr3++;
        (*l)++;
      }
    }
    else
    {
      assert(str2 != NULL);
      assert(str3 != NULL);
      str3[meterStr3] = str2[meterStr2];
      meterStr3++;
      meterStr2++;
    }
  }
  assert(str2 != NULL);
  assert(str3 != NULL);
  assert(l != NULL);
  assert((*l) >= 0);
  return OK;
}

void scienceNumber(char *str, int *l)
{
  int meter = 0, meter2, meter3;
  assert(str != NULL);
  assert(l != NULL);
  assert((*l) >= 0);
  while (meter < *l)
  {
    if (((str[meter] == 'e') || (str[meter] == 'E')) && (meter > 0) && (nextSymbol(str[meter 
        - 1]) == OK) && (str[meter - 1] != 'p') && (str[meter - 1] != 'e') && (str[meter - 1] 
        != '.'))
    {
      assert(str != 0);
      assert(meter < *l);
      meter3 = meter - 1;
      while ((nextSymbol(str[meter3]) == OK) && (meter3 >= 0))
        meter3--;
      (*l)++;
      meter++;
      for (meter2 = (*l - 1); meter2 > meter3; meter2--)
        *(str + meter2) = *(str + meter2 - 1);
      str[meter3 + 1] = '(';
      if (str[meter + 1] == '+')
        *(str + meter) = '*';
      if (str[meter + 1] == '-')
        *(str + meter) = '/';
      if (nextSymbol(str[meter + 1]) == OK)
      {
        (*l)++;
        for (meter2 = (*l - 1); meter2 > meter; meter2--)
          *(str + meter2) = *(str + meter2 - 1);
        *(str + meter) = '*';
      }
      meter++;
      assert(meter < *l);
      *(str + meter) = '1';
      for (meter2 = *l; meter2 > (meter + 1); meter2--)
        *(str + meter2) = *(str + meter2 - 1);
      (*l)++;
      meter++;
      assert(meter < *l);
      *(str + meter) = '0';
      for (meter2 = (*l + 1); meter2 > meter + 1; meter2--)
        *(str + meter2) = *(str + meter2 - 1);
      (*l)++;
      meter++;
      assert(meter < *l);
      *(str + meter) = '^';
      
      meter3 = meter + 1;
      while ((nextSymbol(str[meter3]) == OK) && (meter3 < *l))
        meter3++;
      meter++;
      (*l)++;
      for (meter2 = (*l - 1); meter2 > meter3; meter2--)
        *(str + meter2) = *(str + meter2 - 1);
      str[meter3] = ')';
    }
    meter++;
  }
  assert(str != NULL);
  assert(l != NULL);
  assert((*l) >= 0);
  return;
}

void functions(char *str, int *l)
{
  int meter = 0;
  while (meter < *l)
  {
    switch (str[meter])
    {
    case 's':
      functionSqrtSin(str, &meter, l);
      break;
    case 'f':
      functionFloor(str, &meter, l);
      break;
    case 't':
      functionTg(str, &meter, l);
      break;
    case 'l':
      functionLnLog(str, &meter, l);
      break;
    case 'c':
      functionCosCtgCeil(str, &meter, l);
      break;
    case 'a':
      functionArcFunctions(str, &meter, l);
      break;
    }
    meter++;
  }
  return;
}

void functionSqrtSin(char *str, int *meter, int *l)
{
  int i;
  if ((str[*meter - 1] != 'o') && (str[*meter - 1] != 'c'))
  {
    if (str[*meter + 1] == 'q')
    {
      str[*meter] = 'a';
      for (i = *meter + 1; i < (*l - 3); i++)
        str[i] = str[i + 3];
      for (i = (*l - 3); i < *l; i++)
        str[i] = ' ';
    }
    else
    {
      str[*meter] = 'b';
      for (i = *meter + 1; i < (*l - 2); i++)
        str[i] = str[i + 2];
      for (i = (*l - 2); i < *l; i++)
        str[i] = ' ';
    }
  }
  return;
}

void functionFloor(char *str, int *meter, int *l)
{
  int i;
  str[*meter] = 'm';
  for (i = *meter + 1; i < (*l - 4); i++)
    str[i] = str[i + 4];
  for (i = (*l - 4); i < *l; i++)
    str[i] = ' ';
  return;
}

void functionTg(char *str, int *meter, int *l)
{
  int i;
  if ((str[*meter - 1] != 'r') && (str[*meter - 1] != 'c'))
  {
    str[*meter] = 'd';
    for (i = *meter + 1; i < (*l - 1); i++)
      str[i] = str[i + 1];
    for (i = (*l - 1); i < *l; i++)
      str[i] = ' ';
  }
  return;
}

void functionLnLog(char *str, int *meter, int *l)
{
  int i;
  if ((str[*meter - 1] != 'f') && (str[*meter - 1] != 'i'))
  {
    str[*meter] = 'l';
    for (i = *meter + 1; i < (*l - 1); i++)
      str[i] = str[i + 1];
    for (i = (*l - 1); i < *l; i++)
      str[i] = ' ';
  }
  return;
}

void functionCosCtgCeil(char *str, int *meter, int *l)
{
  int i;
  if ((str[*meter - 1] != 'r') && (str[*meter - 1] != 'c'))
  {
    if (str[*meter + 1] == 'o')
    {
      str[*meter] = 'c';
      for (i = *meter + 1; i < (*l - 2); i++)
        str[i] = str[i + 2];
      for (i = (*l - 2); i < *l; i++)
        str[i] = ' ';
    }
    if (str[*meter + 1] == 't')
    {
      str[*meter] = 'f';
      for (i = *meter + 1; i < (*l - 2); i++)
        str[i] = str[i + 2];
      for (i = (*l - 2); i < *l; i++)
        str[i] = ' ';
    }
    if (str[*meter + 1] == 'e')
    {
      str[*meter] = 'n';
      for (i = *meter + 1; i < (*l - 3); i++)
        str[i] = str[i + 3];
      for (i = (*l - 3); i < *l; i++)
        str[i] = ' ';
    }
  }
  return;
}

void functionArcFunctions(char *str, int *meter, int *l)
{
  int i;
  if (str[*meter + 3] == 's')
    {
      str[*meter] = 'g';
      for (i = *meter + 1; i < (*l - 5); i++)
        str[i] = str[i + 5];
      for (i = (*l - 5); i < *l; i++)
        str[i] = ' ';
    }
    if (str[*meter + 3] == 'c')
    {
      str[*meter] = 'h';
      for (i = *meter + 1; i < (*l - 5); i++)
        str[i] = str[i + 5];
      for (i = (*l - 5); i < *l; i++)
        str[i] = ' ';
    }
    if (str[*meter + 3] == 't')
    {
      str[*meter] = 'j';
      for (i = *meter + 1; i < (*l - 4); i++)
        str[i] = str[i + 4];
      for (i = (*l - 4); i < *l; i++)
        str[i] = ' ';
    }
  return;
}

int nextSymbol(char c)
{
  if ((c == '0') || (c == '1') || (c == '2') || (c == '3') || (c == '4') || (c == '5') || 
      (c == '6') || (c == '7') || (c == '8') || (c == '9') || (c == 'p') || (c == 'e') || 
      (c == '.'))
    return OK;
  return MISTAKE;
}

int operatorss(char c)
{
  if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^'))
    return OK;
  return MISTAKE;
}

int symbolFunction(char c)
{
  if ((c == 's') || (c == 'c') || (c == 't') || (c == 'a') || (c == 'f') || (c == 'l'))
    return OK;
  return MISTAKE;
}