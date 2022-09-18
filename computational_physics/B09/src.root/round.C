#include"TH1.h"
#include"TGraph.h"
#include<TROOT.h>
#include<cmath.h>

static double RoundOffError (int i){
  float p=sqrt(i);
  double q=sqrt(i);
  return q-p;
}

TGraph* RoundOffErrorG (int imin, int imax){
  double *p=new double[imax-imin];
  double *q=new double[imax-imin];
  double r;
  float s;
  for(int i=imin;i<imax;++i){
    q[i]=i;
    r=sqrt(i);
    s=sqrt(i);
    p[i]=r-s;
  }
  TGraph *G=new TGraph("G",imax-imin,q,p);
  return G;
}

TH1D* RoundOffErrorH(int imin, int imax){
  TH1D *H=new TH1D("H","H",10,imin,imax);
  double p;
  float q;
  for(int i=imin;i<imax;++i){
    p=sqrt(i);
    q=sqrt(i);
    H->Fill(p-q);
  }
  return H;
}
