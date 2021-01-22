#include<stdlib.h>
#include"global.h"
void free_all(void)
{
  free(spin);
  free(bsites[0]);
  free(bsites[1]);
  free(opstring);
  free(frstspinop);
  free(lastspinop);
  free(vertexlist);
  
}
