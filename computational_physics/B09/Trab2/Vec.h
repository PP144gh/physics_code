#ifndef __vec__
#define __vec__
#include <iostream>
#include <vector>
using namespace std;

class Vec {
 public: 
  Vec();	
  Vec (int);
  Vec (int,double*);
  Vec(int,double);
  Vec(const Vec&);

  void SetSize(const int);
  void SetEntrie(const int,const double);
  void SetEntries(const int,const double*);
  void SetEntries(const int,const double);
  void SetEntries(const int, const Vec&);
  double* GetEntries() const;
  int Size() const;
  const double dot(const Vec&);
  const Vec Scale(const double);
  const Vec& operator=( const Vec& );
  const Vec& operator+=(const Vec&);
  const Vec& operator -=(const Vec&);
  const Vec operator+(const Vec&); 
  const Vec operator+(); // z= +v = v
  const Vec operator-(const Vec&);
  const Vec operator-(); //simetrico
  const Vec operator*(const Vec&);
  const double operator[](int) const;
  void print() const; 
  //~Vec(){delete[] entries;};
 private:
  int N; //number of elements
  double *entries; //pointer to array of doubles
}; 
#endif
