#ifndef __MAG__
#define __MAG__
#include"TPolyLine3D.h"
#include"TF1.h"
#include"TF3.h"
#include"TAxis.h"
#include<cmath>
#include"cFCgraphics.h"
#include<vector>
#include<string>
#define b (3.07*exp10(-5))
#define mp (1.67*exp10(-27))
#define Re 6371000
#define c (3*exp10(8))
#define q (1.69*exp10(-19))
using namespace std;

class MagField {
 public:
  MagField(double Q=q,double M=mp,double B=b,double R=Re);//  Constructor
  ~MagField(){;};//  Destructor
  static double* MagForce(double,double,double);//  Returns Magnetic Force
  void MagLines(double,double,double,double,int);//  Obtains Magnetic Lines
  void PartTraj1(double,double,double,double,double,double,double,int,char cc='m');//  Obtains Particle Trajectory with RK2
  void PartTraj2(double,double,double,double,double,double,double,int,char cc='m');//  Obtains Particle Trajectory with RK4
  void Draw(string s="opt");//  Draws trajectories
private:
  vector<TPolyLine3D*> vp;//  Vector of trajectories
  TF1 *f;//  dvx/dt=f(x,y,z,vx,vy,vz)
  TF1 *g;//  dvy/dt=g(x,y,z,vx,vy,vz)
  TF1 *h;//  dvz/dt=h(x,y,z,vx,vy,vz)
};
#endif
