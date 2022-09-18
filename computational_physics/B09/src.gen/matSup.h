#include"Vec.h"
#include"vector.h"
#include<iostream>
using namespace std;

class matSup{
 public:
  matSup(double**);
  double* GetMatrix1D();
  vector<Vec> GetMatrixV();
  Vec GetRow(vector<Vec>,int);
  Vec GetRow(double*,int);
  Vec GetRow(double**,int);
  Vec GetColumn(vector<Vec>,int);
  Vec GetColumn(double*,int);
  Vec GetColumn(double**,int);
  double Determinant(vector<Vec>,const Vec&);
  double Determinant(double*,const Vec&);
  double Determinant(double**,const Vec&);
  Vec Solve(vector<Vec>,const Vec&);
  Vec Solve(double*,const Vec&);
  Vec Solve(double**,const Vec&);
  bool Check(vector<Vec>,const Vec&,const Vec&);
  bool Check(double*,const Vec&,const Vec&);
  bool Check(double**,const Vec&,const Vec&);
 private:
  double **m;
  int Size;
};
