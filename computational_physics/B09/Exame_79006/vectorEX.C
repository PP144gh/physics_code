#include <iostream>
using namespace std;

class vector {
public:
  vector() {
    size = 5;
    vec = new double[size];
  }
  ~vector() {delete []vec;}
  const double operator[](int i) const{
    return vec[i];
  }
  double* GetVector() {
    double *tmp=new double[size];
    for (int i = 0; i < size; i++) tmp[i] = vec[i];
    double *tmp2 = tmp;
    return tmp2;
  }
  int GetSize() {return size;}
private:
  double *vec;
  int size;
};


int main() {
  vector V;
  //print vector
  for (int i=0; i<V.GetSize(); i++) {
    cout << V[i] << endl;
  }
  //get array defined inside vector and delete it
  double *f = V.GetVector();
  delete []f; 
}

