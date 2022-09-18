#include "Vec.h"

class EqSolver{
 public:
    /*  Constructors  */
  EqSolver();
  EqSolver(double**,double*,int);
  
  void Print();//  Prints augmented matrix 
  void SwapRows(int,int);//  Swaps Rows
  void LU();//  LU decomposition for general matrix
  Vec LU_resolve(Vec);//  LU=b solving for general matrix
  void LUdecomposition3(float*,float*,float*,int);//  LU decomposition for tridiagonal matrix
  void LUdecomposition3d(double*,double*,double*,int);//ex 3
  void LUsolve3(float*,float*,float*,int,double*);//  LU=b solving for tridiagonal matrix
  void LUsolve3d(double*,double*,double*,int,double*); //ex 3
  Vec Gauss();//  Gauss Elimination
 private:
  double **m;//  Coeficient Matrix
  double *b;//  Independent Vector
  int size;//  Number of rows
};
