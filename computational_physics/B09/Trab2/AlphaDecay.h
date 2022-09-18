#ifndef __ALPHA__
#define __ALPHA__
#include "PhysProcess.h"

class AlphaDecay : public PhysProcess {
 public:
    /*  Constructors  */
  AlphaDecay();
  AlphaDecay(double,double);
 
  void SetT12(double);//  changes T12
  void SetQ(double);//  changes Q
  double Spectrum(double);//  return Spectrum of electron
  double GetT12();//  return T12
  int DecayRate(int,double);//  return number of Elements that Decayed
 protected:
  double T12;//  in seconds
  double Q;//  in MeV
};
#endif
