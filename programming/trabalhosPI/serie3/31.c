#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>




int main(int argc, char **argv)
{
  long int a,b;
  int t;
  char *p;

  //se iniciar o programa sem dar argumentos corretos
  if (argc!=3)
  {
  init (0);
  return 0;
   }

  if (argc==3)
    {
      while(t==0)
	{
     a=strlen(argv[1]);
     b=strlen(argv[2]);

p=(char*)malloc(a+b);
 strcpy(p,argv[1]);
 strcat(p,argv[2]);
 printf("Concatenação da primeira string com a segunda: ");
 printf("%s\n",p);
 t=1;
 free(p);
	}
p=(char*)malloc(a+b);
 strcpy(p,argv[2]);
 strcat(p,argv[1]);
 printf("Concatenação da segunda string com a primeira: ");
 printf("%s\n",p);


 printf("Resultado de strcmp: %d",strcmp(argv[2],argv[1]));

 // caso avalie: if strcmp =0, args sao iguais, >0 um maior qe outro,etc
    }
  return(0);



}
