#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<math.h>
#include"global.h"
void init_genrand64(unsigned long long);
double genrand64_real1(void);
int XOR(int a,int b)
{
  if(a%2==0)
    return a+1;
  else
    return a-1;
}

/*****************************/
/*   Diagoanal update        */
/*****************************/
void diagonal_update(void)
{ 
  int i,b,op,temp;
  double p;
  for (i = 0; i <= mm-1; i += 1)
  {
    op=opstring[i];
    if(op==0)
    {
      b=(int)(genrand64_real1()*nb) + 1;
      if(b>nb){b=nb;}
      int d1,d2;
      d1=bsites[0][b];
      d2=bsites[1][b];
/*      if(d1==0 && d2==0)*/
/*      {*/
/*        disp2("bsite 0 b",bsites[0][b],"bond b",b);*/
/*        disp2("bsite 1 b",bsites[1][b],"bond b",b);*/
/*      }*/
      if(spin[d1]!=spin[d2])
      {
        if(genrand64_real1()*(double)(mm-nh)<=aprob)
        {
          nh=nh+1;
          opstring[i]=2*b;
        }
      }
    }
    else if(op%2==0)
    {
      if(genrand64_real1()<=dprob*(double)(mm-nh + 1))
      {
        opstring[i]=0;
        nh=nh-1;
      }
    }
    else
    {
      b=op/2;
      spin[bsites[0][b]]=-spin[bsites[0][b]];
      spin[bsites[1][b]]=-spin[bsites[1][b]];
    }
  }
  
  
}

/*****************************/
/*   Operator loop update    */
/*****************************/
void link_vertices()
{
  int i,b,op,s1,s2,v0,v1,v2;
  for (i = 0; i <=nn ; i += 1)
  {
    frstspinop[i]=-1;
    lastspinop[i]=-1;
  }
  for (v0 = 0; v0 <= 4*mm-1; v0 += 4)
  {
    op=opstring[v0/4];
    if(op!=0)
    {
      b=op/2;
      s1=bsites[0][b];
      s2=bsites[1][b];
      v1=lastspinop[s1];
      v2=lastspinop[s2];
      if(v1!=-1)
      {
        vertexlist[v1]=v0;
        vertexlist[v0]=v1;
      }
      else
      {
        frstspinop[s1]=v0;
      }
      
      if(v2!=-1)
      {
        vertexlist[v2]=v0+1;
        vertexlist[v0+1]=v2;
      }
      else
      {
        frstspinop[s2]=v0+1;
      }
      lastspinop[s1]=v0+2;
      lastspinop[s2]=v0+3;
    }
    else
    {
      vertexlist[v0]=-1;
      vertexlist[v0+1]=-1;
      vertexlist[v0+2]=-1;
      vertexlist[v0+3]=-1;
    }
  }
  
  for (s1 = 1; s1 <=nn; s1 += 1)
  {
    v1=frstspinop[s1];
    if(v1!=-1)
    {
      v2=lastspinop[s1];
      vertexlist[v2]=v1;
      vertexlist[v1]=v2;
    }
  }
}
void loop_update(void)
{
 int  i,v0,v1,v2;
 
 for (v0 = 0; v0 <=4*mm-1; v0 += 2)
 {
   if(vertexlist[v0]<0)
   {
     continue;
   }
   
   v1=v0;
   if(genrand64_real1()<0.5)
   {
     while(1)
     {
      opstring[v1/4]=opstring[v1/4]^1;
      vertexlist[v1]=-2;
      v2=v1^1;
      v1=vertexlist[v2];
      vertexlist[v2]=-2;
      if ( v1==v0) break;
     }
   }
   else
   {
     while(1)
     {
       vertexlist[ v1]=-1;
          v2=v1^1;
          v1=vertexlist[v2];
          vertexlist[v2]=-1;
          if (v1==v0) break;
     }
   }
 }
 
 
 for(i=1;i<=nn;++i)
 {
   if(frstspinop[i]!=-1)
   {
     if(vertexlist[frstspinop[i]]==-2)
       {spin[i]=-spin[i];}
   }
   else
   {
     if(genrand64_real1()<0.5)
     { spin[i]=-spin[i];}
   }
 }
  
}
/*****************************/
/*   Adjust cut-off          */
/*****************************/
void adjust_cutoff(int step)
{
  int mmnew,i;
  int * string_copy;

/*  mmnew = 2*nh;*/
  mmnew = nh + (int) nh/3;

  if(mmnew<=mm)
  return;
  
  string_copy=(int*)malloc(mm*sizeof(int));
  for (i = 0; i < mm; i += 1)
  {
    string_copy[i]=opstring[i];

  }
  opstring=(int*)realloc(opstring,mmnew*sizeof(int));
  
  for (i = 0; i < mm; i += 1)
  {
    opstring[i]=string_copy[i];
  }
  for (i = mm; i < mmnew; i += 1)
  {
    opstring[i]=0;

  }
  free(string_copy);
  mm=mmnew;
  free(vertexlist);
  vertexlist=(int*)malloc(4*mm*sizeof(int));
  
  // write step and cut-off in a file
  char fname[200];
  sprintf(fname,"./outfiles/cutoff.dat");
  FILE *cutoff=fopen(fname,"a");
  fprintf(cutoff,"%d\n",mm);
  fclose(cutoff);
}
