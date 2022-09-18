import numpy as np
import os
import sys
from numpy import linalg as LA
import math
from math import pi
from math import e
import time
import random
from scipy.optimize import minimize
np.set_printoptions(suppress=True)


def Um(t12,t23,t13,delta):
      s12=math.sin(t12)
      s23=math.sin(t23)
      s13=math.sin(t13)
      c12 = math.sqrt(1-s12**2)
      c13 = math.sqrt(1-s13**2)
      c23 = math.sqrt(1-s23**2) 
      return np.matrix([[c12*c13, s12*c13,s13*e**(-1j*delta),0],[-s12*c23-c12*s23*s13*e**(1j*delta), c12*c23-s12*s23*s13*e**(1j*delta),s23*c13,0],[s12*s23-c12*c23*s13*e**(1j*delta),-c12*s23-s12*c23*s13*e**(1j*delta),c23*c13,0],[0,0,0,1]])

def U14(t14,delta14):
    return np.matrix([[math.cos(t14),0,0,math.sin(t14)*e**(-1j*delta14)],[0,1,0,0],[0,0,1,0],[-math.sin(t14)*e**(1j*delta14),0,0,math.cos(t14)]])

def U24(t24,delta24):
    return np.matrix([[1,0,0,0],[0,math.cos(t24),0,math.sin(t24)*e**(-1j*delta24)],[0,0,1,0],[0,-math.sin(t24)*e**(1j*delta24),0,math.cos(t24)]])

def U34(t34):
    return np.matrix([[1,0,0,0],[0,1,0,0],[0,0,math.cos(t34),math.sin(t34)],[0,0,-math.sin(t34),math.cos(t34)]])

def U12(t12):
    return np.matrix([[math.cos(t12),math.sin(t12),0,0],[-math.sin(t12),math.cos(t12),0,0],[0,0,1,0],[0,0,0,1]])


def calc(mu,mc,mt,MT,xf,gz,gk,tk,tz,xr1,xr2,xr3,xr4):
      d= np.matrix([[mu,0],[0,mc]])
      D= np.matrix([[mt,0],[0,MT]])
      #print (D)
      XL=np.matrix([[xr1,xr3],[xr2*e**(-1j*xf),xr4]])
      #print(XL)
      try:
            testXL=np.linalg.inv(XL)
            #print(testXL)
            AL = np.dot(XL.H,XL)
            dxL, UL= LA.eigh(AL)
            dxsqL= np.diag(dxL)
            SdxL =np.matrix([[np.sqrt(1+dxsqL.item((0,0))),np.sqrt(dxsqL.item((0,1)))],[np.sqrt(dxsqL.item((1,0))),np.sqrt(1+dxsqL.item((1,1)))]])
            BL =  np.dot(XL,XL.H)
            dx2L, WL= LA.eigh(BL)
            dxsq2L= np.diag(dx2L)
            Sdx2L= np.sqrt(np.identity(2) +dxsq2L)

      
            siQdag=np.dot(np.dot(np.sqrt(D),XL),np.sqrt(np.linalg.inv(d)))
      
            XR=-np.dot(np.dot(np.sqrt(np.linalg.inv(D)),np.linalg.inv(siQdag).H),np.sqrt(d))
            #XR=-np.dot(np.dot(np.linalg.inv(D),np.linalg.inv(XL.H)),d)
            #print(XR)
            #print(np.dot(np.dot(XL.H,D),XR)+d)

            AR = np.dot(XR.H,XR)
            dxR, UR= LA.eigh(AR)
            dxsqR= np.diag(dxR)
            #if(dxsqR.item((0,0))<0):
                  #print("a")
                  #print(AR)
                  #print(UR)
                  #print(AR-AR.H)
                  #print(dxR)
                  #print(dxsqR)
            SdxR =np.matrix([[np.sqrt(1+dxsqR.item((0,0))),np.sqrt(dxsqR.item((0,1)))],[np.sqrt(dxsqR.item((1,0))),np.sqrt(1+dxsqR.item((1,1)))]])
            BR =  np.dot(XR,XR.H)
            dx2R, WR= LA.eigh(BR)
            dxsq2R= np.diag(dx2R)
            Sdx2R= np.sqrt(np.identity(2) +dxsq2R)

            #print("aaaaa")
      
            VKL=np.dot(O(tk),np.diag([1,e**(1j*gk)]))
            UKL = np.dot(VKL, UL)
            KL=np.dot(np.dot(UKL,np.linalg.inv(SdxL)),UL.H)
 

            VZL=np.dot(O(tz),np.diag([1,e**(1j*gz)]))
            WZL = np.dot(VZL, WL)
            ZL=np.dot(np.dot(WZL,np.linalg.inv(Sdx2L)),WL.H)


            VKR=O(0)
            UKR = np.dot(VKR, UR)
            KR=np.dot(np.dot(UKR,np.linalg.inv(SdxR)),UR.H)
 

            VZR=O(0)
            WZR = np.dot(VZR, WR)
            ZR=np.dot(np.dot(WZR,np.linalg.inv(Sdx2R)),WR.H)
   
            RL=np.dot(KL,XL.H)
            RR=np.dot(KR,XR.H)
            #print R
            SL=-np.dot(ZL,XL)
            SR=-np.dot(ZR,XR)

            VcL=np.matrix([[KL.item((0,0)),KL.item((0,1)),RL.item((0,0)),RL.item((0,1))],[KL.item((1,0)),KL.item((1,1)),RL.item((1,0)),RL.item((1,1))],[SL.item((0,0)),SL.item((0,1)),ZL.item((0,0)),ZL.item((0,1))],[SL.item((1,0)),SL.item((1,1)),ZL.item((1,0)),ZL.item((1,1))]])
            VcR=np.matrix([[KR.item((0,0)),KR.item((0,1)),RR.item((0,0)),RR.item((0,1))],[KR.item((1,0)),KR.item((1,1)),RR.item((1,0)),RR.item((1,1))],[SR.item((0,0)),SR.item((0,1)),ZR.item((0,0)),ZR.item((0,1))],[SR.item((1,0)),SR.item((1,1)),ZR.item((1,0)),ZR.item((1,1))]])

            #AQUI
            omegatil=np.dot(np.dot(np.dot(KL,XL.H),D),np.dot(np.identity(2) +np.dot(XR,XR.H),ZR.H))
            Omegatil=np.dot(np.dot(np.dot(ZL,np.identity(2) +np.dot(XL,XL.H)),D),np.dot(XR,KR.H))
            aux=D+np.dot(np.dot(XL,d),XR.H)
            Omega=np.dot(np.dot(ZL,aux),ZR.H)
            V= np.matrix([[np.conj(KL.item((0,0))),np.conj(KL.item((1,0))),np.conj(SL.item((0,0)))],[np.conj(KL.item((0,1))),np.conj(KL.item((1,1))),np.conj(SL.item((0,1)))],[np.conj(RL.item((0,0))),np.conj(RL.item((1,0))),np.conj(ZL.item((0,0)))],[np.conj(RL.item((0,1))),np.conj(RL.item((1,1))),np.conj(ZL.item((0,1)))]])
            m=np.matrix([[0,0,omegatil.item((0,0))],[0,0,omegatil.item((1,0))],[Omegatil.item((1,0)),Omegatil.item((1,1)),Omega.item((0,0))]])
            mtil=np.matrix([[omegatil.item((0,1))],[omegatil.item((1,1))],[Omega.item((0,1))]])
            Mtil=np.matrix([[Omegatil.item((1,0)),Omegatil.item((1,1)),Omega.item((1,0))]])
            M=Omega.item((1,1))
            Wu=np.dot(V,V.H)
            J=np.matrix([[abs((V.item((0,0))*V.item((1,1))*np.conj(V.item((1,0))*V.item((0,1)))).imag),abs((V.item((0,1))*V.item((1,2))*np.conj(V.item((1,1))*V.item((0,2)))).imag),abs((V.item((0,2))*V.item((1,0))*np.conj(V.item((0,0))*V.item((1,2)))).imag)],[abs((V.item((1,0))*V.item((2,1))*np.conj(V.item((2,0))*V.item((1,1)))).imag),abs((V.item((1,1))*V.item((2,2))*np.conj(V.item((2,1))*V.item((1,2)))).imag),abs((V.item((1,2))*V.item((2,0))*np.conj(V.item((1,0))*V.item((2,2)))).imag)],[abs((V.item((2,0))*V.item((0,1))*np.conj(V.item((0,0))*V.item((2,1)))).imag),abs((V.item((2,1))*V.item((0,2))*np.conj(V.item((0,1))*V.item((2,2)))).imag),abs((V.item((2,2))*V.item((0,0))*np.conj(V.item((2,0))*V.item((0,2)))).imag)]])
            #print("all")
            #print(m)
            #print(mtil)
            #print(V)
            #print(MT)
            #print(xf)
            #print(gz)
            #print(gk)
            #print(tk)
            #print(tz)
            #print(xr1)
            #print(xr2)
            #print(xr3)
            #print(xr4)
            #print(J)
            
      except np.linalg.LinAlgError as err:
            if 'Singular matrix' in str(err):
                  #print("sing")
                  m=0
                  mtil=0
                  Mtil=0
                  M=0
                  V= np.matrix([[-1,-1,-1],[1,-1,-1],[1,-1,-1],[1,-1,-1]])
                  Wu=0
                  VcL=0
                  omegatil=0;
                  Omegatil=0;
                  Omega=0;
                  J=0;
                  XL=0

      return m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL;


def O(ang):
    return np.matrix([[math.cos(ang),math.sin(ang)],[-math.sin(ang),math.cos(ang)]])

def S(x):
      return (4*x-11*x*x+x*x*x)/(4*(1-x)*(1-x))-3/2*(x*x*x*math.log(x))/((1-x)*(1-x)*(1-x))
def S2(x,y):
      return x*y*(math.log(y)/(y-x)*(1/4+3/2*1/(1-y)-3/4*1/((1-y)*(1-y)))+math.log(x)/(x-y)*(1/4+3/2*1/(1-x)-3/4*1/((1-x)*(1-x)))-3/4*1/((1-x)*(1-y)))

#values at mW from 0712.1419
mu = 0.00129;
mc = 0.626;
mt = 173.8;
#VALORES EXPERIMENTAIS FIXOS
GF=1.16*10**(-5);
mW=80.379;
mD=1864.84;
tauD=410.1*10**(-5);
rcZ=0.778;
BD=0.845;
fD=212*10**(-3);
xD=0.39;
mK=497.611*10**(-3);
mZ=91.19;
mB=5.27965;
mBs=5.36688;
BK=0.7625;
fK=155.7*10**(-3);
fBsqBB=225*10**(-3);
fBssqBBs=274*10**(-3);
kep=0.94;
deltamKexp=3.484*10**(-15);
deltamBexp=3.334*10**(-13);
deltamBsexp=1.1683*10**(-11);
epKexp=2.228*10**(-3);
etaTT=1;
etacT=1;
etatT=1;
xu=(mu/mW)**2;
xc=(mc/mW)**2;
xt=(mt/mW)**2;

i=0
file = open("a2.txt","r")
file2 = open("b2.txt","a")
for lines in file:
      flag=0
      i+=1;
      linelist=lines.split()
      MT=float(linelist[0])*mt
      xT=(mW/MT)**2
      xf=float(linelist[1])
      if(xf>1.5):
            flag=1
      gz=float(linelist[2])
      gk=float(linelist[3])
      tk=float(linelist[4])
      tz=float(linelist[5])
      xr1=float(linelist[6])
      xr2=float(linelist[7])
      xr3=float(linelist[8])
      xr4=float(linelist[9])
      m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL =calc(mu,mc,mt,MT,xf,gz,gk,tk,tz,xr1,xr2,xr3,xr4)
      
      VcLd2=VcL.H;
      VcLd=np.dot(np.dot(np.diag([1,e**(-1j*(np.angle(VcLd2.item((1,3)))-np.angle(VcLd2.item((0,3))))),e**(-1j*(np.angle(VcLd2.item((2,3)))-np.angle(VcLd2.item((0,3))))),e**(-1j*(np.angle(VcLd2.item((3,3)))-np.angle(VcLd2.item((0,3)))))]),VcLd2),np.diag([e**(-1j*(np.angle(VcLd2.item((0,0))))),e**(-1j*(np.angle(VcLd2.item((0,1))))),e**(-1j*(np.angle(VcLd2.item((0,2))))),e**(-1j*(np.angle(VcLd2.item((0,3)))))]))
      #print(VcLd)
      s14=abs(VcLd.item((0,3)));c14=np.sqrt(1-s14*s14);t14=np.arcsin(s14);
      s24=abs(VcLd.item((1,3)))/c14;c24=np.sqrt(1-s24*s24);t24=np.arcsin(s24);
      s34=abs(VcLd.item((2,3)))/(c14*c24);c34=np.sqrt(1-s34*s34);t34=np.arcsin(s34);
      s13=abs(VcLd.item((0,2)))/c14;c13=np.sqrt(1-s13*s13);t13=np.arcsin(s13);
      s12=abs(VcLd.item((0,1)))/(c14*c13);c12=np.sqrt(1-s12*s12);t12=np.arcsin(s12);
      s23=abs(VcLd.item((1,2))+s13*s14*s24)/(c13*c24);c23=np.sqrt(1-s23*s23);t23=np.arcsin(s23);
      VL3=np.dot(np.dot(U34(t34).T,VcLd),U12(t12).T)
      d14=-np.angle(-VL3.item((2,1))/s23)
      if (d14<0):
            d14=d14+2*pi;
      if(d14>2*pi):
            d14=d14%(2*pi)
      d13=np.angle(VL3.item((2,2))/(c13*c23))+d14
      if (d13<0):
            d13=d13+2*pi;
      if(d13>2*pi):
            d13=d13%(2*pi)
      d24=np.angle((VL3.item((1,2))+s13*s14*s24)/(c13*c24*s23))-d13+d14
      if (d24<0):
            d24=d24+2*pi;
      if(d24>2*pi):
            d24=d24%(2*pi)
      VL4d=np.dot(np.dot(np.dot(U34(t34),U24(t24,d24)),U14(t14,d14)),Um(t12,t23,t13,d13))
      VL4=VL4d.H

      #print(abs(VL4))
      #print(abs(VcL))

      Btu=(abs(np.conj(VcL.item((3,0)))*VcL.item((3,2)))**2)/(2*abs(V.item((2,2))))*(1-mZ**2/mt**2)**2*(1+2*mZ**2/mt**2)*(1-3*mW**4/mt**4+2*mW**6/mt**6)**(-1)*10**(8);
      Btc=(abs(np.conj(VcL.item((3,1)))*VcL.item((3,2)))**2)/(2*abs(V.item((2,2))))*(1-mZ**2/mt**2)**2*(1+2*mZ**2/mt**2)*(1-3*mW**4/mt**4+2*mW**6/mt**6)**(-1)*10**(8);

      #print(Btu)
      #print(Btc)


      file2.write("%f" %(MT/mt) + " ")
      file2.write("%f" %t12 + " ")
      file2.write("%f" %t13 + " ")
      file2.write("%f" %t23 + " ")
      file2.write("%f" %t14 + " ")
      file2.write("%f" %t24 + " ")
      file2.write("%f" %t34 + " ")
      file2.write("%f" %d13 + " ")
      file2.write("%f" %d14 + " ")
      file2.write("%f" %d24 + " ")
      file2.write("%f" %flag + " ")
      file2.write("%f" %Btu + " ")
      file2.write("%f" %Btc + "\n")
      

                                          
                        
                  

                  
file.close()
file2.close()
