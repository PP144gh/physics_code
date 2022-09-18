#include"point1DEX.h"
#include<cmath>
#include<iostream>
using namespace std;

class point2D : public point1D {
 public: 
  point2D(double z=0, double q=0){x=z;y=q;};
  double Norma(){return sqrt(x*x+y*y);};
  void Print(){cout<<"point2D("<<x<<","<<y<<")"<<endl<<sqrt(x*x+y*y)<<endl;};
protected:
  double y;
};

