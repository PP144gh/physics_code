#ifndef __MFULL__
#define __MFULL__
#include"Vec.h"
#include<iostream>
#include<vector>
#include"Mat.h"
using namespace std;

class MatFull : public Mat{
 public:
  // Constructors
  MatFull(int,int,double);
  MatFull(int,int,Vec&);
  MatFull(int,int,double*);
  MatFull(int,int,double** );
  MatFull(int,int,Vec*);
  // Copy Contructor
  MatFull(const MatFull&);
  // Default Constructor
  MatFull();
  // Methods
  void Print() const; 
  Vec GetRow(int) const;
  Vec GetCol(int) const;
  Vec operator|(const Vec&)const;
  MatFull operator*(const MatFull&) const;
  int GetNrows() const;
  int GetNcols() const;
  double Getmvec(const int,const int) const; 
  void Setmvec(int, int, double) const;
  //~MatFull(){/*~mvec;*/};
 protected:
  int ncols;
  Vec *mvec;
};
#endif
