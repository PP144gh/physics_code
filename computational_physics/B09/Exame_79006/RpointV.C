#include"point2DEX.h"
#include<vector>
using namespace std;

int main() {
  vector<point*> v;
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
  for (int i=0; i<v.size(); i++) {
    v[i]->Print();
  }

  //calcular a norma de cada ponto, seriar e imprimir os pontos no sentido  
  //crescente da norma 

  double *a=new double[v.size()];
  for(int i=0;i<v.size();++i)
    a[i]=v[i]->Norma();

  int j=0;
  double aux;
  while(1){
    j=0;
    for (int i=0;i<v.size()-1;++i)
      if (a[i]>a[i+1]){
	aux=a[i];
	a[i]=a[i+1];
	a[i+1]=aux;
	j=1;
      }
    if (j==0)
      break;
  }

  cout<<endl;
  for(int i=0;i<v.size();++i)
    cout<<a[i]<<endl;
}
