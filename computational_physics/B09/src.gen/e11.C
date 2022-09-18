void sum1(double *v) {
  int i=0;
  for (double x=0;x<5.5; x+=0.1) {
    v[55+i]= v[54+i]+x;
    v[i]= x;
    ++i;
  }
}
