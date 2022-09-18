#include "DataInterpolator.h"
#include "EqSolver.h"
#include "Vec.h"
using namespace std;

//CONSTRUTOR
DataInterpolator::DataInterpolator(int n, double* i, double* j) {
  N=n;
  double *xtmp= new double [N]; 
  for (int u=0; u<n; ++u) 
    xtmp[u]=i[u];
   
  double *ytmp= new double [N]; 
  for (int v=0; v<n; ++v) 
    ytmp[v]=j[v];

  x=xtmp;
  y=ytmp;
}

//DRAW POINTS
TGraph* DataInterpolator::Draw() {
  TGraph* g= new TGraph(N,x,y);
  g->SetMarkerStyle(2);
  g->SetTitle("Superposition of Graphs;MeV;mbarn");
  return g;
}

//K's CALCULATOR 
double* DataInterpolator::CubicSplineCurvatures() {
  double *a=new double[N-3];
  double *c=new double[N-3];

  //A DIAGONAL SUPERIOR E C DIAGONAL INFERIOR
  for(int i=0; i<N-3;++i) {
    a[i]=(x[i+2]-x[i+1])/6;
    c[i]=a[i]; 
  }
  //B DIAGONAL PRINCIPAL
  double *b=new double[N-2];
  for(int i=0; i<N-2;++i) 
    b[i]=(x[i+2]-x[i])/3;

  EqSolver t;
  t.LUdecomposition3d(a,b,c,N-2);

  double *s=new double[N-2];
  for(int i=0;i<N-2;++i) 
s[i]=( (y[i+2]-y[i+1]) /(x[i+2]-x[i+1]) )-( (y[i+1]-y[i])/(x[i+1]-x[i]));  

  t.LUsolve3d(a,b,c,N-2,s);

  double *k= new double[N];
  k[0]=0; k[N-1]=0;

  for(int i=1; i<N-1; ++i) {
    k[i]=s[i-1];
  }
  return k;
}

TF1* DataInterpolator::CubicSplineSegment(double* k, double o) {

  if(o<x[0] || o>x[N-1]) {
    cout <<" Error, x out of segment range"<< endl;
    return 0;
  }
  //DA O INTERVALO A QUE O PERTENCE. Por exemplo: se estiver entre x[0] e x[1] retorna 1.
  int i=0;
  while(o>x[i]) {
    ++i;
  }
 
  // 0-> xi   1 -> xi+1 2->Ki 3->Ki+1 4->yi 5->yi+1
  TF1 *f = new TF1("f","([2]/6)*( ((pow(x-[1],3))/([0]-[1]))-(x-[1])*([0]-[1]) )- ([3]/6)*( ((pow(x-[0],3))/([0]-[1]))-(x-[0])*([0]-[1]) )+( ([4]*(x-[1])-[5]*(x-[0]))/([0]-[1]) )",x[i-1],x[i]); 
  f->SetTitle("CSpline Segment;MeV;mbarn");
 
  //dado que i e' o intervalo a que pertence. x[i] sera o extremo superior, logo x[i-1] o inferior.
  f->SetParameter(0,x[i-1]);
  f->SetParameter(1,x[i]);
  f->SetParameter(2,k[i-1]);
  f->SetParameter(3,k[i]);
  f->SetParameter(4,y[i-1]);
  f->SetParameter(5,y[i]);
 
  return f;
}

double CSfunctor(double* e, double *par) {
  //1-D function
  double o=e[0];
  int N= par[0]; //tornar a funçao parte da classe da' problemas.

  if(o<par[1] || o>par[N]) {
    cout <<" Error, x out of segment range"<< endl;
    return 0;
  }
  //mesmo raciocionio de acima
  int i=0;
  while(o>par[i+1] && i<(N)) {
    ++i;
  }

  //Como o primeiro valor ja esta atribuido, quando i=1 temos par[1]=x[0], logo par[i] corresponde ao extremo inferior,  nao sendo assim necessa'rio fazer a correçao usada em cima na atribuiçao dos parametros
  // i-> xi   i+1 -> xi+1 N+i->yi N+i+1->yi+1 2N+i->Ki 2N+i+1->Ki+1
  return (par[2*N+i]/6.)*(((o-par[i+1])*(o-par[i+1])*(o-par[i+1])/(par[i]-par[i+1]))-(o-par[i+1])*(par[i]-par[i+1]))-(par[2*N+i+1]/6.)*(((o-par[i])*(o-par[i])*(o-par[i])/(par[i]-par[i+1]))-(o-par[i])*(par[i]-par[i+1]))+ ((par[N+i]*(o-par[i+1])-par[N+i+1]*(o-par[i]))/(par[i]-par[i+1]));
}

TF1* DataInterpolator::CubicSpline(double* k) {
  //como 
  double* par= new double [3*N+1];
  par[0]=N;
  for (int i=0;i<N;++i)
    par[i+1]=x[i];
  for (int i=0;i<N;++i)
    par[N+i+1]=y[i];
  for (int i=0;i<N;++i)
    par[2*N+i+1]=k[i];
                              
  TF1 *f1 = new TF1("CubicSpline",CSfunctor,x[0],x[N-1],3*N+1);
  f1->SetParameters(par);
  f1->SetTitle("CubicSpline;MeV;mbarn");
  return f1;
}

double Nevfunctor(double* e, double *par) {
  //1-D function
  double o=e[0];
  int N= par[0]; //tornar a funçao parte da classe da' problemas.
  int i=0; int j=0;
  double *pol = new double [N];
  for (i=0;i<N;i++)
    pol[i] = par[N+i+1]; //pol de ordem zero

  for (i=1; i<=N-1; i++)
    {
      //definiçao do metodo recursivo
      for (j=0;j<N-i;j++)
	pol[j] = ((o-par[j+1])*pol[j+1]-(o-par[i+1+j])*pol[j])/(par[i+j+1]-par[j+1]);
    }
  return pol[0];
}

TF1* DataInterpolator::NevPolynomial() {
  
  double* par= new double [2*N+1];
  par[0]=N;
  for (int i=0;i<N;++i)
    par[i+1]=x[i];
  for (int i=0;i<N;++i)
    par[N+i+1]=y[i];
                              
  TF1 *f1 = new TF1("Neville Polynomial",Nevfunctor,x[0],x[N-1],2*N+1);
  f1->SetParameters(par);
  f1->SetTitle("Neville Polynomial;MeV;mbarn");
  return f1;
}


//determinador de coeficientes do metodo Newton
double * DataInterpolator::Newtoncoefficient() {
  double * a = new double [N];
  for (int i=0;i<N;++i)
    {
      a[i]=y[i];
    }
  for(int k=1;k<N;++k)
    {
      for (int i=k;i<N;++i)
	{
	  a[i]=(a[i]-a[k-1])/(x[i]-x[k-1]);
	}
    }
  return a;
}


TF1* DataInterpolator::Polynomial() {
  std::string str;
  double * a= new double [N];
  a=Newtoncoefficient();

  string zero="[0]";
  string meio = "";

  //guarda em strings a informaçao: x-xi; Exemplo: j[2]=x-x2
  string *j = new string[N];
  for (int i=0; i<N; ++i) {
    char*tmp1=new char[10];
    sprintf(tmp1,"(x-[%d])",2*i+1);
    string tmp2(tmp1);
    j[i]=tmp2;
    delete[] tmp1;
  }

  string *s= new string[N];
  string r;
  for (int i=0; i<N; ++i) {
    r+=j[i]+"*";
    s[i]=r;   // Exemplo s[2]=(x-x0)*(x-x1)*(x-x2)*
    s[i].erase(s[i].size()-1); //apaga o ultimo *
  }
  for (int i=1; i<N; ++i) {
    char* t = new char[N*50];  
    sprintf(t,"+[%d]*%s",2*i,s[i-1].c_str()); //cria o polinomio de acordo com os coeficientes e s. 
    string l (t);
    meio+=l;
    delete[] t;
  }
  str+=zero;
  if(N>1){ 
    str+=meio;
  }
  const char *formula = new char[str.length()+1];
  formula=str.c_str();
  TF1 *f = new TF1("Newton",formula,x[0],x[N-1]);

  for(int i=0;i<N; ++i) {
    f->SetParameter(2*i,a[i]);
    f->SetParameter(2*i+1,x[i]);
  }
  f->SetTitle("NewtonPolynomial;MeV;mbarn");

  return f;
}

//definiçao do metodo para o polinomio pelo metodo de lagrange
TF1* DataInterpolator::LagPolynomial()
{
  string li[N], l;

  for(int i=0;i<N;++i)
    {
      //stringing the stuff. mesma ideia do de cima
      string yi;
      char*tmp1=new char[10];
      sprintf(tmp1,"%f",y[i]);
      string tmp2(tmp1);
      yi+=tmp2;
      delete[] tmp1;
      for(int j=0;j<N;++j)
	{
	  string xj;
	  char*tmp1=new char[10];
	  sprintf(tmp1,"%f",x[j]);
	  string tmp2(tmp1);
	  xj+=tmp2;
	  delete[] tmp1;

	  string ldenominator;
	  char*tmp3=new char[10];
	  sprintf(tmp3,"%f",x[i]-x[j]);
	  string tmp4(tmp3);
	  ldenominator+=tmp4;
	  delete[] tmp3;
	  
	  //definiçao de l para cada i
	  if(j==i) continue;
	  li[i] = "*((x-" + xj + ")/(" + ldenominator + "))"+ li[i]; 
	}
      if(i==0) 
	l = yi + li[i]; //ordem 1
      else  
	l = yi + li[i] + '+' + l; //polinomio geral
    }

  const char* lagformula = new char[l.size() + 1];
  lagformula=l.c_str();

  TF1* lag= new TF1("Lagrange", lagformula, x[0],x[N-1]);
  lag->SetTitle("Lagrange Polynomial;MeV;mbarn");
  return lag;
}

double DataInterpolator::CubicSplineDeriv(double* k, double a) {

  int i=0;
 
  if(a>x[N-1] || a<x[0])
    {
      cout << " Out of Range" << endl;
      return 0;
    }
  //mesma logica do CubicSplineSegment
  while(a>x[i]) {
    ++i;
  }
  if(a==x[0])
    i=1;
  //aqui e' necessario corrigir. x[i] e' o extremo superior
  return (k[i-1]/6)*(3*(a-x[i])*(a-x[i])/(x[i-1]-x[i]) - (x[i-1]-x[i])) - (k[i]/6)*(3*(a-x[i-1])*(a-x[i-1])/(x[i-1]-x[i]) - (x[i-1]-x[i])) + (y[i-1]-y[i])/(x[i-1]-x[i]);
}

double CSDerivativefunctor(double* e, double *par) {
  //1-D function
  double o=e[0];
  int N= par[0];

  if(o<par[1] || o>par[N]) {
    cout <<" Error, x out of segment range"<< endl;
    return 0;
  }

  int i=0;
  while(o>par[i+1] && i<(N)) {
    ++i;
  }
  // i-> xi   i+1 -> xi+1 N+i->yi N+i+1->yi+1 2N+i->Ki 2N+i+1->Ki+1
  return ( par[2*N+i]/6)*(3*(o-par[i+1])*(o-par[i+1])/(par[i]-par[i+1]) - (par[i]-par[i+1])) - (par[2*N+i+1]/6)*(3*(o-par[i])*(o-par[i])/(par[i]-par[i+1]) - (par[i]-par[i+1])) + (par[N+i]-par[N+i+1])/(par[i]-par[i+1]);
  
}

//used for debugging
TF1* DataInterpolator::CubicSplineDeriva(double* k) {
  double* par= new double [3*N+1];
  par[0]=N;
  for (int i=0;i<N;++i)
    par[i+1]=x[i];
  for (int i=0;i<N;++i)
    par[N+i+1]=y[i];
  for (int i=0;i<N;++i)
    par[2*N+i+1]=k[i];
                              
  TF1 *f1 = new TF1("CubicSpline Analytic Derivative",CSDerivativefunctor,x[0],x[N-1],3*N+1);
  f1->SetParameters(par);
  f1->SetTitle("CubicSpline Analytic Derivative;MeV;mbarn");
  return f1;
}

    

double DataInterpolator::CubicSplineDerivN(double* k, double a)
{
  TF1* CS= CubicSpline(k);
  double h=0.00001; //referido na teorica que e' o melhor
 
  if(a>x[N-1] || a<x[0]) {
    cout << "Out of Range" << endl;
    return 0;
  }
  //forward derivative -> extremo inferior
  if(a==x[0]||(a>x[0] && a<(x[0]+2*h)))
    {
      double fa=CS->Eval(a);
      double fah=CS->Eval(a+h);
      double fa2h=CS->Eval(a+2*h);
      return (1/(2*h))*(-1*fa2h + 4*fah -3*fa);
    }
  if(a==x[N-1]||(a<x[N-1] && a>(x[N-1]-2*h)))
    {//backward derivative -> extremo superior
      double fahd=CS->Eval(a-h);
      double fa2hd=CS->Eval(a-2*h);
      double fa=CS->Eval(a);
      return (1/(2*h))*(fa2hd -4*fahd + 3*fa);
    }
  //neither of the above -> central derivative
  double fah=CS->Eval(a+h);
  double fahd=CS->Eval(a-h);
  return ((fah-fahd)/(2*h));
}

double DataInterpolator::PolynomialDerivN(double a)
{

  TF1* P= Polynomial();
  double h=0.00001; //referido na teorica que e' o melhor
 
  if(a>x[N-1] || a<x[0])
    {
      cout << "Out of Range" << endl;
      return 0;
    }
  //forward derivative -> extremo inferior
  if(a==x[0]||(a>x[0] && a<(x[0]+2*h)))  {
    double fa=P->Eval(a);
    double fah=P->Eval(a+h);
    double fa2h=P->Eval(a+2*h);
    return (1/(2*h))*(-1*fa2h + 4*fah -3*fa);
  }
  //backward derivative -> extremo superior
  if(a==x[N-1]||(a<x[N-1] && a>(x[N-1]-2*h))) {
    double fahd=P->Eval(a-h);
    double fa2hd=P->Eval(a-2*h);
    double fa=P->Eval(a);
    return (1/(2*h))*(fa2hd -4*fahd + 3*fa);
  }
 
  //neither of the above -> central derivative
  double fah=P->Eval(a+h);
  double fahd=P->Eval(a-h);
  return (1/(2*h))*(fah-fahd);
}



TGraph* DataInterpolator::DifInterpol(double* k){
  int scaler=10;
  int l= (x[N-1])*scaler;
  double inc=((x[N-1])/(x[N-1]*scaler)); //se a funçao recebesse  o scaler podia-se ter o grafico c qualquer aproximaçao desejada
  double* dy=new double[l];
  double* xd=new double[l];
  double h=x[0];
  TF1* CS = CubicSpline(k);
  TF1* P=Polynomial();
  
  for (int i=0;i<l;++i)
    {
      xd[i]=h;
      dy[i]=CS->Eval(h)-P->Eval(h);
      h+=inc;
    }

  TGraph* g =new TGraph(l,xd,dy);
  g->SetTitle("Difference between Interpolators;MeV;mbarn");
  return g;
}

TGraph* DataInterpolator::DifCSDeriv(double* k){
  int scaler=10;
  int l= (x[N-1])*scaler;
  double inc=((x[N-1])/(x[N-1]*scaler)); //se a funçao o scaler podia-se ter o grafico c qualquer aproximaçao desejada
  double* dy=new double[l];
  double* xd=new double[l];
  double h=x[0];
   
  for (int i=0;i<l;++i)
    {
      xd[i]=h;
      dy[i]=CubicSplineDerivN(k,h)-CubicSplineDeriv(k,h);
      h+=inc;
    }

  TGraph* g =new TGraph(l,xd,dy);
  g->SetTitle("CS Derivative Difference -> Numerical VS Analytical;MeV;mbarn");
  return g;
}

TGraph* DataInterpolator::DifNDeriv(double* k) {
  int scaler=2; //acima de 2 fica muito lento
  int l= (x[N-1])*scaler;
  double inc=((x[N-1])/(x[N-1]*scaler)); //se a funçao recebesse o scaler podia-se ter o grafico c qualquer aproximaçao desejada
  double* dy=new double[l];
  double* xd=new double[l];
  double h=x[0];
 
  for (int i=0;i<l;++i)
    {
      xd[i]=h;
      dy[i]=PolynomialDerivN(h)-CubicSplineDerivN(k,h);
      h+=inc;
    }
  TGraph* g =new TGraph(l,xd,dy);
  g->SetTitle("Numerical Derivative Difference -> Newton VS CS;MeV;mbarn");
  return g;
}

