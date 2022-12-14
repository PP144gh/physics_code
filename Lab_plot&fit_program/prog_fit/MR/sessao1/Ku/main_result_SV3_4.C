#include "TROOT.h"  //Principal
#include "TFrame.h"  //gClient
#include"DataInterpolator.h"
#include <TAxis.h>
#include"cFCgraphics.h"
#include<TROOT.h>
#include<TGraphErrors.h>
#include<TMultiGraph.h>
#include<TF1.h>
#include<TGraph.h>
#include<TCanvas.h>
#include<TPad.h>
#include<iostream>
#include<iomanip>
#include<TLine.h>
#include<TLatex.h>
#include<TArrow.h>
#include<TLegend.h>
#include "TStyle.h"  //Caixa do fit
#include<TText.h>
#include<TPaveText.h>
#include<fstream>


#include "TApplication.h"  //Janela

#include <algorithm>    // std::min_element, std::max_element
#include <cmath>

using namespace std;


int main(int argc, char **argv)
{


  //COISAS A PREENCHER PARA CADA ANALISE!!!////////////////////////
  string res_label = "pila.txt";//Nome do ficheiro onde sao apresentados os resultados
  string plot_label = "fit.pdf"; //Nome do ficheiro em que e feito o plot MR(H) 
  string file1="datar.txt"; //directoria dos dados do primeiro varrimento 
  string file2="datal.txt"; //directoria dos dados do segundo varrimento

  double I=0.0010002;//corrente
  double eI=0.0000001;//erro corrente
  double eV = 0.000001; //erro tensao
  double eh = 0.1;//erro campo 

  //Limites da curva linear --> Para fazer o fit
  double low_lim=-4;
  double high_lim=4;
  double low_lim2=-4;
  double high_lim2=4;

   /////////////////////////Tirar os dados do file 1 - varrimento 1////////////////////////////
  ifstream file;
  file.open (file1.c_str());

  static int N=0;

  
  char cur = '\0';
  char last = '\0';

  while (file.get(cur)) {
      if (cur == '\n' ||
          (cur == '\f' && last == '\r'))
         N++;
  }

  //N--;
  
  cout << N << endl;

  double *H = new double[N];
  double *R = new double[N];
  double *eR = new double[N];


  file.close();
  file.open (file1.c_str());

  int i=0;
  int test=0;
  while(!file.eof() && test==0)
    {

      file >> H[i] >> R[i] >> eR[i]; // extracts 2 floating point values seperated by whitespace
      i++; 


      if(i>=N)
	test=1;

    }




  ///////////////////Tirar os dados do file 2 - varrimento 2////////////////////////////
  ifstream file_2;
  file_2.open(file2.c_str());


  double *H2 = new double[N];
  double *R2 = new double[N];
  double *eR2 = new double[N];

  file_2.close();
  file_2.open (file2.c_str());

  i=0;
  test=0;
  while(!file_2.eof() && test==0)
    {
      file_2 >> H2[i] >> R2[i] >> eR2[i]; // extracts 2 floating point values seperated by whitespace
      i++;

      if(i>=N)
	test=1;
      // do something with them
    }


  



  //////////////Grafico MR(H) com os respectivos erros/////////////////////////

  ///Varrimento 1

  double *eH = new double[N];
  for(int i=0;i<N;i++){

    eH[i]=eh; //dado no inicio do prog

  }
  

  TGraphErrors *R_H = new TGraphErrors(N,H,R,eH,eR);
  R_H->SetMarkerStyle(1);
  R_H->SetLineColor(kBlue);
  //MR_H->SetFillColor(kBlue);

  

  TGraphErrors *R_H2 = new TGraphErrors(N,H2,R2,eH,eR2);
  R_H2->SetLineColor(kRed);
  R_H2->SetMarkerStyle(1);






  //Varrimento 1
  TF1 *f1= new TF1("f1","[0]-193600*[1]*(x-[2])*(x-[2])");//Funcao a fitar
  f1->SetParLimits(0,3.9,4);
  f1->SetParLimits(1,0,0.00000001);
  //f1->SetParLimits(2,0,3);
  f1->SetLineColor(kRed);
  R_H->Fit("f1","","",low_lim,high_lim);
  double b=f1->GetParameter(0); //ordenada na origem 
  double eb =  f1->GetParError(0); // erro da ordenada na origem 
  double a=f1->GetParameter(1); //declive
  double ea =  f1->GetParError(0); //erro do declive 


  //Varrimento 2
  TF1 *f2= new TF1("f2","[0]-193600*[1]*(x-[2])*(x-[2])");
  f2->SetParLimits(0,3.9,4);
  f2->SetParLimits(1,0,1);
  f2->SetLineColor(kBlue);
  R_H2->Fit("f2","","",low_lim2,high_lim2);
  double b2=f2->GetParameter(0); // ordenada na origem
  double eb2 =  f2->GetParError(0); // erro da ordenada na origem 
  double a2=f2->GetParameter(1); //declive
  double ea2 =  f2->GetParError(0); //erro do declive 


  //Ficheiro com os resultados
  ofstream resultados;
  resultados.open (res_label.c_str());
  resultados << "chupa";
  resultados.close();



  //faz aparecer o canvas
  TApplication theApp("App",&argc, argv);
  theApp.InitializeGraphics();



  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  //c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);




  TMultiGraph *mg = new TMultiGraph("mg","");
  mg->Add(R_H);
  //mg->Add(R_H2);



 /////////////////// Arrows para as orientacoes /////////////////////////////////////////////////////////////////////////////
  float arrow_step = 0.0020;//Distancia entre arrows
  float arrow_offset = 0.0025;//Distancia do arrow mais proximo do grafico ao grafico


  //Regiao 1/////////////////////////

  // H 
  TArrow *r1ar1 = new TArrow(-40,3.85,-30,3.85,0.02,"<|");
  //TText *text_h = new TText(-40+5, 0.55+0.01, "H");
  //text_h->SetTextSize(0.03);
  r1ar1->SetLineColor(1);
  r1ar1->SetFillColor(1);
 
  // M 
  TArrow *r1ar2 = new TArrow(-40,3.84,-30,3.84,0.02,"<|");
  //TText *text_m = new TText(-40+5, 0.45-0.1, "M");
  //text_m->SetTextSize(0.03);
  r1ar2->SetLineColor(kGreen);
  r1ar2->SetFillColor(kGreen);
 
  //J
  float axj=40;
  float ayj=0;
  TArrow *arj = new TArrow(-45,3.82,-45,3.84,0.02,"|>");
  arj->SetLineColor(kYellow);
  arj->SetFillColor(kYellow);
  TText *text_j = new TText(-45,3.82+0.01,"J");
  text_j->SetTextSize(0.03);

  // Ku 
  TArrow *arku = new TArrow(-48,3.81,-48,3.84,0.02,"<|>");
  arku->SetLineColor(49);
  arku->SetFillColor(49);
  TText *text_ku = new TText(-50+3, 3.81+0.001, "Ku");
  text_ku->SetTextSize(0.03);
 

  
  // //Regiao 2///////

  // H 
  TArrow *r2ar1 = new TArrow(0,3.85,0,3.85,0.02,"");
  TText *text_h2 = new TText(-0.7, 3.85, "H=0");
  text_h2->SetTextSize(0.03);
 
 
  // M 
  TArrow *r2ar2 = new TArrow(0,3.86,0,3.88,0.02,"|>");
  r2ar2->SetLineColor(kGreen);
  r2ar2->SetFillColor(kGreen);



  //Regiao 3///////

  // H 
  TArrow *r3ar1 = new TArrow(40,3.85,50,3.85,0.02,"|>");
 
  r3ar1->SetLineColor(kBlack);
  r3ar1->SetFillColor(kBlack);
 
  // M 
  TArrow *r3ar2 = new TArrow(40,3.84,50,3.84,0.02,"|>");
 
  r3ar2->SetLineColor(kGreen);
  r3ar2->SetFillColor(kGreen);
 


  


  //Legenda///////////////////////////

  TLegend* leg;

  //Usa-se a condicao para nao por a legenda em cima dos dados
  if(1<0){
    leg = new TLegend(0.8,0.7,0.9,0.9);//(x1,y1,x2,y2)
  }else{
    leg = new TLegend(0.1,0.7,0.2,0.9);//(x1,y1,x2,y2)
  }
  //leg->SetHeader("Orientac#tilde{o}es");
  leg->AddEntry(R_H,"#rightarrow","lep");
  leg->AddEntry(R_H2,"#leftarrow","lep");

  leg->AddEntry(r1ar2,"M","l");
  leg->AddEntry(r1ar1,"H","l");




  file.close();
  file_2.close();
  //delete  g;
  //delete gr1; // A classe do prof deve fazer delete aos objectos, quando descomento da segmentation violation
  //delete  cubic;

  delete [] H;
  delete [] R;
  delete [] eH;
  delete [] eR;
  delete [] H2;
  delete [] R2;
  delete [] eR2;
 

  
  mg->Draw("AP");
  mg->SetMinimum(3.8);
  mg->SetMaximum(4);
  mg->GetXaxis()->SetTitle("H (Oe)");
  mg->GetYaxis()->SetTitle("R(#Omega)");
  mg->GetYaxis()->SetTitleOffset(1.2);

  
  //1 regiao

  arku->Draw();
  text_ku -> Draw();
  arj->Draw();
  text_j->Draw();


 r1ar1->Draw();
 //text_h->Draw();
 //text_m->Draw();
 r1ar2->Draw();

 r2ar1->Draw();
 text_h2->Draw();
 r2ar2->Draw();

r3ar1->Draw();

 r3ar2->Draw();

  

  //legenda
  leg->Draw();
 

    gStyle->SetOptFit();

  



  c1->Update();
  c1->Modified();
  c1->Print(plot_label.c_str());
  getchar();
  theApp.Terminate();


  return 0;  
}
