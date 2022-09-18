#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

int
main()
{
  double v[10000];
  int n,i;
  FILE*f;

  f=fopen("dados", "rt");


  for(i=1; i<=50; ++i)
    {
      fscanf(f,"%d - %lf\n", &i, &v[i]);

      printf("%d: %lf ", i, v[i]);
      // linhas com 10 números, quando o índice for múltiplo de 10 (o resto da divisão inteira der 0) muda de linha.
      if( i % 10 ==0)
	printf("\n");
    }
  fclose (f);

  return(0);
}
