#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
  double f,ti,tf,emax,s,e,a,b;
  long int n,i;

  // funções
  double red (double x)
  {
    double y;
    y=fmod(x,2*(M_PI));
    return y;
    //pede y
  }

  double fac (long int z)
  {
    double f;
    f=1;
    while(z>1)
      {
	f=f*z;
	--z;
      }
    return f;
    //pede z
  }
  printf("Introduza o ângulo (em radianos) do qual deseja saber o seno, e o erro máximo que este pode ter.\n");
  scanf("%lf %lf",&ti,&emax);
  tf=red(ti);

  i=0;
 s=1;
 a=0;
  while(1)
    {
     

  b=a+(s*(pow(tf,2*i+1)/fac(2*i+1)));
 e=fabs(a-b);
  if (e<emax)
	 break;

 a=b;
  ++i;
 s=-s;
  }

printf("%lf\n",b);
 printf(" %lf\n",sin(tf));



  return(0);
}
