#include<stdlib.h>
#include"global.h"

void init_genrand64(unsigned long long);
double genrand64_real1(void);
void do_initialize(void)
{ 
  lx=LX;
  ly=LY;
  isteps=ISTEPS;
  msteps=MSTEPS;
  nbins=NBINS;
  beta=BETA;
  nn=lx;
  nb=lx;
  spin=(int*)malloc((nn+1)*sizeof(int));
  bsites[0]=(int*)malloc((nb+1)*sizeof(int));
  bsites[1]=(int*)malloc((nb+1)*sizeof(int));
  
  int i;

  init_genrand64(SEED);
  for (i = 1; i <= nn; i += 1)
  {
    spin[i]=2*(int)(2*genrand64_real1())-1;
  }
  mm=nn/4;
  opstring=(int*)malloc(mm*sizeof(int));
  nh=0;
  for (i = 0; i < mm; i += 1)
  {
    opstring[i]=0;

  }
  frstspinop=(int*)malloc((nn+1)*sizeof(int));    
  lastspinop=(int*)malloc((nn+1)*sizeof(int));  
  vertexlist=(int*)malloc((4*mm)*sizeof(int));
  
  
  
  
  
}

