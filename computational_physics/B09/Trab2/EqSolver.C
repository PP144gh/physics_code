#include"EqSolver.h"
#include "Vec.h"
#include<cmath>

    /*  Default Constructor  */
EqSolver::EqSolver(){
  m=new double *[0];
  m[0]=new double;
  b=new double;
  m[0][0]=1;
  b[0]=0;
  size=1;
}

    /*  Constructor  */
EqSolver::EqSolver(double **M, double *B, int n){
  size=n;
  m=new double*[size];
  for(int i=0;i<size;++i)
    m[i]=new double[size];
  b=new double[size];
  for(int i=0;i<size;++i){
    b[i]=B[i];
    for(int j=0;j<size;++j)
      m[i][j]=M[i][j];
  }
}

    /*  Prints Augmented Matrix  */
void EqSolver::Print(){
  for(int i=0;i<size;++i){
    for(int j=0;j<size;++j)
      cout<<m[i][j]<<" "<<flush;
    cout<<"| "<<b[i]<<endl;
  }
}

    /*  Swap Rows p with q  */
void EqSolver::SwapRows(int p, int q){
  double a;
  a=b[p];
  b[p]=b[q];
  b[q]=a;
  double *f=m[p];
  m[p]=m[q];
  m[q]=f;
}

    /*  LU decomposition of general matrix  */
void EqSolver::LU(){
  double c;
  int aa;
  Vec d(size);
  double h[size];
  for(int i=0;i<size;++i){
    h[i]=0;
    b[i]=i;
  }
    /*  Gauss Elimination  */
  for(int i=0;i<size-1;++i){
    for(int j=i;j<size;++j)
      for(int l=i;l<size;++l){
 	c=m[j][i]/m[j][l];
 	if (fabs(c)>h[j])
 	  h[j]=c;
      }
    c=h[i];
    aa=i;
    for(int j=i;j<size;++j)
      if(h[j]>c){
 	c=h[j];
 	aa=j;
      }
    if(aa!=i)
      SwapRows(i,aa);
    for(int j=i+1;j<size;++j){
      c=m[j][i]/m[i][i];
      m[j][i]=c;//  L matrix
      for(int l=i+1;l<size;++l)
       	m[j][l]-=c*m[i][l];//  U matrix
    }
  }
}

    /*  Solving LU=b for general matrix  */
Vec EqSolver::LU_resolve(Vec c){
   Vec dd=c;
   double u=0;
     /*  Changes c to compensate swaping rows during LU decomposition  */
   for(int i=0;i<c.Size();++i){
     if(b[i]!=i){
       u=c[i];
       c.SetEntrie(i,c[b[i]]);
       c.SetEntrie(b[i],u);
     }
     b[(int) b[i]]=b[i];
   }
     /*  Ly=b  */ 
   for(int i=0;i<c.Size();++i){
     u=0;
     for(int j=0;j<i;++j)
       u+=m[i][j]*dd[j];
     dd.SetEntrie(i,c[i]-u);
   }
     /*  Ux=y  */
   for(int i=c.Size()-1;i>-.5;--i){
     u=0;
     for(int j=c.Size()-1;j>i;--j)
       u+=m[i][j]*dd[j];
     dd.SetEntrie(i,(dd[i]-u)/m[i][i]);
   }
   return dd;
 }

    /*  LU decomposition for triadiagonal matrix  */
void EqSolver::LUdecomposition3(float *e, float *f, float *g, int n){
  for(int i=1;i<n;++i){
    e[i-1]=e[i-1]/f[i-1];
    f[i]-=g[i-1]*e[i-1];
  }
}

    /*  LU decomposition for triadiagonal matrix (exercise 3)  */
void EqSolver::LUdecomposition3d(double *e, double *f, double *g, int n){
  for(int i=1;i<n;++i){
    e[i-1]=e[i-1]/f[i-1];
    f[i]-=g[i-1]*e[i-1];
  }
}

    /*  LU=b solving for triadiagonal matrix  */
void EqSolver::LUsolve3(float *e, float *f, float *g, int n, double* p){
  for(int i=1;i<n;++i)//  Ly=b
    p[i]+=-e[i-1]*p[i-1];
  p[n-1]=p[n-1]/f[n-1];//  Ux=y
  for(int i=n-2;i>-.5;--i)
    p[i]=(p[i]-g[i]*p[i+1])/f[i];
}

    /*  LU=b solving for triadiagonal matrix (exercise 3)  */
void EqSolver::LUsolve3d(double *e, double *f, double *g, int n, double* p){
  for(int i=1;i<n;++i)//  Ly=b
    p[i]+=-e[i-1]*p[i-1];
  p[n-1]=p[n-1]/f[n-1];//  Ux=y
  for(int i=n-2;i>-.5;--i)
    p[i]=(p[i]-g[i]*p[i+1])/f[i];
}

    /*  Gauss Elimination, returning result  */
Vec EqSolver::Gauss(){
  double c;
  int aa;
  Vec d(size);
  double h[size];
  for(int i=0;i<size;++i)
    h[i]=0;

  for(int i=0;i<size-1;++i){
    for(int j=i;j<size;++j)
      for(int l=i;l<size;++l){//  Choosing Pivot
 	c=m[j][i]/m[j][l];
 	if (fabs(c)>h[j])
 	  h[j]=c;
      }
    c=h[i];
    aa=i;
    for(int j=i;j<size;++j)
      if(h[j]>c){
 	c=h[j];
 	aa=j;
      }
    if(aa!=i)
      SwapRows(i,aa);//  Swaping Rows to eliminate with best pivot
      /*  Eliminate lines below using row i  */
    for(int j=i+1;j<size;++j){
      c=m[j][i]/m[i][i];
      for(int l=i;l<size;++l)
       	m[j][l]-=c*m[i][l];
      b[j]-=c*b[i];
    }
  }
    /*  Solving system  Ux=b'  */
  for(int i=size-1;i>-1;--i){
    c=0;
    for(int j=size-1;j>i;--j)
      c+=m[i][j]*d[j];
    d.SetEntrie(i,(b[i]-c)/m[i][i]);
  }
  return d;
}
