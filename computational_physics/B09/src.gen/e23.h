#ifndef __e22__
#define __e22__
#include "e22a.h"
#include <string>

class alunoIST : public pessoa {
 public:
  alunoIST(int a,string b);
  alunoIST();
  void SetNumber(int x);
  int GetNumber();
  void SetBranch(string k);
  string GetBranch();
  void print();
  ~alunoIST();
 private:
  int number;
  string branch;
};

void Dummy(alunoIST **p);
#endif
