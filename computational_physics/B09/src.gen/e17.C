void e17(const double** const mx, const double * const vr, int n, int m, double* const pt){
  for(int i=0;i<n;++i)
    for(int j=0;j<m;++j)
      pt[i]+=mx[i][j]*vr[j];
}
