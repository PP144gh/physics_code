/**********************************
 *      Cálculo de derivadas       *
 *        João Barbosa             *
 *         Pedro Gomes             *
 **********************************/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double deriv(double(*f) (double), double x)
{
  double v,h;
  h = 10e-5;
  v = (f(x+h)-f(x))/h;

  printf("\nA derivada no ponto %lf é %lf.\n",x,v);
}

int main(int argc, char** argv)
{
  int a,b,c;
  float x;
  b=0;

  while(b!=10)
    {
      printf("\nAs funções cujas derivadas podem ser calculadas são:\n1-sin(x);\n2-cos(x);\n3-tan(x);\n4-asin(x) (arcseno);\n5-acos(x) (arccoseno);\n6-log(x);\n7-log10(x) (logaritmo na base 10);\n8-exp(5x) (em que 'exp' é o expoente de 'e', número de Nepper).\n9-sin(2x);\n10-Sair.\n\nEscolha a sua função: ");

      a=scanf("%i",&b);

      if(b==10)
	{
	  printf("\nAté à próxima!\n\n");
	  return 0;
	}
      else if(a==0 || b<1 || b>9)
	{
	  printf("\nPor favor, obedeça as instruções (não se esqueça que deve escrever o número correspondente à função desejada!\n\n");
	  return 0;
	}
      printf("Escolha o ponto em que deseja calcular a derivada: ");
      c=scanf("%f",&x);

      if(c==0)
	{
	  printf("\nOcorreu um erro na leitura dos dados. O seu ponto tem de ser um número!\n\n");
	  return 0;
	}

      switch(b)
	{
	case 1:
	  deriv(sin,x);
	  printf("Derivada real: %lf\n\n", cos(x));
	  break;
	case 2:
	  deriv(cos,x);
	  printf("Derivada real: %lf\n\n", -sin(x));
	  break;
	case 3:
	  deriv(tan,x);
	  printf("Derivada real: %lf\n\n", 1/((cos(x))*(cos(x))));
	  break;
	case 4:
	  if(x< -1 || x> 1)
	    {
	      printf("\nO domínio do arcseno é [-1,1]. Escolha um valor de 'x' válido.\n\n");
	      return 0;
	    }
	  deriv(asin,x);
	  printf("Derivada real: %lf\n\n", 1/(sqrt(1-(x*x))));
	  break;
	case 5:
	  if(x< -1 || x> 1)
	    {
	      printf("\nO domínio do arccoseno é [-1,1]. Escolha um valor de 'x' válido.\n\n");
	      return 0;
	    }
	  deriv(acos,x);
	  printf("Derivada real: %lf\n\n", -1/(sqrt(1-(x*x))));
	  break;
	case 6:
	  if(x<=0)
	    {
	      printf("\nO domíno do logaritmo é ]0, +infinito[. Escolha um valor de 'x' válido.\n\n");
	      return 0;
	    }
	  deriv(log,x);
	  printf("Derivada real: %lf\n\n", 1/x);
	  break;
	case 7:
	  if(x<=0)
	    {
	      printf("O domíno do logaritmo é ]0, +infinito. Escolha um valor de 'x' válido.");
	      return 0;
	    }
	  deriv(log10,x);
	  break;
	  printf("Derivada real: %lf\n\n", 1/(x*log(10)));
	case 8:
	  deriv(exp,(5*x));
	  printf("Derivada real: %lf\n\n",(5*exp(5*x)));
	  break;
	case 9:
	  deriv(sin,(2*x));
	  printf("Derivada real: %lf\n\n", 2*cos(2*x));
	  break;
	}
    }
  return 0;
}


