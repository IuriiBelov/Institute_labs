/*
#include "graphics.h"

int main(void)
{
  int gd = DETECT, gm;
  int x,y,i,j,s;
  
  initgraph(&gd, &gm, "");
  
  x=getmaxx();
  y=getmaxy();
  s=0;
  for(i=0;i<=15;i++)
  {setcolor(i);
   for(j=s;j<=(x+1)/15+s;j++) line(j,0,j,y);
   s=s+(x+1)/15;
  }
  //setcolor(10);
  //line(0, 0, getmaxx(), getmaxy());

  readkey();
  closegraph();

  return 0;
}
*/

#include "graphics.h"
int main(void)
{int gd = DETECT, gm, k;
 initgraph(&gd, &gm, "");
 do
 {k=readkey();
  printf("%i ",k);
 }while(k!=27);
 closegraph();
 return 0;
}
