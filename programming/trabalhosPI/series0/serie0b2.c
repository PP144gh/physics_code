#include <stdio.h>
int
main()
{
  float f,c;
  int u;
 printf("Se deseja converter graus Celsius em Fahrenheit escreva 1, se deseja o contrário escreva 2.\n");
 scanf("%d",&u);


 while( u!=1 && u!=2)
   {
     printf("Introduziu um valor incorreto.Se deseja converter graus Celsius em Fahrenheit escreva 1, se deseja o contrário escreva 2.\n");

    scanf("%d",&u);
	  while(getchar()!=10);
	
   }

        if (u==1)
           {
	     printf("Introduza o valor a converter em Fahrenheit.\n");
	     scanf("%f",&c);
	     while(c<-273.15)
	       {
		 printf("Temperaturas dessa ordem não existem.Introduza uma temperatura superior a -273.15ºC\n");
 scanf("%f",&c);
 while(getchar()!=10);
	       }
          f= c * 1.8 + 32;
         printf("Introduziu %.3fºC, que corresponde a %.3fF \n",c, f);
	   }

         if (u==2)
            {
 printf("Introduza o valor a converter em Celsius.\n");
	      scanf("%f",&f);
            c=(f-32)/(1.8);
                 while(c<-273.15)
	         {
		 printf("Temperaturas dessa ordem não existem.Introduza uma temperatura superior a -469.67F\n");
                 scanf("%f",&f);
                 while(getchar()!=10);
	          }
 
             printf("Introduziu %.3fF, que corresponde a %.3fºC \n",f, c);
             }

return (0);
}
