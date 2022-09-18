#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

void
ma (int m, int n, double p)
{
 int i1,i2;
  srand(time(NULL));
  for (i1=1;i1<=m;++i1)
    {
      for(i2=1;i2<=n;++i2)
	{
	  if (p>=((double)rand()/(double)(RAND_MAX)))
	    printf("1 ");
	  else
	    printf("0 ");
	}
      printf("\n");
    }
}



int
main(int argc, char **argv)
{
 int m,n,t;
  double p;
 sscanf (argv[1],"%d",&m);
 sscanf (argv[2],"%d",&n);
 sscanf (argv[3],"%lf",&p);
  while(1)
    {
 
 ma(m,n,p);

 printf("Deseja correr o programa novamente? Se não, prima 0, se sim prima outra coisa qualquer.\n");
 scanf("%d ",&t);
   if(t==0)
     break;
    }
  return 0;
}
