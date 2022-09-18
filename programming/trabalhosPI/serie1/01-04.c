#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

int
main()
{
  int max,n,x;
  int i,i1,i2,t,teste,c;
  srand(time(NULL));
  t=1;

  while (t==1)
    {
      printf("[Pedro Pereira 78889 e Inês Roça 78164]\n*****Bem-Vindo ao casino do MEFT*****\n Conseguiu entrar porque é um aluno ou professor. Consideramo-nos uma espécie de clube secreto pois poucos sabem da nossa existência. Dizem as más línguas que é porque ninguém tem tempo para sequer indagar se existimos, mas nós ignoramos.\n A nossa coqueluche é o jogo da adivinhação do número inteiro positivo aleatório. Com certeza que vai querer jogar.\n Para tal, introduza: O número máximo possível de ser gerado, sabendo que gerará um número entre 0 e o que introduziu.\n****Prémios****\n Caso adivinhe um número entre:\n 0-100:\n 1-3 Tentativas - 6,022e23 moléculas de água.\n <3 Tentativas - 1 bolacha.\n 100-500:\n 1-3 Tentativas - 1 grama de anti-hidrogénio.\n <3 Tentativas - 1 eletrão de estimação.\n500-1000:\n 1-3 Tentativas -  1 grama de matéria negra.\n<3 Tentativas 1 muão com 5 anos de semi-vida.\nPara números superiores a 1000:\n 1-3 Tentativas - Prémio Surpresa.\n<3 Tentativas - 1 corda que fugiu da teoria.\n Número:");




      teste =scanf("%d",&max);
      while(getchar()!=10);

      // caso introduza uma letra ou 0 ou um número negativo
      while ( max<0 || max==0)
	{
	  printf("Introduza um  NÚMERO inteiro positivo, diferente de 0 (não seja batoteiro). O programa encerrará se introduzir novamente um valor absurdo.\n");
	  scanf("%d",&max);
	  while(getchar()!=10);
	  ++c;
	  // c é um contador do número de leituras inválidas
	  if(c==2) 
	    return(0);
	}
      c=0;
     
      // a % b <= b-1  <=> Temos que x vai estar compreendido entre 0 e max
      printf("Vai ser gerado um valor entre 0 e %d\n",max);
      x= rand()% (max+1);
	 
      i=0;
      // i é um contador de tentativas
      while (1)
	{

	  printf("Introduza o valor em que aposta.\n");
	  teste=scanf("%d",&n);
        
	  while(getchar()!=10);
	  ++i;

	  // caso introduza uma letra ou um número negativo
	  while (teste!=1 || n<0)
	    {
	 
	      ++c;
	      printf("Introduza um  NÚMERO inteiro positivo. O programa encerrará se introduzir novamente um valor absurdo.\n");
	      teste=scanf("%d",&n);
	 
	      if (c==2)
		return(0);
	    }
	  if (n>=0 && n>x)
	    {
	      printf("O valor em que apostou é superior ao gerado.\n");
	      
	      if(fabs(n-x)<(x/2))
		printf("Mas está perto.\n");
	      if(fabs(n-x)>(x/2))
		printf("Mas está longe.\n");
	    }
	  if (n>=0 && n<x)
	    {
	      printf("O valor em que apostou é inferior ao gerado.\n");
	      if(fabs(n-x)<(x/2))
		printf("Mas está perto.\n");
	      if(fabs(n-x)>(x/2))
		printf("Mas está longe.\n");
	    }
	  if(n>=0 && n==x)
	    {
	      // intervalo entre 0 e 100
	      if(max<100 && i<=3)
		printf("Parabéns! Acertou após %d tentativas!! Espero que esteja com sede porque acabou de ganhar 6,022e23 moléculas de água!!\n", i);
	      if(max<100 && i>3)
		printf("Parabéns! Acertou após %d tentativas!! Tantas! Não tem mesmo nada melhor pra fazer pois não? Acabou de ganhar uma bolacha. Enjoy.\n", i);
	      // intervalo entre 0 e um nr entre 100 e 500
	      if(max>=100 && max<=500 && i<=3)
		printf("Parabéns! Acertou após %d tentativas!! Acabou de ganhar algo que vai mudar a sua vida, 1 anti-hidrogénio!!\n", i);

	      if(max>=100 && max<=500 && i>3)
		printf("Parabéns! Acertou após %d tentativas!!  Tantas! Não tem mesmo nada melhor pra fazer pois não? Acabou de ganhar um super fofo eletrão de estimação!\n", i);
	      //intervalo entre 0 e um nr entre 500 e 1000
	      if(max>500 && max<=1000 && i<=3)
		printf("Parabéns! Acertou após %d tentativas!! Acabou de ganhar 1 grama de matéria negra, apresse-se e vá ganhar o Nobel!\n", i);

	      if(max>500 && max<=1000 && i>3)
		printf("Parabéns! Acertou após %d tentativas!!  Tantas! Não tem mesmo nada melhor pra fazer pois não? Acabou de ganhar um muão com 5 anos de semi-vida. Já dura mais que alguns animais, cuide bem dele.\n", i);
	      // intervalo entre 0 e um nr >1000
	      if(max>1000&& i<=3)
		printf("Parabéns! Acertou após %d tentativas!! Acabou de ganhar o livro Como criar a teoria da grande unificação (para totós).\n", i);

	      if(max>1000 && i>3)
		printf("Parabéns! Acertou após %d tentativas!!  Tantas! Não tem mesmo nada melhor pra fazer pois não? Acabou de ganhar uma corda que fugiu da teoria,  tão inútil como ela própria.\n", i);



	      printf("Deseja jogar novamente? Digite 1 se sim, digite 2 se não.\n");
	      scanf("%d",&t);
	      while(getchar()!=10);
	      // caso t=2 o programa encerra. t controla o fecho do programa
	      break;

	    }
	}

    }
  return(0);
}
