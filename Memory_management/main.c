#include <stdio.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "system.h"

#define N 100

int main(void)
{
  void *p[N];
  void *p0, *p1, *p2;
  int fail = 0, i, sizes[N];
  _CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  /*
  initSystem(60);
 
  p0 = myMalloc(4);
  memset(p0, 0xAB, 4);
  p1 = myMalloc(4);
  memset(p0, 0xAB, 4);
  p2 = myMalloc(4);
  memset(p0, 0xAB, 4);

  myFree(p2);
  myFree(p0);
  myFree(p1);

  p0 = myMalloc(44);

  closeSystem();
  */


  if (initSystem(10024))
    return 1;
  /*
  p = myMalloc(1008);
  myFree(p);
  p = myMalloc(100);
  myFree(p);
  p = myMalloc(1);
  myFree(p);
  p = myMalloc(28);
  myFree(p);
  */
  for (i = 0; i < N; ++i)
    p[i] = NULL;

  for (i = 0; i < 10000; ++i)
  {
    int idx  = rand() % N;
    int size = rand() % 99 + 1;
    if (NULL == p[idx])
    {
      p[idx]     = myMalloc(size);
      sizes[idx] = size;
      if (p[idx])
      {
        printf("Alloc %d\n", size);
        memset(p[idx], 0xBC, size);
      }
      else
      {
        //printf("Fail %d\n", size);
        fail++;
      }
    }
    else
    {
      printf("Free %d\n", sizes[idx]);
      myFree(p[idx]);
      p[idx] = NULL;
    }
  }
  printf("%i\n", fail);
  closeSystem();
  return 0;
}