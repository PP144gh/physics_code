#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void  
init()
{
  printf("***Pedro Pereira 78889 e Inês Roça 78164***\n");
  printf("Bem vindo. Este programa tem como objetivo calcular o\n");
  printf("valor numérico da derivada duma função y=f(x) num ponto.\n");
  printf(" Caso 1:  sin(x)\n");
  printf(" Caso 2:  sin(2x)\n");
  printf(" Caso 3:  cos(x)\n");
  printf(" Caso 4:  tan(x)\n");
  printf(" Caso 5:  arcsin(x)\n");
  printf(" Caso 6:  arccos(x)\n");
  printf(" Caso 7:  log(x)\n");
  printf(" Caso 8:  log10(x)\n");
  printf(" Caso 9:  exp(5x)\n");
  printf(" Caso 10: Sair\n");
  printf("Introduzir o caso corres. à função\n");     
}


double
deriva(double (*f) (double), double x)

{
  double g,h;
  if (f(x)!=0)
    h=f(x)*1e-10;
  else
    h=1e-5;
  g=(f(x+h)-f(x))/h;
  return g;

}

int 
main ()
{
  int i=0,t,t3,b=1;
  double (*f) (double), x;
  
  while(b==1)
    { 	
      init(); 
      t=scanf("%d",&i);
      if(t!=1)
	{
	  printf("Introduziu um valor absurdo. O programa vai encerrar.\n");
	  return 0;
	}
      //pra poder usar o t em baixo sem declarar outra variavel
      t=0;
      if (i==10)
	return 0;
      else if( i<1 || i>9)
	{
	  printf("Por favor, introduza valores entre 1 e 9, que correspondam à função que pretende derivar. Tente novamente a seguir.\n");
	  return 0;
	}

      printf("Introduza o valor de x onde quer calcular a derivada.\n");
      t=scanf("%lf",&x);
      if(t!=1)
	{
	  printf("Introduziu um valor absurdo. O programa vai encerrar.\n");
	  return 0;
	}
    
      switch(i)
	{
	case 1: 
	  {
	    f=sin;

	    printf("Derivada de sin(x) em x=%lf :%lf\n",x,deriva(f,x));
	    printf("Derivada exata de sin(x) em x=%lf : %lf\n",x,cos(x));
	    printf("Erro: %lf\n",fabs(cos(x)-deriva(f,x)));
	    break;
	     
	  }
	case 2: 
	  {
	    f=sin;	  
	    printf("Derivada de sin(2x) em x=%lf :%lf\n",x,2*deriva(f,2*x));
	    printf("Derivada exata de sin(2x) em x=%lf : %lf\n",x,2*cos(2*x));
	    printf("Erro: %lf\n",fabs(2*cos(2*x)-2*deriva(f,2*x)));
	    // como a derivada de sin é cos, utilizando a formula de derivação dada o programa dá-nos o valor cos(2x) logo temos de multiplicar por 2 para a derivada estar certa
	    break;
	  }
	case 3: 
	  {
	    f=cos;
	  
	    printf("Derivada de cos(x) em x=%lf :%lf\n",x,deriva(f,x));
	    printf("Derivada exata de cos(x) em x=%lf : %lf\n",x,-sin(x));
	    printf("Erro: %lf\n",fabs(-sin(x)-deriva(f,x)));
	    break;
	  }
	case 4: 
	  {
	    f=tan;
	  
	    printf("Derivada de tan(x) em x=%lf :%lf\n",x,deriva(f,x));
	    printf("Derivada exata de tan(x) em x=%lf : %lf\n",x,(1/( pow(cos(x),2))));
	    printf("Erro: %lf\n",fabs(1/( pow(cos(x),2)))-deriva(f,x));
	    break;
	  }
	case 5: 
	  {
	    if(x>-1 && x<1)
	      {
		f=asin;
		printf("Derivada de arccsin(x) em x=%lf :%lf\n",x,deriva(f,x));
		printf("Derivada exata de arcsin(x) em x=%lf : %lf\n",x,(1/(sqrt(1-pow(x,2)))));
		printf("Erro: %lf\n",fabs(1/(sqrt(1-pow(x,2))))-deriva(f,x));
	      }
	    else
	      {
		printf("arccosseno não está definida nesse valor do domínio. Derivada não existe.\n");
	      }
	    break;
	  }
	case 6:
	  { 
	    if(x>-1 && x<1)
	      {
		f=acos;
		printf("Derivada de arcos(x) em x=%lf :%lf\n",x,deriva(f,x));
		printf("Derivada exata de arccos(x) em x=%lf : %lf\n",x,(-1/(sqrt(1-pow(x,2)))));
		printf("Erro: %lf\n",fabs(-1/(sqrt(1-pow(x,2))))-deriva(f,x));
	      }
	    else
	      {
		printf("arcccosseno não está definida nesse valor do domínio. Derivada não existe.\n");
	      }
	    break;
        
	  }
	case 7: 
	  {
	    if (x>0)
	      {
		f=log;
		printf("Derivada de log(x) em x=%lf :%lf\n",x,deriva(f,x));
		printf("Derivada exata de log(x) em x=%lf : %lf\n",x,(1/x));
		printf("Erro: %lf\n",fabs((1/x)-deriva(f,x)));
	      }
	    else
	      {
		printf("log(x) não está definida nesse valor do domínio. Derivada não existe.\n");
	      }
	    break;
	  }

	case 8: 
	  {
	    if (x>0)
	      {
		f=log10;
		printf("Derivada de log(x) em x=%lf :%lf\n",x,deriva(f,x));
		printf("Derivada exata de log(x) em x=%lf : %lf\n",x,(1/(x*log(10))));
		printf("Erro: %lf\n",fabs((1/(x*log(10))- deriva(f,x))));
	      }
	    else
	      {
		printf("log10(x) não está definida nesse valor do domínio. Derivada não existe\n");
	      }
	    break;
	  }
	case 9: 
	  {
	    //isto dá valores muito estranhos. Demasiado grandes e a partir dum valor de x "pequeno", por ex x=9, ele diz que os números são infinito
	    f=exp;
	    printf("Derivada de exp(5x) em x=%lf : %lf\n",x,5*deriva(f,5*x));
	    printf("Derivada exata de exp(5x) em x=%lf : %lf\n",x,(5*exp(5*x)));
	    printf("Erro: %lf\n",fabs((5*exp(5*x)- 5*deriva(f,5*x))));
	    break;
	    //com a formula dada o programa calcula o valor de exp(5x), é necessário multiplicar por 5 para representar a formula de derivação correta.
	  }
	}
      //pra poder usar o novamente
      t=0;
      printf("Deseja sair? Se sim, prima um número qualquer. Se deseja calcular outra derivada prima 1.\n");
      t=scanf("%d",&b);
      if(t!=1)
	{
	  printf("Introduziu uma letra. O programa vai encerrar.\n");
	  return 0;
	}
    }
 

  return 0;
    
}
