#include<cstdlib>
#include<ctime>
#include<iostream>
#include"PixelDet.h"

PixelDet::PixelDet(){
  a=100;
  b=100;
  c=5;
  p=new bool*[a];
  for(int i=0;i<a;++i)
    p[i]=new bool[b];
}

PixelDet::~PixelDet(){
  for (int i=0;i<a;++i)
    delete[] p[i];
  delete[] p;
}

int* PixelDet::EventNoise(float probability){
  int b,t=0;
  srand(time(NULL));
  for (int i=0;i<a;++i)
    for(int j=0;j<b;++j){
      if (rand()%100<5){
	p[i][j]=1;
	++b;
      }
      else
	p[i][j]=0;
    }

  int f[b];
  b=0;
  for(int i=0;i<a;++i)
    for(int j=0;j<b;++j){
      ++t;
      if(p[i][j]==1){
	a[b]=t;
	++b;
      }
    }

  return f;
}
