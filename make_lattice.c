#include"global.h"


void make_lattice()
{
  int s,x1,x2;
  
  for (x1 = 0; x1 <=lx-1; x1 += 1)
  {
    s=1+x1;
    x2=(x1+1)%lx;
    bsites[0][s]=s;
    bsites[1][s]=1+x2;
 
  }
}
