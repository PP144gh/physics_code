#include <iostream>
using namespace std;

class vector {
public:
  vector() {
    size = 5;
    vec = new double[size];
  }
  ~vector() { delete[]vec;} //delete do array existente na classe vector
  double* GetVector() {
    double tmp[size];
    for (int i = 0; i < size; i++){ tmp[i] = vec[i]; }
    double *tmp2 = tmp;
    return tmp2;
  }
  int GetSize() {return size;}
const double operator[] (int i) const{
  return vec[i];
}

private:
  double *vec;
  int size;
};


int main() {
  vector V;
 int size= V.GetSize();
  //print vector
  for (int i=0; i<size; i++) {
    cout << V[i] << endl; //impressao corrigida com definiçao do operador []
  }
  //get array defined inside vector and delete it
 
  double *f = new double [size];
   f=V.GetVector();
   //  delete[] f; nao e' preciso. f aponta para o V da classe, que e' apagado pelo destrutor.
}

