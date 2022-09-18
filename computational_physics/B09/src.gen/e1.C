double addnumbers(int a,int b){
  double sum = 0.;
  if (a>b) { //swap
    int buf = a;
    a = b;
    b = buf;
  }
  for (int i=a; i<=b; i++) 
    sum += i;
  return sum;
}
double addnumbers(double a,double b){
double sum = 0.;
  if (a>b) { //swap
    double buf = a;
    a = b;
    b = buf;
  }
  for (double i=a; i<=b; i+=.5) 
    sum += i;
  return sum;
}

