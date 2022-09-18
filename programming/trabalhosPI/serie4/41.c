#include<stdio.h>
#include<math.h>

 double
 berny (double x, double y)
 {
   double z;
   z= modf(2*x,&y);
   return z;
 }

int main()
{ 
  FILE*f;
  double x,x0,y;
  int i=1;
  
    printf("Digite o valor de x0.\n");
    scanf("%lf", &x0);

 f=fopen("Bernoulli.dat", "w");
    for(i=1;i<=100; ++i)
      {
	
	x= berny (x0,y);
	x0=x;
	printf("\n %d:       %.10lf\n",i,x);
	fprintf(f,"\n%d:      %.10lf\n",i,x);
      }

 fclose(f);
      return(0);

}
