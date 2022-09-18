#include<iostream>
#include<vector>
#include"Vec.h"
#include"MatSparse.h"
#include<cmath>
using namespace std;

    /*  Default Constructor  */

MatSparse::MatSparse(){
  NN=1;
  nrows=1;
  ncols=1;
  a=new double;
  b=new int;
  c=new int[2];
  a[0]=1;
  b[0]=0;
  c[0]=0;
  c[1]=1;
}

    /*  Constructor from MatFull  */

MatSparse::MatSparse(const MatFull &M){
  int k=0,i;
  int t=0,lll;
  int y=0;
  double bv;

  nrows=M.GetNrows();
  ncols=M.GetNcols();
  bv=abs(M.Getmvec(nrows-1,ncols-1));
  if (bv==0)
    M.Setmvec(nrows-1,ncols-1,bv+1);
  for(i=0;i<nrows;++i)
    for(k=0;k<ncols;++k)
      if(M.Getmvec(i,k)!=0)
	++y;

  double u[M.GetNrows()][M.GetNcols()];
  for(int uu=0;uu<nrows;++uu) 
    for(int uk=0;uk<ncols;++uk) 
      u[uu][uk]=M.Getmvec(uu,uk);
    
  c=new int[nrows+1];
  a=new double[y];
  b=new int[y];
  k=0;

  if (bv==0){
    M.Setmvec(nrows-1,ncols-1,bv);
    --u[nrows-1][ncols-1];
  }

  for(i=0; i<nrows; i++) {
    for(int j = 0; j<ncols; j++) {
      if(u[i][j] != 0) {
 	a[k]=u[i][j];
 	b[k]=j; 
 	if(t==0) {
 	  c[i]=k;
 	  t=1;
 	}
 	k++;
      }
      else if(t==0)
 	if(j==ncols-1)
 	  c[i]=c[i-1];
    }
    t = 0;
  }
  c[i]=y;

  for (i=0,lll=0;i<nrows+1;++i)
    if (i>lll)
      if (c[i]==c[i+1]){
	lll=i;
	while(c[lll]==c[i])
	  ++lll;
	for (int j=i+1;j<1+lll;++j)
	  c[j]=c[lll];
      }
}

    /*  Copy Constructor  */

MatSparse:: MatSparse(const MatSparse& M){
  ncols=M.ncols;
  NN=M.NN;
  nrows=M.nrows;
  a=new double[NN];
  b=new int[NN];
  c=new int[nrows+1];
  for(int i=0; i<NN; i++){
    a[i]=M.a[i];
    b[i]=M.b[i];
  }
  for(int i=0; i<nrows; i++)
    c[i]=M.c[i];
  c[nrows]=NN;
}

    /*  Constructors  */

MatSparse:: MatSparse(int r, int cl, double *A, int *B,int *C){
  ncols=r;
  nrows=cl;
  NN=sizeof A/sizeof(double);
  a=new double[NN];
  b=new int[NN];
  c=new int[nrows+1];
  for(int i=0; i<NN; i++){
    a[i]=A[i];
    b[i]=B[i];
  }
  for(int i=0; i<nrows+1; i++)
    c[i]=C[i];
}

    /*  Copy Assignment  */

const MatSparse& MatSparse:: operator=(MatSparse& M){
  ncols=M.ncols;
  NN=M.NN;
  nrows=M.nrows;
  a=new double[NN];
  b=new int[NN];
  c=new int[nrows+1];

  for(int i=0; i<NN; i++){
    a[i]=M.a[i];
    b[i]=M.b[i];
  }
  for(int i=0; i<=nrows; i++)
    c[i]=M.c[i];
  return *this;
}

    /*  Print Full Matrix  */

void MatSparse::Print() const {
  int kk=0,t=0;	
  int l=0,ef=0;
  for(int i=0; i<nrows; i++) {
    l=c[t+1]-c[t];
    ef=0;
    for(int j=0; j<ncols; j++) 
      if(b[kk] == j) 
	if(kk >= c[t] && ef<l) {
	  if(a[kk] > 0)
	    cout<<"  "<<a[kk]<<flush;
	  else
	    cout<<" "<<a[kk]<<flush;
	  kk++;
	  ef++;
	}
	else
	  cout << "  0" << flush;			       
      else
	cout << "  0" << flush; 
    cout << endl;
    t++;
  }
  cout << endl;
}

void MatSparse::SparseToFull(double **p) const{
  int t=0,t1=0;
  int l=0,bf=0;
  for(int i=0; i<nrows; i++) { 
    if(c[t]==c[t+1]){
      for(int k=0;k<ncols;++k)
        p[i][k]=0;
    }
    else{
      l=c[t+1]-c[t];
      bf=0;
      for(int j=0; j<ncols; j++) {
	if(b[t1] == j) {
	  if(t1 >=c[t] && bf<l) {
	    p[i][j]=a[t1];
	    bf++;
	    t1++;
	  }
	  else
	    p[i][j]=0;	  
	}
	else
	  p[i][j]=0;
      }
    }
    t++;
  }
}

    /*  Multiplication of Matrix and Vector  */

Vec MatSparse:: operator|(const Vec& maior) const{
  double **p=new double*[nrows];
  for(int i=0;i<nrows;++i)
    p[i]=new double[ncols];
  int t=0;
  int  t1=0;
  SparseToFull(p);
  MatFull M(Getnrows(),Getncols(),p);
  int a=maior.Size();
  Vec v(a,0.);
  v=M|maior;
  return v;
}

    /*  Multiplication of Matrixes */

MatSparse MatSparse::operator*(const MatSparse& matbb) const{
  double **g,**p;
  g=new double*[nrows];
  for(int i=0; i<nrows;i++)
    g[i]=new double[ncols];
  p=new double*[matbb.nrows];
  for(int i=0; i<matbb.nrows;i++)
    p[i]=new double[matbb.ncols];
  SparseToFull(g);
  matbb.MatSparse::SparseToFull(p);
  if (p[matbb.nrows-1][matbb.ncols-1]==0)
    ++p[matbb.nrows-1][matbb.ncols-1];
  MatFull P(nrows,ncols,g);
  MatFull O(matbb.nrows,matbb.ncols,p);
  delete[] g;
  MatFull MU(P*O);
  if (p[matbb.nrows-1][matbb.ncols-1]==0)
    for (int i=0;i<MU.GetNcols();++i)
      MU.Setmvec(i,ncols-1,MU.Getmvec(i,ncols-1)-p[i][ncols-1]);
  delete[] p;
  MatSparse D(MU);
  return D;
}

    /*  Return of Column A */

Vec MatSparse::GetCol(int A) const{
  int t=0;
  int t1=0;
  double **g;
  g=new double*[nrows];
  for(int i=0; i<nrows;i++)
    g[i]=new double[ncols];
  SparseToFull(g);
  MatFull P(nrows,ncols,g);
  int a=nrows;
  Vec B(a,0.);
  B=P.GetCol(A);
  return B;
}

    /*  Return of Row A */

Vec MatSparse::GetRow(int A) const{
  int t=0;
  int t1=0;
  double **g;
  SparseToFull(g);
  MatFull P(nrows,ncols,g);
  int a=nrows;
  Vec B(a,0.);
  B=P.GetRow(A);
  return B;
}

    /*  Return of number of Rows */

int MatSparse::Getnrows() const{
  return nrows;
}

    /*  Return of number of Cols */

int MatSparse::Getncols() const{
  return ncols;
}
