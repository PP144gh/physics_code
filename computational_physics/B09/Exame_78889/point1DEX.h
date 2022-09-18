#include "pointEX.h"
#include <cmath>
#include <iostream>
using namespace std;
class point1D : public point {
 public: 
  point1D(){;}
  point1D(double xx);
  virtual double Norma();
  virtual void Print();
 protected:
  double x;
};

