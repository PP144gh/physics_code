#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

//função 'welcome'
void  
init()
{
  printf("***Pedro Pereira 78889 e Inês Roça 78164***\n");
  printf("Bem vindo. Este programa tem como objetivo ler um ficheiro\n");
  printf("do tipo .txt e reescrever outro do mesmo tipo mas com o\n");
  printf("texto invertido. Isto é em cada linha, o último carater é o\n");
  printf("primeiro, o penúltimo é o segundo, etc. \n");
  printf("Para o correr devidamente, siga a sintaxe: \n");
  printf("./programa file_de_leitura.txt file_de_escrita.txt\n");
  exit(1);
      
}

//função caso o utilizador não cumpra a sintaxe do prog.
void
input_error()
{
  printf("Introduziu algo absurdo. O programa vai encerrar.\n");
  printf("Para o correr devidamente, siga a sintaxe: \n");
  printf("./programa file_de_leitura.txt file_de_escrita.txt\n");
  exit(1);
}
//função de erro de leitura do ficheiro
void
file_error()
{
  printf("Erro na leitura do ficheiro. O programa vai encerrar.\n");
  printf("Introduza o nome dum ficheiro de leitura existente, e de\n");
  printf("tipo válido. (.txt)\n");
  printf("- Nos nossos testes utilizámos o ficheiro doc.txt -\n");
  exit(1);
}
//introdução inválida para o tipo do ficheiro de saída
void
outf_error()
{
  printf("Introduziu um tipo de ficheiro inválido para o ficheiro\n");
  printf("de saída. Introduza nome_ficheiro_saída.txt\n");
  exit(1);
}

//função que inverte a string
char*
troca_txt(char p[500])
{
  int i,x;
  char a;
  x=strlen(p)-1;
  for(i=0;i<x/2;++i)
    {
      a=p[i];
      p[i]=p[x-i-1];
      p[x-i-1]=a;
    }
  return p;
}

//funçao necessaria para testar se o utilizador introduziu um tipo de ficheiro de saída válido
char*
troca_argv(char p[20])
{
  int i,x;
  char a;

  x=strlen(p);
  for(i=0;i<x/2;++i)
    {
     a=p[i];
      p[i]=p[x-i-1];
      p[x-i-1]=a;
    }
  return p;
}


//main
int
main(int argc, char **argv)
{
  int M,N,i,teste1=0,teste2=0,i2;
  char  v[500];
  FILE *f,*g;


  if(argc==1) 
    { 
      init();
    } 
  if (argc==3)
    {
    
      f=fopen(argv[1],"rt");
      if (f==NULL)
	file_error();

      //Encontrámos a funçao strncmp na C reference card cedida pelo professor
     
      else if( strncmp (troca_argv(argv[2]),"txt.",4)==0)
	{ 
	  //inverte novamente a string, para se ter a original, pois é necessário invertê-la para fazer o teste.
	  troca_argv(argv[2]);   
	  g=fopen(argv[2],"wt");
	  while(fgets(v,500,f)!=NULL)
	    {
	      troca_txt(v); 
	       
	      fprintf(g,"%s",v);
	    }
	  fclose(f);
	  fclose(g);
	}
      else 
	{
	  outf_error();
	}
    }
  else
    {
      input_error();
    }
  return 0;
}
