#include <string>
#include "cFCgraphics.h"

#ifndef __CINT__
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TROOT.h>
#include <TGFrame.h> //gClient
#include <TCanvas.h>
#include <TPad.h>
#include <TSystem.h>
#include <TList.h>
#include <TApplication.h>
#include <TVirtualX.h>
#endif

using namespace std;

class Material {
 public:
  Material();
  Diamond (TF1*);
  ~Diamond()  {};
  void SetRefractiveIndex();
  TF1* GetRefractiveIndex ();
  void FitRefractiveIndex(TGraphErrors* );
  TGraphErrors* DrawRefractiveIndex(); //draw points
  //void DrawRefractiveIndex (); //draw points and function

 private:
  string name;
  TF1* index;
};
