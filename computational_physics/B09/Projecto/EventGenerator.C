#include<cstdlib>
#include<iostream>
#include"EventGenerator.h"
#include <string>
#include <vector>
#include "TRandom3.h"
#include "TStyle.h"
#include "TROOT.h"
#include <cmath>
#include "cFCgraphics.h"
#include <ctime>
#include <fstream>
#include <sstream>
#define PI 3.14159265358979323846264338327950288419716939937510582
using namespace std;



//constructor
EventGenerator::EventGenerator(int a,int b){
  Npix=a;
  Pixwidth=b;
  x=0;
  y=0;
  beta =1;
  N0=0;
  tempo=0;
  betaR=0;
  errob=0;
  RR=0;
  eRR=0;
  maxx=0;
  minx=0;
  maxy=0;
  miny=0;
  xR=0;
  yR=0;
  epos=0;
  ppx=0;
  ppy=0;
  int k=0;
  static int cc=0;
  cc+=1;
  char*s=new char [1];
  sprintf(s, "%d", cc); //evita warnings memory leak
  int tmp=sqrt(Npix); //assumindo uma matriz de pixeis sempre quadrada  
  Pixmat=new TH2F(s,"PixelMatrix",tmp,0,tmp*Pixwidth,tmp,0,tmp*Pixwidth);
  PixID= new int[Npix];
  //so regista os pixeis visiveis no ecra, Npix, explicado melhor em detalhe no relatorio. Associa a cada um deles o valor de GetBin para facilitar metodos posteriores.
  while(k<tmp) {
    for(int i=k*tmp; i<(k+1)*tmp; ++i) {
      PixID[i]=tmp+3+i+2*k;
    }
    ++k; }
  PID.reserve(5);
}

EventGenerator::~EventGenerator(){
  delete[] PixID;
}

//Necessario definir para usar o objeto dentro da funçao makeevent
EventGenerator::EventGenerator( const EventGenerator& o){

  Npix=o.Npix;
  Pixwidth=o.Pixwidth;
  x=o.x;
  y=o.y;
  beta=o.beta;
  N0=o.N0; tempo=0;
  betaR=o.betaR;
  errob=o.errob;
  RR=o.RR;
  eRR=o.eRR;
  maxx=o.maxx;
  minx=o.minx;
  maxy=o.maxy;
  miny=o.miny;
  xR=o.xR;
  yR=o.yR;
  epos=o.epos;
  ppx=o.ppx;
  ppy=o.ppy;
  Pixmat=o.Pixmat;
  int k=0;
  int tmp= sqrt(Npix);
  PixID= new int[Npix];
  while(k<tmp) {
 
    for(int i=k*tmp; i<(k+1)*tmp; ++i) {
      PixID[i]=tmp+3+i+2*k;
    }
    ++k; }

}

vector <int> EventGenerator::EventNoise(float probnoise){
  if ((probnoise>1) || (probnoise<0)) {
    cout << "Error probability has to be between 0 and 1."<<endl;
  }
  Noisy.reserve(1);
  TRandom3 rand(0);
  for (int i=0;i<Npix;++i) {
    if ( (rand.Rndm()*100)<=probnoise*100){  //melhor random generator?
      Noisy.push_back(PixID[i]);
      HNoisy.push_back(i);
    }
  }
  return Noisy;
}

vector <int> EventGenerator::RingSignal( float bb) {
  beta=bb;
  double p=1.3*beta;
  N0= fabs(int(20.*(1-(1/(p*p)))));
  R=40*sqrt((p*p)-1);
  double RAL= 1.5/R; // Radial Activation Limit -> angulo em rad do troço minimo de circunferencia para ativaçao
  // cout << "Perimetro Teorico " << 2*PI*R << endl;
  TRandom3 rand(0);
  double t=0;
  vector <int> aux;
  vector <double> rad;
  vector <double> ang;
  vector <int> Id;
  vector <double> Len;
  double *pos = new double[2];
  double trash1,trash2;
 
  pos[0]=1+x/Pixwidth; 
  double xdev = modf (pos[0] , &trash1);
  pos[1]=1+y/Pixwidth;
  double ydev = modf (pos[1] , &trash2);
  for (int i=0; i<int(2*PI*10/RAL) ; ++i) {
    //o +1 tem o mesmo intuito do NeigSignal. Adiciona-se x dev e ydev para a circunferencia estar centrada no ponto onde a particula embate
    double xx= xdev+pos[0]+ (R*cos (t))/Pixwidth;
    double yy= ydev+pos[1]+ (R*sin (t))/Pixwidth;
    t+=RAL/10;
    double yu= Pixmat->GetBin(xx,yy);
      aux.push_back(yu);
      rad.push_back(t); }

  //teste para verificar pixeis ativaveis (com mais de 1.5 mm de troço)
  size_t i=0;
  while( i<aux.size()){
    if(aux[i]== aux[i+10]) {
      Id.push_back(aux[i]);
    
      int j=0;
      while (aux[i]==aux[j+i+10]){
	++j;
      }
      ang.push_back(rad[int((i+j+10))]);
      i=j+i+10;
      Len.push_back(1.5+(j)*R*RAL/10);
    }
    else {
      ++i;
    }
  }

  //caso o ultimo pixel seja igual ao primeiro
  if(Id[Id.size()]==Id[0]) {
    Id.erase(Id.end()-1);
    Len.erase(Len.end()-1);
    ang.erase(ang.end()-1);
  }
  
  int size =Id.size()-1;
  vector <int> rands;
  for (int i=0; i<N0; ++i) {
    int a = int(rand.Rndm()*size);
    rands.push_back(a);
    
    //teste pra nao repetir
    if (i>0) {
      for(size_t j=0; j<rands.size()-1; ++j) {
	if(rands[i]==rands[j]){
	  a = int(rand.Rndm()*size);
	  rands.erase(rands.end()-1);
	  rands.push_back(a);
	  j=0;
	    
	}
      }
    }
    int g=rands[i];
  
    PringID.push_back(Id[g]);
    AziAng.push_back(ang[g]);
      
    //traduçao
    for (int i=0; i<Npix; ++i) {
      if (Id[g] == PixID[i]) {
	HPringID.push_back(i);
      }
     
    }
    PringL.push_back(Len[g]);
  }
  return PringID;  
}
 
vector <int> EventGenerator::EventSignal(float a[2]) {
  int tmp=sqrt(Npix);
  float *pos=new float [2];
  // o +1 serve para caso uma particula caia em (3,2) acenda o pixel 0 , com x de 0 a 5 e y de a 5. Sem o +1 nao acendia nada, so acendia o pixel 0 quando caisse numa posiçao com x e y >5
  x=a[0];
  y=a[1];
  pos[0]=1+x/Pixwidth; 

  pos[1]=1+y/Pixwidth;
 
  int n[9];

  //pixel onde cai a particula
  n[8]= Pixmat->GetBin(pos[0],pos[1]);
 
  //# dos 3X3 PIXEIS QUE RODEIAM O PIXEL ONDE CAI A PARTICULA
  n[0]=n[8]+tmp+1;
  n[1]=n[8]+tmp+2;
  n[2]=n[8]+tmp+3;
  n[3]=n[8]-1;
  n[4]=n[8]+1;
  n[5]=n[8]-tmp-1;
  n[6]=n[8]-tmp-2;
  n[7]=n[8]-tmp-3;

  //traduçao 
  int nr[9];
  for (int i=0; i<Npix; ++i) {
    for (int j=0; j<9 ; ++j) {
      if (n[j] == PixID[i]) { //procura na lista de identificadores o respetivo
	nr[j]=i;}  // guarda o numero do pixel
    }
  }
 

  //9C5 combinaçoes. isto e, ha 126 combinaçoes possiveis de pixeis ativos.  random de 0 a 125, escolhe 1 delas.
  TRandom3 r(0);
  int p=int(r.Uniform(0,125));
  switch(p) {
  case 0:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);

    break;	}
  case 1:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    break;	}
  case 2:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[6]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[6]);

    break;	}
  case 3:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[7]);
    break;	}
  case 4:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[8]);
    break;	}
  case 5:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    break;	}
  case 6:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    break;	}
  case 7:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[7]);
    break;	}
  case 8:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[8]);
    break;	}
  case 9:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    break;	}
  case 10:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    break;	}
  case 11:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[5]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[8]);
    break;	}
  case 12:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 13:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 14:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 15:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    break;	}
  case 16:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    break;	}
  case 17:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[7]);
    break;	}
  case 18:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[8]);
    break;	}
  case 19:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    break;	}
  case 20:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    break;	}
  case 21:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[8]);
    break;	}
  case 22:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 23:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 24:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 25:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    break;	}
  case 26:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    break;	}
  case 27:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[8]);
    break;	}
  case 28:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 29:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 30:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[4]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 31:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 32:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 33:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 34:{
    PID.push_back(n[0]);
    PID.push_back(n[1]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 35:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    break;	}
  case 36:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    break;	}
  case 37:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[7]);
    break;	}
  case 38:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[8]);
    break;	}

  case 39:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    break;	}
  case 40:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    break;	}
  case 41:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[8]);
    break;	}
  case 42:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 43:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 44:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 45:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    break;	}
  case 46:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    break;	}
  case 47:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[8]);
    break;	}
  case 48:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 49:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 50:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 51:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 52:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 53:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 54:{
    PID.push_back(n[0]);
    PID.push_back(n[2]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 55:{
    PID.push_back(n[0]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    break;	}
  case 56:{
    PID.push_back(n[0]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    break;	}
  case 57:{
    PID.push_back(n[0]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[8]);
    break;	}
  case 58:{
    PID.push_back(n[0]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 59:{
    PID.push_back(n[0]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 60:{
    PID.push_back(n[0]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 61:{
    PID.push_back(n[0]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 62:{
    PID.push_back(n[0]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 63:{
    PID.push_back(n[0]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 64:{
    PID.push_back(n[0]);
    PID.push_back(n[3]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 65:{
    PID.push_back(n[0]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 66:{
    PID.push_back(n[0]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 67:{
    PID.push_back(n[0]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 68:{
    PID.push_back(n[0]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 69:{
    PID.push_back(n[0]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[0]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 70:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    break;	}
  case 71:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    break;	}
  case 72:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[7]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[7]);
    break;	}
  case 73:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[8]);
    break;	}
  case 74:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    break;	}
  case 75:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    break;	}
  case 76:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[8]);
    break;	}
  case 77:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 78:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 79:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 80:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    break;	}
  case 81:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    break;	}
  case 82:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[8]);
    break;	}
  case 83:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 84:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 85:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 86:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 87:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 88:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 89:{
    PID.push_back(n[1]);
    PID.push_back(n[2]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 90:{
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    break;	}
  case 91:{
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    break;	}
  case 92:{
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[8]);
    break;	}
  case 93:{
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 94:{
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 95:{
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 96:{
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 97:{
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 98:{
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 99:{
    PID.push_back(n[1]);
    PID.push_back(n[3]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 100:{
    PID.push_back(n[1]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 101:{
    PID.push_back(n[1]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 102:{
    PID.push_back(n[1]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 103:{
    PID.push_back(n[1]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 104:{
    PID.push_back(n[1]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[1]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 105:{
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    break;	}
  case 106:{
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    break;	}
  case 107:{
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[8]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[8]);
    break;	}
  case 108:{
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 109:{
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 110:{
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 111:{
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 112:{
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 113:{
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 114:{
    PID.push_back(n[2]);
    PID.push_back(n[3]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 115:{
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
  case 116:{
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 117:{
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 118:{
    PID.push_back(n[2]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 119:{
    PID.push_back(n[2]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[2]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 120:{
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    break;	}
    
  case 121:{
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[8]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[8]);
    break;	}
  case 122:{
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 123:{
    PID.push_back(n[3]);
    PID.push_back(n[4]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 124:{
    PID.push_back(n[3]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[3]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}
  case 125:{
    PID.push_back(n[4]);
    PID.push_back(n[5]);
    PID.push_back(n[6]);
    PID.push_back(n[7]);
    PID.push_back(n[8]);
    HPID.push_back(nr[4]);
    HPID.push_back(nr[5]);
    HPID.push_back(nr[6]);
    HPID.push_back(nr[7]);
    HPID.push_back(nr[8]);
    break;	}

  }   
  return PID;
}



void EventGenerator::MakeEvent(float* l,float bb, double probnoise, EventGenerator A) {
  //contador do numero do evento
  static int counter=0;
  counter+=1;
  ofstream out;
 //faz as contas e imprime no ficheiro  as variaveis.
  out.open("data.txt", std::ios_base::app);
  out << counter << endl;
  beta=bb;
  out << beta << endl;
  double p=1.3*beta;
  R=40*sqrt((p*p)-1);
  out << R << endl;
  x=l[0];
  out <<x << endl;
  y=l[1];
  out << y << endl;
  vector <int> b=A.EventNoise(probnoise);
  Noisy=b;
  for (size_t i=0 ; i<Noisy.size() ; ++i) {
    out << Noisy[i] <<" ";
  }
  out << endl;
  vector <int> a= A.GetHNoisy();
  HNoisy=a;
  for (size_t i=0 ; i<HNoisy.size() ; ++i) {
    out << HNoisy[i] <<" ";
  }
  out << endl;  

  vector <int> f =A.EventSignal(l);
  PID=f;
  for (size_t i=0 ; i<PID.size() ; ++i) {
    out << PID[i] <<" ";
  }
  out << endl;
  vector<int>q= A.GetHPID();
  HPID=q;
  for (size_t i=0 ; i<HPID.size() ; ++i) {
    out <<HPID[i] <<" ";
  }
  out << endl;
  vector <int> o=A.RingSignal(bb);
  N0=o.size();
  //no caso de N0=0 nao temos anel de pixeis ativo
  if(N0==0)
    {
      out << 0<< endl;
      out << 0 << endl;
      out << N0<<endl;
      out << 0 << endl;
      out << 0 << endl;
    }
  else {
 
    PringID=o;
    for (size_t i=0 ; i<PringID.size() ; ++i) {
      out <<PringID[i] <<" ";
    }
    out << endl;
 
    vector <int> u=A.GetHPringID();
    HPringID=u;
    for (size_t i=0 ; i<HPringID.size() ; ++i) {
      out <<HPringID[i] <<" ";
    }
     out << endl;
    //save N0
    out << N0<<endl;

    vector <double> v=A.GetPringL();
    PringL=v;

    for (size_t i=0 ; i<PringL.size() ; ++i) {
      out <<PringL[i] <<" ";
    }
    out << endl;
    vector <double> w=A.GetAziAng();
    AziAng=w;
    for (size_t i=0 ; i<AziAng.size() ; ++i) {
      out <<AziAng[i] <<" ";
    }
    out << endl;

  }
 
  out.close();
  //imprime so no primeiro evento
  if(counter==1)
    cout << "Doing Math. Please wait."<<endl;
}

vector <int> EventGenerator::GetHPID() {

  return HPID;
}
vector <int> EventGenerator::GetHNoisy() {
  return HNoisy;
}
vector <int> EventGenerator::GetHPringID() {
  return HPringID;
}

vector <double> EventGenerator::GetPringL() {
  return PringL;
}

vector <double> EventGenerator::GetAziAng() {
  return AziAng;
}

void EventGenerator::RecEvent() {
  ofstream out;

  out.open("data.txt", std::ios_base::app);

  std::clock_t start;
  start=std::clock();
  //assumindo que distinguimos o ruido do sinal(cor azul e vermelha, respetivamente), obtem-se beta com um certo erro derivado de N0.
  betaR=(sqrt(1/(1-(double(N0+0.5)/20)))/1.3);
  double p=1.3*betaR;
  RR=40*sqrt((p*p)-1);
  int px;
  int py;
  int pz;
  if(N0>0) {
  Pixmat->GetBinXYZ(PringID[0],px,py,pz); // recebe so ints
  }
  int * pxx= new int [PID.size()];
  int* pyy= new int [PID.size()];
  minx=Pixwidth*sqrt(Npix)+1;
  maxx=0;
  maxy=0;
  miny=Pixwidth*sqrt(Npix)+1;
  for (size_t i=0; i<PID.size(); ++i) {
    Pixmat->GetBinXYZ(PID[i],pxx[i],pyy[i],pz);
    if(pxx[i]>maxx)
      maxx=pxx[i];
    if(pxx[i]<minx)
      minx=pxx[i];
    if(pyy[i]>maxy)
      maxy=pyy[i];
    if(pyy[i]<miny)
      miny=pyy[i];
  }
  minx=(minx-1)*Pixwidth;
  maxx=(maxx-1)*Pixwidth;
  maxy=(maxy-1)*Pixwidth;
  miny=(miny-1)*Pixwidth;

  //quando estamos em algumas partes do detetor, os pixeis ativados no anel nao vao corresponder ao valor real de N0. Nesses asos assume-se o ponto medio do quadrado possivel, como o ponto onde caiu a particula.
  double mediumx=(minx+maxx)/2;
  double mediumy=(miny+maxy)/2;
  
  //mudança de espaço + ida para o meio
  ppx=(px+-1)*Pixwidth+2.5;
  ppy=(py+-1)*Pixwidth+2.5;
 

  double yy=miny;
  double xx=minx;
  double tmp=0;
  
  double result=100000; 
  int k=0;
  int i=0;
  int ilim=maxx-minx;
  int klim=maxy-miny;

  //para um y fixo varre todos os valores de x com um passo de 0.1, regista o valor de xR e yR que minimizam a equaçao da circunferencia
  while(k<=klim*10) {
   
    while( i<=ilim*10) {	
      tmp=fabs((xx-ppx)*(xx-ppx)+(yy-ppy)*(yy-ppy)-RR*RR);
      if(tmp<result){
	result=tmp;
	
	xR=xx;
	yR=yy;  }
      xx+=0.1;
      ++i;
    }
    i=0;
    xx=minx;
    yy+=0.1;
    ++k;
  }
 
  double cte=Pixwidth*sqrt(Npix);
  double rn=sqrt(((mediumx-ppx)*(mediumx-ppx)+(mediumy-ppy)*(mediumy-ppy)));
  double eRRn=fabs((mediumx-ppx)/rn *5 +(mediumy-ppy)/rn *5);
  if((mediumx<0.15*cte) || (mediumx>0.9*cte) || (mediumy<0.15*cte) || (mediumy>0.9*cte)){
    double betaRn=sqrt(((rn/40)*(rn/40)+1))/1.3;
    double errobn=(rn)/(sqrt(1+rn*rn)*(1.3));
    out << betaRn <<" " << errobn << endl;
    out << rn << " " << eRRn <<endl;
  }
  else {
    errob=betaR*1/2*(1/(20-(N0+0.5)))*0.5;
    eRR=1600/RR*1.3*betaR*errob;
    out << betaR <<" " << errob << endl;
    if(N0>0) {
    out << RR << " " << eRR <<endl;
    }
    else {
      out <<"5 " << "5"<<endl; //N0=0  nao temos pixeis ativados na circunferencia, mas o raio teorio vai de 0 ate 10.
    }
  }
  out << minx << " " << maxx << endl;
  out << miny << " " << maxy << endl;
  if(N0==0)
    {
      out << 0<< endl;
      out << 0 << endl;
    }
  else {
    out << ppx<< endl;
    out << ppy << endl;
  }
  if((N0==0) || (mediumx<0.15*cte) || (mediumx>0.9*cte) || (mediumy<0.15*cte) || (mediumy>0.9*cte)){
    epos=fabs(2.5+sqrt((eRRn*eRRn)/2));
    out << mediumx << endl;
    out << mediumy << endl;
    out << epos << endl;
  }
  else {
    epos=fabs(2.5+sqrt((eRR*eRR)/2));
    out << xR << endl;
    out << yR << endl;
    out << epos << endl;
  }
 
  tempo=(std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000);
  out << tempo << endl;
  out.close();
}





