#include <stdio.h>
#include <math.h>

int main()
{
  float x1,x2,a,b,c,d,p,q;
  printf("Dada a equação ax²+bx+c=0, insira os valores de a, b e c separados por           um espaço\n");
  scanf("%f %f %f", &a,&b,&c);
  printf("%.2fx²+%.2fx+%.2f=0\n", a,b,c);
   d= b*b-4*a*c;

 if( d>0)
   {
      x1=(-b+sqrt(d))/(2*a);
      x2=(-b-sqrt(d))/(2*a);
      printf("Soluções são %.2f e %.2f\n", x1,x2);
   }

 if (d==0)
   {
     x1=-b/(2*a);
     printf("A solução é %.2f e é uma raíz dupla\n", x1);
       }
 if (d<0)
   {
     p= -b/(2*a);
     q=sqrt(-d)/(2*a);
     printf(" As soluções são imaginárias. São: %.2f+%.2fi e %.2f-%.2fi\n",p,q,p,q);
       }
return(0);
}
