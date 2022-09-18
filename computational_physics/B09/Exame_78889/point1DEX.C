#include "point1DEX.h"
#include <cmath>
#include <iostream>
using namespace std;


point1D:: point1D(double xx) {
  x=xx;
}
double point1D::Norma() {
  double d=sqrt(x*x);
 cout <<"[point1D::Norma()] " << d << endl;
  return d; 
}
void point1D::Print() { 
  cout <<"[point1D::Print()] point1D(" << x <<")"<< endl;
}



