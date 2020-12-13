#ifndef H_FILE_LABB11_SYSTEM__
#define H_FILE_LABB11_SYSTEM__

typedef struct tag_block
{
  struct tag_block *prev, *next;
  int size;
} block_t;

int initSystem(int size);
void *myMalloc(int size);
void myFree(void *p);
void closeSystem(void);

#endif