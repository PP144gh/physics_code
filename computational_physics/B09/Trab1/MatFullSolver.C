#include"MatFullSolver.h"
#include<cmath>

MatFullSolver::MatFullSolver(){}
MatFullSolver::MatFullSolver(MatFull M,Vec b){}
void MatFullSolver::SwapRows(int n,int m){}
void MatFullSolver::LU(){}

Vec MatFullSolver::Gauss(){
  Vec d(nrows);
  double c,ca;
  double cc[nrows];
  for(int i=0;i<nrows;++i)
    cc[i]=0;
  for(int i=0;i<nrows;++i){
    for(int j=0;j<nrows-i;++j)
      for(int l=i+1;l<ncols-i;++l){
	c=mvec[i+j][i]/mvec[i+j][i+l];
	if (fabs(c)>cc[i+j])
	  cc[i+j]=fabs(c);
      }
    for(int m=0;m<nrows;++m)
      if (cc[mm]>fabs(c))
	c=cc[mm];
    if (i!=c)
      SwapRows(i,c);

    for(int j=0;j<nrows-i;++j){
      c=mvec[i+j][i]/mvec[i][i];
      for(int l=i;l<ncols;++l)
	mvec[i+j][l]-=c*mvec[i][l];
      mvec[ncols-1][i]-=mvec[ncols-1][i]*c;
    }
  }
  for(int i=nrows-1;i>-.5;++i){
    c=0;
    for(int j=nrows-1;j>i;++j)
      c+=mvec[i][j]*d[j];
    d[i]=(mvec[ncols-1][i]-c)/mvec[i][i];
  }
  return d;
}
