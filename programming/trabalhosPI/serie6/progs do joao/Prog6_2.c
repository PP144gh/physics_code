/***********************************
 *     Gerador aleatório           *
 *    de números complexos         *
 *        João Barbosa             *
 *         Pedro Gomes             *
 **********************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

void help()
{
  printf("\nBem vindo ao programa que gera números complexos aleatoriamente.\nDeve inserir as ordens na linha de comandos na forma <./programa> <n>, em que 'n' é o quantidade de números complexos que deseja gerar.\nAtente que este programa só gera números complexos no intervalo [-12,23] (quer a parte real, quer a parte imaginária).\nBoa sorte!\n\n");

  exit(1);
}



typedef struct{
  double r;
  double i;
  double norm;
} complexo;

void bubble(complexo **v,int n)
{
  int t,i;
  complexo *a;

  while(1)
    {
      t = 0;
      for(i=0;i<(n-1);i++)
	{
	  if(v[i]->norm < v[i+1]->norm)
	    {
	      a=v[i];
	      v[i]=v[i+1];
	      v[i+1]=a;
	      t=1;
	    }
	}
      if(t==0) break;
    }
}

int main(int argc, char** argv)
{
  int a,n;
  srand(time(NULL));

  complexo **ger;

  

  if(argc < 2 || argc > 2)
    {
      help();
      return 0;
    }

  a=sscanf(argv[1],"%i",&n);
  
  if(a==0)
    {
      printf("\nErro.\nDeve inserir as ordens na linha de comandos na forma <./programa> <n>, em que 'n' é o quantidade de números complexos que deseja gerar.\n\n");
      return 0;
    }
  ger=malloc(n*sizeof(complexo*));
  for(a=0;a<n;++a)
    { 
      ger[a]=malloc(sizeof(complexo));
      ger[a]->r =  ((double)rand()*35/(double)RAND_MAX)-12;
      ger[a]->i =  ((double)rand()*35/(double)RAND_MAX)-12;
      ger[a]->norm = sqrt(ger[a]->r*ger[a]->r + ger[a]->i*ger[a]->i);
    }

  bubble(ger,n);
  printf("\n\nComplexos ordenados:\n\n");
  for(a=0;a<n;++a)
    {
      if(ger[a]->i >= 0)
	printf("%lf+%lfi\n",ger[a]->r,ger[a]->i);
      if(ger[a]->i < 0)
	printf("%lf%lfi\n",ger[a]->r,ger[a]->i);
    }
  printf("\n");
   for(a=0;a<n;++a)
    { 
      free(ger[a]);
    }
   free(ger);
   return 0;
}
