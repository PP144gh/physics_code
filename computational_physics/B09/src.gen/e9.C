#include <cmath>
using namespace std;
double mainSum(int *vi,int *vj) {
  double r=0;
  for(int i=0; i<=*vi; ++i) {
    //	cout <<"i= "<<i <<"  "<<   x << endl;   Utilizado no main, para testar
    for(int j=5;j<=*vj;++j) {
      r+= cos (pow(i,2) + pow(j,0.5));
      //	  cout << "j= "<< j<< " " << x << endl; Utilizado no main, para testar
    }
  }
  return r;
}
