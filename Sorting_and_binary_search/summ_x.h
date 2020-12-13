#ifndef __PROJECT_CHAPTER_2_H_FILE_SUMM_X__
#define __PROJECT_CHAPTER_2_H_FILE_SUMM_X__

typedef struct
{
  int firstIndex;
  int secondIndex;
} summands_t;

/* Function returns indices of elements of S which summ is x (or -1 if such elements don`t exist)*/
summands_t summX(int *S, int n, int x);

#endif