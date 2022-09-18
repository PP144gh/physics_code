#include<iostream>
#include"Vec.h"
#include"Mat.h"
#include"MatFull.h"
#include"MatSparse.h"
using namespace std;

int main(){
  double **a=new double*[3];
  for (int i=0;i<3;++i)
    a[i]=new double[4];
  a[0][0]=2; a[0][1]=0;  a[0][2]=5; a[0][3]=0;
  a[1][0]=0; a[1][1]=-7; a[1][2]=0; a[1][3]=-2;
  a[2][0]=1; a[2][1]=0;  a[2][2]=3; a[2][3]=0;

  double **b=new double*[5];
  for(int i=0;i<5;++i)
    b[i]=new double[4];
  b[0][0]=0; b[0][1]=10; b[0][2]=5; b[0][3]=0;
  b[1][0]=5; b[1][1]=0;  b[1][2]=8; b[1][3]=-2;
  b[2][0]=1; b[2][1]=-5; b[2][2]=0; b[2][3]=6;
  b[3][0]=0; b[3][1]=0;  b[3][2]=0; b[3][3]=0;
  b[4][0]=1; b[4][1]=0;  b[4][2]=3; b[4][3]=0;
   
  double **c=new double*[5];
  for (int i=0;i<5;++i)
    c[i]=new double[5];
  c[0][0]=1; c[0][1]=7;  c[0][2]=5;  c[0][3]=3;   c[0][4]=-3;
  c[1][0]=5; c[1][1]=2;  c[1][2]=8;  c[1][3]=-2;  c[1][4]=4;
  c[2][0]=1; c[2][1]=-5; c[2][2]=-4; c[2][3]=6;   c[2][4]=7.6;
  c[3][0]=0; c[3][1]=-5; c[3][2]=3;  c[3][3]=3.2; c[3][4]=3.3;
  c[4][0]=1; c[4][1]=7;  c[4][2]=2;  c[4][3]=2.1; c[4][4]=1.2;

  MatFull A(3,4,a);
  MatSparse Sa(A);
  cout << "Matriz A " << endl;
  Sa.Print();
  MatFull B(5,4,b);
  MatSparse Sb(B);
  cout << "Matriz B" << endl;
  Sb.Print();
  MatFull C(5,5,c);
  MatSparse Sc(C);
  cout << "Matriz C*B" << endl;
  (Sc*Sb).Print();
}
