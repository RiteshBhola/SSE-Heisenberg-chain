#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<math.h>
#include<unistd.h>
#include"mt19937ar.h"
#include"global.h"


int neighbor(int site,int dir);
void do_initialize(void);
void diagonal_update(void);
void link_vertices();
void loop_update(void);
void adjust_cutoff(int);
void allocate_observ(void);
void measure(void);
void write_stats();

void make_lattice(void);
void free_all(void);
int main()
{
  int i,j;
  do_initialize();
  make_lattice();
  
  aprob=0.5*(double)(beta*nb);
  dprob=2.0/((double)(beta*nb));
  fdisp2("aprob",aprob,"dprob",dprob);
  /*warm up*/

  for (i = 0; i < isteps; i += 1)
  { //disp1("warm up step i ",i);
    diagonal_update();
    link_vertices();
    loop_update();
    
/*    disp("off diagonal update done");*/
  
  adjust_cutoff(i);
/*    disp("cut off adjusted");*/
  }
  printf("Equilibriation done.\nCut off M =%d\n",mm);
  char fname1[200];
  sprintf(fname1,"./outfiles2/opstring_L%d_beta%d.dat",lx,(int)beta);
  FILE *opstringf=fopen(fname1,"a");
  for (j = 0; j < nbins; j += 1)
  {
    for (i = 0; i < msteps; i += 1)
    {
      diagonal_update();
      link_vertices();
      loop_update();
      
      fprintf(opstringf,"%d %d %d %d\n",i,nh,mm,nh*nh);

      //measure();
    }
      //write_stats();
      
      
  }
  fclose(opstringf);
  free_all();
  return 0;
}
