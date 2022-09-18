#ifndef __MAT__
#define __MAT__
#include<iostream>
#include<vector>
#include"Vec.h"
#include<cmath>
using namespace std;

class Mat{
 public:
  virtual void Print() const  = 0;
  virtual Vec GetRow(int) const = 0;
  virtual Vec GetCol(int) const = 0;
  virtual Vec operator|(const Vec&) const = 0;
 protected:
  int nrows; //nb of rows
};

  #endif

  
