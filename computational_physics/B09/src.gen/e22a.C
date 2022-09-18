#include <string>
#include <iostream>
using namespace std;

string g=".";
unsigned int tt=0;

#include "e22a.h"

pessoa::pessoa(string c,unsigned int t){Name=c;DataN=t;};
pessoa::pessoa(){Name=g;DataN=tt;};
void pessoa::SetName(string c){Name=c;};
void pessoa::SetBourneDate(unsigned int a){DataN=a;};
string pessoa::GetName(){return Name;};
unsigned int pessoa::GetBourneDate(){return DataN;};
void pessoa::print(){cout<<"Nome: "<<Name<<" nascido em "<<DataN<<endl;};
pessoa::~pessoa(){};

// pessoa **DoArray (int n){
//   pessoa **p;
//   p=new pessoa* [n];
//   for (int i=0;i<n;++i)
//     p[i]=new pessoa;	
//   return p;
}
