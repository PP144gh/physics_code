#include "point1DEX.h"
using namespace std;
class point2D : public point1D {
 public: 
  point2D() {;}
  point2D(double xx, double yy);
  virtual double Norma();
 virtual void Print();
protected:
  double y;
};

