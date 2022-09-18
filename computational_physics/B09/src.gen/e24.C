#include "e24.h"
#include "e23.h"
#include "e22a.h"

Turma::Turma(alunoIST **c, int n){va=c;Nalunos=n;}; 
Turma::Turma(){va=NULL;Nalunos=0;};
Turma::Turma(Turma& t){va=t.va;Nalunos=t.Nalunos;};
Turma& Turma::operator=(const Turma& t){
  if(this!=&t)
    {va=t.va;Nalunos=t.Nalunos;}
  return (*this);
}
void Turma::SetAluno (alunoIST* const k){*va=k;};
alunoIST* Turma::FindAluno(){return (*va);};
int Turma::GetNalunos(){return Nalunos;};
Turma::~Turma(){}; 
