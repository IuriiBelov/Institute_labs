#ifndef H_FILE_LABB11_MEMORY__
#define H_FILE_LABB11_MEMORY__

typedef struct tag_block
{
  struct tag_block *next, *prev;
  int size;
} block_t;

int initSystem(void);
void *myMalloc(int size);
void myFree(void *p);
void closeSystem(void);

#endif