#include <iostream> //cin and cout
#include <limits> // precision limits of double and float, min and max of variables
#include <cstring> // use of chars
#include <cmath> // M_PI
#include <cstdlib> //exit from switch
#include "e1.h"
#include "e2.h"
#include "e3.h"
#include "e4.h"
#include "e6.h"
#include "e7.h"
#include "e8.h"
#include "e9.h"
#include "e10.h"
#include "e11.h"
#include "e12.h"
#include "e13.h"
#include "e14.h"
#include "e15.h"
#include "e17.h"
#include "e18.h"
#include "e22a.h"
#include "e23.h"
#include "e24.h"
#include <vector>
using namespace std;

int main(int argc, char **argv) {
  if(argc != 2) {
    cout << "Enter the number of the program you wish to run after ./main.exe . Ex: For problem number 1 enter ./main.exe 1" << endl;
    exit(1);
  }
  else   { 
    int a=atoi(argv[1]);
    switch(a){
    case 1:{
      char j[5],k[5];
      cout << "Enter numbers: " << flush;
      cin >> j >> k;
      if( strchr (j,'.')==NULL && strchr (k,'.')==NULL ){
	int a=atoi(j);
	int b=atoi(k);
	cout<<"Result: "<<addnumbers(a,b)<<endl;  
      }
      else{
	double a=atof(j);
	double b=atof(k);
	cout<<"Result: "<<addnumbers(a,b)<<endl;
      }

      break;}
 
  case 2:  {
      double x;
      cout <<"This program gives the result of the function f(x)=x+(sin(x))^2"<< endl;
      cout << "Enter x"<< endl;
      cin >> x;
      cin.clear();
      cout << "Result = " <<z(x) << endl;
      break;}

 case 3:{
      char l;
      cout <<"This program gives the number of bytes occupied in memory by variables of type: a- short int; b- int; c- long int; d- unsigned int; e- float; f- double; g- long double. Enter the letter that corresponds to the variable type you want." <<endl;
      cin >> l;
      cin.clear();
      cout <<"Size of " << l <<"="<< size(l)<< " bytes" << endl;
      break;}
    
 case 4:{
      cout <<"This program gives you the value of Pi in different precisions." << endl;
      cout.precision(200);
      cout << "Maximum value of PI stored in the library:  "<< endl;
      cout<< M_PI << endl;
      cout.precision(std::numeric_limits<double>::digits10);
      cout << "Pi with double precision ("<< std::numeric_limits<double>::digits10<<  ") : " << endl;
      cout<< pi() << endl;
      cout.precision(std::numeric_limits<float>::digits10);
      cout << "Pi with float precision ("<< std::numeric_limits<float>::digits10<<  ") : " << endl;
      cout<< pi() << endl;
      break;}

    case 5:
      {cout << "This program prints the minimum and maximum value of the variable types: int, unsigned int and float." << endl;
      cout << "Minimum value for int: " << std::numeric_limits<int>::min() << endl;
      cout << "Maximum value for int: " << std::numeric_limits<int>::max() << endl;
      cout << "Minimum value for unsigned int: " << std::numeric_limits<unsigned int>::min() << endl;
      cout << "Maximum value for unsigned  int: " << std::numeric_limits<unsigned int>::max() << endl;
      cout << "Minimum value for float: " << std::numeric_limits<float>::min() << endl;
      cout << "Maximum value for float: " << std::numeric_limits<float>::max() << endl;
      break;}
 
    case 6:{
      int x;
      cout << "This program uses recursive methods to calculate x² from sums and multiplications. Enter the value of x." << endl;
      cin >> x;
      cin.clear();
      cout << "From sums: x² =" << squares(x) << endl;
      cout << "From sums and multiplications: x²=" << squarem(x) << endl;
      break;}
    
    case 7:
      int n,m;
      cout << "This program adds the square of all integers between a number n and m, entered by you."  << endl;
      cout << "Enter integers: " << flush;
      cin >> n >> m ;
      cin.clear();
      cout << "n=" << n << " and m=" << m << endl;
      cout << "Result with double precision = " <<  addnumbersS(n,m) << endl;
      cout << "Result with int precision = " << (int) addnumbersS(n,m) << endl;

      break;
    case 8:
      cout << "This program gives the factorial of the number n, entered by you. Enter n."  << endl;
      cin >> n;
      cin.clear();
      cout << n<< "!=" << fac(n)<< endl;

      break;

    case 9:
      cout << "This program gives the value of (summation from 0 to imax (summation from 0 to jmax cos(i²+sqrt(j)) ) ). Enter imax and jmax."  << endl;
      int vi[0],vj[0]; 
      cin>> *vi >> *vj;
      cout << "For i=" << *vi << " and j=" << *vj<< " Sum equals: " << mainSum(vi,vj) << endl;
      break;

    case 10:{
      cout<< "This program generates random numbers between 5 and 55, calculates their mean and variance and for each random x gives y=x/x-10 " << endl;
    double *v= new double[1002];
      random(v);
   for (int i=0; i<1000;++i)
	cout << i << " : " << v[i] << " y= "<< v[i]/(v[i]-10)<< endl;

 cout << "Mean: "<<  v[1001] << " Variance: " << v[1002]<< endl;

	delete[] v;
      break;
      }

    case 11:{
  cout<< "This program sums every number distanced 0.1 from 0.1 to 5.4. EX: 0.1+0.2+0.3+....+5.3+5.4 " << endl;
      double *v= new double[110];
     sum1(v);
   
      for (int i=0;i<55;++i) {
	cout <<"Current x value: " << v[i] << " / Partial Sum: " << v[55+i] << endl;
      }
      delete[] v;
	break;
    }

    case 12: {     
      cout << "This program creates an array of 100 integers (7) and an array of 5 doubles (4.765) and then prints it." << endl;
      double *v= new double[4];
      int *w= new int[99];
      array(w,v);
      cout <<"Integers" << endl;
      for(int i=0; i<100; ++i)
	cout << "Iteration: "<< i << " Number saved: " <<  w[i]<< endl;
      cout <<"Doubles" << endl;
      for(int i=0; i<5; ++i) 
	cout << "Iteration: "<< i << " Number saved: " <<  v[i]<< endl;
      
      delete[] v;
      delete[] w;
      break;
    }

 case 13:{
      cout  << "This program gives the value of f(x)=sqrt(sin(2x)) by different methods. Enter x in degrees." << endl;
      double x=0;
      double r;
      cin >> x;
      cout<< "f(x) returned by value: " << fv(x) << endl;
      fr(x,r);
      cout<< "f(x) returned by reference: " << r << endl; 
      r=0;
      fp(x,&r);
      cout<< "f(x) returned by pointer: " << r << endl;
      cout <<"x in degrees " << x << endl;
      break;}

    case 14: {
	cout << "This program gives you the sum of all the elements in an double array with n elements filled with 2's. Enter n." << endl;
	n=0;
	cin>> n;
	double *v= new double[n];
	std::fill_n(v, n,2);
	cout <<"The sum of "<<   n <<" elements is "<<  sumarr(v,n) << endl;
	delete[] v;
	break;
      }

     case 15:
     cout << *func1() << endl;
     cout << func2() << endl;
      break;
      
    case 17:{     
      int n=0,m=0;
      double a=0.;
      cout<<"Colunas: ";
      cin>>m;
      cout<<"Linhas: ";
      cin>>n;

      double** mx;
      mx=new double *[n];
      for (int i=0; i<n;++i)
	mx[i]=new double [m];

      for (int i=0;i<n;++i)
	for(int j=0;j<m;++j){
	  cout<<"A entrada ("<<i<<","<<j<<") da matriz e ";
	  cin>>a;
	  mx[i][j]=a;
	}

      double *vr,*pt;
      vr=new double [m];
      pt=new double [m];

      for (int i=0;i<m;++i){
	cout<<"A entrada "<<i<<" do vetor e ";
	cin>>a;
	vr[i]=a;
	pt[i]=0;
      }
      e17( (const double** const) mx, (const double* const) vr, n, m, (double* const) pt);  
      cout<<"O resultado e (";
      for (int i=0;i<m;++i){
	cout<<pt[i];
	if (i!=m-1)
	  cout<<",";
      }
      cout<<")"<<endl;      
      delete[] vr;
      delete[] pt;
      break;
    }
    case 18:{
      int n=0;
      srand (time (NULL));
      cout<<"Quantos aleatorios queres? ";
      cin>>n;
      vector<double> v=rand2vec(n);
      for (int i=0;i<n;++i)
	cout<<v[i]<<" ";
      cout<<endl;
      vector<double> *u=rand2vecp(n);
      for (int i=0;i<n;++i)
	cout<<u[0][i]<<" ";
      cout<<endl;
      break;
    }
    case 22:{
      // pessoa T[10];
      // string c=T[1].GetName();
      // cout<<c<<endl;
      string k;unsigned int l;
      cout<<"Nome: ";cin>>k;
      cout<<"Data de Nascimento: ";cin>>l;
      pessoa P(k,l);
      P.print();
      int x;
      cout<<"Quantos pessoas queres? ";
      cin>>x;
      pessoa **p=DoArray(x);
      for (int i=0;i<x;++i)
     	p[i]->print();
      for (int i=0;i<x;++i)
      	p[i][0].~pessoa();
      delete[] p;
      break;
    }
    case 23:{
      alunoIST **p=new alunoIST*[10];
      for(int i=0;i<10;++i)
	p[i]=new alunoIST;
      Dummy(p);
      for (int i=0;i<10;++i)
    	p[i][0].~alunoIST();
      delete[] p;
      break;
    }
    case 24:{
      alunoIST **p=new alunoIST*[0];
      p[0]=new alunoIST;
      Turma T(p,2);
      int x;
      x=T.GetNalunos();
      cout<<x<<endl;
      alunoIST *u=T.FindAluno();
      string c;
      c=u[0].GetBranch();
      cout<<c<<endl;
      u[0].~alunoIST();
      p[0][0].~alunoIST();      
      delete[] p;
      break;
    }


    default:
      cout << "That program doesn't exist or hasn't been done yet. Since we are very productive, the most likely is that he doesn't exist." << endl;
      exit(2);
    }
  }
  return 0;
}
