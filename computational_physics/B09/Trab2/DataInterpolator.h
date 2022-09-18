#include "TF1.h"
#include "TGraph.h"
#include <TROOT.h>
#include <TStyle.h>
#include <iostream>
using namespace std;

class DataInterpolator {
 public:
  // N data points
  DataInterpolator(int n, double* i, double*j);
  ~DataInterpolator() {delete[] x; delete[] y;} 
  TGraph* Draw(); //draw points

  // cubic spline (N knots)
  double* CubicSplineCurvatures(); // return k’s
  TF1* CubicSplineSegment(double* k, double o); // k=input curvatures
  TF1* CubicSpline(double* k); // k=input curvatures
  double CubicSplineDeriv(double* k, double a); // at point a
  double CubicSplineDerivN(double* k, double a);
  TF1* CubicSplineDeriva(double *k);

  //polynomial 
  //neville 
  TF1* NevPolynomial();
  //newton
  double * Newtoncoefficient();
  TF1* Polynomial();
  double PolynomialDerivN(double a);
  //lagrange
  TF1* LagPolynomial();
  //Dif stuff
  TGraph* DifInterpol(double* k);
  TGraph* DifCSDeriv(double* k);
  TGraph* DifNDeriv(double* k);

 private:
  double *x;
  double *y;
  int N;
};
//functors
double CSfunctor(double* e, double *par);
double CSDerivativefunctor(double *e, double *par);
double Nevfunctor(double* e, double *par);

