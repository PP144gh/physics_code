#include"MetodosNumericos.h"

void MetodosNumericos::ipLagrange(double *x, double *y, int n, double c, double &z){//z=p(c)
  z=0;
  double l=1;
  for(int i=0;i<n+1;++i){
    for(int j=0;j<n+1;++j)
      if(j!=i)
	l*=(c-x[j])/(x[i]-x[j]);
    z+=y[i]*l;
  }
}

void MetodosNumericos::ipNewthon(double *x, double *y, int n, double c, double &z){
  double *a=new double[n];
  for(int i=0;i<n;++i)
    a[i]=y[i];
  for(int k=1;k<n;++k)
    for(int i=k;i<n;++i)
      a[i]=(a[i]-a[k-1])/(x[i]-x[k-1]);
  z=a[n];
  for(int i=n-1;i>-1;++i)
    z=a[i]+(c-x[i])*z;
}

void MetodosNumericos::ipNeville(double *x, double *y, int n, double c, double &z){
  double *p=new double[n];
  for(int i=0;i<n;++i)
    p[i]=y[i];
  for(int i=1;i<n;++i)
    for(int k=i;k<n;++k)
      p[i]=((c-x[k-1])*p[i]-(c-x[i])*p[k-1])/(x[k-1]-x[i]);
  z=p[n];
}

void MetodosNumericos::solBisectionMethod(TF1 *f, double a, double b, double h, double &z, double &e){
  for(;e<z;){
    z=(b-a)/2;
    e=b-a;
    if(f->Eval(z)*f->Eval(b)<0)
      a=z;
    else if (f->Eval(z)*f->Eval(a)<0)
      b=z;
    else
      e=0;
  }
}

void MetodosNumericos::solFixedPointMethod(TF1 *f, double a, double b, double h, double &z, double &e){
  double z1=0,z0=0;
  z0=(b-a)/2;
  z1=f->Eval(z0);
  z=f->Eval(z1);
  e=(z-z1)/(1+z0-z1);
  for(;e<h;){
    z0=z1;
    z1=z;
    z=f->Eval(z);
    e=(z-z1)/(1+z0-z1);
  }
}

void MetodosNumericos::solNewtonMethod(TF1 *f, double a, double b, double h, double &z, double &e){
  e=b-a;
  z=(b-a)/2;
  for(;e<h;){
    z=z-f->Eval(z)/f->Derivative(z);
    e*=fabs(f->Derivative2(z)/2/fabs(f->Derivative(z)));
  }
}

void MetodosNumericos::solSecantMethod(TF1 *f, double a, double b, double h, double &z, double &e){
  double z1=3*(b-a)/4,z0=(b-a)/4,zaux=0;
  z=(z0*f->Eval(z1)-z1*f->Eval(z0))/(f->Eval(z1)-f->Eval(z0));
  e=(b-a)/2;
  for(;e<h;){
    zaux=z;
    z=(z0*f->Eval(z1)-z1*f->Eval(z0))/(f->Eval(z1)-f->Eval(z0));
    z0=z1;
    z1=zaux;
    e=(z-z1)/(1+z0-z1);
  }
}

void MetodosNumericos::matLU(double **m, int size){
  double c,ad,*g;
  int aa;
  double *h=new double[size];
  double *b=new double[size];
  for(int i=0;i<size;++i){
    h[i]=0;
    b[i]=i;
  }
  for(int i=0;i<size-1;++i){
    for(int j=i;j<size;++j)
      for(int l=i;l<size;++l){
 	c=m[j][i]/m[j][l];
 	if (fabs(c)>h[j])
 	  h[j]=c;
      }
    c=h[i];
    aa=i;
    for(int j=i;j<size;++j)
      if(h[j]>c){
 	c=h[j];
 	aa=j;
      }
    if(aa!=i){
      ad=b[i];
      b[i]=b[aa];
      b[aa]=ad;
      g=m[i];
      m[i]=m[aa];
      m[aa]=g;  
    }
    for(int j=i+1;j<size;++j){
      c=m[j][i]/m[i][i];
      m[j][i]=c;
      for(int l=i+1;l<size;++l)
       	m[j][l]-=c*m[i][l];  
    }
  }
  double **l=new double*[size];
  for(int i=0;i<size;++i)
    l[i]=new double[size];
  for(int i=0;i<size;++i)
    for(int j=0;j<size;++j)
      l[i][j]=m[i][j];
  m=new double*[size+1];
  for(int i=0;i<size+1;++i)
    m[i]=new double[size];
  for(int i=0;i<size;++i)
    for(int j=0;j<size;++j)
      m[i][j]=l[i][j];
  for(int i=0;i<size;++i)
    m[size][i]=b[i];  
}

void MetodosNumericos::matLU_resolve(double **m, double *c, int size, double* p){
   double u=0;
   for(int i=0;i<size;++i)
     p[i]=c[i];
   for(int i=0;i<size;++i){
     if(p[i]!=i){
       u=p[i];
       p[i]=p[(int) p[i]];
       p[(int) p[i]]=u;
     }
     p[(int) p[i]]=p[i];
   }
   for(int i=0;i<size;++i){
     u=0;
     for(int j=0;j<i;++j)
       u+=m[i][j]*c[j];
     p[i]-=u;
   }
   for(int i=size-1;i>-.5;--i){
     u=0;
     for(int j=size-1;j>i;--j)
       u+=m[i][j]*c[j];
    p[i]=(p[i]-u)/m[i][i];
   }
}

void MetodosNumericos::matLUdecomposition3(float *e, float *f, float *g, int n){
  for(int i=1;i<n;++i){
    e[i-1]=e[i-1]/f[i-1];
    f[i]-=g[i-1]*e[i-1];
  }
}

void MetodosNumericos::matLUdecomposition3d(double *e, double *f, double *g, int n){
  for(int i=1;i<n;++i){
    e[i-1]=e[i-1]/f[i-1];
    f[i]-=g[i-1]*e[i-1];
  }
}

void MetodosNumericos::matLUsolve3(float *e, float *f, float *g, int n, double* p){
  for(int i=1;i<n;++i)
    p[i]+=-e[i-1]*p[i-1];
  p[n-1]=p[n-1]/f[n-1];
  for(int i=n-2;i>-.5;--i)
    p[i]=(p[i]-g[i]*p[i+1])/f[i];
}

void MetodosNumericos::matLUsolve3d(double *e, double *f, double *g, int n, double* p){
  for(int i=1;i<n;++i)
    p[i]+=-e[i-1]*p[i-1];
  p[n-1]=p[n-1]/f[n-1];
  for(int i=n-2;i>-.5;--i)
    p[i]=(p[i]-g[i]*p[i+1])/f[i];
}

void MetodosNumericos::matGauss(double **m, double *b, int size, double *d){
  double c,aaa;
  int aa;
  double *gh;
  double h[size];
  for(int i=0;i<size;++i)
    h[i]=0;

  for(int i=0;i<size-1;++i){
    for(int j=i;j<size;++j)
      for(int l=i;l<size;++l){
 	c=m[j][i]/m[j][l];
 	if (fabs(c)>h[j])
 	  h[j]=c;
      }
    c=h[i];
    aa=i;
    for(int j=i;j<size;++j)
      if(h[j]>c){
 	c=h[j];
 	aa=j;
      }
    if(aa!=i){
      aaa=b[aa];
      b[aa]=b[i];
      b[i]=aaa;
      gh=m[i];
      m[i]=m[aa];
      m[aa]=gh;
    }
    for(int j=i+1;j<size;++j){
      c=m[j][i]/m[i][i];
      for(int l=i;l<size;++l)
       	m[j][l]-=c*m[i][l];
      b[j]-=c*b[i];
    }
  }
  for(int i=size-1;i>-1;--i){
    c=0;
    for(int j=size-1;j>i;--j)
      c+=m[i][j]*d[j];
    d[i]=(b[i]-c)/m[i][i];
  }
}

void MetodosNumericos::der1h1(TF1 *f, double h, double x, double &v, double &e){
  v=(f->Eval(x+h)-f->Eval(x))/h;
}

void MetodosNumericos::der1h2(TF1 *f, double h, double x, double &v, double &e){
  v=(f->Eval(x+h)-f->Eval(x-h))/2/h;
}

void MetodosNumericos::der1h4(TF1 *f, double h, double x, double &v, double &e){
  double a=f->Eval(x-2*h)+8*f->Eval(x+h);
  double b=f->Eval(x+2*h)+8*f->Eval(x-h);
  v=(a-b)/12/h;
}

void MetodosNumericos::der2h2(TF1 *f, double h, double x, double &v, double &e){
  v=(f->Eval(x+h)-2*f->Eval(x)+f->Eval(x-h))/h/h;
}

void MetodosNumericos::der2h4(TF1 *f, double h, double x, double &v, double &e){
  v=(16*f->Eval(x-h)+16*f->Eval(x+h)-(f->Eval(x-2*h)+f->Eval(x+2*h)+30*f->Eval(x)))/h/h/12;
}

void MetodosNumericos::intTrapezoidalRule(TF1 *f, int n, double a, double b, double &x, double &e){
  x=0;
  double h=(b-a)/n;
  for(int i=0;i<n;++i)
    x+=h/2*(f->Eval(a+i*h)+f->Eval(a+(i+1)*h));
  e=(b-a)*(b-a)/12/n/n*fabs(f->Derivative(b)-f->Derivative(a));
}

void MetodosNumericos::intSimpsonRule(TF1 *f, int n, double a, double b, double &x, double &e){
  x=0;
  double h=(b-a)/n;
  for(int i=0;i<(n-1)/2;++i)
    x+=h/3*(f->Eval(x+i*h)+4*f->Eval(x+(i+1)*h)+f->Eval(x+(i+2)*h));
  if(n%2==0)
    x+=h/12*(5*f->Eval(b)+8*f->Eval(b-h)-f->Eval(b-2*h));
  double m=0;
  e=(b-a)*h*h*h*h/180*m;
}

void MetodosNumericos::intMonteCarlo(TF1 *f, int n, double a, double b, double &x){
  gRandom->SetSeed(0);
  x=0;
  for(int i=0;i<n;++i)
    x+=f->Eval(gRandom->Rndm()*(b-a)+a);
  x=x/n*(b-a);
}

void MetodosNumericos::intMC_pdf(TF1 *f, TF1 *g, int n, double a, double b, double &ff){
  gRandom->SetSeed(0);
  double gInt,uInt;
  double HH;
  intSimpsonRule(g,1000,a,b,gInt,HH);
  double x=0,y=0;
  ff=0;
  for(int i=0;i<n;++i){
    x=gRandom->Rndm();
    for(double j=a;j<b;j+=0.0001){
      intSimpsonRule(g,1000,a,j,uInt,HH);
      if(fabs(x-uInt/gInt)<0.001){
	x=j;
	break;
      }
    }
    y=gRandom->Rndm();
    if (y<=g->Eval(x)/f->Eval(x))
      ff+=f->Eval(x);
  }
  ff=ff/n*(b-a);
}

void MetodosNumericos::difRK2(TF1 *f, double yi, double ti, double h, double &yn){
  f->SetParameter(0,ti);
  yn=yi+h/2*f->Eval(yi);
  f->SetParameter(0,ti+h/2);
  yn=yi+h*f->Eval(yn);
}

void MetodosNumericos::difRK4(TF1 *f, double yi, double ti, double h, double &yn){
  f->SetParameter(0,ti);
  double y1=h*f->Eval(yi);
  f->SetParameter(0,ti+h/2);
  double y2=h*f->Eval(yi+y1/2);
  double y3=h*f->Eval(yi+y2/2);
  f->SetParameter(0,ti+h);
  double y4=h*f->Eval(yi+y3);
  yn=yi+(y1+2*y2+2*y3+y4)/6;
}

void MetodosNumericos::difEuler(TF1 *f, double yi, double ti, double h, double &yn){
  f->SetParameter(0,ti);
  yn=yi+h*f->Eval(yi);
}

void MetodosNumericos::difPredictorCorrector(TF1 *f, double yi, double ti, double h, double &yn){
  f->SetParameter(0,ti);
  double g=f->Eval(yi);
  f->SetParameter(0,ti+h);
  yn=yi+h*g;
  yn=yi+h/2*(g+f->Eval(yn));
}

void MetodosNumericos::difPVB2or1dim(TF1 *a, TF1 *b, TF1 *c, TF1 *e, double xi, double xn, double yi, double yn, int N, double *p){
  double *u=new double[N-3];
  double *v=new double[N-3];
  double *AibC=new double[N-2];
  double h=(xn-xi)/N;
  for(int i=0;i<N-3;++i){
    u[i]=a->Eval(xi+i*h+h)/h/h+b->Eval(xi+i*h+h)/2/h;
    v[i]=a->Eval(xi+i*h)/h/h-b->Eval(xi+i*h)/2/h;
  }
  for(int i=0;i<N-2;++i)
    AibC[i]=c->Eval(xi+i*h)-2*a->Eval(xi+i*h)/h/h;
  MetodosNumericos::matLUdecomposition3d(v,AibC,u,N);
  for(int i=0;i<N-2;++i)
    p[i]=e->Eval(xi+i*h);
  p[0]-=yi*(a->Eval(xi)/h/h-b->Eval(xi)/2/h);
  p[N-3]-=yn*(a->Eval(xi)/h/h+b->Eval(xi)/2/h);
  MetodosNumericos::matLUsolve3d(v,AibC,u,N,p);
}
