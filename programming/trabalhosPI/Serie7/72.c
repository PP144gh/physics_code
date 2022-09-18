
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int
gera()
{
  return (rand()%2);

}

/* unsigned short int */
/* trocaspin(int *v) */
/* { */
/*   int t1,i=0; */
/*   unsigned short int s; */
/*  printf("Qual o spin que pretende mudar?\n"); */
/*       t1=scanf("%d",&i); */
/*       if(t1!=1) */
/* 	{ */
/* 	  printf("Introduziu algo absurdo. Vai encerrar\n"); */
/* 	  return 0; */
/* 	} */
/*       if(i<0 || i>15) */
/* 	{ */
/* 	printf("Introduziu uma ordem de spin inválida.Vai encerrar\n"); */
/*       return 0; */
/* 	} */
/*       else */
/* 	{ */
/* 	  s=s^v[i]; */
/* 	  printf("%i\n",s); */
/* 	} */
/*       return s; */
/* 	} */

//por as funçoes fora da main

int main(int argc, char **argv)
{
  double a;
  int i,b=0,t1=0, v[16]={32768,16384,8192,4096,2048,1024,512,256,128,64,32,16,8,4,2,1};
  char t[17];
  unsigned short int s=0;
  srand(time(NULL));

      for(i=0;i<16;++i)
	{
	  //a
	  //compara em binário, adiciona 1's onde não existem em s
	  if(gera()==1)
	    s=s|v[i];
	}
      printf("%i\n",s);

      //b
      for(i=0;i<16;++i)
	{
	  //compara em binário,compara s (em binario) com 2^k (em binario),..., caso não tenham nenhum 1 em comum, o valor tomado na posção k é 0.
	  if((s&v[i])==0)
	    t[i]=48;
	  else
	    t[i]=49;
	}
      t[i]=0;
      printf("%s\n",t);

      i=0;
      printf("Qual o spin que pretende mudar?\n");
      t1=scanf("%d",&i);
      if(t1!=1)
	{
	  printf("Introduziu algo absurdo. Vai encerrar\n");
	  return 0;
	}
      if(i<0 || i>15)
	{
	printf("Introduziu uma ordem de spin inválida.Vai encerrar\n");
      return 0;
	}
      else
	{
	  //c
	  //compara em binário,compara s (em binario) com 2^k (em binario),..., troca o numero na posição i da representaçao binaria.
	  s=s^v[i];
	  printf("%i\n",s);

	  for(i=0;i<16;++i)
	    {
	      //compara em binário,compara s (em binario) com 2^k (em binario),..., caso não tenham nenhum 1 em comum, o valor tomado na posção k é 0.
	
	      if((s&v[i])==0)
		t[i]=48;
	      else
		t[i]=49;
	    }
	  printf("%s\n",t);

	}
      t1=0;
      while(b==0)
	{
	  printf("Quer trocar outro spin? Se sim  prima 0, senão prima outro número qualquer.\n");
	  t1=scanf("%d",&b);
	  if(t1!=1)
	    {
	      printf("Introduziu algo absurdo. Vai encerrar\n");
	      return 0;
	    }
 
      
	}
      return 0;
}


