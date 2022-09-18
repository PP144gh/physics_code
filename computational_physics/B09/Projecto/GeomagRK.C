#include"MagField.h"

int main(){
  /*      Alineas d,e)     */
   
  MagField M1,M2,M3,M4;
  // Trajetoria da particula 1 apos detetor
  M1.PartTraj2((Re+500000)*sqrt(2)/2,0,(Re+500000)*sqrt(2)/2,-2.1*exp10(7),0,-2.1*exp10(7),0.000006,2500000);
  // Trajetoria da particula 1 antes detetor
  M2.PartTraj2((Re+500000)*sqrt(2)/2,0,(Re+500000)*sqrt(2)/2,-2.1*exp10(7),0,-2.1*exp10(7),-0.000001,5000000,'r');
  // Trajetoria da particula 2 apos detetor
  M3.PartTraj2((Re+500000)*sqrt(2)/2,0,(Re+500000)*sqrt(2)/2,0,0,-3*exp10(8)*.998,0.00001,80000);
  // Trajetoria da particula 2 apos detetor
  M4.PartTraj2((Re+500000)*sqrt(2)/2,0,(Re+500000)*sqrt(2)/2,0,0,-3*exp10(8)*.998,-0.00001,5000000,'r');
  M1.Draw("close");
  M2.Draw("close");
  M3.Draw("close");
  M4.Draw("far");
  
  /*       Alinea a)     */
  MagField LL;
  LL.MagLines(0.5,-0.5,0.5,0.001,300000);
  LL.MagLines(-0.5,0.5,0.5,0.001,300000);
  LL.Draw("together");
}
