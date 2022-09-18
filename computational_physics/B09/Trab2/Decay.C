#include"Element.h"
#include"PhysProcess.h"
#include"BetaDecay.h"
#include<iostream>
#include"cFCgraphics.h"
#include"TH2F.h"
#include"TRandom3.h"
#include"TF1.h"
#include<TROOT.h>
#include<TStyle.h>
#include<TColor.h>
#include"ctime"
#include<cmath>
#include"TGraph.h"
#include"TCanvas.h"
#include"TMath.h"
#include"AlphaDecay.h"
using namespace std;

    /*  Returns N(x[0])  */
double SpectrumB(double *x, double *p=NULL){
  BetaDecay B(1,1.1612);
  return B.Spectrum(x[0]);
}

    /*  Returns N(x[0])*eff(x[0])   */
double SpectrumEff(double *x, double *p=NULL){
  return sqrt(x[0]*x[0]+2*x[0]*0.511)*sqrt(1.1612-x[0])*(x[0]+0.511)/(1+exp(6-15*x[0]));
}

    /*  Returns x[0]*N(x[0])*eff(x[0])  */
double EnergyMedium(double *x, double *p=NULL){
  return x[0]*SpectrumEff(x,p);
}

    /*  Integral using Montes de Carlos Method  */
double* integrationMC(TF1 *f, int n, double a, double b){
  gRandom->SetSeed(0);
  double w=3.4995;
  double phi=asin(0.05)-0.3*w;
  double I=(1-0.05*.3)/(cos(0.3*w+phi)-cos(1.1612*w+phi));
  double l,u=0,x,q,z;
  double *h=new double[2];
    /*  Random Generator with Importance Sampling, using pdf f(x)=0.05 if 0 < x < 0.3, or sin(wx+phi)/I if 0.3<x<1.1612  */
  for (int i=0;i<n;){
    l=gRandom->Rndm();
    if(l<0.3*0.05)
      x=l/.05;
    else
      x=(acos(cos(w*.3+phi)-I*(l-0.3*0.05))-phi)/w;
    u=gRandom->Rndm();
    if(u<sin(w*x+phi)/f->Eval(x)){
      q+=f->Eval(x);
      z+=f->Eval(x)*f->Eval(x);
      ++i;
    }
  }
  q/=n;//  mean of f
  z/=n;//  mean of f*f
  h[0]=q*(b-a);//  Integral value
  h[1]=sqrt((z-q*q)/n)*(b-a)*h[0];//  Integral error
  return h;
}

    /*  Integral using Simpson Method  */
double* integrationSimpson(TF1 *f, int n,double a, double b){
  double x=a;
  double *z=new double[2];
  z[0]=0;
  double M,m;
  double h=(b-a)/n;//  Width of each slice
  for(int i=0;i<n/2;++i){
    M+=2*h*f->GetMaximum(x,x+2*h);
    m+=2*h*f->GetMinimum(x,x+2*h);
    z[0]+=h/3*(f->Eval(x)+4*f->Eval(x+h)+f->Eval(x+2*h));
    x+=2*h;
  }
  if (n%2==1)//  Integral of last slice
    z[0]+=h/12*(-f->Eval(b-2*h)+8*f->Eval(b-h)+5*f->Eval(b));
  z[1]=(M-m)/2;//  Integral error
  return z;
}

int main(){
    /*  Set up of Elements Bi and Po  */
  Element X("Bi",210,83,100);
  Element Y("Po",210,84,0);
  double Dia=24*60*60;//  Converts time from days to seconds
  BetaDecay B(5.012*Dia,1.1612);
  AlphaDecay C(138.376*Dia,5.40746);
  PhysProcess *pb=&B;
  PhysProcess *pc=&C;
  pb->SetName("Decaimento Beta");
  pc->SetName("Decaimento Alpha");
  X.SetPhysProcess(pb);
  Y.SetPhysProcess(pc);
  cout<<endl;

    /*  Exercise 1  */
  int a[3][300],b[3][300],c[3][300],j;
  double p=0,d;
  int u=100;
  TGraph **gx=new TGraph*[3];
  TGraph **gy=new TGraph*[3];

    /*  Cicle for the 3 inicial conditions  */
  for(int mm=0;mm<3;++mm){
    u*=10;
    X.SetN(u);
    cout<<"N inicial: "<<X.GetN()<<endl<<endl;
    cout<<0<<" ---> Bi: "<<X.GetN()<<"  |  Po: "<<0<<endl;
    a[mm][0]=X.GetN();
    b[mm][0]=0;
    c[mm][0]=0;
      /*  Simulation of the Decay for both elements  */
    for(int i=1;i<300;++i){
      c[mm][i]=i;
      a[mm][i]=B.DecayRate(X.GetN(),Dia);
      Y.SetN(Y.GetN()+a[mm][i]);
      a[mm][i]=X.GetN()-a[mm][i];
      d=C.DecayRate(Y.GetN(),Dia);
      if (d>p){//  Determination of the largest Alpha Decay
	p=d;
	j=i;
      }
      b[mm][i]=Y.GetN()-d;
      if (i<11)
	cout<<i<<" ---> Bi: "<<a[mm][i]<<"  |  Po: "<<b[mm][i]<<endl;
      X.SetN(a[mm][i]);
      Y.SetN(b[mm][i]);
    }
    gx[mm]=new TGraph(20,c[mm],a[mm]);//  Setting up Graphics for Beta Decay
    gx[mm]->SetMarkerStyle(5);
  gx[mm]->SetMarkerColor(kTeal-6);

    gx[mm]->SetTitle("Decay of Bi");
    gx[mm]->GetXaxis()->SetTitle("t (days)");
    gx[mm]->GetYaxis()->SetTitle("N");
    gy[mm]=new TGraph(300,c[mm],b[mm]);//  Setting up Graphics for Alpha Decay
    gy[mm]->SetTitle("Decay of Po");
    gy[mm]->GetXaxis()->SetTitle("t (days)");
    gy[mm]->GetYaxis()->SetTitle("N");
    cout<<endl<<"------------------------------------"<<endl<<endl;
  }

    /*  Exercise 2  */
  cout<<endl;
  for (int i=0;i<3;++i)
    cout<<"Para N inicial "<<a[i][0]<<" tem-se "<<a[i][2]<<" atomos de bismuto ao fim de 2 dias e "<<b[i][2]<<" atomos de polonio"<<endl<<endl;

  TF1 **f=new TF1*[3];//  Analitycal solutions for Beta Decay
  f[0]=new TF1("f0","[0]*exp(-[1]*x)",0,20);
  f[1]=new TF1("f1","[0]*exp(-[1]*x)",0,20);
  f[2]=new TF1("f2","[0]*exp(-[1]*x)",0,20);
  TF1 **g=new TF1*[3];//  Analitycal solutions for Alpha Decay
  g[0]=new TF1("g0","[0]*[1]/([2]-[1])*(exp([1]*x)-exp([2]*x))",0,300);
  g[1]=new TF1("g1","[0]*[1]/([2]-[1])*(exp([1]*x)-exp([2]*x))",0,300);
  g[2]=new TF1("g2","[0]*[1]/([2]-[1])*(exp([1]*x)-exp([2]*x))",0,300);

  f[0]->SetParameter(0,1000);
  f[0]->SetParameter(1,log(2)/(B.GetT12()/Dia));
  f[1]->SetParameter(0,10000);
  f[1]->SetParameter(1,log(2)/(B.GetT12()/Dia));
  f[2]->SetParameter(0,100000);
  f[2]->SetParameter(1,log(2)/(B.GetT12()/Dia));
  for(int i=0;i<3;++i){
    f[i]->SetTitle("Analytical decay of Bi");
    f[i]->GetXaxis()->SetTitle("t (days)");
    f[i]->GetYaxis()->SetTitle("N");
  }

  g[0]->SetParameter(0,1000);
  g[0]->SetParameter(1,-log(2)/(B.GetT12()/Dia));
  g[0]->SetParameter(2,-log(2)/(C.GetT12()/Dia));
  g[1]->SetParameter(0,10000);
  g[1]->SetParameter(1,-log(2)/(B.GetT12()/Dia));
  g[1]->SetParameter(2,-log(2)/(C.GetT12()/Dia));
  g[2]->SetParameter(0,100000);
  g[2]->SetParameter(1,-log(2)/(B.GetT12()/Dia));
  g[2]->SetParameter(2,-log(2)/(C.GetT12()/Dia));
  for(int i=0;i<3;++i){
    g[i]->SetTitle("Analytical decay of Po");
    g[i]->GetXaxis()->SetTitle("t (days)");
    g[i]->GetYaxis()->SetTitle("N");
  }

    /*  Exercise 3  */
  cout<<endl<<"O instante em que se produz mais particulas alfa e' o "<<j<<endl<<endl;

    /*  Exercise 4  */
  TH1F *h=new TH1F("h","h",100,0,1.2);
  TF1 *fg=new TF1("fg",SpectrumB,0,1.1612,0);
  gRandom->SetSeed(0);
  double z,pz,y;
  double pmax=fg->GetMaximum(0,1.612);
    /*  Generation of randoms using Acceptance Rejection Method  */
  for(int i=0;i<10000;){
    z=gRandom->Rndm()*1.1612;
    pz=fg->Eval(z);
    y=gRandom->Rndm();
    if (y<=pz/pmax){
      h->Fill(z);
      ++i;
    }
  }
  h->SetTitle("Kinetic Energy of Electrons");
  h->GetXaxis()->SetTitle("Te (MeV)");
  h->GetYaxis()->SetTitle("N");
  fg->SetTitle("Teorical Kinetic Energy of Electrons");
  fg->GetXaxis()->SetTitle("Te (MeV)");
  fg->GetYaxis()->SetTitle("N");

    /*  Exercise 5  */
  TF1 *gf=new TF1("gf",SpectrumEff,0,1.1612,0);
  double* iS=integrationSimpson(gf,2300,0,1.1612);//  Calcule of Simpson Integral
  double* iMC=integrationMC(gf,100000,0,1.1612);//  Calcule of Monte Carlo Integral
  cout<<endl<<"Simpson: "<<iS[0]<<" com erro de "<<iS[1]<<endl<<"MC: "<<iMC[0]<<" com erro de "<<iMC[1]<<endl<<endl;

    /*  Exercise 6  */
  TF1 *ppp=new TF1("ppp",EnergyMedium,0,1.1612,0);
  double iEM=integrationSimpson(ppp,500,0,1.1612)[0];//  Calcule of Integral of N(Te)*eff(Te)*Te
  cout<<"Valor medio da Energia do Eletrao Detetavel: "<<endl<<iEM/1.1612<<" MeV" <<endl<<endl;

    /*  Drawing of Graphics  */
  cFCgraphics D;
  D.AddObject(gx[0]);
  D.AddObject(f[0]);
  D.AddObject(gx[1]);
  D.AddObject(f[1]);
  D.AddObject(gx[2]);
  D.AddObject(f[2]);  
  D.AddObject(gy[0]);
  D.AddObject(g[0]);
  D.AddObject(gy[1]);
  D.AddObject(g[1]);
  D.AddObject(gy[2]);
  D.AddObject(g[2]);
  D.AddObject(h);
  D.AddObject(fg);
  D.Draw();
}
