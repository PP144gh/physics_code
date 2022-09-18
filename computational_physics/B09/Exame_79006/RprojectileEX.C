#include"cFCgraphics.h"
#include"TGraph.h"
#include"TAxis.h"
#include"TPolyLine3D.h"
#include"TF3.h"
#include<cmath>
#include<iostream>
#define g 10
#define m 100
using namespace std;

//  calculo da trajetoria do corpo e energia mecanica em funcao do tempo
vector<double>* Trajectory(double xi, double yi, double vxi, double vyi, double k, double h){
  vector<double> *z=new vector<double> [4];
  double xk1,xk2,xk3,xk4;
  double yk1,yk2,yk3,yk4;
  double vxk1,vxk2,vxk3,vxk4;
  double vyk1,vyk2,vyk3,vyk4;
  z[0].push_back(xi);
  z[1].push_back(yi);
  z[2].push_back(vxi);
  z[3].push_back(vyi);
  int j=1;
  for(int i=0;j!=0;++i){
    xk1=h*z[2][i];
    yk1=h*z[3][i];
    vxk1=-h*k*z[2][i];
    vyk1=-h*k*z[3][i]-g*h;

    xk2=h*(z[2][i]+xk1/2);
    yk2=h*(z[3][i]+yk1/2);
    vxk2=-h*k*(z[2][i]+vxk1/2);
    vyk2=-h*k*(z[3][i]+vyk1/2)-g*h;

    xk3=h*(z[2][i]+xk2/2);
    yk3=h*(z[3][i]+yk2/2);
    vxk3=-h*k*(z[2][i]+vxk2/2);
    vyk3=-h*k*(z[3][i]+vyk2/2)-g*h;

    xk4=h*(z[2][i]+xk3);
    yk4=h*(z[3][i]+yk3);
    vxk4=-h*k*(z[2][i]+vxk3);
    vyk4=-h*k*(z[3][i]+vyk3)-g*h;

    z[0].push_back(z[0][i]+(xk1+2*xk2+2*xk3+xk4)/6);
    z[1].push_back(z[1][i]+(yk1+2*yk2+2*yk3+yk4)/6);
    z[2].push_back(z[2][i]+(vxk1+2*vxk2+2*vxk3+vxk4)/6);
    z[3].push_back(z[3][i]+(vyk1+2*vyk2+2*vyk3+vyk4)/6);
    if (z[1][i+1]<0)
      j=0;
  }
  z[0].pop_back();
  z[1].pop_back();
  z[2].pop_back();
  for(unsigned int i=0;i<z[0].size();++i){
    z[3][i]=m*g*z[1][i]+0.5*m*(z[3][i]*z[3][i]+z[2][i]*z[2][i]);
    z[2][i]=i*h;
  }
  return z;
}

int main(){
  vector<double> *v1=Trajectory(0,0,1,1,0,0.001);
  double **mn=new double*[4];
  for(int i=0;i<4;++i)
    mn[i]=new double[v1[0].size()];
  double s1=0;//  espaco percorrido pelo corpo 1
  for(unsigned int i=0;i<v1[0].size();++i){
    mn[0][i]=v1[0][i];
    mn[1][i]=v1[1][i];
    mn[2][i]=v1[2][i];
    mn[3][i]=v1[3][i];
    if(i!=0)
      s1+=sqrt(pow(v1[0][i]-v1[0][i-1],2) + pow(v1[1][i]-v1[1][i-1],2));
  }
  vector<double> *v2=Trajectory(0,0,1,1,0.2,0.001);
  double **my=new double*[4];
  for(int i=0;i<4;++i)
    my[i]=new double[v2[0].size()];
  double s2=0;//  espaco percorrido pelo corpo 2
  for(unsigned int i=0;i<v2[0].size();++i){
    my[0][i]=v2[0][i];
    my[1][i]=v2[1][i];
    my[2][i]=v2[2][i];
    my[3][i]=v2[3][i];
    if(i!=0)
      s2+=sqrt(pow(v1[0][i]-v1[0][i-1],2) + pow(v1[1][i]-v1[1][i-1],2));
  }
  vector<double> *v3=Trajectory(0,0,1,1,1,0.001);
  double **mx=new double*[4];
  for(int i=0;i<4;++i)
    mx[i]=new double[v3[0].size()];
  double s3=0;//  espaco percorrido pelo corpo 3
  for(unsigned int i=0;i<v3[0].size();++i){
    mx[0][i]=v3[0][i];
    mx[1][i]=v3[1][i];
    mx[2][i]=v3[2][i];
    mx[3][i]=v3[3][i];
    if(i!=0)
      s3+=sqrt(pow(v1[0][i]-v1[0][i-1],2) + pow(v1[1][i]-v1[1][i-1],2));
  }
  vector<double> *v4=Trajectory(0,0,1,1,5,0.001);
  double **mz=new double*[4];
  for(int i=0;i<4;++i)
    mz[i]=new double[v4[0].size()];
  double s4=0;//  espaco percorrido pelo corpo 4
  for(unsigned int i=0;i<v4[0].size();++i){
    mz[0][i]=v4[0][i];
    mz[1][i]=v4[1][i];
    mz[2][i]=v4[2][i];
    mz[3][i]=v4[3][i];
    if(i!=0)
      s4+=sqrt(pow(v1[0][i]-v1[0][i-1],2) + pow(v1[1][i]-v1[1][i-1],2));
  }
  vector<double> *v5=Trajectory(0,0,1,1,10,0.001);
  double **mk=new double*[4];
  for(int i=0;i<4;++i)
    mk[i]=new double[v5[0].size()];
  double s5=0;//  espaco percorrido pelo corpo 5
  for(unsigned int i=0;i<v5[0].size();++i){
    mk[0][i]=v5[0][i];
    mk[1][i]=v5[1][i];
    mk[2][i]=v5[2][i];
    mk[3][i]=v5[3][i];
    if(i!=0)
      s5+=sqrt(pow(v1[0][i]-v1[0][i-1],2) + pow(v1[1][i]-v1[1][i-1],2));
  }  

  //  coloca-se a posiçao em y a zero para todos os pontos
  double **a=new double*[5];
  a[0]=new double[v1[0].size()];
  for(unsigned int i=0;i<v1[0].size();++i)
    a[0][i]=0;
  a[1]=new double[v2[0].size()];
  for(unsigned int i=0;i<v2[0].size();++i)
    a[1][i]=0;
  a[2]=new double[v3[0].size()];
  for(unsigned int i=0;i<v3[0].size();++i)
    a[2][i]=0;
  a[3]=new double[v4[0].size()];
  for(unsigned int i=0;i<v4[0].size();++i)
    a[3][i]=0;
  a[4]=new double[v5[0].size()];
  for(unsigned int i=0;i<v5[0].size();++i)
  a[4][i]=0;

  //  desenho das trajetorias
  TPolyLine3D *G1=new TPolyLine3D(v1[0].size(),mn[0],a[0],mn[1]);
  TPolyLine3D *G2=new TPolyLine3D(v2[0].size(),my[0],a[1],my[1]);
  TPolyLine3D *G3=new TPolyLine3D(v3[0].size(),mx[0],a[2],mx[1]);
  TPolyLine3D *G4=new TPolyLine3D(v4[0].size(),mz[0],a[3],mz[1]);
  TPolyLine3D *G5=new TPolyLine3D(v5[0].size(),mk[0],a[4],mk[1]);
  G2->SetLineColor(kRed);
  G3->SetLineColor(kGreen);
  G4->SetLineColor(kBlue);
  G5->SetLineColor(kBlue);
  {
    TF3 *H=new TF3("H","x*x+y*y+z*z+1",0,0.2,0,0.1,0,0.15);
    H->SetTitle("Trajetoria");
    cFCgraphics E;
    E.CreatePad("pad");
    E.AddObject(H,"pad");
    E.AddObject(G1,"pad");
    E.AddObject(G2,"pad","same");
    E.AddObject(G3,"pad","same");
    E.AddObject(G4,"pad","same");
    E.AddObject(G5,"pad","same");
    E.DumpPad("pad");
    E.DrawPad("pad");
    E.Print("Prob4_trajectorias.pdf");
  }

  //  desenho da energia mecanica em funcao do tempo
  TPolyLine3D *T1=new TPolyLine3D(v1[0].size(),mn[2],a[0],mn[3]);
  TPolyLine3D *T2=new TPolyLine3D(v2[0].size(),my[2],a[1],my[3]);
  TPolyLine3D *T3=new TPolyLine3D(v3[0].size(),mx[2],a[2],mx[3]);
  TPolyLine3D *T4=new TPolyLine3D(v4[0].size(),mz[2],a[3],mz[3]);
  TPolyLine3D *T5=new TPolyLine3D(v5[0].size(),mk[2],a[4],mk[3]);
  T2->SetLineColor(kRed);
  T3->SetLineColor(kGreen);
  T4->SetLineColor(kBlue);
  T5->SetLineColor(kBlue);
  {
    TF3 *H=new TF3("H","x*x+y*y+z*z+1",0,0.25,0,0.1,0,150);
    H->SetTitle("Trajetoria");
    cFCgraphics E;
    E.CreatePad("Pad");
    E.AddObject(H,"Pad");
    E.AddObject(T1,"Pad");
    E.AddObject(T2,"Pad","same");
    E.AddObject(T3,"Pad","same");
    E.AddObject(T4,"Pad","same");
    E.AddObject(T5,"Pad","same");
    E.DumpPad("Pad");
    E.DrawPad("Pad");
    E.Print("Prob4_energia.pdf");
  }

  //  indicaçao do tempo de voo e espaco percorrido
  cout<<"Corpo 1"<<endl<<"tempo: "<<mn[2][v1[0].size()-1]<<"s    "<<"espaco: "<<s1<<"m"<<endl<<endl;
  cout<<"Corpo 2"<<endl<<"tempo: "<<my[2][v2[0].size()-1]<<"s  "<<"espaco: "<<s2<<"m"<<endl<<endl;
  cout<<"Corpo 3"<<endl<<"tempo: "<<mx[2][v3[0].size()-1]<<"s  "<<"espaco: "<<s3<<"m"<<endl<<endl;
  cout<<"Corpo 4"<<endl<<"tempo: "<<mz[2][v4[0].size()-1]<<"s  "<<"espaco: "<<s4<<"m"<<endl<<endl;
  cout<<"Corpo 5"<<endl<<"tempo: "<<mk[2][v5[0].size()-1]<<"s   "<<"espaco: "<<s5<<"m"<<endl<<endl;
}
