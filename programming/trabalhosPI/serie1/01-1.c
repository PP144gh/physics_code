#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

int
main()
{
  double x,y,r,q;
  int n,p,i;
  r=0.5;

  printf("Quantos pontos deseja gerar?\n");
  scanf("%d",&p);
  while( getchar()!=10);

  // p==0 caso introduza 0 ou uma letra, p<0 caso introduza um nr negativo

  if (p==0 || p<0)
    {
      printf("Introduza um valor inteiro positivo. O programa encerrará se introduzir novamente um valor absurdo.\n");
      scanf("%d",&p);
    }
  srand (time(NULL));
  if (p>0)
    {
      for (i=0;i<p; ++i)
	{
    
	  x= ((double) rand())/ ((double) RAND_MAX);
	  y= ((double) rand())/ ((double) RAND_MAX);
	  x=x-0.5;
	  y=y-0.5;

	  if ( pow (x,2)+ pow (y,2)<= pow(r,2))
	    {        
	      n=n+4;
	    }
	}
      q=((double)n)/p;
      printf("Razão entre o quádruplo de pontos caídos no circulo e dos pontos totais para %d pontos = %lf\n",p,q);
      printf("Explicação: A área do quadrado é 1 e a do círculo inscrito no quadrado é 1/4 de pi. Ao gerarmos pontos aleatórios, o quociente entre o número de pontos que pertencem ao círculo e ao quadrado dá uma estimativa da razão das suas áreas, isto é, 1/4pi. Como multiplicámos o número de pontos que pertencem ao círculo por 4, a razão será somente pi. Quanto mais pontos gerarmos mais o valor se aproximará de pi.\n");
      return(0);
    }

}
