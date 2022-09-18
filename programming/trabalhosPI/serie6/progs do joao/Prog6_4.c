/***********************************
 *       Modelo de Ising           *
 *                                 *
 *        João Barbosa             *
 *         Pedro Gomes             *
 **********************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
void help()
{
  printf("\nErro\n\n.");
  exit(1);
}

int main(int argc, char **argv)
{

  double *v,c,k,x,m;
  int N,i,b,a;
  srand(time(NULL));
  if(argc != 2)
        {
      help();
      return 0;
    }
  a=sscanf(argv[1],"%i",&N);

  if(a == 0)
    {
      help();
    }
  v=malloc(2048*sizeof(double));
  c=0;
  for(b=1;b<=N;++b)
    {
      m=0;
      for(i=0;i<2048;++i)
	{
	  a = rand() % 2;
	  if(a==0)
	    v[i]=.5;
	  else
	    v[i]=-.5;
	  m=m+v[i];
	}
      printf("\nMagnetização da configuração %i: %lf",b+1,m);
      c=c+m;
    }
  x=c/N;
  k=x/N;
  printf("\nMédia das magnetizações: %lf",x);
  printf("\nMagnetização média por spin: %lf\n\n",k);
  free(v);
  return 0;
}
