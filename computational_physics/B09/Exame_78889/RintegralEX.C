#include <cmath>
#include "TF1.h"
#include "TRandom3.h"
using namespace std; 


int main() {
  TRandom3 rand(0);
  double xi;
  double r=0;
  double rs=0; //para o erro
  TF1 *f = new TF1 ("f","exp(-x*x)",0,1);
    // loop para calculo do integral
    for (int i=0; i<100; i++) {
      xi=rand.Uniform(0,1);
      r+=f->Eval(xi);
      rs+=f->Eval(xi)*f->Eval(xi);
    }
    r/=100; //valor  (b-a) =1
    rs/=100;
 double error=sqrt((rs-r*r)/100)*r;//  Integral error
  // imprimir resultados
 cout << "Valor Integral MC: " << r << "+/- " << error << endl;
}
