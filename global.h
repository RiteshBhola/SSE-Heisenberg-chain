#include"/home/ritesh/display.h"
#define LX 150ll
#define LY 1
#define SEED 1520
#define My_PI 3.1415926535897
#define NBINS 1
#define BETA  256
#define MSTEPS 2000000
#define ISTEPS 4000
#define CHAIN

/* configuration variables */
int lx,ly;
int lxby2;
int nn;
int nb;
int nh;
int mm;
int nbins;
int msteps;
int isteps;

int* spin;
int* bsites[2];
int* opstring;
int* frstspinop;
int* lastspinop;
int* vertexlist;

double beta;
double aprob;
double dprob;

/*Measurement variables*/
double enrg1;
double enrg2;
double amag1;
double amag2;
double asusc;
double stiff;
double ususc;
double* data1; /*size is seven*/
double* data2;





