#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "SheikerSort.h"
#include "HeapSort.h"

#define BEGIN 10
#define STEP 10
#define N 20
#define MISTAKE 1
#define OK 0


void headLines(FILE *fp);
//function that prints headlines of sorts in the file
void randomValues(int *massiv, int size);
//function that sets random values to elements of the massiv
void copyValues(int *massivSelection, int *massivInsertion, int *massivBubble, int 
    *massivSheiker, int *massivHeap, int size);
//function that copies random values from one massive to other
void timer(LARGE_INTEGER *timeStartAlgoritm, LARGE_INTEGER *timeFinishAlgoritm, int *massiv, 
    int size, void (*function)(int *a, int b));
//function that calculates time of the algoritm
double timeSort(LARGE_INTEGER time);
//function that treates time of the algoritm
void printfResults(int meterN, double timeSelection, double timeInsertion, double timeBubble, 
    double timeSheiker, double timeHeap, FILE *fp);
//function that prints times of the algoritms in the file
void freeMemory(int *massivSelection, int *massivInsertion, int *massivBubble, int 
    *massivSheiker, int *massivHeap);
//function that frees all the memory

int main(void)
{
  int *massivSelection;
  //massive of random values
  int *massivInsertion, *massivBubble, *massivSheiker, *massivHeap;
  //copies of the massiv
  int size;
  //current size of the massiv
  int meterN = 0;
  //number of interation
  LARGE_INTEGER timeProcessor;
  LARGE_INTEGER timeStartSelection, timeFinishSelection, timeStartInsertion, 
      timeFinishInsertion, timeStartBubble, timeFinishBubble, timeStartSheiker, 
      timeFinishSheiker, timeStartHeap, timeFinishHeap;
  double timeSelection, timeInsertion, timeBubble, timeSheiker, timeHeap;
  //times of the algoritms
  FILE *fp;
  fp = fopen("time.csv", "w");
  if (fp == NULL)
  {
    printf("ERROR: file not found\n");
    return MISTAKE;
  }
  headLines(fp);
  QueryPerformanceFrequency(&timeProcessor);
  for (size = BEGIN; size <= (BEGIN * N); size += STEP)
  {
    meterN++;
    massivSelection = malloc(size * sizeof(int));
    massivInsertion = malloc(size * sizeof(int));
    massivBubble = malloc(size * sizeof(int));
    massivSheiker = malloc(size * sizeof(int));
    massivHeap = malloc(size * sizeof(int));
    if ((massivSelection == NULL) || (massivInsertion == NULL) || (massivBubble == NULL) || 
        (massivSheiker == NULL) || (massivHeap == NULL))
    {
      printf("ERROR: not enough dynamic memory\n");
      freeMemory(massivSelection, massivInsertion, massivBubble, massivSheiker, massivHeap);
      return MISTAKE;
    }
    randomValues(massivSelection, size);
    copyValues(massivSelection, massivInsertion, massivBubble, massivSheiker, massivHeap, size);
    timer(&timeStartSelection, &timeFinishSelection, massivSelection, size, selectionSort);
    timer(&timeStartInsertion, &timeFinishInsertion, massivInsertion, size, insertionSort);
    timer(&timeStartBubble, &timeFinishBubble, massivBubble, size, bubbleSort);
    timer(&timeStartSheiker, &timeFinishSheiker, massivSheiker, size, sheikerSort);
    timer(&timeStartHeap, &timeFinishHeap, massivHeap, size, heapSort);
    timeSelection = (timeSort(timeFinishSelection) - timeSort(timeStartSelection)) / 
        timeSort(timeProcessor);
    timeInsertion = (timeSort(timeFinishInsertion) - timeSort(timeStartInsertion)) / 
        timeSort(timeProcessor);
    timeBubble = (timeSort(timeFinishBubble) - timeSort(timeStartBubble)) / 
        timeSort(timeProcessor);
    timeSheiker = (timeSort(timeFinishSheiker) - timeSort(timeStartSheiker)) / 
        timeSort(timeProcessor);
    timeHeap = (timeSort(timeFinishHeap) - timeSort(timeStartHeap)) / 
        timeSort(timeProcessor);
    printfResults(meterN, timeSelection, timeInsertion, timeBubble, timeSheiker, timeHeap, fp);
    freeMemory(massivSelection, massivInsertion, massivBubble, massivSheiker, massivHeap);
  }
  fclose(fp);
  return OK;
}

void headLines(FILE *fp)
{
  fprintf(fp, ";");
  fprintf(fp, "Selection;");
  fprintf(fp, "Insertion;");
  fprintf(fp, "Bubble;");
  fprintf(fp, "Sheiker;");
  fprintf(fp, "Heap;");
  fprintf(fp, "\n");
  return;
}

void randomValues(int *massiv, int size)
{
  int meter;
  srand((unsigned)(time(NULL)));
  for (meter = 0; meter < size; meter++)
    massiv[meter] = rand() % (10 * size);
  return;
}

void copyValues(int *massivSelection, int *massivInsertion, int *massivBubble, int 
    *massivSheiker, int *massivHeap, int size)
{
  int meter;
  for (meter = 0; meter < size; meter++)
  {
    massivInsertion[meter] = massivSelection[meter];
    massivBubble[meter] = massivSelection[meter];
    massivSheiker[meter] = massivSelection[meter];
    massivHeap[meter] = massivSelection[meter];
  }
  return;
}

void timer(LARGE_INTEGER *timeStartAlgoritm, LARGE_INTEGER *timeFinishAlgoritm, int *massiv, 
    int size, void (*function)(int *a, int b))
{
  QueryPerformanceCounter(timeStartAlgoritm);
  function(massiv, size);
  QueryPerformanceCounter(timeFinishAlgoritm);
  return;
}

double timeSort(LARGE_INTEGER time)
{
  double rez = (double)time.QuadPart;
  return rez;
}

void printfResults(int meterN, double timeSelection, double timeInsertion, double timeBubble, 
    double timeSheiker, double timeHeap, FILE *fp)
{
  fprintf(fp, "%i;", meterN);
  fprintf(fp, "%lf;", timeSelection);
  fprintf(fp, "%lf;", timeInsertion);
  fprintf(fp, "%lf;", timeBubble);
  fprintf(fp, "%lf;", timeSheiker);
  fprintf(fp, "%lf;", timeHeap);
  fprintf(fp, "\n");
  return;
}

void freeMemory(int *massivSelection, int *massivInsertion, int *massivBubble, int 
    *massivSheiker, int *massivHeap)
{
  free(massivSelection);
  free(massivInsertion);
  free(massivBubble);
  free(massivSheiker);
  free(massivHeap);
  return;
}