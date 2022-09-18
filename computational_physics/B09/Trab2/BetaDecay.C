#include"BetaDecay.h"
#include<cmath>
#include"TRandom.h"

    /*  Default Constructor  */
BetaDecay::BetaDecay(){
  Q=1;
  T12=1;
}

    /*  Constructor  */
BetaDecay::BetaDecay(double p, double q){
  T12=p;
  Q=q;
}

    /*  Changes T12 to t  */
void BetaDecay::SetT12(double t){
  T12=t;
}

    /*  Changes Q to q  */
void BetaDecay::SetQ(double q){
  Q=q;
}

    /*  Returns T12  */
double BetaDecay::GetT12(){
  return T12;
}

    /*  Returns Spectrum of Electron  */
double BetaDecay::Spectrum(double T){
  return (sqrt(T*T+2*T*9.1*9*exp10(-15))*sqrt(Q-T)*(T+9.1*9*exp10(-15)));
}

    /*  Return the number of Elements that decayed in t seconds  */
int BetaDecay::DecayRate(int N, double t){
  double p=log(2)/T12*t;//  Probability of decay
  double d=24*60*60;//  Passes t from seconds to days
  int u=0;
  for(int i=0;i<t/d;++i)
    for(int j=0;j<N;++j)
      if(gRandom->Rndm()<p)
	++u;
  return u;
}
