#include "cFCgraphics.h"
#include "TF2.h"
#include <iostream>
#include "TGraph.h"

using namespace std;

class ODEsolver
{
  public:
    ODEsolver(TF2*,double,double,double);
    double IterRK4(double,double);
  private:
    TF2 *f;
    double ti;
    double yi;
    double step;
};

ODEsolver::ODEsolver(TF2* fa, double tia, double yia, double stepa)
{
  ti=tia;
  yi=yia;
  step=stepa;
  f=fa;
}

double ODEsolver::IterRK4(double tn, double yn)
{
  double k1 = f->Eval(tn,yn);
  double k2 = f->Eval(tn+step/2,yn+step/2*k1);
  double k3 = f->Eval(tn+step/2,yn+step/2*k2);
  double k4 = f->Eval(tn+step,yn+step*k3);

  double yns = yn + step/6*(k1+2*k2+2*k3+k4);
  return yns;
}

int main()
{
  double y0=0;
  double x0=0;
  double g=10;
  double t0=0;
  double vx0=1;
  double vy0=1;

  double h=0.001;
  TF2 *f11 = new TF2("f11","-[1]*[0]",0,10,0,10);
  TF2* f12= new TF2("f12","[0]",0,10,0,3000);
  ODEsolver ODE11(f11,t0,vx0,h);
  ODEsolver ODE12(f12,t0,x0,h);
  TGraph *GRK411 = new TGraph(21);
  GRK411->SetMarkerStyle(6);
  GRK411->SetTitle("Velocidade em x;t;m/s");
  TGraph *GRK412 = new TGraph(21);
  GRK412->SetMarkerStyle(6);
 GRK412->SetTitle("Posiçao x;t;x");

 

  double yRK411=vx0;
  double yRK412=x0;
 bool r=0;
 bool t2=0;
  GRK411->SetPoint(0,t0,vx0);
  GRK412->SetPoint(0,t0,x0);

  //K
  double k=1;
  f11->SetParameter(1,k);

 TF2 *f21 = new TF2("f21","-[2]-[1]*[0]",0,10,0,10);
  TF2* f22= new TF2("f22","[0]",0,10,0,3000);
  ODEsolver ODE21(f21,t0,vy0,h);
  ODEsolver ODE22(f22,t0,y0,h);
  TGraph *GRK421 = new TGraph(21);
  GRK421->SetMarkerStyle(6);
  GRK421->SetTitle("Velocidade em y;t;m/s");
  TGraph *GRK422 = new TGraph(21);
  GRK422->SetMarkerStyle(6);
  GRK422->SetTitle("Posiçao y;t;y");

  f21->SetParameter(2,g);
 
 TGraph *GRK4 = new TGraph(21);
  GRK4->SetMarkerStyle(6);
  GRK4->SetTitle("Posiçao ;x;y");
 GRK4->SetMarkerColor(kGreen);
  double yRK421=vy0;
  double yRK422=y0;
  r=0;
  t2=0;
  GRK421->SetPoint(0,t0,vy0);
  GRK422->SetPoint(0,t0,y0);
  GRK4->SetPoint(0,x0,y0);



  for (double i=0; i<300; i++)
    {
      f11->SetParameter(0,yRK411);
      yRK411=ODE11.IterRK4(t0+i*h,yRK411);
     
      GRK411->SetPoint(i+1,t0+(i+1)*h,yRK411);
      f12->SetParameter(0,yRK411);
      yRK412=ODE12.IterRK4(t0+i*h,yRK412);
      GRK412->SetPoint(i+1,t0+(i+1)*h,yRK412);
  if((r==1) && (t2==0)) {
	cout <<"*****************************"<< endl;
    cout <<"espaço percorrido " <<sqrt(yRK412*yRK412+yRK422*yRK422) <<"m "<< endl;
	cout <<"*****************************"<< endl;
	t2=1;
      }
      f11->SetParameter(0,yRK421);
      yRK421=ODE21.IterRK4(t0+i*h,yRK421);
     
      GRK421->SetPoint(i+1,t0+(i+1)*h,yRK421);
      f22->SetParameter(0,yRK421);
      yRK422=ODE22.IterRK4(t0+i*h,yRK422);
      if((yRK422<=0) && (r==0)){
	cout <<"*****************************"<< endl;
	cout <<"tempo queda "<< t0+i*h<<"s" << endl;
	cout <<"*****************************"<< endl;
	r=1;
      }
      GRK422->SetPoint(i+1,t0+(i+1)*h,yRK422);
      GRK4->SetPoint(i+1,yRK412,yRK422);
    }
  cFCgraphics D;
  D.AddObject(GRK4);
  D.Draw("all");
  D.Print("Prob4_trajectorias.pdf");

}
