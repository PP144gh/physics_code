#include"Element.h"
#include<iostream>
using namespace std;

    /*  Default Constructor  */
Element::Element(){
  name="H";
  N=1;
  Z=1;
  A=1;
}

    /*  Constructor  */
Element::Element(string fname, int fZ, int fA, int fN){
  name=fname;
  Z=fZ;
  A=fA;
  N=fN;
}

    /*  Adds Physical Process to Element  */
void Element::SetPhysProcess(PhysProcess *p){
  v.push_back(p);
}

    /*  Prints all information available about Element  */
void Element::Print(){
  cout<<"Element: "<<name<<endl;
  cout<<":::::::::::::::::::::"<<endl<<endl;
  cout<<"Number of Elements: "<<N<<endl;
  cout<<"Atomic Number: "<<A<<endl;
  cout<<"Mass Number: "<<Z<<endl;
  cout<<endl<<"Physical Processes:"<<endl;
  for(unsigned int i=0;i<v.size();++i)
    cout<<"-->"<<v[i]->GetName()<<endl;
}

    /*  Changes N to n  */
void Element::SetN(int n){
  N=n;
}

    /*  Returns N  */
int Element::GetN(){
  return N;
}

    /*  Returns Physical Process n  */
PhysProcess* Element::Getv(int n){
  return v[n];
}
