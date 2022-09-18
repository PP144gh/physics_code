#ifndef __METNUM__
#define __METNUM__
#include<TROOT.h>
#include"TF1.h"
#include"TRandom.h"
#include<cmath>

class MetodosNumericos {
 public:
  MetodosNumericos(){;};
  static void ipLagrange(double*,double*,int,double,double&);
  static void ipNewthon(double*,double*,int,double,double&);
  static void ipNeville(double*,double*,int,double,double&);
  static void solBisectionMethod(TF1*,double,double,double,double&,double&);
  static void solFixedPointMethod(TF1*,double,double,double,double&,double&);
  static void solNewtonMethod(TF1*,double,double,double,double&,double&);
  static void solSecantMethod(TF1*,double,double,double,double&,double&);
  static void matLU(double**,int);
  static void matLU_resolve(double**,double*,int,double*);
  static void matLUdecomposition3(float*,float*,float*,int);
  static void matLUdecomposition3d(double*,double*,double*,int);
  static void matLUsolve3(float*,float*,float*,int,double*);
  static void matLUsolve3d(double*,double*,double*,int,double*); 
  static void matGauss(double**,double*,int,double*);
  static void der1h1 (TF1*,double,double,double&,double&);
  static void der1h2 (TF1*,double,double,double&,double&);
  static void der1h4 (TF1*,double,double,double&,double&);
  static void der2h2 (TF1*,double,double,double&,double&);
  static void der2h4 (TF1*,double,double,double&,double&);
  static void intTrapezoidalRule (TF1*,int,double,double,double&,double&);
  static void intSimpsonRule (TF1*,int,double,double,double&,double&);
  static void intMonteCarlo (TF1*,int,double,double,double&);
  static void intMC_pdf (TF1*,TF1*,int,double,double,double&);
  static void difRK2 (TF1*,double,double,double,double&);
  static void difRK4 (TF1*,double,double,double,double&);
  static void difEuler (TF1*,double,double,double,double&);
  static void difPredictorCorrector (TF1*,double,double,double,double&);
  static void difPVB2or1dim(TF1*,TF1*,TF1*,TF1*,double,double,double,double,int,double*);
 private:
};
#endif
