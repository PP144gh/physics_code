#ifndef __POL__
#define __POL__
#include<string>
#include<vector>
using namespace std;

class Pol {
public:
  //  Default Constructor
  Pol();
  //  Constructors
  Pol(string, int);
  Pol(string, int, int*);
  Pol(string, int, vector<double>);
  //  Copy Constructors
  Pol(const Pol&);
  Pol(Pol*);
  //  Operators
  int operator==(const Pol&);
  Pol& operator=(const Pol&);
  Pol& operator+=(const Pol&);
  Pol& operator-=(const Pol&);
  Pol& operator*=(const Pol&);
  Pol operator+(const Pol&);
  Pol operator-(const Pol&);
  Pol operator*(const Pol&);
  //  Methods
  void SetPolynomial(int, int*);
  void SetCoefficient(int, int);
  void Scale(double);
  void Print();
  void PrintPol();
  string GetNome();
  int GetGrau();
  int GetCoef(int);
  void SetNome(string);
  void SetGrau(int);
  void SetCoef(int *);
  void SetCoef(vector<double>);
  double evaluate (double);
  double eva(double);
  vector<double> ruffini(double);
  const Pol derivada();
  //  Destructor
  ~Pol(){};
private:
  string nome;
  int grau;
  vector<double> coef;
};
#endif
