#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<double> rand2vec(int n){
  vector<double> u(0,0);
  for (int i=0;i<n;++i)
    u.push_back(((double) rand())/( (double) RAND_MAX)*360);
  return u;
}

vector<double>* rand2vecp(int n){
  vector<double> *u=new vector<double>;
  for (int i=0;i<n;++i)
    u[0].push_back(((double) rand())/( (double) RAND_MAX)*360);
  return (u);
}
