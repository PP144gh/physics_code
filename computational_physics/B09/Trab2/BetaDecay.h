#ifndef __BETA__
#define __BETA__
#include "PhysProcess.h"
#include "TROOT.h"

class BetaDecay : public PhysProcess {
 public:
    /*  Constructors  */
  BetaDecay();
  BetaDecay(double,double);
  
  void SetT12(double);//  changes T12
  void SetQ(double);//  changes Q
  double Spectrum(double);//  return Spectrum of electron
  double GetT12();//  return T12
  int DecayRate(int,double);//  return number of Elements that decayed
 protected:
  double T12;//  in Seconds
  double Q;//  in MeV
};
#endif
