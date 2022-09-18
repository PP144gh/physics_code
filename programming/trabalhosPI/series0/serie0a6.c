#include <stdio.h>
int
main()
{
  int i,r,n,teste;
  n=0;
  printf("Quer a tabuada de que número?");

  teste=0;
  while(teste != 1)
    {
      teste = scanf("%d",&i);
      if (teste !=1)
        { 
          printf("O valor que introduziu não é um número.\n");
          printf("Quer a tabuada de que número?\n");
          while (getchar() != 10);
          //teste= scanf("%d",&i);
        }
    }



  if(i<0)
    {
      printf("O valor introduzido é negativo. Introduza um valor compreendido entre 0 e 100 exclusivé.\n");
printf("Quer a tabuada de que número?\n");
teste= scanf("%d",&i);
	     }
 if(i>99)
    {
      printf("O valor introduzido é superior ou igual a 100. Introduza um valor compreendido entre 0 e 100 exclusivé.\n");
printf("Quer a tabuada de que número?\n");
teste= scanf("%d",&i);
	     }

 
    while (n<=10)
      {
	r= i * n;
	printf("%d x %d = %d\n", i,n,r);
n= n+1;
  }
    return (0);
      }







 
