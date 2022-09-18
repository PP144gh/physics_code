#include"TH1.h"
#include"TGraph.h"
#include<TROOT.h>

static double RoundOffError(int i);
TGraph* RoundOffErrorG(int imin, int imax);
TH1D* RoundOffErrorH(int imin, int imax);
