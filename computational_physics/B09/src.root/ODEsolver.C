#include"EDOsolver.h"

ODEsolver::ODEsolver(TF1 *F=NULL, double TI=0, double YI=0, double STEP=0){
  f=F;
  ti=TI;
  yi=YI;
  step=STEP;
}

void ODEsolver::SetTi(double TI){
  ti=TI;
  return NULL;
}

void ODEsolver::SetYi(double YI){
  yi=YI;
  return NULL;
}

double ODEsolver::IterEuler(){
  double yn=0;
  f->SetParameter(0,ti);
  yn=yi+step*f(yi);
  return yn;
}

double ODEsolver::IterPredictorCorrector(){
  double yn=0;
  f->SetParameter(0,ti);
  double a=f(yi);
  yn=yi+step*a;
  f->SetParameter(0,ti+step);
  yn=yi+step/2*(a+f(yn));
  return yn;
}

double ODEsolver::RK2(){
  double yn=0,a=0;
  f->SetParameter(0,ti);
  a=f(yi);
  f->SetParameter(0,ti+step/2);
  yn=yi+step/2*a;
  yn=yi+step*f(yn);
  return yn;
}

double EDOsolver::RK4(){
  double yn=0;
  f->SetParameter(0,ti);
  double y1=step*f(yi);
  f->SetParameter(0,ti+step/2);
  double y2=step*f(yi+y1/2);
  double y3=step*f(yi+y2/2);
  f->SetParameter(0,ti+step);
  double y4=step*f(yi+y3);
  yn=yi+(y1+2y2+2y3+y4)/6;
  return yn;
}
 
