#include"AlphaDecay.h"
#include<cmath>
#include"TRandom.h"

    /*  Default Constructor  */
AlphaDecay::AlphaDecay(){
  Q=1;
  T12=1;
}

    /*  Constructor  */
AlphaDecay::AlphaDecay(double p, double q){
  T12=p;
  Q=q;
}

    /*  Changes T12 to t  */
void AlphaDecay::SetT12(double t){
  T12=t;
}

    /*  Changes Q to q  */
void AlphaDecay::SetQ(double q){
  Q=q;
}

    /*  Returns T12  */
double AlphaDecay::GetT12(){
  return T12;
}

    /*  Returns Spectrum of Electron  */
double AlphaDecay::Spectrum(double T){
  return 0;//  zero because the function isn't known
}


    /*  Return the number of Elements that decayed in t seconds  */
int AlphaDecay::DecayRate(int N, double t){
  double p=log(2)/T12*t;//  Probability of decay
  double d=24*60*60;//  Passes t from seconds to days
  int u=0;
  gRandom->SetSeed(0);
  for(int i=0;i<t/d;++i)
    for(int j=0;j<N;++j)
      if(gRandom->Rndm()<p)
	++u;
  return u;
}
