#include "MatFull.h"
#include "Vec.h"
#include<iostream>

class MatFullSolver : public MatFull{
 public:
  MatFullSolver();
  MatFullSolver(MatFull,Vec);
  void SwapRows(int,int);
  void LU();
  Vec Gauss();
 protected:
  Vec *b;
};
