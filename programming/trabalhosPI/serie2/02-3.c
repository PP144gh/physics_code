#include<stdio.h>
#include<math.h>

void  
init(int status)
{
  printf("***Pedro Pereira 78889 e Inês Roça 78164***\n");
  printf("Bem vindo à calculadora do mínimo múltiplo comum");
  printf(" e máximo divisor comum de dois números A e B.");
  printf(" Ao correr novamente o programa escreva-os, separados por"); 
  printf(" um espaço, a seguir do comando de inicialização.\n");
  
      
}



int main(int argc, char **argv)
{
  long int a,b,r,c,d,a1,b1;
  int t1,t2,t3,i;
  // se iniciar o programa sem dar argumentos corretos
  if (argc!=3)
    {
      init (0);
      return 0;
    }
  if (argc==3)
    {
     
      t1=sscanf(argv[1],"%ld", &a);

      t2=sscanf(argv[2],"%ld",&b);

      if(a==0 || b==0)
	{
	  printf("Não faz muito sentido determinar o máximo divisor comum");
	  printf(" ou o mínimo múltiplo comum entre um número e zero. O máximo divisor comum será");
	  printf(" o número diferente de zero e o mínimo múltiplo comum será 0. Determinar para 0 e 0 é absurdo.");
	  printf(" Por isso, introduza dois valores inteiros positivos diferentes de zero.\n");
	  t1=14;
	  //esta igualdade vai obrigar o utilizador a introduzir novos valores
	}

      // caso introduza números negativos ou letras
      if (t1!=1 || t2!= 1)
	{
	  i=0;
	  // i é um contador de introduções absurdas
	  while(1)
	    {
	      if(t1!=14)
		//t1=14 somente quando o utilizador introduz zeros inicialmente. Este if previne os prints com informação parecida à de cima.
		{
		  ++i;
		  printf("Introduza dois números inteiros positivos. ");
		  printf("Se se enganar novamente concluirei que não é digno de utilizar este algoritmo milenar e encerrarei.\n");
		}
	      t3=scanf("%ld %ld", &a, &b);
	      while(getchar()!=10);  
	      // para que caso o utilizador introduza valores absurdos, o printf com o aviso de encerramento seja mostrado.
	      t1=15;
	      //quando lê corretamente
	      if(t3==2)
		break;
	      // à 2ª introdução de valores absurdos ele encerra
	      if(i==1)
		return 0;
	    }
	}
    }

  //variáveis para guardar os valores originais, de forma a serem apresentados no fim
  a1=a;
  b1=b;
  while(1)
    {
      r=a%b;
      if (r==0)
	{
	  c=b;
	  break;
	}
      a=b;
      b=r;
    }
  printf("O máximo divisor comum entre %ld e %ld é %ld.\n",a1,b1,c);
  d=((a1*b1)/c);
  printf("O menor multiplo comum entre %ld e %ld é %ld.\n",a1,b1,d);



  return(0);
}
