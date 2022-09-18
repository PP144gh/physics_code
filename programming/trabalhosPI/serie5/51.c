#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

void  
init()
{
  printf("***Pedro Pereira 78889 e Inês Roça 78164***\n");
  printf("Bem vindo à calculadora do mínimo múltiplo comum");
  printf(" e máximo divisor comum de dois números A e B.");
  printf(" Ao correr novamente o programa escreva-os, separados por"); 
  printf(" um espaço, a seguir do comando de inicialização.\n");
  exit(1);
      
}
char*
troca(char p[9])
{
  int i,x;
  char a;
  x=strlen(p);
  for(i=0;i<x/2;++i)
    {
      a=p[i];
      p[i]=p[x-i-1];
      p[x-i-1]=a;
    }
  return p;
}

char*
base (char p[9], int i1,int b)
{
  int i2,r,i3;
 
  i3=i1;
  for(i2=0;i3!=0;++i2)
    {
      r=i3%b;
      if(r>9)
	p[i2]=r+55;
      else
	p[i2]=r+48;
      i3=i3/b;
    }
  p[i2]=0;
  troca(p); 
  return p;
}





int 
main(int argc, char **argv)
{
  char v[9]; 
 int i1;
  for(i1=0; i1<=255;++i1)
    {
      printf("decimal:%i     ",i1);
      printf("binária:%s     ",base(v,i1,2));
      printf("octal:%s     ",base(v,i1,8));
      printf("hexa:%s     ",base(v,i1,16)); 
      printf("\n");	  
    }
  return 0;
}
    
