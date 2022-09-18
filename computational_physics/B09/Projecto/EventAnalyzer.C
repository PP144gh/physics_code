#include<cstdlib>
#include<iostream>
#include "EventAnalyzer.h"
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

EventAnalyzer:: EventAnalyzer(int a, int b) : EventGenerator(a,b) { }


//limpa o ficheiro
void EventAnalyzer::CleanData() {
  ofstream out("data.txt");
  out.close();
}

void EventAnalyzer::HistP() {
  cFCgraphics D;
  D.CreatePad("Pad2");
  ifstream in("data.txt");
   
  cout << beta << endl;
  string line;
  int k=1;
  TH1F * p = new TH1F("Diferenca Posicao","Dif Pos",100,0,15);
  p->GetXaxis()->SetTitle("mm");
  p->GetYaxis()->SetTitle("#");
  gStyle->SetOptStat("ne");
  gStyle->SetPalette(1);
  int n=1;
  double startline=1;
  double d=0;
  //le as informaçoes necessarias a realizaçao do histograma.
  while(getline(in,line)){
 
    if (k==(startline+2)) {
      in >> x;
    }
    if (k==(startline+3)) {
      in >> y;
    }
    if (k==(startline+19)) {
      in >> xR;
    }
    if (k==(startline+20)) {
      in >> yR;
    }  
 
    if(((k)%24==0)  ){
      d=sqrt((x-xR)*(x-xR)+(y-yR)*(y-yR));
      ++n;
      startline=n+23*(n-1);
      p->Fill(d);
    }
    ++k;
  }

  D.AddObject(p,"Pad2");
  D.DumpPad("Pad2");
  D.DrawPad("Pad2");

  D.Print("HistPosition.pdf");
}

void EventAnalyzer::HistR() {
  cFCgraphics D;
  D.CreatePad("Pad2");
  ifstream in("data.txt");
 
  string line;
  int k=1;
  TH1F * p = new TH1F("Diferenca Raio","Dif Raio",100,0,10);
  p->GetXaxis()->SetTitle("mm");
  p->GetYaxis()->SetTitle("#");
  gStyle->SetOptStat("ne");
  gStyle->SetPalette(1);

  int n=1;
  double startline=1;
  double d=0;
  while(getline(in,line)){
 
    if (k==(startline+1)) {
      in >> R;
    }
  
    if (k==(startline+14)) {
      in >> RR;
    } 
   
    if(((k)%24==0)  ){
      d=fabs(R-RR);
     
      ++n;
   
      startline=n+23*(n-1);
      p->Fill(d);
     
    }
    ++k;
  }

  D.AddObject(p,"Pad2");
  D.DumpPad("Pad2");
  D.DrawPad("Pad2");

  D.Print("HistRadius.pdf");
}

void EventAnalyzer::HistB() {
  cFCgraphics D;
  D.CreatePad("Pad2");
  ifstream in("data.txt");
   

  string line;
  int k=1;
  TH1F * p = new TH1F("Diferenca Beta","Dif Beta",100,0,0.1);
  p->GetYaxis()->SetTitle("#");
  gStyle->SetOptStat("ne");
  gStyle->SetPalette(1);

  int n=1;
  double startline=1;
  double d=0;
  while(getline(in,line)){
 

    if (k==(startline)) {
      in >> beta;
    }
  
    if (k==(startline+13)) {
      in >> betaR;
    } 
   
    if(((k)%24==0)  ){
      d=fabs(beta-betaR);  
      ++n;
      startline=n+23*(n-1);
      p->Fill(d);
     
    }
    ++k;
  }

  D.AddObject(p,"Pad2");
  D.DumpPad("Pad2");
  D.DrawPad("Pad2");
  D.Print("HistBeta.pdf");
}

void EventAnalyzer::HistT() {
  cFCgraphics D;
  D.CreatePad("Pad2");
  ifstream in("data.txt"); 
  string line;
  int k=1;
  TH1F * p = new TH1F("Tempo a Reconstruir","Time",250,0,0.3);
  p->GetXaxis()->SetTitle("ms");
  p->GetYaxis()->SetTitle("#");
  gStyle->SetOptStat("ne");
  gStyle->SetPalette(1);

  int n=1;
  double startline=1;
  while(getline(in,line)){
 
    if (k==(startline+22)) {
      in >> tempo;
    } 
   
    if(((k)%24==0)  ){  
      ++n;
      startline=n+23*(n-1);
      p->Fill(tempo);
    }
    ++k;
  }

  D.AddObject(p,"Pad2");
  D.DumpPad("Pad2");
  D.DrawPad("Pad2");
  D.Print("HistTime.pdf");
}

void EventAnalyzer::HistL() {
  cFCgraphics D;
  D.CreatePad("Pad2");
  ifstream in("data.txt");
  string line;
  int k=1;
  TH1F * p = new TH1F("Segmentos","Segmentos Circunferencia",40,1.5,8);
  p->GetXaxis()->SetTitle("mm");
  p->GetYaxis()->SetTitle("#");
  gStyle->SetOptStat("ne");
  gStyle->SetPalette(1);

  int n=1;
  double startline=1;
  double tmp=0;
  while(getline(in,line)){
 
    if (k==(startline+11)){
      char buffer [100000];
      in.get(buffer, 100000,'\n');
      int charcount=0;
      for(int m=0; buffer[m]; ++m) {
	if(buffer[m]==' ') {
	  ++charcount;
	}
      }
      stringstream s;
      s << buffer;

      for(int i=0;i<charcount; ++i){
	s >> tmp;
	p->Fill(tmp);
      }
    }
   
 
    if(((k)%24==0)  ){ 
      ++n;
      startline=n+23*(n-1);
    }
    ++k;
  }

  D.AddObject(p,"Pad2");
  D.DumpPad("Pad2");
  D.DrawPad("Pad2");
  D.Print("HistLength.pdf");
}

void EventAnalyzer::HistA() {
  cFCgraphics D;
  D.CreatePad("Pad2");
  ifstream in("data.txt");
   

  string line;
  int k=1;
  TH1F * p = new TH1F("Angulo","Angulo",65,0,6.5);
  p->GetXaxis()->SetTitle("rad");
  p->GetYaxis()->SetTitle("#");
  gStyle->SetOptStat("mne");
  gStyle->SetPalette(1);
  int n=1;
  double startline=1;
  double tmp=0;
  while(getline(in,line)){
 
    if (k==(startline+12)){
      char buffer [100000];
      in.get(buffer, 100000,'\n');
      int charcount=0;
      for(int m=0; buffer[m]; ++m) {
	if(buffer[m]==' ') {
	  ++charcount;
	}
      }
      stringstream s;
      s << buffer;

      for(int i=0;i<charcount; ++i){
	s >> tmp;
	p->Fill(tmp);
      }
    }
   
 
    if(((k)%24==0)  ){
      ++n;
      startline=n+23*(n-1);
    }
    ++k;
  }
  cout <<"***************************************************"<< endl;
  cout <<"Valor Medio Angulo Azimutal: "<< p->GetMean() << endl;
  cout <<"****************************************************"<< endl;
  D.AddObject(p,"Pad2");
  D.DumpPad("Pad2");
  D.DrawPad("Pad2");
  D.Print("HistAngle.pdf");
}


void EventAnalyzer::HistN() {
  cFCgraphics D;
  TPad *pad2=D.CreatePad("Pad2");
  TPad *pad3=D.CreatePad("Pad3");
  ifstream in("data.txt");
   

  string line;
  int k=1;
  TH1F * p = new TH1F("Ruido1600","Ruido",1600,0,Npix);
  p->GetXaxis()->SetTitle("Pixel");
  p->GetYaxis()->SetTitle("#");
  gStyle->SetOptStat("mne");
  gStyle->SetPalette(1);

  int n=1;
  double startline=1;
  double tmp=0;
  while(getline(in,line)){
 
    if (k==(startline+5)){
      char buffer [100000];
      in.get(buffer, 100000,'\n');
      int charcount=0;
      for(int m=0; buffer[m]; ++m) {
	if(buffer[m]==' ') {
	  ++charcount;
	}
      }
      stringstream s;
      s << buffer;  
      for(int i=0;i<charcount; ++i){
	s >> tmp;
	p->Fill(tmp);
      }
    
    }
    if(((k)%24==0)  ){
      ++n;
      startline=n+23*(n-1);
    }
    ++k;
  }
  cout <<"***************************************************"<< endl;
  cout <<"Valor Me'dio dos Pixeis com Ruido: "<< p->GetMean() << endl;
  cout <<"****************************************************"<< endl;
   
  TH1* r=p->Rebin(16,"Ruido100");
 
  D.AddObject(p,"Pad2");
  D.AddObject(r,"Pad3");
  D.AddObject(pad2);
  D.AddObject(pad3);

  D.DumpPad("Pad2");
  D.DumpPad("Pad3");
  D.Draw();
  D.Print("HistNoise.pdf");
}

//faz todos os histogramas
void EventAnalyzer::Hist() {
  HistP();
  HistR();
  HistB();
  HistT();
  HistL();
  HistA();
  HistN();

}

void EventAnalyzer::InfoDraw(int n) {

   //cleanup
  Pixmat->Reset();
  Noisy.clear();
  HNoisy.clear();
  PID.clear();
  HPID.clear();
  PringID.clear();
  HPringID.clear();
  PringL.clear();
  AziAng.clear();

  //acontecimento 1 -> linha 0
  //acontecimento 2 -> linha 24
  //...
  ifstream in("data.txt");
  double startline=n+23*(n-1);
   
  //leitor do ficheiro; le linha a linha as variaveis. de 24 em 24 linhas troca de acontecimento.
  string line;
  int k=0;
  double tmp=0;
  while(getline(in,line)){
    ++k;
    if (k==(startline)) 
      in >> beta;
    if (k==(startline+1)) 
      in >> R;
    if (k==(startline+2)) 
      in >> x;
    if (k==(startline+3)) 
      in >> y;
    if (k==(startline+4)) {
      char buffer [100000];
      in.get(buffer, 100000,'\n');
      int charcount=0;
      for(int m=0; buffer[m]; ++m) {
	if(buffer[m]==' ') {
	  ++charcount;
	}
      }
      stringstream s;
      s << buffer;
      for(int i=0;i<charcount; ++i){
	s >> tmp;
	Noisy.push_back(tmp);
      }	
    }
   
    if (k==(startline+5)){
      char buffer [100000];
      in.get(buffer, 100000,'\n');
      int charcount=0;
      for(int m=0; buffer[m]; ++m) {
	if(buffer[m]==' ') {
	  ++charcount;
	}
      }
      stringstream s;
      s << buffer;

      for(int i=0;i<charcount; ++i){
	s >> tmp;
	HNoisy.push_back(tmp);
      }	
    }	 
    if (k==(startline+6)){
      char buffer [100000];
      in.get(buffer, 100000,'\n');
      int charcount=0;
      for(int m=0; buffer[m]; ++m) {
	if(buffer[m]==' ') {
	  ++charcount;
	}
      }
      stringstream s;
      s << buffer;

      for(int i=0;i<charcount; ++i){
	s >> tmp;
	PID.push_back(tmp);
      }	
    }
    if (k==(startline+7)) {
      char buffer [100000];
      in.get(buffer, 100000,'\n');
      int charcount=0;
      for(int m=0; buffer[m]; ++m) {
	if(buffer[m]==' ') {
	  ++charcount;
	}
      }
      stringstream s;
      s << buffer;

      for(int i=0;i<charcount; ++i){
	s >> tmp;
	HPID.push_back(tmp);
      }	
    }
    if (k==(startline+8)){
      char buffer [100000];
      in.get(buffer, 100000,'\n');
      int charcount=0;
      for(int m=0; buffer[m]; ++m) {
	if(buffer[m]==' ') {
	  ++charcount;
	}
      }
      stringstream s;
      s << buffer;

      for(int i=0;i<charcount; ++i){
	s >> tmp;
	PringID.push_back(tmp);
      }	
    } 
    if (k==(startline+9)){ 
      char buffer [100000];
      in.get(buffer, 100000,'\n');
      int charcount=0;
      for(int m=0; buffer[m]; ++m) {
	if(buffer[m]==' ') {
	  ++charcount;
	}
      }
      stringstream s;
      s << buffer;

      for(int i=0;i<charcount; ++i){
	s >> tmp;
	HPringID.push_back(tmp);
      }	
    }
    if (k==(startline+10)) 
      in >> N0;
    if (k==(startline+11)){
      char buffer [100000];
      in.get(buffer, 100000,'\n');
      int charcount=0;
      for(int m=0; buffer[m]; ++m) {
	if(buffer[m]==' ') {
	  ++charcount;
	}
      }
      stringstream s;
      s << buffer;

      for(int i=0;i<charcount; ++i){
	s >> tmp;
	PringL.push_back(tmp);
      }
	
    }
    if (k==(startline+12)){
      char buffer [100000];
      in.get(buffer, 100000,'\n');
      int charcount=0;
      for(int m=0; buffer[m]; ++m) {
	if(buffer[m]==' ') {
	  ++charcount;
	}
      }
      stringstream s;
      s << buffer;
      for(int i=0;i<charcount; ++i){
	s >> tmp;
	AziAng.push_back(tmp);
      }	
    }
    if (k==(startline+13)) 
      in >> betaR >> errob;
    if (k==(startline+14)) 
      in >> RR >> eRR;
    if (k==(startline+15)) 
      in >> minx >> maxx;
    if (k==(startline+16)) 
      in >> miny >> maxy;
    if (k==(startline+17)) 
      in >> ppx;
    if (k==(startline+18)) 
      in >> ppy;
    if (k==(startline+19)) 
      in >> xR;
    if (k==(startline+20)) 
      in >> yR;
    if (k==(startline+21)) 
      in >> epos;
    if (k==(startline+22)) 
      in >> tempo;
    if(k>(startline+22))
      break;
  }

  cFCgraphics D;
  //stilo
  Pixmat->SetOption("COL4");
  Pixmat->GetXaxis()->SetTitle("mm");
  Pixmat->GetYaxis()->SetTitle("mm");
  gStyle->SetOptStat("ne");
  gStyle->SetPalette(1);
  gROOT->SetStyle("Plain");

  //noise
  for (size_t i=0; i<Noisy.size(); ++i) {
     
    Pixmat->SetBinContent(Noisy[i],0.4);
  }

  //signal
  for (size_t i=0; i<PID.size(); ++i) {  
    Pixmat->SetBinContent(PID[i],2.7);
  }

  for (size_t i=0; i<PringID.size(); ++i) {
    Pixmat->SetBinContent(PringID[i],2.7);
  }

  cout<< "Pixeis c ruido"<<endl;
  for (size_t i=0; i<HNoisy.size(); ++i) {
    cout <<  HNoisy[i]<< endl;
  }

  cout<< "Pixeis c Sinal"<< endl;
  for (size_t i=0; i<HPID.size(); ++i) {
    cout <<  HPID[i]<< endl;
  }

  for (size_t i=0; i<HPringID.size(); ++i) {
    cout << "ring " << HPringID[i]<< endl;  
  }

  cout << "Troços (por ordem)" << endl;
  for (size_t i=0; i< PringL.size() ; ++i)
    cout << PringL[i] << endl;

  cout <<"Angulo Azimutal" << endl;
  for (size_t i=0; i< AziAng.size() ; ++i)
    cout << AziAng[i] << endl;


  cout << "***RECONSTRUCTION****" << endl;

  cout <<"N0: " << N0 << endl;
  cout << "v = ("<< betaR << "+/-" << errob<<")c " << endl;
 
  cout << "Raio: " << RR <<"+/-" << eRR << " mm" << endl;
 
  cout << "Intervalo de x possivel " <<"["<< minx << "," << maxx<<"]"<< endl;

  cout << "Intervalo de y possivel " <<"["<< miny << "," << maxy<<"]"<< endl;
 
  cout << "Ponto da Circunferencia escolhido: ("<< ppx<<","<< ppy <<")" << endl;

  cout <<"Posiçao (x,y): "<< "("<<xR << "," << yR <<")"<<" +/- ("<< epos<<","<<epos<<")"<< endl;

  cout << "***REAL****" << endl;
  cout <<"v = " << beta <<"c"<< endl;
  cout << "Raio: " << R <<"mm"<< endl;
  cout <<"Posiçao (x,y): "<< "("<<x << "," << y <<")"<< endl;

 
  std::cout << "Tempo a Reconstruir: " << tempo << " ms" << std::endl;

  D.CreatePad("Pad");
  D.AddObject(Pixmat,"Pad");
  D.DumpPad("Pad");
  D.DrawPad("Pad");

  char buff [11];
  sprintf(buff,"Event%dDraw.pdf",n);

  string s(buff);

  D.Print(s);

}
