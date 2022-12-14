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
  string res_label = "resultados_SV4_B.txt";//Nome do ficheiro onde sao apresentados os resultados
  string plot_label = "SV4_B.pdf"; //Nome do ficheiro em que e feito o plot MR(H) 
  string file1="../3s/data/SV4_B_50_2a.txt"; //directoria dos dados do primeiro varrimento 
  string file2="../3s/data/SV4_B_50_2b.txt"; //directoria dos dados do segundo varrimento

  double I=0.0010094;//corrente
  double eI=0.0000001;//erro corrente
  double eV = 0.000001; //erro tensao
  double eh = 0.1;//erro campo !!!!! TOU A POR ASSIM PARA O FIT DAR, MAS NA VERDADE O ERRO E 0.1 !!!!!!! 

  //Limites da curva linear --> Para fazer o fit
  double low_lim=0;
  double high_lim=20;
  double low_lim2=0;
  double high_lim2=20;

  //FIM DAS COISAS PARA PREENCHER A CADA ANALISE///////////////////


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

      file >> H[i] >> R[i]; // extracts 2 floating point values seperated by whitespace
      R[i]=R[i]/I; //PASSAR TENSOES PARA RESISTENCIAS
      eR[i] = eV/I + R[i]/I*eI; //erro resistencia
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
      file_2 >> H2[i] >> R2[i]; // extracts 2 floating point values seperated by whitespace
      R2[i]=R2[i]/I; //PASSAR TENSOES PARA RESISTENCIAS
      eR2[i] = eV/I + R2[i]/I*eI; //erro resistencia
      i++;

      if(i>=N)
	test=1;
      // do something with them
    }


  /////////////////////////Rp e Rap////////////////////////////////////////////////

  ///Varrimento 1

  double Rp = *std::min_element(R,R+N);
  double eRp = *std::min_element(eR,eR+N); //Quanto maior a resistencia maior o seu erro, ver formula de erro
  double Rap = *std::max_element(R,R+N);
  double eRap = *std::max_element(eR,eR+N);

  ///Varrimento 2

  double Rp2 = *std::min_element(R2,R2+N);
  double eRp2 = *std::min_element(eR2,eR2+N);
  double Rap2 = *std::max_element(R2,R2+N);
  double eRap2 = *std::max_element(eR2,eR2+N);


  // Media do Rp e Rap
  double Rp_med = (Rp+Rp2)/2;
  double eRp_med = (eRp+eRp2)/2;
  double Rap_med = (Rap+Rap2)/2;
  double eRap_med = (eRap+eRap2)/2;



  //////////////Grafico MR(H) com os respectivos erros/////////////////////////

  ///Varrimento 1

  double *MR = new double[N];
  double *eH = new double[N];
  double *eMR = new double[N];
  for(int i=0;i<N;i++){

    double e_mr= eR[i]/Rp + R[i]/(Rp*Rp)*eRp; //erro magneto-resistencia

    eH[i]=eh; //dado no inicio do prog
    eMR[i]=e_mr;
    MR[i]=(R[i]-Rp)/Rp;

  }
  

  TGraphErrors *MR_H = new TGraphErrors(N,H,MR,eH,eMR);
  MR_H->SetMarkerStyle(6);
  MR_H->SetMarkerColor(kBlue);
  MR_H->SetFillColor(kBlue);


  ///Varrimento 2

  double *MR2 = new double[N];
  double *eH2 = new double[N];
  double *eMR2 = new double[N];
  for(int i=0;i<N;i++){

    //Os erros eV, eI e eH sao os mesmos para ambos os varrimentos
    double e_mr2= eR2[i]/Rp2 + R2[i]/(Rp2*Rp2)*eRp2; //erro magneto-resistencia

    eH2[i]=eh; //dado no inicio do prog
    eMR2[i]=e_mr2;//em percentagem
    MR2[i]=(R2[i]-Rp2)/Rp2;//em percentagem

  }
  

  TGraphErrors *MR_H2 = new TGraphErrors(N,H2,MR2,eH2,eMR2);
  MR_H2->SetMarkerColor(kRed);
  MR_H2->SetMarkerStyle(7);




  ////////////////////Encontrar Hc e Hoff////////////////////


  double R_half = (Rap+Rp)/2; //Resistencia a meia altura para o varrimento 1
  double eR_half = (eRap+eRp)/2; //Erro
  double R_half2 = (Rap2+Rp2)/2; //Resistencia a meia altura para o varrimento 2
  double eR_half2 = (eRap2+eRp2)/2; //Erro
  double R_half_med=(R_half+R_half2)/2; //Faz-se a media para obter a resistencia a meia altura final
  double eR_half_med=(eR_half+eR_half2)/2;//Erro


  //Varrimento 1
  TF1 *f1= new TF1("f1","[0]+[1]*x");//Funcao a fitar
  f1->SetParLimits(1,0,1);
  TGraphErrors *R_H = new TGraphErrors(N,H,R,eH,eR);//Grafico R(H) para dazer o fit
  R_H->Fit("f1","","",low_lim,high_lim);
  double b=f1->GetParameter(0); //ordenada na origem 
  double eb =  f1->GetParError(0); // erro da ordenada na origem 
  double a=f1->GetParameter(1); //declive
  double ea =  f1->GetParError(0); //erro do declive 

  double dH1=(R_half_med-b)/a; //H correspondente a R a meia altura
  double edH1=(eR_half_med+eb)/a + TMath::Abs(R_half_med-b)/(a*a)*ea;

  //Varrimento 2
  TF1 *f2= new TF1("f2","[0]+[1]*x");
  f2->SetParLimits(1,0,1);
  TGraphErrors *R_H2 = new TGraphErrors(N,H2,R2,eH2,eR2);//grafico R(H) para fazer o fit
  R_H2->Fit("f2","","",low_lim2,high_lim2);
  double b2=f2->GetParameter(0); // ordenada na origem
  double eb2 =  f2->GetParError(0); // erro da ordenada na origem 
  double a2=f2->GetParameter(1); //declive
  double ea2 =  f2->GetParError(0); //erro do declive 

  double dH2=(R_half_med-b2)/a2; //H correspondente a R a meia altura
  double edH2=(eR_half_med+eb2)/a2 + TMath::Abs(R_half_med-b2)/(a2*a2)*ea2;


  // Campo coercivo
  double Hc=TMath::Abs(dH2-dH1)/2;
  double eHc = (edH1+edH2)/2; //erro
  
  // Campo de offset
  double Hoff=(dH2+dH1)/2;
  double eHoff = (edH1+edH2)/2; //erro

  //// Sensibilidade e erros (em percentagem)
  double S1 = a/Rp*100; //Varrimento 1
  double eS1 = (ea/Rp + a/(Rp*Rp)*eRp)*100; 
  double S2 = a2/Rp2*100; //Varrimento 2
  double eS2 = (ea2/Rp2 + a2/(Rp2*Rp2)*eRp2)*100;


  //Ficheiro com os resultados
  ofstream resultados;
  resultados.open (res_label.c_str());
  resultados << "------ Varrimento 1 ------ " << "\n" <<"Rp: " << Rp  << " +- " << eRp << " Ohm" << "\n" << "Rap: " << Rap << " +- " << eRap << " Ohm" << "\n" << "------ Varrimento 2 ------ " << "\n" << "Rp: " << Rp2  << " +- " << eRp2 << " Ohm" << "\n" << "Rap: " << Rap2 << " +- " << eRap2 << " Ohm" << "\n" << "------ Media ------ " << "\n" << "Rp: " << Rp_med  << " +- " << eRp_med << " Ohm" << "\n" << "Rap: " << Rap_med << " +- " << eRap_med << " Ohm" << "\n" <<  "---------------------" << "\n" << "Hc: " << Hc  << " +- " << eHc << " Oe" << "\n" << "Hoff: " << Hoff << " +- " << eHoff << " Oe" << "\n" << "S (varrimento 1) (%) " << S1 << " +- " << eS1 << "\n" << "S (varrimento 2) (%)" << S2 << " +- " << eS2 << "\n";
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
  mg->Add(MR_H);
  mg->Add(MR_H2);



 /////////////////// ARROWS PARA AS ORIENTACOES /////////////////////////////////////////////////////////////////////////////
  float arrow_step = 0.0025;//Distancia entre arrows
  float arrow_offset = 0.0035;//Distancia do arrow mais proximo do grafico ao grafico


  //Regiao 1/////////////////////////

  float ax1 = H[0]/2-10;
  float ay1 = MR[0]+0.005;

  // H 
  TArrow *r1ar1 = new TArrow(ax1,ay1+arrow_offset,ax1+10,ay1+arrow_offset,0.02,"<|");
  r1ar1->SetLineColor(1);
  r1ar1->SetFillColor(1);

  // Mpl
  TArrow *r1ar2 = new TArrow(ax1,ay1+arrow_offset-arrow_step,ax1+10,ay1+arrow_offset-arrow_step,0.02,"<|");
  r1ar2->SetLineColor(8);
  r1ar2->SetFillColor(8);


  // Mfl
  TArrow *r1ar3 = new TArrow(ax1,ay1+arrow_offset-2*arrow_step,ax1+10,ay1+arrow_offset-2*arrow_step,0.02,"<|");
  r1ar3->SetLineColor(9);
  r1ar3->SetFillColor(9);

  /*
  // J
  float axj=40;
  float ayj=0;
  TArrow *arj = new TArrow(axj,ayj,axj+10,ayj,0.02,"|>");
  arj->SetLineColor(49);
  arj->SetFillColor(49);
  TPaveText *text_j = new TPaveText(axj,ayj+5,axj+10,ayj+5);
  text_j->SetLabel("J");
  */

  // Ku
  float axku=40;
  float ayku=0.003;
  TArrow *arku = new TArrow(axku,ayku,axku+10,ayku,0.02,"<|>");
  arku->SetLineColor(49);
  arku->SetFillColor(49);
  TText *text_ku = new TText(axku+3, ayku+0.002, "Ku");
  text_ku->SetTextSize(0.04);


  //Regiao 2///////

  float ax2 = Hoff-10.;
  float ay2 = (R_half-Rp)/Rp;

  // H 
  TText *text_H = new TText(ax2, ay2+arrow_offset+arrow_step/2, "H = 0");
  text_H->SetTextSize(0.04);


  // M pl
  TArrow *r2ar2 = new TArrow(ax2,ay2+arrow_offset+2*arrow_step,ax2+10,ay2+arrow_offset+2*arrow_step,0.02,"<|");
  r2ar2->SetLineColor(8);
  r2ar2->SetFillColor(8);

  // M fl
  TArrow *r2ar3 = new TArrow(ax2-2,ay2+arrow_offset,ax2-2,ay2+arrow_offset+0.008,0.02,"|>");
  r2ar3->SetLineColor(9);
  r2ar3->SetFillColor(9);



  //Regiao 3///////

  float ax3 = -H[0]/2+10;
  float ay3 = MR[N-2];

  // H 
  TArrow *r3ar1 = new TArrow(ax3,ay3-arrow_offset,ax3+10,ay3-arrow_offset,0.02,"|>");
  r3ar1->SetLineColor(1);
  r3ar1->SetFillColor(1);

  // M pl 
  TArrow *r3ar2 = new TArrow(ax3,ay3-arrow_offset-arrow_step,ax3+10,ay3-arrow_offset-arrow_step,0.02,"<|");
  r3ar2->SetLineColor(8);
  r3ar2->SetFillColor(8);

  // M fl
  TArrow *r3ar3 = new TArrow(ax3,ay3-arrow_offset-2*arrow_step,ax3+10,ay3-arrow_offset-2*arrow_step,0.02,"|>");
  r3ar3->SetLineColor(9);
  r3ar3->SetFillColor(9);


  //Legenda///////////////////////////

  TLegend* leg;

  //Usa-se a condicao para nao por a legenda em cima dos dados
  if(S1<0){
    leg = new TLegend(0.8,0.7,0.9,0.9);//(x1,y1,x2,y2)
  }else{
    leg = new TLegend(0.1,0.7,0.2,0.9);//(x1,y1,x2,y2)
  }
  //leg->SetHeader("Orientac#tilde{o}es");
  leg->AddEntry(MR_H,"#rightarrow","p");
  leg->AddEntry(MR_H2,"#leftarrow","p");

  leg->AddEntry(r1ar1,"H","l");
  leg->AddEntry(r1ar2,"M pl","l");
  leg->AddEntry(r1ar3,"M fl","l");
  //leg->AddEntry(arj,"J","l");




  file.close();
  file_2.close();
  delete [] R;
  delete [] H;
  delete [] MR;
  delete [] eH;
  delete [] eMR;
  delete [] R2;
  delete [] H2;
  delete [] MR2;
  delete [] eH2;
  delete [] eMR2;
  delete [] eR;
  delete [] eR2;


  mg->Draw("AP");
  mg->GetXaxis()->SetTitle("H (Oe)");
  mg->GetYaxis()->SetTitle("MR");
  mg->GetYaxis()->SetTitleOffset(1.2);

  
  //arrows
  r1ar1->Draw();
  //r2ar1->Draw(); Basta por um texto a dizer que H=0
  text_H->Draw();
  r3ar1->Draw();

  r1ar2->Draw();
  r2ar2->Draw();
  r3ar2->Draw();

  r1ar3->Draw();
  r2ar3->Draw();
  r3ar3->Draw();

  arku->Draw();
  text_ku -> Draw();

  //arj->Draw();
  //text_j->Draw();


  

  //legenda
  leg->Draw();
  



  c1->Update();
  c1->Modified();
  c1->Print(plot_label.c_str());
  getchar();
  theApp.Terminate();


  return 0;  
}
