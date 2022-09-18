#include <iostream>
#include "Vec.h"
#include<vector>
#include<cmath>

Vec::Vec() { //default constructor
N=1;
entries = new double [N];
entries[0]=0;
}

Vec::Vec(int n) {
  N=n;
  entries= new double [N];
  for(int i=0; i<N; ++i) 
    entries[i]=0; //entradas de Vec todas 0
}

Vec::Vec(int n,double *r) { 
  N=n;
  entries= new double [N];
  for (int i=0; i<n;++i)
    entries[i]=r[i]; //valores ordenados do array vao ser os do Vec
}

Vec::Vec(int n,double r) {
  N=n;
  entries= new double [N];
  for (int i=0; i<n;++i)
    entries[i]=r; //entras de Vec todas igual a r
}

Vec::Vec(const Vec& v) { //copy constructor
  N=v.N;
  entries= new double [N];
  for (int i=0; i<N;++i)
    entries[i]=v.entries[i];
}


int Vec::Size() const {
  return N;
}

const Vec Vec::Scale(const double x) {
  double *r= new double [N];
  for (int i=0; i<N;++i)
    r[i]=x*entries[i];

  Vec w(N,r);
  return w;
}

const double Vec::dot( const Vec& w) {
  double r=0;  
  if (N==w.N)
    for (int i=0;i<N; ++i)
      r+=entries[i]*w.entries[i];
  else{
    cout<<"Erro:::::  Tem de ter o mesmo tamanho"<<endl;
    return 0;
  }
  return r;
} 

void Vec::print() const {
  for(int i=0; i<N; ++i) 
    cout <<entries[i] << " " <<flush;

  cout << endl;  
}

const Vec& Vec::operator+=(const Vec& v) {
  if (N!=v.N) 
    cout<<"ERRO::: Tem de ter a mesma dimensao"<<endl;
  else{
    for (int i=0;i<N; ++i)
      entries[i]+=v.entries[i];
  }
  return *this;
}

const Vec& Vec::operator-=(const Vec& v) {
  if (N!=v.N) 
    cout<<"ERRO::: Tem de ter a mesma dimensao"<<endl;
  else{
    for (int i=0;i<N; ++i)
      entries[i]-=v.entries[i];
  }
  return *this; 
}

const Vec& Vec::operator=(const Vec& v) {

  if(this!=&v) {
  N=v.N;
  entries=new double[N];
  for (int i=0; i<N ; ++i)
    entries[i]=v.entries[i]; 
  }
  return *this;
}


const Vec Vec::operator*(const Vec& v) {
  if (N!=v.N){
    cout<<"ERRO::: Tem de ter a mesma dimensao"<<endl;
    return v;
  }
  else{
    Vec w;
    w.entries=new double[N];
    w.N=N;
    for (int i=0;i<N; ++i)
      w.entries[i]=entries[i]*v.entries[i];
    return w;
  }
}


const Vec Vec::operator+( const Vec& v) {
  Vec w(*this);
  w+=v;
  return w;
}

const Vec Vec::operator-(const Vec& v) {
  Vec w(*this);
  w-=v;
  return w;
}

const double Vec::operator[] (int i) const{
  return entries[i];
}

 
const Vec Vec::operator-() {
  for(int i=0;i<N;++i)
    entries[i]=-entries[i];
  return *this;
}

const Vec Vec::operator+() {
  return *this;
}

void Vec::SetSize(const int a){
  N=a;
}
void Vec::SetEntries(const int a,const double b){
  for(int i=0;i<a;++i)
    entries[i]=b;
}
void Vec::SetEntrie(const int a,const double b){
  entries[a]=b;
}
void Vec::SetEntries(const int a,const double* b){
  for(int i=0;i<a;++i)
    entries[i]=b[i];
}
void Vec::SetEntries(const int a, const Vec& A){
  for(int i=0;i<a;++i)
    entries[i]=A.entries[i];
}
double* Vec::GetEntries() const{
  double *p=new double[N];
  for(int i=0;i<N;++i)
    p[i]=entries[i];
  return p;
}


