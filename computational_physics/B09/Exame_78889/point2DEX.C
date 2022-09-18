#include "point2DEX.h"
#include <cmath>
#include <iostream>
using namespace std;


point2D:: point2D(double xx, double yy) : point1D(xx) {
  y=yy;
}
double point2D::Norma() {
  double d=sqrt(x*x+y*y);
 cout <<"[point1D::Norma()] " << d << endl;
  return d; 
}
void point2D::Print() { 
  cout <<"[point1D::Print()] point1D(" << x <<","<<y<<")"<< endl;
}
