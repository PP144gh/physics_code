#ifndef __MSPARSE__
#define __MSPARSE__
#include"Vec.h"
#include<iostream>
#include<vector> 
#include"Mat.h"
#include"MatFull.h"
using namespace std;

class MatSparse : public Mat{
 public:
  //  Constructors
  MatSparse(int, int, double*, int*, int*);
  //  Default Constructor
  MatSparse(); 
  //  Copy Constructor
  MatSparse(const MatSparse&);
  //  Constructor from MatFull
  MatSparse(const MatFull&);
  //  Methods
  void Print() const;
  Vec GetCol(int) const;
  Vec GetRow(int) const;
  MatSparse operator*(const MatSparse&) const;
  Vec operator|(const Vec&) const;
  const MatSparse& operator=(MatSparse&);
  int Getnrows() const;
  int Getncols() const;
  void SparseToFull(double**) const;
  //~MatSparse(){delete[] a;delete[] b;delete[] c;};
 private:
  int ncols;
  int NN;
  double *a; 
  int *b; 
  int *c; 
};
#endif
