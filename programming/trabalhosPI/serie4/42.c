#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

void
help1 ()
{
  printf("\n");
  printf("*****************************************\n");
  printf("* Pedro Pereira 78889 e Inês Roça 78164 *\n");
  printf("*****************************************\n\n");
  printf("Bem-Vindo à calculadora de complexos. Se desejar\n");
  printf("determinar o módulo dum complexo, introduza algo do tipo:\n");
  printf("./prog (espaço) mod (espaço) parte real (espaço) parte imaginária\n");
  printf("Se desejar antes realizar operações entre dois complexos:\n");
  printf("Siga a mesma sintaxe de cima mas em vez de mod\n");
  printf("introduza +,-,x ou '\' dependendendo da operação que\n");
  printf("pretende fazer. Depois, introduza a parte real e imaginária\n");
  printf("do 2º complexo.\n");
  exit(1);
}

void
help2 ()
{
  printf("\n");
  printf("Não introduziu um número correto de argumentos.\n");
  printf("Se quiser determinar o módulo dum complexo introduza\n");
  printf("mod e as respetivas partes do mesmo. Se quiser operar entre\n");
  printf("2 complexos, introduza +.-,x ou / e as partes reais e\n");
  printf("imaginárias de cada um. O programa vai encerrar.\n");
  exit(1);
}


typedef struct
{
  double r;
  double i;
} complexo;

void
mod (complexo *x, double *m)
{
  *m =sqrt(((*x).r)*((*x).r)+ ((*x).i)*((*x).i));
}

void
sub (complexo *x, complexo *y, complexo *z)
{
  (*z).r=(*x).r-(*y).r;
  (*z).i=(*x).i-(*y).i;
}

void
soma (complexo *x, complexo *y, complexo *z)
{
  (*z).r=(*x).r+(*y).r;
  (*z).i=(*x).i+(*y).i;
}

void
mult (complexo *x, complexo *y, complexo *z)
{
  (*z).r=( ((*x).r)*((*y).r)-( ((*x).i)*( ((*y).i) )));
  (*z).i=((((*x).r) * (*y).i) +(((*y).r) * ((*x).i)));
}
void
quo (complexo *x, complexo *y, complexo *z)
{
  (*z).r=(( ((*x).r)*((*y).r)+( ((*x).i)*( ((*y).i) )))/((((*y).r)*((*y).r))+((((*y).i)*((*y).i)))));

  (*z).i= (( (-(*x).r)*((*y).i)+( ((*y).r)*( ((*x).i) )))/((((*y).r)*((*y).r))+((((*y).i)*((*y).i)))));

}


int
main(int argc, char **argv)
{
  int teste1=0,teste2=0,teste3=0,teste4=0; 
  complexo x,y,z;
  double m;

  if(argc==1)
    {
      help1();
      return 0;
    }

  if (argc==4)
   {
     teste1=sscanf (argv[2],"%lf",&(x.r));
     teste2=sscanf (argv[3],"%lf",&(x.i));
     if((teste1+teste2!=2))
       {
         printf("Introduziu um ou mais argumentos que não são números\n");
         printf("reais.\n O programa vai encerrar. Lembre-se que\n");
         printf("um número\n complexo é um par ordenado de dois\n");
         printf("números reais.\n");
         return 0;
       }
     if(0==strcmp(argv[1],"mod"))
       {
         mod(&x,&m);
         if((x.i)<0)
           printf("O complexo lido foi: %.3lf - %.3lfi.\nO seu módulo é = %.3lf\n",(x.r),fabs((x.i)),m);
         else 
           printf("O complexo lido foi: %.3lf + %.3lfi.\nO seu módulo é = %.3lf\n",(x.r),(x.i),m);
	 return 0;
       }
     else
       {
         printf("Introduziu algo não reconhecível. No primeiro argumento\n");
         printf("introduza mod se quer determinar o módulo do complexo\n");
         printf("que introduziu. Pode fazer operações entre complexos\n");     
	 printf("se introduzir uma operação válida e dois complexos\n");
	 printf("(parte real e imaginária do 1º seguidas das do 2º.\n");
         return 0;
       }
    }
  if(argc==6)
    {
     teste1=sscanf (argv[2],"%lf",&(x.r));
     teste2=sscanf (argv[3],"%lf",&(x.i));
     teste3=sscanf (argv[4],"%lf",&(y.r)); 
     teste4=sscanf (argv[5],"%lf",&(y.i)); 
    if((teste1+teste2+teste3+teste4!=4))
       {
         printf("Introduziu um ou mais argumentos que não são números\n");
         printf("reais.\n O programa vai encerrar. Lembre-se que\n");
         printf("um número\n complexo é um par ordenado de dois\n");
         printf("números reais.\n");
         return 0;
       }
     if((x.i)<0)
       printf("O 1º complexo lido foi: %.3lf - %.3lfi\n",(x.r),fabs((x.i)));
     else 
       printf("O 1º complexo lido foi: %.3lf + %.3lfi\n",(x.r),(x.i));
     if((y.i)<0)
       printf("O 2º complexo lido foi: %.3lf - %.3lfi\n",(y.r),fabs((y.i)));
     else 
       printf("O 2º complexo lido foi: %.3lf + %.3lfi\n",(y.r),(y.i));  

     if(0==strcmp(argv[1],"+"))
       {
         soma(&x,&y,&z);
         if((z.i)<0)
          printf("A sua soma é: %.3lf - %.3lfi\n",(z.r),fabs((z.i)));
         else 
          printf("A sua soma é: %.3lf + %.3lfi\n",(z.r),(z.i));
	  return 0;
	}
     if(0==strcmp(argv[1],"x"))
       {
         mult(&x,&y,&z);
         if((z.i)<0)
           printf("O seu produto é: %.3lf - %.3lfi\n",(z.r),fabs((z.i)));
         else 
           printf("O seu produto é: %.3lf + %.3lfi\n",(z.r),(z.i));
         return 0;
       }
     if(0==strcmp(argv[1],"/"))
       {
         if((y.r)==0 || (y.i)==0)
           {
             printf("Não pode dividir por zero. O programa vai encerrar.\n");
             return 0;
           }
         quo (&x,&y,&z);
         if((z.i)<0)
           printf("O seu quociente é: %.3lf - %.3lfi\n",(z.r),fabs((z.i)));
         else 
           printf("O seu quociente é: %.3lf + %.3lfi\n",(z.r),(z.i));
         return 0;
       }
     if(0==strcmp(argv[1],"-"))
       {
         sub(&x,&y,&z);	
	 if((z.i)<0)
	   printf("A subtração do primeiro com o segundo é: %.3lf - %.3lfi\n",(z.r),fabs((z.i)));
	 else 
	   printf("A subtração do primeiro com o segundo é: %.3lf + %.3lfi\n",(z.r),(z.i));
	 return 0;
	}
      else
       {
         printf("Introduziu algo não reconhecível. No primeiro argumento\n");
         printf("introduza +,-,x ou '\' dependendendo da operação que\\n");
         printf("quer realizar entre os complexos. O programa vai encerrar.\n");
         return 0;
       }
    }
  else 
   {
     help2();
     return 0;
   }
  return 0;
}

