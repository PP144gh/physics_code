#include<stdio.h>
int main()
{
  float x, u;
  int i;
  x=0.7;
  i=0;
      printf("Insira o valor inicial de x: ");
      scanf("%f", &x);
      printf("Insira o valor de u: ");
      scanf("%f", &u);
      x=u*x;
  while((i<=20)&&(x<=1)&&(x>=0))
    {
      printf("Iter %d: x=%f\n", i, x);
      x=u*x;
      i++;
    }
  return 0;
}
