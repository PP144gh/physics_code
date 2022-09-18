#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

int
main(int argc, char **argv)
{
  int M,N,i,teste1=0,teste2=0,i2;
  char  v[1000];
  FILE *f,*g;


  /* if(argc==1) */
  /*   { */
  /*     help1(); */
  /*     return 0; */
  /*   } */

  if (argc==4)
    {
      if((strcmp(argv[1],"m2M")==0))
	{
	  f=fopen(argv[2],"rt");
	  if (f==NULL)
	    printf("Erro na leitura do ficheiro. Vai encerrar.\n");
	  g=fopen(argv[3],"wt");
	  while(fgets(v,1000,f)!=NULL)
	    {
	      for(i=0;v[i]!=0;++i)
		{
		  if(v[i]>=97 && v[i]<=122)
		    v[i]=v[i]-32; 
		}
	      fprintf(g,"%s",v);
	    }
	  fclose(f);
	  fclose(g);
	}

      else if((strcmp(argv[1],"M2m")==0))
	{
	  f=fopen(argv[2],"rt");
	  if (f==NULL)
	    printf("Erro na leitura do ficheiro. Vai encerrar.\n");
	  g=fopen(argv[3],"wt");

	  while(fgets(v,1000,f)!=NULL)
	    {
	    
	      for(i=0;v[i]!=0;++i)
		{
		  if(v[i]>=65 && v[i]<=90)
		    v[i]=v[i]+32; 
		}
	      fprintf(g,"%s",v);
	    }
	  fclose(f);
	  fclose(g);
	}
      else
	{
	  printf("Introduziu algo absurdo. O programa vai encerrar.");
	  return 0;
	}

   
    }
  return 0;
}
