#include<string>
using namespace std;

class point { 
  
 public:
  point() {;}
  virtual double Norma()=0; //calculate modulo 
  virtual void Print()=0; //print
  void Setname(string fname="") {name=fname;}
  
 protected:
  string name;
};

