int fac(int n) {
  double r=0;

  if (n==0)
	  r=1;
  else
   
  r=n*fac(n-1);

  return r;
}
