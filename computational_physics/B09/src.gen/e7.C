double addnumbersS(int n,int m){
  double sum = 0.;
   if (n>m) { //swap
     int buf = m;
     m = n;
     n = buf;
   }
  
   for (int i=n; i<=m; i++) 
   sum =sum+i*i;
  return sum;
}
