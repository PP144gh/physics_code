#include<stdio.h>
#include<math.h>

 double
 logistica (double x, double r)
 {
   double z;
   z= r * x * (1-x);
   return z;
 }

int main()
{ 
  FILE*f;
  double x,x0,r,z,a,b;
  int i,i2;
  
    printf("Digite o valor de x0 e do parâmetro r, por essa ordem e separados por um espaço, que pretende, para o cáculo da funçãop logística.\n");
    scanf("%lf %lf", &x0,&r);
    i=0;
    a=x0;
   b=r;

    while(i<=2000)
      {
	x= logistica (x0,r);
	x0=x;
	++i;
      }
    z=x;
 f=fopen("orbitas", "w");
    for (i=0; i<=64; ++i )
    {
      x= logistica (x0,r);
      printf("\n%d : %lf\n",i,x);
     
      fprintf(f,"\n%d : %lf\n",i,x);
      
      if (fabs(x-z)<=1.e-6)
	  break;
     
      x0=x;
 
      
    }
    i2=i+1;

 printf("Possuiu uma órbita com %d valores\n", i2);
 fprintf(f,"órbita com %d valores; rinicial = %le ; x0= %lf\n", i2, b,a);
 fclose(f);
      return(0);

}
