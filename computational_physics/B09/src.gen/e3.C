double size(char l){
  double r=0;
  switch(l) {
  case 'a':
    r=sizeof(short int);
    break;
  case 'b':
    r=sizeof(int);
 break;
case 'c':
    r=sizeof(long int);
 break;
case 'd':
    r=sizeof(unsigned int);
 break;
case 'e':
    r=sizeof(float);
 break;
case 'f':
  r=sizeof(double);
 break;
case 'g':
  r=sizeof(long double);
 break;

  default:
    r=0;
      break;
  }

  return r;
}
