#include "summ_x.h"
#include "merge_sort.h"

int firstSummand(int *S, int first, int last, int x);

summands_t summX(int *S, int n, int x)
{
  int i;
  summands_t result;
  mergeSort(S, n);
  result.firstIndex = firstSummand(S, 0, n - 1, x);
  printf("%i\n", result.firstIndex);
  if (result.firstIndex == -1)
  {
    result.secondIndex = -1;
    return result;
  }
  result.secondIndex = -1;
  for (i = 0; i < n; i++)
  {
    if (i == result.firstIndex)
      continue;
    if (S[i] + S[result.firstIndex] == x)
    {
      result.secondIndex = i;
      return result;
    }
  }
  result.firstIndex = -1;
  return result;
}

int firstSummand(int *S, int first, int last, int x)
{
  int middle;
  if (first == last)
    return first;
  if (first == last - 1)
    if (x > 2 * S[first])
      return last;
    else
      return first;
  middle = (first + last) / 2;
  if (x > 2 * S[middle])
    return firstSummand(S, middle + 1, last, x);
  else if (x < 2 * S[middle])
    return firstSummand(S, first, middle - 1, x);
  else
    if (S[middle - 1] == S[middle] || S[middle + 1] == S[middle])
      return middle;
    else
      return -1;
}