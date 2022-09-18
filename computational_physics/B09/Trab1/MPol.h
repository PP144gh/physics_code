#ifndef __MPOL__
#define __MPOL__
#include "Pol.h"

class MPol {
 public:
  vector<string> ReadFile(string); //vetor que recebe polinomios dum file
  MPol(); //default constructor

  Pol Convert(string); // recebe uma string com um polinomio e retorna um objeto Pol com o respetivo coeficiente e grau
  void AddPol(Pol&); //adiciona polinomio ao fim da lista
  Pol FindPol(string);  //encontra um polinomio
  void DelPol(string); //remove polinomio do fim da lista
  vector<Pol> List(); //retorna o vetor de objetos pol (A lista)
 private: 
  vector<Pol> pollo; //vetor de objetos Pol (Lista)
};
#endif
