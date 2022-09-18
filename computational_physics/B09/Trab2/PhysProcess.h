#ifndef __PHY__
#define __PHY__
#include<string>
using namespace std;

class PhysProcess{
 public:
  PhysProcess(){;};//  Constructor does nothing since class is virtual
  virtual double Spectrum(double) = 0;//  Pure virtual function
  void SetName(string c){name=c;};//  Changes name to c
  string GetName(){return name;};//  Returns name of Physical Process
 protected:
  string name;//  Name of Physical Process
};
#endif
