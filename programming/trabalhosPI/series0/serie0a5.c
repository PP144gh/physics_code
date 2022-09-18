#include <stdio.h>
int
main()
{
  int i,r,n,teste;
  n=0;
  printf("Quer a tabuada de que número?");
  teste= scanf("%d",&i);
 if (teste !=1)
   { 
     printf("O valor que introduziu é absurdo.\n");
     return(0);
  }
 
    while (n<=10)
      {
	r= i * n;
	printf("%d x %d = %d\n", i,n,r);
n= n+1;
  }
    return (0);
      }
