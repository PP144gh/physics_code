#ifndef __e22a__
#define __e22a__
#ifndef __pessoa__
#define __pessoa__
#include <string>
#include <iostream>
using namespace std;

class pessoa {
public:
  pessoa(string, unsigned int) {;};
  ~pessoa(){;};
  void SetName(string c);
  void SetBourneDate(unsigned int a);
  string GetName();
  unsigned int GetBourneDate();
  virtual void print();

protected:
  string Name;
  unsigned int DataN;
};

pessoa **DoArray (int n){
  pessoa **p;
  p=new pessoa* [n];
  for (int i=0;i<n;++i)
    p[i]=new pessoa;	
  return p;
}

#endif
#endif
