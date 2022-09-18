#include "e23.h"
#include <string>
#include <iostream>
using namespace std;

alunoIST::alunoIST(int a, string b){number=a;branch=b;};
alunoIST::alunoIST(){number=0;branch=".";};
void alunoIST::SetNumber(int x){number=x;};
int alunoIST::GetNumber(){return number;};
void alunoIST::SetBranch(string k){branch=k;};
string alunoIST::GetBranch(){return branch;};
void alunoIST::print(){
  cout<<"Nome: "<<Name<<" nascido em "<<DataN<<" de " << branch << " com nota "<<number<<endl;
};
alunoIST::~alunoIST(){};

void Dummy(alunoIST **p){
  for (int i=0;i<10;++i)
    p[i]->print();
};
