#include"EqSolver.h"
#include<vector>
#include<iostream>
using namespace std;
int main(){
  float *a=new float[4];
  float *b=new float[5];
  float *c=new float[4];
  double *p=new double[5];
  /*  Definition of equation system  */
  c[0]=-10;c[1]=-10;c[2]=-5; c[3]=-5;
  b[0]=20; b[1]=20; b[2]=15; b[3]=10;b[4]=5;
  a[0]=-10;a[1]=-10;a[2]=-5;a[3]=-5;
  p[0]=100;p[1]=50;p[2]=100;p[3]=50;p[4]=100;
  EqSolver D;
  D.LUdecomposition3(a,b,c,5);//  LU Decomposition
  D.LUsolve3(a,b,c,5,p);//  LU solve
  for(int i=0;i<5;++i)
    cout<<"Deslocamento mola " << i+1 <<": "<< p[i]<<" mm" << endl;
  cout<<endl;
  delete[] a;
  delete[] b;
  delete[] c;
  delete[] p;
}
