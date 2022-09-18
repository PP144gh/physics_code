#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

void
help1 ()
{
  printf("\n");
  printf("*****************************************\n");
  printf("* Pedro Pereira 78889 e Inês Roça 78164 *\n");
  printf("*****************************************\n\n");
  printf("Bem-Vindo à calculadora de complexos. Se desejar\n");
  printf("determinar o módulo dum complexo, introduza algo do tipo:\n");
  printf("./prog (espaço) mod (espaço) parte real (espaço) parte imaginária\n");
  printf("Se desejar antes realizar operações entre dois complexos:\n");
  printf("Siga a mesma sintaxe de cima mas em vez de mod\n");
  printf("introduza +,-,x ou '\' dependendendo da operação que\n");
  printf("pretende fazer. Depois, introduza a parte real e imaginária\n");
  printf("do 2º complexo.\n");
  exit(1);
}

void
help2 ()
{
  printf("\n");
  printf("Não introduziu um número correto de argumentos.\n");
  printf("Se quiser determinar o módulo dum complexo introduza\n");
  printf("mod e as respetivas partes do mesmo. Se quiser operar entre\n");
  printf("2 complexos, introduza +.-,x ou / e as partes reais e\n");
  printf("imaginárias de cada um. O programa vai encerrar.\n");
  exit(1);
}

void
C (double *v, int M, int N)
{
  int i=1,t;
  double a;

  while(1)
    {
      t=0;
      for(i=1; i<(M*N); ++i)
	{
	  if (v[i-1]<v[i])
	    {
	      a=v[i-1];
	      v[i-1]=v[i];
	      v[i]=a;
	      t=1;
	    }
	}
	  if(t==0)
	    break;
    }
    }

int
D (double *v,int M, int N)
{
  int i1,i2;

  for(i1=1,i2=1; i1<(M*N); ++i1)
	{
	  if (v[i1]!=v[i2-1])
	    {
	      v[i2]=v[i1];

		++i2;
	    }
	}
  v=(double*)realloc(v,i2*sizeof(double) );

  return i2;
}

double*
B (int M,int N)
{
  double *v;
  int i1,i2,i3=0;

  v=(double*)malloc( (M*N)*sizeof(double) );
  for(i1=1;i1<=N;++i1)
    {
      for(i2=1;i2<=M;++i2)
	{
	  v[i3]= (double) i1/(double)i2;
	  ++i3;
	}
    }
  C(v,M,N);
  return v;
}


  int
    main(int argc, char **argv)
  {
    int M,N,i,teste1=0,teste2=0,i2;
    double *v;
    FILE *f;


    if(argc==1)
      {
	help1();
	return 0;
      }

    if (argc==3)
      {
	teste1=sscanf (argv[1],"%d",&M);
	teste2=sscanf (argv[2],"%d",&N);

	if((teste1+teste2!=2))
	  {
	    printf("Introduziu um ou mais argumentos que não são números\n");
	    printf("reais.\n O programa vai encerrar. Lembre-se que\n");
	    printf("um número\n complexo é um par ordenado de dois\n");
	    printf("números reais.\n");
	    return 0;
	  }
	v=B(M,N);
	i2=D(v,M,N);
	f=fopen("dados.txt","wt");
	for(i=0;i<i2;++i)
	  {
	    fprintf(f,"%lf\n",v[i]);
	  }
      }
    free(v);
    fclose(f);
    return 0;
  }
