#include <stdio.h>
int
main()
{
  FILE *fich;
  int i,r,n,teste;
  n=0;
  fich=fopen("tabuada","w");
  printf("Quer a tabuada de que número?\n");
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
        fprintf(fich,"%d x %d = %d\n", i,n,r);

        ++n;
  }
    fclose(fich);
return (0);
      }
