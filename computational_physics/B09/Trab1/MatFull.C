#include<vector>
#include<iostream>
#include"Vec.h"
#include"MatFull.h"
#include"MatSparse.h"
#include<cmath>
using namespace std;

    /*  Constructors  */

MatFull::MatFull(int R,int C, double N){
  ncols=C;
  nrows=R;
  mvec=new Vec[nrows];
  for(int i=0; i<nrows; i++){
    mvec[i].SetSize(ncols);
    mvec[i].SetEntries(ncols,N);
  }
}

MatFull::MatFull( int R, int C, Vec& a){
  nrows=R;
  mvec=new Vec[nrows];
  ncols=C;
  for(int i=0; i<nrows; i++){
    mvec[i].SetSize(ncols);
    mvec[i].SetEntries(ncols,a[i]);
  }
}

MatFull::MatFull( int R, int C, double* V){
  mvec=new Vec[nrows];
  ncols=C;
  nrows=R;
  for(int i=0; i<nrows; i++){
    mvec[i].SetSize(ncols);
    mvec[i].SetEntries(ncols,V);
  }
}

MatFull::MatFull(int R, int C, Vec*b){
  ncols=C;
  nrows=R;
  mvec=new Vec[nrows];
  for(int i=0;i<nrows;++i){
    mvec[i].SetSize(ncols);
    for(int j=0;j<ncols;++j)
      mvec[i].SetEntries(j,b[i][j]);
  }
}

MatFull::MatFull( int r, int c, double **n){
  nrows=r; 
  ncols=c;
  mvec=new Vec[r];
  for(int i=0; i<r; i++){
    mvec[i].SetSize(c);
    mvec[i].SetEntries(c, n[i]);
  }
}

    /*  Copy Constructor  */

MatFull::MatFull(const MatFull& meme){
  nrows=meme.nrows;
  ncols=meme.ncols;
  mvec=new Vec[(meme.mvec[0]).Size()];
  for(int i=0; i<(meme.mvec[0]).Size(); i++){
    mvec[i].SetSize(meme.ncols);
    mvec[i].SetEntries(meme.ncols,meme.mvec[i]);
  }
}

    /*  Default Constructor  */

MatFull::MatFull(){
  nrows=1;
  ncols=1;
  mvec=new Vec;
  mvec[0].SetSize(1);
  mvec[0].SetEntries(1,1);
}

    /*  Print  */

void MatFull::Print() const{
  for(int i=0; i<nrows; i++){
    for(int j=0;j<ncols;j++){
      cout<< mvec[i][j] << " ";     
    }
    cout<<endl;
  }
}

    /*  Return of Column A  */

Vec MatFull::GetCol( int A) const{
  double *c=new double[nrows];
  for(int i=0; i<nrows; i++){
    c[i]=mvec[i][A];
  }
  Vec B(nrows,c);
  return B;
} 

    /*  Return of Row A  */

Vec MatFull::GetRow( int A) const{
  double *c=new double[ncols];
  for(int i=0; i<ncols; i++){
    c[i]=mvec[A][i];
  }
  Vec B(ncols,c);
  return B;
}


    /*  Return of Value from Index(i,j)  */

double MatFull::Getmvec(const int i,const int j ) const{
  double u;
  u=mvec[i][j];
  return u;
}
 
    /*  Set Value of Index(i,j)  */

void MatFull::Setmvec(int i, int j, double a) const{
  mvec[i].SetEntrie(j,a);
}

    /*  Multiplication of Matrix and Vector  */

Vec MatFull::operator|(const Vec& A) const{ //multiplicaçao vetor matriz
  int n=A.Size();
  double *result =new double[n];
  int b=mvec[0].Size();
  for(int i=0; i<ncols; i++){
    for(int j=0; j<mvec[0].Size(); j++){
      result[i]+=mvec[i][j]*(A.GetEntries())[j];
    }
}
 Vec P (n, result);
 return P;
}

    /*  Return of Number of Rows  */

int MatFull::GetNrows() const{
  return nrows;
}

    /*  Return of Number of Columns  */

int MatFull::GetNcols() const{
  return ncols;
}

    /*  Multiplication of Matrixes  */

MatFull MatFull::operator*(const MatFull& M) const{
  int nn=nrows;
  int mc=M.ncols;
  double **c=new double*[nn];
  for(int i=0; i<nrows; i++)
    c[i]=new double[mc];
  if (M.nrows==ncols)
    for(int i=0; i<nn; i++)
      for(int j=0; j<mc; j++)
	c[i][j]=GetRow(i).dot(M.GetCol(j));

  MatFull A(M.nrows,ncols,c);
  return A;
}


 
