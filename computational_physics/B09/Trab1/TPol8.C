#include "Pol.h"
#include<iostream>
#include"cTrab1.h"
#include<cmath>
using namespace std;

int main(){
  int a[]={1,-8,28,-56,70,-56,28,-8,1};
  Pol P("P",8,a);
  for(double x=0.99996;x<1.00011;x+=0.00001)
    cout<<x<<"::::::::"<<P.eva(x)<<"  --->  "<<cTrab1::P8(x)<<endl;
}
