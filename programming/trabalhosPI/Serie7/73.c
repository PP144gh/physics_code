#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

void
init ()
{
  printf("Bem-vindo ao Crivo de Erastótenes.\n");
  printf("O Crivo de Eratóstenes é um algoritmo e um método\n");
  printf("simples e prático para encontrar números primos até\n");
  printf("um certo valor limite. Introduza-o a seguir da instrução\n");
  printf("de inicialização do programa.\n");
  exit(0);
}

void
tmucharg ()
{
  printf("Introduziu demasiados argumentos. O programa vai encerrar.\n");
  printf("Lembre-se que é suposto introduzir o valor limite");
  printf("até ao qual pretende determinar os primos.");
  printf("Por exemplo, se deseja determinar os números primos de\n");
  printf("1 até 10, que são 2,3,5 e 7, introduza 10.");
  exit(0);
}


void
nonv()
{

  printf("Introduziu algo absurdo. O programa vai encerrar.\n");
  printf("Lembre-se que é suposto introduzir o valor limite\n");
  printf("até ao qual pretende determinar os primos.\n");
  printf("Logo, não faz sentido introduzir letras, números não naturais ou\n");
  printf("naturais menores que 2, visto que o 2 é o primeiro número\n");
  printf("natural primo. Tenha em conta que se introduzir um número decimal\n");
  printf("O programa tomará como valor limite o que está antes do ponto.\n");
  printf("Por exemplo, se deseja determinar os números primos de 1 até 10,\n");
  printf("que são 2,3,5 e 7, introduza 10. Corra o programa novamente e\n");
  printf("introduza um número natural maior que 2!\n");
  exit(0);
}


void
ve21 (int n, int *v)
{
  int i;
  v[0]=0;
  v[1]=0;

  for(i=2;i<=n;++i)
    {
      v[i]=1;
    }
}

void
criv (int n, int *v)
{
  int i,j;
  int teste=sqrt(n);
  for(i=2;i<=teste;++i)
    {
      for(j=i;j<=n/i;++j)
	{
	  //testar só com nrs nao eliminados
	  if(v[i]!=0)
	    {
	      v[i*j]=0;
	     
	    }
	}
    }
}
void
priprin(int n, int *v)
{
  int i,j=0;
  printf("Os números primos de 1 a %d são:\n",n);
  for(i=0;i<=n;++i)
    {
      if (v[i]!=0)
	{
	  printf(" ");
	  //%5 pa guardar espaço pa 5 carateres, alinha à direita todos os numeros com 5 ou menos carateres 
	  printf("%5d",i);
	  printf(" ");
	  ++j;
	  //colunas de 10
	  if(j%10==0)
	    printf("\n");
	}
    }
  //mudar de linha caso tenha uma linha com menos de 10 colunas
  printf("\n");
}


int main(int argc, char **argv)
{
  int *v,t,n;
  char *pt;

  if (argc==1)
    init();
  //teste argumentos
  else if(argc!=2)
    tmucharg();
 
  n=strtod(argv[1],&pt);
  //teste só letras ou numero menor que o menor natural primo
  if(pt==argv[1] || n<2)
    nonv();

  else
    {
      //teste nr + letras
      if ( (*pt)!=0 && pt!=argv[1])
	{
	  printf("Introduziu um número sucedido pelos carateres %s\n",pt);
	  printf("Como sou simpático vou assumir que se enganou e tomar\n");
	  printf("como valor limite a parte numérica do que introduziu.\n");
	}
    }

  v =malloc ((n+1)*sizeof(int));
  ve21(n,v);
  criv(n,v);       
    
  priprin(n,v);
  free(v);
  return 0;
} 
