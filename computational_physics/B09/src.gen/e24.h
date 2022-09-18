#ifndef __e24__
#define __e24__
#include "e23.h"
#include "e22a.h"

class Turma {
public:
  Turma(alunoIST **c, int n); 
  Turma();
  Turma(Turma& t);
  Turma& operator=(const Turma& t);
  void SetAluno (alunoIST* const k);
  alunoIST* FindAluno();
  int GetNalunos();
  ~Turma(); 
private:
  alunoIST **va;
  int Nalunos;
};
#endif
