#include "TROOT.h"
#include "TApplication.h"
#include "TFrame.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include <fstream>
#include <sstream>
#include <iostream>


void makeHistogram(std::string fileName){

using namespace std;
	ifstream ifs(fileName.c_str());
	double pi;
	TCanvas* c=new TCanvas("c","c",600,600);
	TH1D* hist=new TH1D("hist",fileName.c_str(),10,0,5);
	while(ifs.is_open() && !ifs.eof()){
		ifs >> pi;
		hist->Fill(pi);
	}
	hist->Draw("");
	std::string pngFileName=fileName+".png";
	std::string pdfFileName=fileName+".pdf";
	c->SaveAs(pngFileName.c_str());
	c->SaveAs(pdfFileName.c_str());
	ifs.close();
}


int main(int argc,char **argv)
{
  makeHistogram("hist_data.txtt");
 
  return 0;
}
