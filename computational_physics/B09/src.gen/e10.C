#include <cstdlib>
#include <time.h>
#include <cmath>
void random (double *v) {    
srand (time(NULL));
 double sum=0, var=0;
 
      for (int i=0; i<1000;++i){

	v[i]=5 +((double) rand()/(double) RAND_MAX ) * 50;
	sum += v[i];
      }
      double mean= sum/1000;
 for (int i=0; i<1000;++i){

	var += (v[i]-mean)*(v[i]-mean);
      }
 var=var/1000;
 v[1001]=mean;
 v[1002]=sqrt(var);

}
     
