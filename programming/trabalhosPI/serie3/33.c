#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>



int
A (char *a)
{
  int i;
  i=0;
  while(a[i]!=0)
    {
      ++i;
    }
  return i;
}


char*
B (char *a, char *b)
{
  int z,i1;
  
 
  for(i1=0; b[i1]!=0; ++i1)

    {
      a[i1]=b[i1];

	
    }
  a[i1]=0;
  return a;


}


char*
C (char *a, char *b)
{
  int z,i1;
  
  z=A(a);

  
    for(i1=0; b[i1]!=0;++i1)

    {
      a[z+i1]=b[i1];

	
    }
  a[z+i1]=0;
 

  return a;


}


int main(int argc, char **argv)
{
  int a,b,z, i1;
  char *c,*p;
 
  /*se iniciar o programa sem dar argumentos corretos
    if (argc!=3)
    {
    init (0);
    return 0;
    }
  */
  if (argc==3)
    {

      a= A(argv[1]);
      b=A(argv[2]);
      printf("Comprimento de string 1: %d, comprimento de string 2: %d\n",a,b);



      z= A(argv[1]) + A(argv[2] +1); //meter nos outros
   

    p=(char*)malloc(z);


      B(p,argv[1]);

      printf("String 1: %s , Copy de string 1 e 2: %s\n",argv[1],p);

 
      C(p,argv[2]);

      printf("cat de de string 1 com string 2: %s \n",p);



      return(0);



    }

}

