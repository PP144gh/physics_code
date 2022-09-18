#include "Pol.h"
#include <iostream>
using namespace std;

int main(){
  int a[]={0,0,2,4,0,1,0,0,1};
  int b[]={4,-2,0,0,1};
  Pol A("P1",8,a);
  Pol B("P2",4,b);
  cout<<"1. P(x) = 4P1(x)"<<endl;
  Pol C;
  A.Scale(4);
  A.PrintPol();
  A.Scale(1./4.);
  cout<<"2. P(x) = P1(x) + P2(x)"<<endl;
  C=A+B;
  C.PrintPol();
  cout<<"3. P(x) = P1(x) * P2(x)"<<endl;
  C=A*B;
  C.PrintPol();
  return 0;
}
