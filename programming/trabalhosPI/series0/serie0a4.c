#include <stdio.h>
int
main()
{
  float f,c;
int teste;
 printf("Introduza o valor da temperatura em graus centigrados?");
 teste= scanf("%f",&c);
f= c * 1.8 + 32;
 if (teste !=1)
   { 
     printf("O valor que introduziu é absurdo.\n");
     return(0);
  }
 
printf("Res: %5.2f F, fez %d leitura(s)do valor em graus centigrados. \n",f, teste);

return (0);
}
