#include "cFCgraphics.h"
#include "DataInterpolator.h"
#include "Vec.h"
#include "EqSolver.h"
#include "TLatex.h" //Legenda no Grafico das sobreposiçoes

using namespace std;
int main () {
  cFCgraphics gr;
  TPad *pad1=  gr.CreatePad("Pad1");
  TPad *pad2 = gr.CreatePad("Pad2");
  TPad *pad3=gr.CreatePad("Pad3");
  TPad *pad4= gr.CreatePad("Pad4");

  //pontos
  int N=9;
  double*x=new double [9];
  double *y=new double [9];

  x[0]=0.;
  x[1]=25.;
  x[2]=50.;
  x[3]=75.;
  x[4]=100.;
  x[5]=125.;
  x[6]=150.;
  x[7]=175.;
  x[8]=200.;
  y[0]=10.6;
  y[1]=16.0;
  y[2]=45.0;
  y[3]=83.5;
  y[4]=52.8;
  y[5]=19.9;
  y[6]=10.8;
  y[7]=8.25;
  y[8]=4.7;

  DataInterpolator A(N,x,y);

  double *k= A.CubicSplineCurvatures();
  //b
  TGraph *g=A.Draw();
  g->SetMarkerColor(kBlack-2);
  g->SetMarkerStyle(8);
  gr.AddObject(g,"Pad1","ap");
  TLatex *latex = new TLatex(g->GetX()[5], g->GetY()[3],"CubicSpline");
  g->GetListOfFunctions()->Add(latex);
  latex->SetTextSize(0.06);
  latex->SetTextColor(kRed);
  TLatex *latex2 = new TLatex(g->GetX()[5], g->GetY()[3]-5,"Newton Polynomial");
  g->GetListOfFunctions()->Add(latex2);
  latex2->SetTextSize(0.06);
  latex2->SetTextColor(kGreen+2);
 TLatex *latex3 = new TLatex(g->GetX()[5], g->GetY()[3]-10,"Points");
  g->GetListOfFunctions()->Add(latex3);
  latex3->SetTextSize(0.06);
  latex3->SetTextColor(kBlack);
 
 TF1* r=A.CubicSpline(k);

  r->SetLineColor(kRed);
  r->SetLineWidth(2);
  gr.AddObject(r,"Pad1","same");
 
    TF1* p=A.Polynomial();
  p->SetLineColor(kGreen+2);
  p->SetLineWidth(2);
  gr.AddObject(p,"Pad1","same");

  gr.DumpPad("Pad1");
  gr.AddObject(pad1);
 

  //c
  TGraph* u=A.DifInterpol(k);
  u->SetMarkerColor(kViolet-6);
  gr.AddObject(u);
  //d
  TGraph* v=A.DifCSDeriv(k);
  v->SetMarkerColor(kTeal-6);
  gr.AddObject(v);
 
  //e
  TGraph* t=A.DifNDeriv(k);
  t->SetMarkerColor(9);
  gr.AddObject(t);

  //extra
  TF1* j =A.CubicSplineDeriva(k);
  j->SetLineColor(46);
  j->SetLineWidth(2);
  gr.AddObject(j,"Pad2");
  gr.DumpPad("Pad2");
  gr.AddObject(pad2);

  TF1* j1 =A.LagPolynomial();
  j1->SetLineColor(kBlue);
  j1->SetLineWidth(2);
  gr.AddObject(j1,"Pad3");
  gr.DumpPad("Pad3");
  gr.AddObject(pad3);

  TF1* j2 =A.NevPolynomial();
  j2->SetLineColor(kTeal);
  j2->SetLineWidth(2);
  gr.AddObject(j2,"Pad4");
  gr.DumpPad("Pad4");
  gr.AddObject(pad4);

  //a (aqui para se ver ao mesmo tempo que os graficos)
 cout << "************************************************" << endl;
  cout << "Valor da Interpolaçao por Cubic Spline no ponto de Energia 57.3: "<<  r->Eval(57.3)<< " mbarn" << endl;
  cout << "Valor da Interpolaçao por Polinomio no ponto de Energia 57.3: "<<  p->Eval(57.3)<<" mbarn" <<  endl;
 cout << "************************************************" << endl;

  gr.Draw();

  delete[] k;
  return 0;
}
