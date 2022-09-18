#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>



int 
main(int argc, char **argv)
{
  int i,n,c;
  unsigned short int v[65536],*b;  
  FILE *f;
  char a;
 
  //ver nr maximo 
  f=fopen("spins.txt","wb");
  for(i=0; i<=65535;++i)
    v[i]=i;

  a =fwrite(v, sizeof(unsigned short int), 65536,f); 

  fclose(f); 

  for(i=0;i<16;++i)
    {
      n = n*2 + (argv[1][i]-48);
    }
  printf("%d",n);

  f=fopen("spins.txt","rt");
	
  c=fseek(f,2*n*sizeof(unsigned short int), SEEK_SET); 

  fread(&b,sizeof(unsigned short int),c,f);
  fclose(f); 
  printf("%d\n", b); 


  return 0;



 
  
    }

  

  
