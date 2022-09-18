#include <cmath>
 void fp(double x, double *r) {
 x=(x/180)*M_PI;
  *r=sqrt(sin(2*x));

}

void fr(double x, double &r) {
 x=(x/180)*M_PI;
  r=sqrt(sin(2*x));

}
double fv(double x){
  double r=0;
  x=(x/180)*M_PI;
  r=sqrt(sin(2*x));

  return r;
}
