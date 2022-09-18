/***********************************
 *     Gerador aleatório           *
 *          de spins               *
 *        João Barbosa             *
 *         Pedro Gomes             *
 **********************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int main(int argc, char **argv)
{
  int i,a,c,n=0;
  FILE *f1;
  if(argc != 2)
    {
      printf("\nInsira o número de argumentos apropriados.\n\n");
      return 0;
    }
  f1=fopen("spins.txt","wt");
  for(i=0;i<=65536;++i)
    {
      a=fprintf(f1,"%i\n",i);
      if(a==0)
	{
	  printf("\nOcorreu um erro na escrita do ficheiro. Tente novamente.\n\n");
	  return 0;
	}
    }
  fclose(f1);
  printf("\nEscrita do ficheiro com sucesso!\n");
  c = strlen(argv[1]);
  if(c != 16)
    {
      printf("\nA sua configuração tem de ter 16 dígitos. Tente novamente\n\n");
      return 0;
    }
  for(i=0;i<16;++i)
    {
      if(argv[1][i]!='0' && argv[1][i]!='1')
	{
	  printf("\nOs seus dígitos só podem ser '0's e '1's.\n\n");
	  return 0;
	}
      n = n*2 + (argv[1][i]-48);
    }
  printf("\nLinha da configuração: %i.\n",n);
  f1=fopen("spins.txt","rt");
  for(i=0;i<=n;++i)
    {
      a = fscanf(f1,"%i",&c);
      if(a==0)
	{
	  printf("\nOcorreu um erro na leitura do ficheiro.\n\n");
	  return 0;
	}
    }
  fclose(f1);
  printf("Confirmação da linha no ficheiro: %i\n\n",c);
  return 0;
}

