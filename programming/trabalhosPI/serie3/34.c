#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>


int main(int argc, char **argv)
{
  double r,a,c;
  char b;

  /*se iniciar o programa sem dar argumentos corretos
    if (argc!=4)
    {
    init (0);
    return 0;
    }
  */
  if (argc==4)
    {
    sscanf (argv[1],"%lf", &a);
  sscanf (argv[2],"%c",&b);
  sscanf (argv[3],"%lf",&c);
    }
  //printf(" resultado: (%c) %lf\n",b,r);
  {
    if(b=='+')
      r=a+ c;

    if(b=='x')
      r=a* c;

    if(b=='-')
      r=a- c;

    if(b=='/')
      r=a/ c;
    if(b=='^')
      r=pow(a,c);

  }
  printf(" resultado: %lf\n",r);


  return 0;
}
