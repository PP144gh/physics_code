#include<TROOT.h>
#include"TF1.h"

class ODEsolver{
 public:
  ODEsolver(TF1*,double,double,double);
  void SetTi(double);
  void SetYi(double);
  double IterEuler();
  double IterPredictorCorrector();
  double RK2();
  double RK4();
 private:
  TF1 *f;
  double ti;
  double yi;
  double step;
};
