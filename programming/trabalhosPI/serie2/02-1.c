#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void
help (int status)
{
  printf("\n");
  printf("Além do nome do programa introduza quantos números quer gerar e o nº máximo a ser gerado");
  exit(status);
}
int
main(int argc, char **argv)
{
  double max, *v,a;
  int n,i,t,r,c;
  FILE*f;
  v=(double*)malloc(n*sizeof(double));
  r=1;
  if ((argc != 3))
    help (0);
  sscanf(argv[2],"%lf",&max);
  sscanf(argv[1],"%d",&n);
      



  while(r==1)
    {
      f=fopen("dados", "wt");

      if (c>=1)
	{
	  printf("Por favor introduza por ordem: O número de valores que pretende gerar e separado por um espaço, o número máximo possível de ser gerado, sabendo que só gerará número positivos.\n");
	  scanf("%d %3lf",&n,&max);
	  while(getchar()!=10);
	  v=(double*)realloc(v,n*sizeof(double));

	  // ==0 caso introduza 0 ou uma letra, <0 caso introduza um nr negativo

	  if (n==0 || n<0 || max==0 || max<0)
	    {
	      printf("Introduza um par de NÚMEROS positivos, sendo que o primeiro tem de ser inteiro e o segundo pode ser real. O programa encerrará se introduzir novamente um par de valores absurdo.\n");
	      scanf("%d %3lf",&n,&max);
	    }
	}
      // gerar nrs reais aleatórios entre 0 e max 
      srand(time(NULL));
      for(i=1; i<=n; ++i)
	{
	  v[i]= max*((double) rand())/ ((double) RAND_MAX);
	}

      while(1)
	{
	  t=0;
	  // começa-se em i=2 e não em i=1 para que o 1º elemento seja v[1], para facilitar o uso do módulo em baixo. nunca poderia começar em i=0 senão comparava-se i[-1] (absurdo) com i[0].
	  for(i=2; i<=n; ++i)
	    {
	      if (v[i-1]<v[i])
		{
		  a=v[i-1];
		  v[i-1]=v[i];
		  v[i]=a;
		  t=1;
		}
	    }
	  // quando não houver trocas termina a instrução e inicia os prints
	  if(t==0)
	    break;
	}
      for(i=1; i<=n; ++i)
	{
	  fprintf(f,"%d - %3lf\n", i, v[i]);
	  printf("%d: %3lf ", i, v[i]);

	  // // linhas com 4 números, quando o índice for múltiplo de 4 (o resto da divisão inteira der 0) muda de linha.
	  if( i % 4  ==0)
	    printf("\n");
	}
      fclose (f);
    
      printf("Deseja voltar a executar o programa? Se sim introduza 1, senão introduza 2.\n");
      scanf("%d",&r);
      ++c;

      if (r==2)
	{
	  free(v);
	  break;
	}
    }
  return(0);
}



