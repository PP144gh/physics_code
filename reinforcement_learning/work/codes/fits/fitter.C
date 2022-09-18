#include "TROOT.h"
#include "TFrame.h" //gClient
#include "TCanvas.h"
#include "TPad.h"
#include "TSystem.h"
#include <TList.h>
#include "TApplication.h"
#include "TVirtualX.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include <cmath>
#include <iostream>
#include "TPaveStats.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TAxis.h"
#include <unistd.h>

#include <fstream>

using namespace std;

int main(int argc, char **argv) {
 

  //faz aparecer o canvas
  TApplication theApp("App", &argc, argv);
  theApp.InitializeGraphics();
 
  //box com resultados do fit
  gStyle->SetOptFit();
  //settings do canvas  
  TCanvas *c1 = new TCanvas("c1","Nome",200,10,700,500);
  c1->SetFillColor(0);
  c1->SetGrid();
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);

  //Definir multiplos graficos num canvas
  TMultiGraph *mg = new TMultiGraph("mg","mg");
  mg->SetTitle("'Adventurous' Evolution");

  //grafico 1
  // string dados1 = "calFN2.txt";
  TGraph *gr1 = new TGraphErrors("data.txt","%lg %lg");
  gr1->SetName("gr1");
  gr1->SetTitle("graph 1");
  gr1->SetMarkerStyle(5);
  gr1->SetMarkerColor(kRed);

  //por L e comentar o fit e o stat do fit correspondete -> pa desenhar linha a unir pontos
  //gr1->SetDrawOption("AP");
  //Com opçao L define a cor da linha que une os pontos, e a cor das barras de erro
  gr1->SetLineColor(1);
  gr1->SetLineWidth(1);
  gr1->SetFillStyle(0);

  
  double low_lim=0;
  double high_lim=20;
  //funcao a fittar 3-2 4-3 5-4
  TF1 *f1 = new TF1("f1","10+([0]-10)/(1+exp(-[1]*(x-[2])))");
  f1->SetParLimits(0,50,200);
  //f1->SetParLimits(1,0.8,1);
  // f1->SetParLimits(3,2000,3000);
  //f1->FixParameter(2,0);
  f1->SetLineColor(kBlue);

  
   gr1->Fit("f1","QMF","",low_lim,high_lim);


  c1->Update();

  
 //grafico 2
  // string dados1 = "calFN2.txt";
  TGraph *gr2 = new TGraphErrors("data.txt","%lg %lg");
  gr2->SetName("gr2");
  gr2->SetTitle("graph 2");
  gr2->SetMarkerStyle(5);
  gr2->SetMarkerColor(kBlack);

  //por L e comentar o fit e o stat do fit correspondete -> pa desenhar linha a unir pontos
  //gr1->SetDrawOption("AP");
  //Com opçao L define a cor da linha que une os pontos, e a cor das barras de erro
  gr2->SetLineColor(1);
  gr2->SetLineWidth(1);
  gr2->SetFillStyle(0);

 double low_lim1=20;
  double high_lim1=75;
  //funcao a fittar 3-2 4-3 5-4
  TF1 *f2 = new TF1("f2","50+([0]-50)/(1+exp(-[1]*(x-[2])))");
  f2->SetParLimits(0,50,200);
  // f2->SetParLimits(2,60,70);
   f2->SetParLimits(1,0,3000);
  //f1->FixParameter(2,0);
  f2->SetLineColor(kRed);

  
   gr2->Fit("f2","QMF","",low_lim1,high_lim1);
 



  c1->Update();
  
  
  //   gPad->SetLogx();
  // mg->Add(gr1);
  //TGraphErrors *gr2 = new TGraphErrors("dados2.txt","%lg %lg %lg %lg"); 
  //mg->Add(gr2);

 

  
  //   gPad->SetLogx();

	  
    
  TLine*  line = new TLine(45,0,45,200);
  line->SetLineStyle(1);
  
 mg->Draw("AP");

  mg->Add(gr1);
  
  mg->Add(gr2);
  c1->Update();

  
  TLegend* legend = new TLegend(0.6, 0.8, .9, .9);
  legend->AddEntry(line, "Pop reaches new food site", "l");

  line->Draw();
  line->SetLineColor(kGreen+1);
  legend->Draw();
  

  //Draws, prints e updates no canvas
  // mg->Draw("AP");
  mg->GetXaxis()->SetLimits(0,100);
    mg->GetXaxis()->SetTitle("Days");
  mg->GetYaxis()->SetTitle("Population");
  mg->SetMinimum(0.);
  mg->SetMaximum(200);
  c1->Update();

  //legenda
  // posiçao legenda (x,y) -> primeiro argumento x, ultimo argumento y
  // TLegend *leg = new TLegend(1,0.8,0.7,0.9);
  //argumentos add entry 
  //  L: draw line associated with TAttLine if obj inherits from TAttLine
  // P: draw polymarker associated with TAttMarker if obj inherits from TAttMarker
  // F: draw a box with fill associated wit TAttFill if obj inherits TAttFill
  //  E: draw vertical error bar 

  
  // leg->AddEntry("gr1","X=0.06m (T3)","lep");
  // leg->Draw();

  

  //box com resultados do fit


//box com resultados do fit
   TPaveStats *stats1 = (TPaveStats*)gr1->GetListOfFunctions()->FindObject("stats");
       TPaveStats *stats2 = (TPaveStats*)gr2->GetListOfFunctions()->FindObject("stats");
  stats1->SetTextColor(kBlue); 
   stats2->SetTextColor(kRed); 
    stats2->SetX1NDC(0.7); stats2->SetX2NDC(0.9); stats2->SetY1NDC(0.1); stats2->SetY2NDC(0.3);
     stats1->SetX1NDC(0.1); stats1->SetX2NDC(0.3); stats1->SetY1NDC(0.7); stats1->SetY2NDC(0.9);
 
   

  c1->Modified();
 
  c1->Print("plot.pdf");

  getchar();
  theApp.Terminate();
  return 0;
}
