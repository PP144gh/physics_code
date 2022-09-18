#include "MPol.h"
#include<iostream>
#include<string>
#include<vector>
#include<cstring>
#include "cTrab1.h"
using namespace std;

int main(){
  cTrab1 X;
  string x=X.GetPolOperations(B09);
  cout << endl << x << endl;
  // +R - S + P

  MPol p;
  vector<string> s;
  s=p.ReadFile("Pol.txt"); //passa polinomios do txt para o vetor
  for(int i=0;i<s.size();++i) 
    cout<<s[i]<<endl; //impressão das expressões dos polinomios
  cout<<endl<<endl;
  Pol P;
  P=p.Convert(s[0]); // Pol P
 
  p.AddPol(P);
  Pol Q;
  Q=p.Convert(s[1]); //Pol Q

  p.AddPol(Q);
  Pol R;
  R=p.Convert(s[2]);// Pol R
 
  p.AddPol(R);
  Pol S;
  S=p.Convert(s[3]); //Pol S

  p.AddPol(S);
  Pol T;
  T=p.Convert(s[4]); //Pol T
 
  p.AddPol(T);
  Pol U;
  U=p.Convert(s[5]); //Pol U

  p.AddPol(U);


  Pol A;
  A=R-S; //R-S

  p.AddPol(A); //Add à lista
  Pol B;
  B=A+P; // (R-S)+P
  p.AddPol(B); //Add à lista
 cout << "Lista total" << endl;
  vector<Pol> Z;
  Z=p.List();
  for (int i=0;i<Z.size();++i) {
    Z[i].PrintPol(); 
    if(i==5)
      cout << "Resultado de R-S " << endl;
    if(i==6)
      cout << "Resultado (R-S)+ P" << endl;
  }
 

  p.DelPol(s[1]);
  p.DelPol(s[4]);
  cout << "Lista sem Q e T" << endl;

  vector<Pol> W;
  W=p.List();
  for (int i=0;i<W.size();++i) 
    W[i].PrintPol();

 
  
 

  return 0;
}
