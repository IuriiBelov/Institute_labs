#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <assert.h>
#include "treatment.h"
#include "calculation.h"
#include "length.h"
#include "error.h"

#define OK 0
#define MISTAKE 1
#define ENTER 10
#define COMMENT 2
#define EMPTY 2

int arguments(FILE**fp, int argc, char*argv[]);
//function that checks arguments of command line
int proverka(char const *str);
//function that checks if the string is empty or comment

int main(int argc, char*argv[])
{
  int resultCheckArguments;
  //result of function "arguments"
  int resultProverka;
  //result of function "proverka"
  FILE*fp;
  //input stream
  char *str;
  //string of the expression
  char *str1, *str2, *str3;
  //auxiliary strings
  int readingSymbol;
  //symbol of input stream that is being reading
  int i = 0;
  //quantity of dynamic memory
  int j;
  //meter
  int l;
  //length of the string
  double rez = 0;
  //result of the calculation
  int mistake;
  //variable that has value "1" if there is a mistake and "0" if not
  int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
  _CrtSetDbgFlag(flag | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
  _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT);
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
  _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT);
  resultCheckArguments = arguments(&fp, argc, argv);
  if (resultCheckArguments == 1)
    return MISTAKE;
  do
  {
    mistake = OK;
    str = malloc(2 * sizeof(char));
    if (str == NULL)
    {
      fprintf(stdout, "ERROR: not enough dynamic memory\n");
      return MISTAKE;
    }
    do
    {
      readingSymbol = getc(fp);
      str[i] = (char)(readingSymbol);
      i++;
      str1 = realloc(str, (i + 1) * sizeof(char));
      if (str1 == NULL)
      {
        fprintf(stdout, "ERROR: not enough dynamic memory\n");
        free(str);
        return MISTAKE;
      }
      str = str1;
    } while ((readingSymbol != ENTER) && (readingSymbol != EOF));
    str1 = NULL;
    assert(str != NULL);
    l = length(str);
    str2 = malloc((i + 1) * sizeof(char));
    if (str2 == NULL)
    {
      fprintf(stdout, "ERROR: not enough dynamic memory\n");
      free(str);
      return MISTAKE;
    }
    assert(str2 != NULL);
    assert(l >= 0);
    for (j = 0; j < l; j++)
        str2[j] = str[j];
    str2[l] = '\0';
    resultProverka = proverka(str);
    if ((resultProverka == COMMENT) || (resultProverka == EMPTY))
    {
      if (str2[0] != '\0')
      {
        assert(str2 != NULL);
        if (str[l] == '\n')
          fprintf(stdout, "%s\n", str2);
        else
          fprintf(stdout, "%s", str2);
      }
      else
        if (str[0] == '\n')
          fprintf(stdout, "\n");
    }
    else
    {
      assert(str2 != NULL);
      assert(str != NULL);
      fprintf(stdout, "%s == ", str2);
      str3 = malloc((l + 1) * 4 * sizeof(char));
      if (str3 == NULL)
      {
        fprintf(stdout, "ERROR: not enough dynamic memory\n");
        free(str);
        free(str2);
        return MISTAKE;
      }
      treatment(str, str3, &mistake);
      if (mistake == OK)
        rez = calculate(str3, &mistake);
      free(str3);
      if (mistake > OK)
      {
        switch (mistake)
        {
        case NOT_ENOUGH_DYNAMIC_MEMORY:
          fprintf(stdout, "ERROR: not enough dynamic memory");
          break;
        case TWO_OPERANDS_EACH_AFTER_ANOTHER:
          fprintf(stdout, "ERROR: two operands each after another");
          break;
        case INADMISSIBLE_SYMBOL_IN_THE_STRING:
          fprintf(stdout, "ERROR: inadmissible symbol in the string");
          break;
        case WRONG_BRACKET:
          fprintf(stdout, "ERROR: wrong bracket");
          break;
        case WRONG_CONSTANT:
          fprintf(stdout, "ERROR: wrong constant");
          break;
        case WRONG_OPERATOR:
          fprintf(stdout, "ERROR: wrong operator");
          break;
        case WRONG_OPERAND:
          fprintf(stdout, "ERROR: wrong operand");
          break;
        case WRONG_NUMBER_IN_SCIENCE_NOTATION:
          fprintf(stdout,"ERROR: wrong number in science notation");
          break;
        case WRONG_FUNCTION:
          fprintf(stdout, "ERROR: wrong function");
          break;
        case DIVISION_BY_ZERO:
          fprintf(stdout, "ERROR: Division by zero");
          break;
        case SQRT_BY_NEGATIVE_NUMBER:
          fprintf(stdout, "ERROR: sqrt by negative number");
          break;
        case THE_VALUE_IS_INFINITY:
          fprintf(stdout, "ERROR: the value is infinity");
          break;
        case LN_BY_NEGATIVE_NUMBER:
          fprintf(stdout, "ERROR: ln by negative number");
          break;
        case INADMISSIBLE_ARGUMENT_FOR_ARCSIN:
          fprintf(stdout, "ERROR: inadmissible argument for arcsin");
          break;
        case INADMISSIBLE_ARGUMENT_FOR_ARCCOS:
          fprintf(stdout, "ERROR: inadmissible argument for arccos");
          break;
        }
        if (str[l] == '\n')
          fprintf(stdout, "\n");
      }
      else
      {
        if (str[l] == '\n')
          fprintf(stdout, "%g\n", rez);
        else
          fprintf(stdout, "%g", rez);
      }
    }
    free(str2);
    i = 0;
    free(str);
  } while (readingSymbol != EOF);
  return OK;
}

int arguments(FILE**fp, int argc, char*argv[])
{
  if (argc == 1)
  {
    *fp = stdin;
    return 0;
  }
  if (argc == 2)
  {
    *fp = fopen(argv[1], "r");
    if (*fp == 0)
    {
      fputs("ERROR: file not found\n", stdout);
      return 1;
    }
    else
        return 0;
  }
  if (argc > 2)
  {
    fputs("ERROR: too many arguments\n", stdout);
    return 1;
  }
  return 0;
}

int proverka(char const *str)
{
  int l;
  //length of the string
  int i;
  //meter
  int k = 0;
  //quantity of space symbols
  assert(str != 0);
  if ((str[0] == ENTER) || (str[0] == EOF))
    return EMPTY;
  if ((str[0] == '/') && (str[1] == '/'))
    return COMMENT;
  l = length(str);
  assert(l >= 0);
  for (i = 0; i < l; i++)
  {
    if ((str[i] >= 0) && (isspace(str[i])))
        k++;
    if (k == (i + 1))
        if (str[i + 1] == '/')
            if (str[i + 2] == '/')
                return COMMENT;
  }
  if (k == l)
      return EMPTY;
  return 0;
}