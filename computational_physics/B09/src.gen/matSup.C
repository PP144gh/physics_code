#include"matSup.h"

matSup::matSup(double **M){
  m=M;
}

double* matSup::GetMatrix1D(){
  double *p=new double[Size*Size];
  for(int i=0;i<Size;++i)
    for(int j=0;j<Size;++j)
      p[i+j]=m[i][j];
  return p;
}

vector<Vec> matSup::GetMatrixV(){
  vector<Vec> q;
  Vec Q(Size);
  for(int i=0;i<Size;++i){
    Q=m[i];
    q.push_back(Q);
  }
  return q;
}

Vec matSup::GetRow(vector<Vec> v, int i){
  return v[i];
}

Vec matSup::GetRow(double *p, int j){
  Vec Q(Size);
  for(int i=0;i<Size;++i)
    Q.SetEntrie(i,p[j*Size+i]);
  return Q;
}

Vec matSup::GetRow(double **p, int i){
  Vec Q=m[i];
  return Q;
}

Vec matSup::GetColumn(vector<Vec> v, int j){
  Vec T(Size);
  for(int i=0;i<Size;++i)
    T.SetEntrie(i,v[i].GetEntrie(j));
  return T;
}

Vec matSup::GetColumn(double *p, int j){
  vec T(Size);
  for(int i=0;i<Size;++i)
    T.SetEntrie(i,p[j+i*Size]);
  return T;
}

double matSup::Determinant(vector<Vec> v, const Vec& b){
  double det=0;
  return det;
}

double matSup::Determinant(double *p, const Vec& b){
  double det=0;
  return det;
}

double matSup::Determinant(double **q, const Vec& b){
  double det=0;
  return det;
}
