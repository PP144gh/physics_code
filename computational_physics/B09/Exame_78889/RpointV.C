#include <vector>
#include "point2DEX.h"
using namespace std;
int main() {
  vector <point*> v;
  v.push_back(new point1D(10.));
  v.push_back(new point2D(4.,4.));
   v.push_back(new point1D(1.));
   v.push_back(new point2D(3.,3));
   v.push_back(new point2D(2.,3));
   v.push_back(new point2D(5.,3));
   v.push_back(new point2D(1.,3));
   v.push_back(new point1D(5.));
   v.push_back(new point1D(4.));
   v.push_back(new point2D(10.,5));

  //imprimir a lista de pontos tal qual foi introduzida
  for (size_t i=0; i<v.size(); i++) {
    cout << "Pontos" << endl;
    v[i]->Print();
  }

  //calcular a norma de cada ponto, seriar e imprimir os pontos no sentido  
  //crescente da norma 
  double a [10];
  double b[10];
  double tmp;
  cout <<"Normas Desordenadas" << endl;
  for (size_t i=0; i< v.size(); i++) {
    a[i] = v[i]->Norma();
    b[i]=  a[i];
  }
  //bubble sort kind of
  for(size_t j=0; j <(v.size()-1); ++j) {
    for (size_t i=0; i<v.size()-j-1 ; i++) {
      if (a[i]>a[i+1]){
	tmp=a[i];
	a[i]=a[i+1];
	a[i+1]=tmp;
      }
    }
  }
  cout << "Normas ordenadas" << endl;
  for (size_t i=0; i< v.size(); i++) {
    cout << a[i]<< endl;
  }


  cout <<"Pontos ordenados por ordem crescente de norma:"<< endl;
  for (size_t j=0; j<v.size(); j++) {
    for (size_t i=0; i< v.size(); i++) {
      if(a[j]==b[i]){
	v[i]->Print();
      }
    }
  }
}
