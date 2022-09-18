#include"Pol.h"
#include<string>
#include<vector>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;

    /*  Default Constructor  */

Pol::Pol(){nome="polinomio";grau=0;coef.push_back(0);}

    /*  Constructors  */

Pol::Pol(string k,int n){
  nome=k;
  grau=n;
  for (int i=0;i<=n;++i)
    coef.push_back(0);
}

Pol::Pol(string k,int n,int* a){
  nome=k;
  grau=n;
  for (int i=0;i<=n;++i)
    coef.push_back(a[i]);
}

Pol::Pol(string k,int n,vector<double> a){
  nome=k;
  grau=n;
  for (int i=0;i<=n;++i)
    coef.push_back(a[i]);
}

    /*  Copy Constructor  */

Pol::Pol(const Pol& p){
  nome=p.nome;
  grau=p.grau;
  for(int i=0;i<=grau;++i)
    coef.push_back(p.coef[i]);
}

Pol::Pol(Pol* p){
  nome=p->nome;
  grau=p->grau;
  for(int i=0;i<=grau;++i)
    coef.push_back(p->coef[i]);
}

    /*  Logical Iqual  */

int Pol::operator==(const Pol& t){
  if (nome!=t.nome)
    return 0;
  if (grau!=t.grau)
    return 0;
  for (int i=0;i<grau;++i)
    if (coef[i]!=t.coef[i])
      return 0;
  return 1;
}

    /*  Copy Assignment  */

Pol& Pol::operator=(const Pol& t){
  if(this!=&t){
    nome=t.nome;
    grau=t.grau;
    if (!coef.empty())
      coef.clear();
    for(int i=0;i<=grau;++i)
      coef.push_back(t.coef[i]);
  }
  return (*this);
}

    /*  += Operator  */

Pol& Pol::operator+=(const Pol& t){
  if (grau>t.grau)
    for(int i=0;i<=t.grau;++i)
      coef[i]+=t.coef[i];
  else{
    for(int i=grau+1;i<=t.grau;++i)
      coef[i]=0;
    for(int i=0;i<=t.grau;++i)
      coef[i]+=t.coef[i];
    grau=t.grau;
  }
  return (*this);
}

    /*  -= Operator  */

Pol& Pol::operator-=(const Pol& t){
  if (grau>t.grau)
    for(int i=0;i<=t.grau;++i)
      coef[i]-=t.coef[i];
  else{
    for(int i=grau+1;i<=t.grau;++i)
      coef[i]=0;
    for(int i=0;i<=t.grau;++i)
      coef[i]-=t.coef[i];
    grau=t.grau;
  } 
  return (*this);
}

    /*  + Operator  */

Pol Pol::operator+(const Pol& t){
  if (grau>t.grau){
    int a[grau+1];
    for(int i=0;i<=t.grau;++i)
      a[i]=coef[i]+t.coef[i];
    for(int i=t.grau+1;i<=grau;++i)
      a[i]=coef[i];
    Pol P("p",grau,a);
    return P;
  }
  else {
    int a[t.grau+1];
    for(int i=0;i<=grau;++i)
      a[i]=t.coef[i]+coef[i];
    for(int i=grau+1;i<=t.grau;++i)
      a[i]=t.coef[i];
    Pol P("p",t.grau,a);
    return P;
  }
}

    /*  - Operator  */

Pol Pol::operator-(const Pol& t){
  if (grau>t.grau){
    int a[grau+1];
    for(int i=0;i<=t.grau;++i)
      a[i]=coef[i]-t.coef[i];
    for(int i=t.grau+1;i<=grau;++i)
      a[i]=coef[i];
    Pol P("p",grau,a);
    return P;
  }
  else {
    int a[t.grau+1];
    for(int i=0;i<=grau;++i)
      a[i]=-t.coef[i]+coef[i];
    for(int i=grau+1;i<=t.grau;++i)
      a[i]=-t.coef[i];
    Pol P("p",t.grau,a);
    return P;
  }
}

    /*  * Operator  */

Pol Pol::operator*(const Pol&t){
  int c=grau+t.grau;
  int a[c+1];
  for (int i=0;i<=c;++i)
    a[i]=0;
  for(int i=0;i<=grau;++i)
    for(int j=0;j<=t.grau;++j)
      a[i+j]+=coef[i]*t.coef[j];
  Pol A("vezes",c,a);
  return A;
}

    /*  *= Operator  */

Pol& Pol::operator*=(const Pol& t){
  int b=grau;
  grau+=t.grau-1;
  int a[grau+1];
  for (int i=0;i<=grau;++i)
    a[i]=0;  
  for(int i=0;i<=grau;++i){
    for(int j=0;(j<=i)&&(j<=b);++j)
      a[i]+=coef[j]*t.coef[i-j];
    cout<<a[i]<<"::::";
  }
  cout<<endl;
  if(!coef.empty())
    coef.clear();
  for(int i=0;i<=grau;++i)
    coef.push_back(a[i]);
  return (*this);
}

    /*  Set Polynom  */

void Pol::SetPolynomial(int a,int* b){
  nome="polinomio";
  grau=a;
  for (int i=0;i<=grau;++i)
    coef.push_back(b[i]);
}

    /*  Set Coefficient a to Value b  */

void Pol::SetCoefficient(int a,int b){
  coef[a]=b;
}

    /*  Print  */

void Pol::Print(){
  cout<<"polynomial: "<<nome<<"["<<grau<<"] coeffs = ";
  for(int i=0;i<=grau;++i)
    cout<<coef[i]<<" ";
  cout<<endl;
}

void Pol::PrintPol(){
  cout<<"polynomial: "<<nome<<"["<<grau<<"] = ";
  for(int i=0;i<=grau;++i){
    if (coef[i]>0){
      if (coef[i]==1)
	cout<<"+x^"<<i<<" ";
      else
	cout<<"+"<<coef[i]<<"x^"<<i<<" ";
    }
    else if (coef[i]<0){
      if (coef[i]==-1)
	cout<<"-x^"<<i<<" ";
      else
	cout<<coef[i]<<"x^"<<i<<" ";
    }
  }
  cout<<endl;
}

    /*  Gets value of Polynom in z  */

double Pol::evaluate (double z){
  double x=0.;
  for(int i=0;i<=grau;++i)
    x+=coef[i]*pow(z,i);
  return x;
}

    /*  Multiplies Polynom with double  */

void Pol::Scale(double x){
  for(int i=0;i<=grau;++i)
    coef[i]*=x;
}

    /*  Return Name  */

string Pol::GetNome(){
  return nome; 
}

    /*  Return Degree  */

int Pol::GetGrau(){
  return grau;
}

    /*  Return Coefficient a  */

int Pol::GetCoef(int a){
  return coef[a];
}

    /*  Set Polynom Name  */

void Pol::SetNome(string x){
  nome=x;
}

    /*  Set Degree Name  */

void Pol::SetGrau(int x){
  grau=x;
}

    /*  Set all Coeficients  */

void Pol::SetCoef(int *a){
  for (int i=0;i<grau;++i)
    coef[i]=a[i];
}

void Pol::SetCoef(vector<double> a){

  coef=a;
}

    /*  Returns Polynom Derivates  */

const Pol Pol::derivada(){
  int *a=new int[grau-1];
  for(int i=0;i<grau-1;++i)
    a[i]=coef[i+1]*i+coef[i+1];
  Pol P("deribada",grau-1,a);
  delete[] a;
  return P;
}

vector<double> Pol::ruffini(double x){
   vector<double> a;
   a.push_back(GetCoef(GetGrau()));
   int u=1;
   for (int i=GetGrau()-1;i>-1;--i){
     a.push_back(GetCoef(i)+x*a[u-1]);
     ++u;
   }
   a.pop_back();
   reverse(a.begin(),a.end());
   return a;
}

double Pol::eva(double x){
  Pol B("P",grau,coef);
  int u=0;
  int a=0,b;
  double d;
  vector<double> t;
  if(abs(evaluate(x))>exp(-2))
    return (evaluate(x));
  else{while(abs(B.evaluate(x))<exp(-2)){
      t=B.ruffini(x);
      B.SetGrau(t.size()-1);
      B.SetCoef(t);
      ++u;
    }
    if ( abs(int(x)-x) < (abs(int(x)+1-x)) )
      a=int(x);
    else
      a=int(x)+1;
    double o=B.evaluate(x)*pow(x-a,u);
    return o;
  }
  return 0;
}
