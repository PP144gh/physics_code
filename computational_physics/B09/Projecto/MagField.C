#include"MagField.h"

    /*  Constructor  */
MagField::MagField(double Q, double m, double B, double R){
  f=new TF1("f","[0]*sqrt(1-([4]*[4]+[5]*[5]+[6]*[6])/[7])/pow([1]*[1]+[2]*[2]+[3]*[3],2.5)*(2*[5]*[3]*[3]-[5]*[1]*[1]-[5]*[2]*[2]-3*[2]*[3]*[6])",-1,1);// dvx/dt=f(x,y,z,vx,vy,vz)
  g=new TF1("f","[0]*sqrt(1-([4]*[4]+[5]*[5]+[6]*[6])/[7])/pow([1]*[1]+[2]*[2]+[3]*[3],2.5)*(3*[1]*[3]*[6]-2*[4]*[3]*[3]+[1]*[1]*[4]+[2]*[2]*[4])",-1,1);// dvy/dt=g(x,y,z,vx,vy,vz)
  h=new TF1("f","[0]*sqrt(1-([4]*[4]+[5]*[5]+[6]*[6])/[7])/pow([1]*[1]+[2]*[2]+[3]*[3],2.5)*(3*[4]*[2]*[3]-3*[1]*[5]*[3])",-1,1);// dvz/dt=h(x,y,z,vx,vy,vz)
  f->SetParameter(0,Q*B*R*R*R/m);
  f->SetParameter(7,c*c);
  g->SetParameter(0,Q*B*R*R*R/m);
  g->SetParameter(7,c*c);
  h->SetParameter(0,Q*B*R*R*R/m);
  h->SetParameter(7,c*c);
}

    /*  returns Magnetic Force in point (x,y,z)*Re  */
double* MagField::MagForce(double x, double y, double z){
  double *p=new double[3];
  p[0]=b*pow(x*x+y*y+z*z,2.5)*3*z*x;//  Component x of Magnetic Force
  p[1]=b*pow(x*x+y*y+z*z,2.5)*3*z*y;//  Component y of Magnetic Force
  p[2]=b*pow(x*x+y*y+z*z,2.5)*(2*z*z-x*x-y*y);//  Component z of Magnetic Force
  return p;
  delete []p;
}

    /*  Obtains Magnetic Lines  */
void MagField::MagLines(double xa, double yb, double zd, double h, int n){
  double *x=new double[n];
  double *y=new double[n];
  double *z=new double[n];
  double *u;
  x[0]=xa;y[0]=yb;z[0]=zd;
  for(int i=0;i<n;++i){//  Cicle that adds small Magnetic Force vectors to last points
    u=MagForce(x[i],y[i],z[i]);
    x[i+1]=x[i]+h*u[0]/sqrt(u[0]*u[0]+u[1]*u[1]+u[2]*u[2]);
    y[i+1]=y[i]+h*u[1]/sqrt(u[0]*u[0]+u[1]*u[1]+u[2]*u[2]);
    z[i+1]=z[i]+h*u[2]/sqrt(u[0]*u[0]+u[1]*u[1]+u[2]*u[2]);
  }
  TPolyLine3D *p=new TPolyLine3D(n,x,y,z);//  Magnetic Line
  vp.push_back(p);
  delete []x;
  delete []y;
  delete []z;
  delete []u;
}

    /*  Runge-Kutta method of order 2  */ 
void MagField::PartTraj2(double x0, double y0, double z0, double vx, double vy, double vz, double ha, int n, char cc){
  double xk1, xk2, xk3, xk4;// x
  double yk1, yk2, yk3, yk4;// y
  double zk1, zk2, zk3, zk4;// z
  double vxk1, vxk2, vxk3, vxk4;// vx
  double vyk1, vyk2, vyk3, vyk4;// vy
  double vzk1, vzk2, vzk3, vzk4;// vz
  double *x=new double[n];
  double *y=new double[n];
  double *z=new double[n];
  x[0]=x0;y[0]=y0;z[0]=z0;
  TF1 *X=new TF1("X","[0]",-1,1);
  TF1 *Y=new TF1("X","[0]",-1,1);
  TF1 *Z=new TF1("Z","[0]",-1,1);
  double r=5*Re;
  //  Case in which r can be > 25*Re
  if (cc!='r'){
    int i;
    //  Cicle that calculates trajectory
    for(i=0;i<n&&r>Re;++i){
      f->SetParameter(1,x[i]);
      f->SetParameter(2,y[i]);
      f->SetParameter(3,z[i]);
      f->SetParameter(4,vx);
      f->SetParameter(5,vy);
      f->SetParameter(6,vz);
      g->SetParameter(1,x[i]);
      g->SetParameter(2,y[i]);
      g->SetParameter(3,z[i]);
      g->SetParameter(4,vx);
      g->SetParameter(5,vy);
      g->SetParameter(6,vz);
      h->SetParameter(1,x[i]);
      h->SetParameter(2,y[i]);
      h->SetParameter(3,z[i]);
      h->SetParameter(4,vx);
      h->SetParameter(5,vy);
      h->SetParameter(6,vz);
      X->SetParameter(0,vx);
      Y->SetParameter(0,vy);
      Z->SetParameter(0,vz);

      xk1=ha*X->Eval(0);
      yk1=ha*Y->Eval(0);
      zk1=ha*Z->Eval(0);
      vxk1=ha*f->Eval(0);
      vyk1=ha*g->Eval(0);
      vzk1=ha*h->Eval(0);

      f->SetParameter(1,x[i]+xk1/2);
      f->SetParameter(2,y[i]+yk1/2);
      f->SetParameter(3,z[i]+zk1/2);
      f->SetParameter(4,vx+vxk1/2);
      f->SetParameter(5,vy+vyk1/2);
      f->SetParameter(6,vz+vzk1/2);
      g->SetParameter(1,x[i]+xk1/2);
      g->SetParameter(2,y[i]+yk1/2);
      g->SetParameter(3,z[i]+zk1/2);
      g->SetParameter(4,vx+vxk1/2);
      g->SetParameter(5,vy+vyk1/2);
      g->SetParameter(6,vz+vzk1/2);
      h->SetParameter(1,x[i]+xk1/2);
      h->SetParameter(2,y[i]+yk1/2);
      h->SetParameter(3,z[i]+zk1/2);
      h->SetParameter(4,vx+vxk1/2);
      h->SetParameter(5,vy+vyk1/2);
      h->SetParameter(6,vz+vzk1/2);
      X->SetParameter(0,vx+vxk1/2);
      Y->SetParameter(0,vy+vyk1/2);
      Z->SetParameter(0,vz+vzk1/2);

      xk2=ha*X->Eval(0);
      yk2=ha*Y->Eval(0);
      zk2=ha*Z->Eval(0);
      vxk2=ha*f->Eval(0);
      vyk2=ha*g->Eval(0);
      vzk2=ha*h->Eval(0);

      f->SetParameter(1,x[i]+xk2/2);
      f->SetParameter(2,y[i]+yk2/2);
      f->SetParameter(3,z[i]+zk2/2);
      f->SetParameter(4,vx+vxk2/2);
      f->SetParameter(5,vy+vyk2/2);
      f->SetParameter(6,vz+vzk2/2);
      g->SetParameter(1,x[i]+xk2/2);
      g->SetParameter(2,y[i]+yk2/2);
      g->SetParameter(3,z[i]+zk2/2);
      g->SetParameter(4,vx+vxk2/2);
      g->SetParameter(5,vy+vyk2/2);
      g->SetParameter(6,vz+vzk2/2);
      h->SetParameter(1,x[i]+xk2/2);
      h->SetParameter(2,y[i]+yk2/2);
      h->SetParameter(3,z[i]+zk2/2);
      h->SetParameter(4,vx+vxk2/2);
      h->SetParameter(5,vy+vyk2/2);
      h->SetParameter(6,vz+vzk2/2);
      X->SetParameter(0,vx+vxk2/2);
      Y->SetParameter(0,vy+vyk2/2);
      Z->SetParameter(0,vz+vzk2/2);

      xk3=ha*X->Eval(0);
      yk3=ha*Y->Eval(0);
      zk3=ha*Z->Eval(0);
      vxk3=ha*f->Eval(0);
      vyk3=ha*g->Eval(0);
      vzk3=ha*h->Eval(0);

      f->SetParameter(1,x[i]+xk3);
      f->SetParameter(2,y[i]+yk3);
      f->SetParameter(3,z[i]+zk3);
      f->SetParameter(4,vx+vxk3);
      f->SetParameter(5,vy+vyk3);
      f->SetParameter(6,vz+vzk3);
      g->SetParameter(1,x[i]+xk3);
      g->SetParameter(2,y[i]+yk3);
      g->SetParameter(3,z[i]+zk3);
      g->SetParameter(4,vx+vxk3);
      g->SetParameter(5,vy+vyk3);
      g->SetParameter(6,vz+vzk3);
      h->SetParameter(1,x[i]+xk3);
      h->SetParameter(2,y[i]+yk3);
      h->SetParameter(3,z[i]+zk3);
      h->SetParameter(4,vx+vxk3);
      h->SetParameter(5,vy+vyk3);
      h->SetParameter(6,vz+vzk3);
      X->SetParameter(0,vx+vxk3);
      Y->SetParameter(0,vy+vyk3);
      Z->SetParameter(0,vz+vzk3);

      xk4=ha*X->Eval(0);
      yk4=ha*Y->Eval(0);
      zk4=ha*Z->Eval(0);
      vxk4=ha*f->Eval(0);
      vyk4=ha*g->Eval(0);
      vzk4=ha*h->Eval(0);

      //  Calcule of next point and speed of the particle
      x[i+1]=x[i]+(xk1+2*xk2+2*xk3+xk4)/6;
      y[i+1]=y[i]+(yk1+2*yk2+2*yk3+yk4)/6;
      z[i+1]=z[i]+(zk1+2*zk2+2*zk3+zk4)/6;
      vx+=(vxk1+vxk2*2+vxk3*2+vxk4)/6;
      vy+=(vyk1+vyk2*2+vyk3*2+vyk4)/6;
      vz+=(vzk1+vzk2*2+vzk3*2+vzk4)/6;
      //  Distance of the particule to the center of the earth
      r=sqrt(x[i+1]*x[i+1]+y[i+1]*y[i+1]+z[i+1]*z[i+1]);
    }
    TPolyLine3D *p=new TPolyLine3D(i,x,y,z);//  Trajectory of the particle
    vp.push_back(p);
  }
  //  Case in which r as to be <25*Re
  else{
    int j=0;
    //  Cicle that calculates trajectory
    for(;j<n && r>Re && r<25*Re;++j){
      f->SetParameter(1,x[j]);
      f->SetParameter(2,y[j]);
      f->SetParameter(3,z[j]);
      f->SetParameter(4,vx);
      f->SetParameter(5,vy);
      f->SetParameter(6,vz);
      g->SetParameter(1,x[j]);
      g->SetParameter(2,y[j]);
      g->SetParameter(3,z[j]);
      g->SetParameter(4,vx);
      g->SetParameter(5,vy);
      g->SetParameter(6,vz);
      h->SetParameter(1,x[j]);
      h->SetParameter(2,y[j]);
      h->SetParameter(3,z[j]);
      h->SetParameter(4,vx);
      h->SetParameter(5,vy);
      h->SetParameter(6,vz);
      X->SetParameter(0,vx);
      Y->SetParameter(0,vy);
      Z->SetParameter(0,vz);

      xk1=ha*X->Eval(0);
      yk1=ha*Y->Eval(0);
      zk1=ha*Z->Eval(0);
      vxk1=ha*f->Eval(0);
      vyk1=ha*g->Eval(0);
      vzk1=ha*h->Eval(0);

      f->SetParameter(1,x[j]+xk1/2);
      f->SetParameter(2,y[j]+yk1/2);
      f->SetParameter(3,z[j]+zk1/2);
      f->SetParameter(4,vx+vxk1/2);
      f->SetParameter(5,vy+vyk1/2);
      f->SetParameter(6,vz+vzk1/2);
      g->SetParameter(1,x[j]+xk1/2);
      g->SetParameter(2,y[j]+yk1/2);
      g->SetParameter(3,z[j]+zk1/2);
      g->SetParameter(4,vx+vxk1/2);
      g->SetParameter(5,vy+vyk1/2);
      g->SetParameter(6,vz+vzk1/2);
      h->SetParameter(1,x[j]+xk1/2);
      h->SetParameter(2,y[j]+yk1/2);
      h->SetParameter(3,z[j]+zk1/2);
      h->SetParameter(4,vx+vxk1/2);
      h->SetParameter(5,vy+vyk1/2);
      h->SetParameter(6,vz+vzk1/2);
      X->SetParameter(0,vx+vxk1/2);
      Y->SetParameter(0,vy+vyk1/2);
      Z->SetParameter(0,vz+vzk1/2);

      xk2=ha*X->Eval(0);
      yk2=ha*Y->Eval(0);
      zk2=ha*Z->Eval(0);
      vxk2=ha*f->Eval(0);
      vyk2=ha*g->Eval(0);
      vzk2=ha*h->Eval(0);

      f->SetParameter(1,x[j]+xk2/2);
      f->SetParameter(2,y[j]+yk2/2);
      f->SetParameter(3,z[j]+zk2/2);
      f->SetParameter(4,vx+vxk2/2);
      f->SetParameter(5,vy+vyk2/2);
      f->SetParameter(6,vz+vzk2/2);
      g->SetParameter(1,x[j]+xk2/2);
      g->SetParameter(2,y[j]+yk2/2);
      g->SetParameter(3,z[j]+zk2/2);
      g->SetParameter(4,vx+vxk2/2);
      g->SetParameter(5,vy+vyk2/2);
      g->SetParameter(6,vz+vzk2/2);
      h->SetParameter(1,x[j]+xk2/2);
      h->SetParameter(2,y[j]+yk2/2);
      h->SetParameter(3,z[j]+zk2/2);
      h->SetParameter(4,vx+vxk2/2);
      h->SetParameter(5,vy+vyk2/2);
      h->SetParameter(6,vz+vzk2/2);
      X->SetParameter(0,vx+vxk2/2);
      Y->SetParameter(0,vy+vyk2/2);
      Z->SetParameter(0,vz+vzk2/2);

      xk3=ha*X->Eval(0);
      yk3=ha*Y->Eval(0);
      zk3=ha*Z->Eval(0);
      vxk3=ha*f->Eval(0);
      vyk3=ha*g->Eval(0);
      vzk3=ha*h->Eval(0);

      f->SetParameter(1,x[j]+xk3);
      f->SetParameter(2,y[j]+yk3);
      f->SetParameter(3,z[j]+zk3);
      f->SetParameter(4,vx+vxk3);
      f->SetParameter(5,vy+vyk3);
      f->SetParameter(6,vz+vzk3);
      g->SetParameter(1,x[j]+xk3);
      g->SetParameter(2,y[j]+yk3);
      g->SetParameter(3,z[j]+zk3);
      g->SetParameter(4,vx+vxk3);
      g->SetParameter(5,vy+vyk3);
      g->SetParameter(6,vz+vzk3);
      h->SetParameter(1,x[j]+xk3);
      h->SetParameter(2,y[j]+yk3);
      h->SetParameter(3,z[j]+zk3);
      h->SetParameter(4,vx+vxk3);
      h->SetParameter(5,vy+vyk3);
      h->SetParameter(6,vz+vzk3);
      X->SetParameter(0,vx+vxk3);
      Y->SetParameter(0,vy+vyk3);
      Z->SetParameter(0,vz+vzk3);

      xk4=ha*X->Eval(0);
      yk4=ha*Y->Eval(0);
      zk4=ha*Z->Eval(0);
      vxk4=ha*f->Eval(0);
      vyk4=ha*g->Eval(0);
      vzk4=ha*h->Eval(0);

      //  Calcule of next point and speed of the particle
      x[j+1]=x[j]+(xk1+2*xk2+2*xk3+xk4)/6;
      y[j+1]=y[j]+(yk1+2*yk2+2*yk3+yk4)/6;
      z[j+1]=z[j]+(zk1+2*zk2+2*zk3+zk4)/6;
      vx+=(vxk1+vxk2*2+vxk3*2+vxk4)/6;
      vy+=(vyk1+vyk2*2+vyk3*2+vyk4)/6;
      vz+=(vzk1+vzk2*2+vzk3*2+vzk4)/6;
      //  Distance of the particule to the center of the earth
      r=sqrt(x[j+1]*x[j+1]+y[j+1]*y[j+1]+z[j+1]*z[j+1]);
    }
    TPolyLine3D *p=new TPolyLine3D(j,x,y,z);
    vp.push_back(p);
  }
}

    /*  Runge-Kutta method of order 2  */ 
void MagField::PartTraj1(double x0, double y0, double z0, double vx, double vy, double vz, double ha, int n, char cc){
  double *x=new double[n];
  double *y=new double[n];
  double *z=new double[n];
  x[0]=x0;y[0]=y0;z[0]=z0;
  double r=5*Re;
  double xn,yn,zn,vxn,vyn,vzn;
  //  Case in which R can be >25*Re
  if (cc!='r'){
    int j;
    for(j=0;j<n && r>Re;++j){
      f->SetParameter(1,x[j]);
      f->SetParameter(2,y[j]);
      f->SetParameter(3,z[j]);
      f->SetParameter(4,vx);
      f->SetParameter(5,vy);
      f->SetParameter(6,vz);
      g->SetParameter(1,x[j]);
      g->SetParameter(2,y[j]);
      g->SetParameter(3,z[j]);
      g->SetParameter(4,vx);
      g->SetParameter(5,vy);
      g->SetParameter(6,vz);
      h->SetParameter(1,x[j]);
      h->SetParameter(2,y[j]);
      h->SetParameter(3,z[j]);
      h->SetParameter(4,vx);
      h->SetParameter(5,vy);
      h->SetParameter(6,vz);
      xn=x[j]+ha/2*vx;
      yn=y[j]+ha/2*vy;
      zn=z[j]+ha/2*vz;
      vxn=vx+ha/2*f->Eval(0);
      vyn=vy+ha/2*g->Eval(0);
      vzn=vz+ha/2*h->Eval(0);
      f->SetParameter(1,xn);
      f->SetParameter(2,yn);
      f->SetParameter(3,zn);
      f->SetParameter(4,vxn);
      f->SetParameter(5,vyn);
      f->SetParameter(6,vzn);
      g->SetParameter(1,xn);
      g->SetParameter(2,yn);
      g->SetParameter(3,zn);
      g->SetParameter(4,vxn);
      g->SetParameter(5,vyn);
      g->SetParameter(6,vzn);
      h->SetParameter(1,xn);
      h->SetParameter(2,yn);
      h->SetParameter(3,zn);
      h->SetParameter(4,vxn);
      h->SetParameter(5,vyn);
      h->SetParameter(6,vzn);

      //  Calcule of next point and speed of the particle
      x[j+1]=x[j]+ha*vxn;
      y[j+1]=y[j]+ha*vyn;
      z[j+1]=z[j]+ha*vzn;
      vx+=f->Eval(0)*ha;
      vy+=ha*g->Eval(0);
      vz+=ha*h->Eval(0);
      //  Distance of the particule to the center of the earth
      r=sqrt(x[j+1]*x[j+1]+y[j+1]*y[j+1]+z[j+1]*z[j+1]);
    }
    TPolyLine3D *p=new TPolyLine3D(j,x,y,z);//  Trajectory of the Particle
    vp.push_back(p);
  }
  //  Case in which r as to be <25*Re
  else{
    int j;
    for(j=0;j<n&&r<25*Re&&r>Re;++j){
      f->SetParameter(1,x[j]);
      f->SetParameter(2,y[j]);
      f->SetParameter(3,z[j]);
      f->SetParameter(4,vx);
      f->SetParameter(5,vy);
      f->SetParameter(6,vz);
      g->SetParameter(1,x[j]);
      g->SetParameter(2,y[j]);
      g->SetParameter(3,z[j]);
      g->SetParameter(4,vx);
      g->SetParameter(5,vy);
      g->SetParameter(6,vz);
      h->SetParameter(1,x[j]);
      h->SetParameter(2,y[j]);
      h->SetParameter(3,z[j]);
      h->SetParameter(4,vx);
      h->SetParameter(5,vy);
      h->SetParameter(6,vz);
      xn=x[j]+ha/2*vx;
      yn=y[j]+ha/2*vy;
      zn=z[j]+ha/2*vz;
      vxn=vx+ha/2*f->Eval(0);
      vyn=vy+ha/2*g->Eval(0);
      vzn=vz+ha/2*h->Eval(0);
      f->SetParameter(1,xn);
      f->SetParameter(2,yn);
      f->SetParameter(3,zn);
      f->SetParameter(4,vxn);
      f->SetParameter(5,vyn);
      f->SetParameter(6,vzn);
      g->SetParameter(1,xn);
      g->SetParameter(2,yn);
      g->SetParameter(3,zn);
      g->SetParameter(4,vxn);
      g->SetParameter(5,vyn);
      g->SetParameter(6,vzn);
      h->SetParameter(1,xn);
      h->SetParameter(2,yn);
      h->SetParameter(3,zn);
      h->SetParameter(4,vxn);
      h->SetParameter(5,vyn);
      h->SetParameter(6,vzn);

      x[j+1]=x[j]+ha*vxn;
      y[j+1]=y[j]+ha*vyn;
      z[j+1]=z[j]+ha*vzn;
      vx+=f->Eval(0)*ha;
      vy+=ha*g->Eval(0);
      vz+=ha*h->Eval(0);
      //  Distance of the particule to the center of the earth
      r=sqrt(x[j+1]*x[j+1]+y[j+1]*y[j+1]+z[j+1]*z[j+1]);
    }
    TPolyLine3D *p=new TPolyLine3D(j,x,y,z);//  Trajectory of the Particle
    vp.push_back(p);
  }
  delete []x;
  delete []y;
  delete []z;
}

    /*  Draws Trajectories contained in the object  */
void MagField::Draw(string s){
  cFCgraphics E;
  double a=Re*3.5;
  if (s=="together")
    a=6.5;
  if (s=="far")
    a=Re*12;
  if (s=="close")
    a=Re*1.5;
  TF3 *h=new TF3("h","x*x+y*y+z*z+1",-a,a,-a,a,-a,a);//  Axis
  TF3 *f1=new TF3("f1","x*x+y*y+z*z-6371000*6371000",-a,a,-a,a,-a,a);//  Earth with distance in meters
  TF3 *f2=new TF3("f2","x*x+y*y+z*z-1",-a,a,-a,a,-a,a);//  Earth with distance in Re
  TF3 *g=new TF3("g","(x-(6371000+500000)/sqrt(2))*(x-(6371000+500000)/sqrt(2))+y*y+pow(z-(6371000+500000)/sqrt(2),2)-800000*800000",-a,a,-a,a,-a,a);//  Detector
  if(s!="together"){
    h->SetTitle("Trajetoria da Particula");
    h->GetXaxis()->SetTitle("x (m)");
    h->GetYaxis()->SetTitle("y (m)");
    h->GetZaxis()->SetTitle("z (m)");
  }
  else{
    h->SetTitle("Linhas de Campo");
    h->GetXaxis()->SetTitle("x (Re)");
    h->GetYaxis()->SetTitle("y (Re)");
    h->GetZaxis()->SetTitle("z (Re)");
  }
  g->SetFillColor(80);
  g->SetLineColor(65);
  f1->SetFillColor(30);
  f1->SetLineColor(15);
  f2->SetFillColor(30);
  f2->SetLineColor(15);
  if (s=="together")
    E.CreatePad("Pad");
  for(unsigned int i=0;i<vp.size();++i){
    if (s!="together")
      E.CreatePad("Pad");
    if (s=="together"){
      E.AddObject(h,"Pad");
      E.AddObject(vp[i],"Pad");
      E.AddObject(f2,"Pad");
    }
    else{
      E.AddObject(h,"Pad");
      if (s!="clean"){
	E.AddObject(f1,"Pad");
	E.AddObject(g,"Pad","same");
      }
      E.AddObject(vp[i],"Pad");
      E.DumpPad("Pad");
      E.DrawPad("Pad");
    }
  }
  if (s=="together"){
    E.DumpPad("Pad");
    E.DrawPad("Pad");
  }
}
