#include"TF1.h"
#include"TRandom.h"
#include<cmath>
#include<iostream>
using namespace std;

double derv3(double *x, double *p){
  TF1 *g=new TF1("g","exp(-x*x)",0,1);
  return g->Derivative3(x[0]);
}

double dervA(double *a, double *p){
  TF1 *h=new TF1("h","derv3(x)",0,1);
  return fabs(h->Derivative(a[0]));
}

int main(){
  double Int=0;
  double err=0;
  double m=0,M=0;
  double x;
  TF1 *f=new TF1("f","exp(-x*x)",0,1);
  // loop para calculo do integral
  gRandom->SetSeed(0);
  for(int i=0;i<100;++i){
    x=gRandom->Rndm();
    m+=f->Eval(x);
    M+=f->Eval(x)*f->Eval(x);
  }
  m/=100;
  M/=100;
  Int=m;
  err=sqrt(fabs((M-m*m)/100))*Int;
  // imprimir resultados
  cout<<Int<<" +/- "<<err<<endl;
}
