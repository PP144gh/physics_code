#include <cmath>

double f(double x){

  double r =0;
  r=sin(x)*sin(x);
  return r;
}


double z(double x) {

  double r =0;
  r=x+f(x);
  return r;
}
