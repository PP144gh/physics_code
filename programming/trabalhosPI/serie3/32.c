#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
 
void
help1 (void)
{
  printf("*****************************************\n");
  printf("* Pedro Pereira 78889 e Inês Roça 78164 *\n");
  printf("*****************************************\n\n");
  printf("Bem-Vindo. Introduza após o comando de execução\n");
  printf("uma string e 2 carateres\n");
  printf("de acordo com a seguinte sintaxe:\n");
  printf("<exe> <string> <char1> <char2>\n");
  printf("Este programa tem como objetivos:\n");
  printf("1. Dizer quantas vezes o char1 surge na string.\n");
  printf("2. Dar a posição da primeira occorrência do char1\n");
  printf("na string. (No caso do char1 não surgir na string\n");
  printf("a posição será por definição -1).\n");
  printf("3. Criar uma nova string onde o char1 é\n");
  printf("substituído pelo char2 em todas as suas ocorrências.");

}

void
help2 (void)
{
  printf("A ideia do programa é trabalhar com uma string\n");
          printf("e dois carateres. Ou seja, é de bom agrado\n");
	  printf("que os carateres sejam somente isso\n");
          printf("carateres, e não conjuntos deles. O programa vai ser\n");
	  printf("encerrado. Na próxima execução cumpra a sintaxe:\n");
	  printf("<execução> <string> <char1> <char2>\n"); 
	  printf("Tenha em atenção que uma string pode ser só um carater,\n");
	  printf("ou um conjunto deles.");
	  
}

// contador do nr de carateres iguais
// ao char 1 na string
int
A (char *a, char *b)
{
  int i1, i2;
  i2=0;
  for(i1=0; a[i1]!=0; ++i1)
   {
     if (a[i1]==b[0])
       ++i2;
    }
  return i2;
}


int
B (char *a, char *b)
{
  int i,i1;
  i=0;
  i1=0;
  while(1)
    {
      ++i;
// faz o ciclo até surgir um valor do vetor a 
// (string) que seja igual ao de b[0](char1) 
      if (a[i1]==b[0])
        {
	  return i;
	}
// se o vetor a (string) chegar ao terminador 
//sem que nenhum valor seu seja igual ao de b[0](char1) retorna -1
      if(a[i1]==0)
	return -1;
      ++i1;
    }
}

char*
C (char *a, char *b, char *c)
{
  int i1;
  char *p;
// cria um vetor com o comprimento de a, copia a para p
  p=(char*)malloc(strlen(a)+1);
  strcpy(p,a);
// faz o ciclo enquanto o valor de p não for o terminador
  for(i1=0; p[i1]!=0; ++i1)
//quando um valor de p for igual ao de b[0] (char1) 
//este é substituido por c[0] (char2)
    {
   if (p[i1]==b[0])
        p[i1]=c[0];
    }
  return p;
}

int main(int argc, char **argv)
{
  char *p ;
  //se iniciar o programa sem dar argumentos corretos
  if ( argc!=4)
    {     
      help1 ();
      return 0;
    }
 
  else
    {
      if ( strlen(argv[2])!=1 || strlen(argv[3])!=1 )
        {
	  help2 ();
	  return 0;
	}
      else
	{
//alinea a
	  if ( (A (argv[1],argv[2]))>1 ||  (A (argv[1],argv[2]))==0)
	    printf("O carater '%s' surge %d vezes na string: '%s'.\n\n",argv[2], (A (argv[1],argv[2])),argv[1]);
	  else
	    printf("O carater '%s' surge %d vez na string: '%s'.\n\n",argv[2],(A (argv[1],argv[2])),argv[1]);
//alinea b
	  printf("A primeira ocorrência do carater '%s' \nna string '%s' é na posição: %d.\n\n",argv[2],argv[1],(B(argv[1],argv[2])));
//alinea c

	  if((B(argv[1],argv[2]))!=-1)
	    {
	  printf ("Nova string onde %s foi substituído\npor %s na string %s: %s.\n\n",argv[2],argv[3],argv[1],(p=C(argv[1],argv[2],argv[3])));
          free(p);
	    }
	  else
	    {
	      printf("O carater %s não surge na string %s, logo\nnão faz sentido criar uma string nova onde %s\nseja substituído por %s.",argv[2],argv[1],argv[2], argv[3]);
	    }
	}
// nos carateres se em vez de %s metermos %c, ao correr o programa no cygwin
// não aparece o carater na linha de comandos. Por isso optámos por deixar %s
    }
  return(0);
}
