#include <time.h>
#include <cstdlib>

//por ponteiro
int *func1(void){
srand (time(NULL));
 int n= (double) rand();
 int *p= &n;
 return p;

  }
//por referencia
int &func2(void){
srand (time(NULL));
 int n= (double) rand();
int *p= &n;
 return *p;
  }
