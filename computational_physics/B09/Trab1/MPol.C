#include"MPol.h"
#include<fstream>
#include<cstdlib>
using namespace std;

MPol::MPol(){ //default constructor
}

vector<string> MPol::ReadFile (string c){ 
  ifstream file ("Pol.txt");
  string pol;
  vector<string> lpol;
  while(getline(file, pol)) {
    lpol.push_back(pol); //passa valores do file para lpol pelo metodo de pushback
 }
  file.close();
  return lpol;
}

Pol MPol::Convert (string t){
  vector<int> b;
  char f[10];
  size_t found=t.find("X");
  int u=0;

  while(1){ //ciclo onde se proura o X
    if (found!=string::npos){
      b.push_back(found);
      found=t.find("X",found+1);
    }
    else
      break;
  }

  vector<int> *v=new vector<int>[b.size()];

  for (int i=0;i<b.size();++i){
    f[0]=t[b[i]+2];
    v[i].push_back(atoi(f));
  }
  for(int i=0;i<b.size();++i){
    u=0;
    f[0]=t[b[i]-1];
    if (f[0]=='+') //verificar se está um + antes do coeficiente
      v[i].push_back(1);
    else if (f[0]=='-')//verificar se está um - antes do coeficiente
      v[i].push_back(-1);
    else{
      while( (f[u-1]!=' ') && (f[u-1]!='+') && (f[u-1]!='-') ){
	f[u]=t[b[i]-2-u];
	++u;
      }
      char g[u-2];
      for (int j=0;j<u-1;++j)
	g[j]=f[u-2-j];
      if (f[u-1]=='-')
	v[i].push_back(-atoi(g)); //insere o simetrico do modulo coeficiente no vetor, pois está um -antes do numero na string
      else
	v[i].push_back(atoi(g));
    }
  }

  vector<int> aux(2,1);
  int j;
  while(1){
    j=0;
    for (int i=0;i<b.size()-1;++i)
      if (v[i][0]>v[i+1][0]){
	aux=v[i];
	v[i]=v[i+1];
	v[i+1]=aux;
	j=1;
      }
    if (j==0)
      break;
  }

  string k="l";
  int gg=v[b.size()-1][0];
  int a[gg];
  j=0;
  for (int i=0;i<=gg;++i){
    if (v[j][0]==i){
      a[i]=v[j][1];
      ++j;
    }
    else
      a[i]=0;
  }

  Pol P(k,gg,a);
  return P;
}

void MPol::AddPol(Pol& o){ //adiciona pol o  ao vetor de objetos Pol pollo
  pollo.push_back(o);
}

Pol MPol::FindPol(string c){
  Pol p;
  p=Convert(c); //descodifica o grau e coeficientes do pol na string c e retorna um pol p com essas carateristicas
  for (int i=0;i<pollo.size();++i)
    if (p==pollo[i])
      return p;
  Pol T("Erro",1);
  return T;
}

void MPol::DelPol(string c){ 
  Pol p;  
  p=Convert(c);
  for (int i=0;i<pollo.size();++i)
    if (p==pollo[i])
      pollo.erase(pollo.begin()+i);
}

vector<Pol> MPol::List(){
  return pollo;
}
