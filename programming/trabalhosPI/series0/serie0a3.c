#include <stdio.h>
int
main()
{
float f;
int c;
c=0;
while(c<=100)
{
f=c * 1.8 + 32;
printf ("%d C = %6.2f F\n",c,f);
c=c+1;
}
return (0);
}
