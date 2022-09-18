#include <vector>
#include <string>
#include"PhysProcess.h"
using namespace std;

class Element{
 public:
    /*  Constructors  */
  Element();
  Element(string,int,int,int);

  void SetPhysProcess(PhysProcess*);//  Adds Physical Process to Element
  void Print();//  Prints information of Element
  void SetN(int);//  Changes number of Elements
  int GetN();//  Returns number of Elements
  PhysProcess* Getv(int);//  Returns Physical Process
 private:
  int N;//  Number of Elements
  int Z;//  Mass Number
  int A;//  Atomic Number
  string name;//  Name of Element
  vector<PhysProcess*> v;//  Vector with all Physical Processes atached to Element
};
