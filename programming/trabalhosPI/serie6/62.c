#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>




typedef struct
{
  double r;
  double i;
  double n;
} complexoen;

void
def (complexoen *x)
{
  x->r=((((double)rand()/(double)(RAND_MAX))*35)-12);
  (*x).i=((((double)rand()/(double)(RAND_MAX))*35)-12);
  (*x).n=sqrt(((*x).r)*((*x).r)+ ((*x).i)*((*x).i));
}


void
ord (complexoen **v, int n)
{
  int i=1,t;
  complexoen *a;

  while(1)
    {
      t=0;
      for(i=1; i<n; ++i)
	{
	  if ((v[i-1]->n)<(v[i]->n))
	    {
	      a=v[i-1];
	      v[i-1]=v[i];
	      v[i]=a;
	      t=1;
	    }
	}
      if(t==0)
	break;
    }
}

/* void */
/* troca(complexoen **v, complexoen **u) */
/* { */
/*  complexoen *a; */

/*       a=*v */
/*       *v=*u; */
/*       *u=a; */
/* } */




int
main(int argc,char **argv)
{
  int i,n;
  complexoen **v;
  
  srand(time(NULL));
 
  sscanf(argv[1],"%d",&n);

  if(argc==2)
    {
      v=malloc(n*(sizeof(complexoen*)));
      for(i=0;i<n;++i)
	{
	  v[i]=malloc((sizeof(complexoen)));
	  def(v[i]);
	  printf("%d  %lf %lf %lf\n",i, v[i]->r,v[i]->i,v[i]->n);
	 
 
	}
      printf("\n");

      ord(v,n);
      for(i=0;i<n;++i)
	{
	  printf("%d  %lf %lf %lf\n",i, v[i]->r,v[i]->i,v[i]->n);
	}
      //fazer free dos mallocs
    }

}
