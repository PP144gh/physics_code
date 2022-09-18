#include<stdio.h>
#include<math.h>


int main()
{ 
  FILE*f;
  int i,i2,d;
  double a,b,x;
  
  f=fopen("orbitas","r");
  d=0;
while (1 )
    {
      d=d+1;
     
      i2=fscanf(f,"\n%d : %lf\n",&i,&x);
      if (i2!=2)
	break;
      printf("%d : %lf   ",i,x);
      if(d%2==0)   
	printf("\n");
    }

  fscanf(f,"órbita com %d valores; rinicial = %le ; x0= %lf\n", &i2,& b,&a);
printf("órbita com %d valores; rinicial = %le ; x0= %lf\n", i2, b,a);
 
fclose(f);

      return(0);

}
