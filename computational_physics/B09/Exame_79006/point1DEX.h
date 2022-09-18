#include"pointEX.h"
#include<cmath>
#include<iostream>
using namespace std;

class point1D : public point {
 public: 
  point1D(double z=0){x=z;};
  double Norma(){return fabs(x);};
  void Print(){cout<<"point1D("<<x<<")"<<endl<<fabs(x)<<endl;}; 
protected:
  double x;
};

