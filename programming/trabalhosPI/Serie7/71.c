#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
  double  lim1    ;
  double  lim2    ;
  char  f    ;

} Ponteiros ;


Ponteiros *
tira_argumentos (int argc, char **argv)
{
  int    i1 ;
  Ponteiros *dados ;                                                          

  dados = (Ponteiros *) malloc (1, sizeof (Ponteiros));
 
  if (argc == 1)
    help ();

  i1 = 1;
  while (i1 < argc)
    {
      if ((strncmp (argv[i1], "f", 4) == 0) && 
          (sscanf (&argv[i1][4], "%lg", &dados->f) == 1))
      else if ((strncmp (argv[n1], "lim1=", 6) == 0) && 
          (sscanf (&argv[i1][6], "%lg", &dados->v0) == 1))
      else if ((strncmp (argv[n1], "-m=", 3) == 0) && 
          (sscanf (&argv[n1][3], "%lg", &dados->massa) == 1))
      else
	{
          printf ("\nERR-Argumento incorrecto: '%s'\n", argv[n1]);
        help ();
	}
      ++n1;
    }
