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

def L(plist):

      ###calc para L, calc2 para L2
      m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta =calc(plist)
      
      f0=abs(V.item((0,0)))
      f0cent=V11
      sigf0=errV11

      f1=abs(V.item((0,1)))
      f1cent=V12
      sigf1=errV12

      f2=abs(V.item((0,2)))
      f2cent=V13
      sigf2=errV13

      f3=abs(V.item((1,0)))
      f3cent=V21
      sigf3=errV21

      f4=abs(V.item((1,1)))
      f4cent=V22
      sigf4=errV22

      #print(((f4-f4cent)/sigf4)**2)

      f5=abs(V.item((1,2)))
      f5cent=V23
      sigf5=errV23

      f6=abs(V.item((2,0)))
      f6cent=V31
      sigf6=errV31

      f7=abs(V.item((2,1)))
      f7cent=V32
      sigf7=errV32

      f8=abs(V.item((2,2)))
      f8cent=V33
      sigf8=errV33
      

      f9=gamma
      f9cent=gammaexp
      sigf9=errgammaexp

      f10=deltamK;
      f10cent=deltamKexp;
      sigf10=errdeltamKexp;
      
      f11=deltamB;
      f11cent=deltamBexp;
      sigf11=errdeltamBexp;
      
      f12=deltamBs
      f12cent=deltamBsexp;
      sigf12=errdeltamBsexp;
      
      f13=epK;
      f13cent=epKexp;
      sigf13=errepKexp;

      #valor do desvio de unit da ckm
      f14=abs(VcL.item((3,0)))
      f14cent=dev_unit
      sigf14=0.001

      f15=abs(VcL.item((3,1))*np.conj(VcL.item((3,0))))*10**(4)
      f15cent=1.22*10**(-4)*10**(4)
      sigf15=0.01

      summ_exp_1=((f0-f0cent)/sigf0)**2+((f1-f1cent)/sigf1)**2+((f2-f2cent)/sigf2)**2+((f3-f3cent)/sigf3)**2+((f4-f4cent)/sigf4)**2+((f5-f5cent)/sigf5)**2+((f6-f6cent)/sigf6)**2+((f7-f7cent)/sigf7)**2+((f8-f8cent)/sigf8)**2+((f9-f9cent)/sigf9)**2
      summ_exp_2=((f10-f10cent)/sigf10)*max(0,((f10-f10cent)/sigf10))+((f11-f11cent)/sigf11)*max(0,((f11-f11cent)/sigf11))+((f12-f12cent)/sigf12)*max(0,((f12-f12cent)/sigf12))+((f13-f13cent)/sigf13)*max(0,((f13-f13cent)/sigf13))+((f15-f15cent)/sigf15)*max(0,((f15-f15cent)/sigf15))
      summ_bound=((f14-f14cent)/sigf14)**2

      #max(0,f14-f14cent)*100 truque forçar coisas a um valor

      
      return (summ_exp_1+summ_exp_2+summ_bound)
      #return (summ_exp_1)+

def L2(plist):

      ###calc para L, calc2 para L2
      m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta =calc2(plist)
      
      f0=abs(V.item((0,0)))
      f0cent=V11
      sigf0=errV11

      f1=abs(V.item((0,1)))
      f1cent=V12
      sigf1=errV12

      f2=abs(V.item((0,2)))
      f2cent=V13
      sigf2=errV13

      f3=abs(V.item((1,0)))
      f3cent=V21
      sigf3=errV21

      f4=abs(V.item((1,1)))
      f4cent=V22
      sigf4=errV22

      #print(((f4-f4cent)/sigf4)**2)

      f5=abs(V.item((1,2)))
      f5cent=V23
      sigf5=errV23

      f6=abs(V.item((2,0)))
      f6cent=V31
      sigf6=errV31

      f7=abs(V.item((2,1)))
      f7cent=V32
      sigf7=errV32

      f8=abs(V.item((2,2)))
      f8cent=V33
      sigf8=errV33
      

      f9=gamma
      f9cent=gammaexp
      sigf9=errgammaexp

      f10=deltamK;
      f10cent=deltamKexp;
      sigf10=errdeltamKexp;
      
      f11=deltamB;
      f11cent=deltamBexp;
      sigf11=errdeltamBexp;
      
      f12=deltamBs
      f12cent=deltamBsexp;
      sigf12=errdeltamBsexp;
      
      f13=epK;
      f13cent=epKexp;
      sigf13=errepKexp;

      #valor do desvio de unit da ckm
      f14=abs(VcL.item((3,0)))
      f14cent=dev_unit
      sigf14=0.001

      f15=abs(VcL.item((3,1))*np.conj(VcL.item((3,0))))*10**(4)
      f15cent=1.22*10**(-4)*10**(4)
      sigf15=0.01

      summ_exp_1=((f0-f0cent)/sigf0)**2+((f1-f1cent)/sigf1)**2+((f2-f2cent)/sigf2)**2+((f3-f3cent)/sigf3)**2+((f4-f4cent)/sigf4)**2+((f5-f5cent)/sigf5)**2+((f6-f6cent)/sigf6)**2+((f7-f7cent)/sigf7)**2+((f8-f8cent)/sigf8)**2+((f9-f9cent)/sigf9)**2
      summ_exp_2=((f10-f10cent)/sigf10)*max(0,((f10-f10cent)/sigf10))+((f11-f11cent)/sigf11)*max(0,((f11-f11cent)/sigf11))+((f12-f12cent)/sigf12)*max(0,((f12-f12cent)/sigf12))+((f13-f13cent)/sigf13)*max(0,((f13-f13cent)/sigf13))+((f15-f15cent)/sigf15)*max(0,((f15-f15cent)/sigf15))
      summ_bound=((f14-f14cent)/sigf14)**2

      #max(0,f14-f14cent)*100 truque forçar coisas a um valor

      
      return (summ_exp_1+summ_exp_2+summ_bound)
      #return (summ_exp_1)+


def LV(plist):

      ###calc para L, calc2 para L2
      m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta =calc(plist)
      
      f0=abs(V.item((0,0)))
      f0cent=V11
      sigf0=errV11

      f1=abs(V.item((0,1)))
      f1cent=V12
      sigf1=errV12

      f2=abs(V.item((0,2)))
      f2cent=V13
      sigf2=errV13

      f3=abs(V.item((1,0)))
      f3cent=V21
      sigf3=errV21

      f4=abs(V.item((1,1)))
      f4cent=V22
      sigf4=errV22

      f5=abs(V.item((1,2)))
      f5cent=V23
      sigf5=errV23

      f6=abs(V.item((2,0)))
      f6cent=V31
      sigf6=errV31

      f7=abs(V.item((2,1)))
      f7cent=V32
      sigf7=errV32

      f8=abs(V.item((2,2)))
      f8cent=V33
      sigf8=errV33

      f9=gamma
      f9cent=gammaexp
      sigf9=errgammaexp

      f10=deltamK;
      f10cent=deltamKexp;
      sigf10=errdeltamKexp;
      
      f11=deltamB;
      f11cent=deltamBexp;
      sigf11=errdeltamBexp;
      
      f12=deltamBs
      f12cent=deltamBsexp;
      sigf12=errdeltamBsexp;
      
      f13=epK;
      f13cent=epKexp;
      sigf13=errepKexp;

      #valor do desvio de unit da ckm
      f14=abs(VcL.item((3,0)))
      f14cent=dev_unit
      sigf14=0.001

      f15=abs(VcL.item((3,1))*np.conj(VcL.item((3,0))))*10**(4)
      f15cent=1.22*10**(-4)*10**(4)
      sigf15=0.01

      summ_exp_1=((f0-f0cent)/sigf0)**2+((f1-f1cent)/sigf1)**2+((f2-f2cent)/sigf2)**2+((f3-f3cent)/sigf3)**2+((f4-f4cent)/sigf4)**2+((f5-f5cent)/sigf5)**2+((f6-f6cent)/sigf6)**2+((f7-f7cent)/sigf7)**2+((f8-f8cent)/sigf8)**2+((f9-f9cent)/sigf9)**2
      summ_exp_2=((f10-f10cent)/sigf10)**2+((f11-f11cent)/sigf11)**2+((f12-f12cent)/sigf12)**2+((f13-f13cent)/sigf13)**2
      summ_bound=((f14-f14cent)/sigf14)**2+((f15-f15cent)/sigf15)**2
      
      return (summ_exp_1)

def L2V(plist):

      ###calc para L, calc2 para L2
      m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta =calc2(plist)
      
      f0=abs(V.item((0,0)))
      f0cent=V11
      sigf0=errV11

      f1=abs(V.item((0,1)))
      f1cent=V12
      sigf1=errV12

      f2=abs(V.item((0,2)))
      f2cent=V13
      sigf2=errV13

      f3=abs(V.item((1,0)))
      f3cent=V21
      sigf3=errV21

      f4=abs(V.item((1,1)))
      f4cent=V22
      sigf4=errV22

      #print(((f4-f4cent)/sigf4)**2)

      f5=abs(V.item((1,2)))
      f5cent=V23
      sigf5=errV23

      f6=abs(V.item((2,0)))
      f6cent=V31
      sigf6=errV31

      f7=abs(V.item((2,1)))
      f7cent=V32
      sigf7=errV32

      f8=abs(V.item((2,2)))
      f8cent=V33
      sigf8=errV33
      

      f9=gamma
      f9cent=gammaexp
      sigf9=errgammaexp

      f10=deltamK;
      f10cent=deltamKexp;
      sigf10=errdeltamKexp;
      
      f11=deltamB;
      f11cent=deltamBexp;
      sigf11=errdeltamBexp;
      
      f12=deltamBs
      f12cent=deltamBsexp;
      sigf12=errdeltamBsexp;
      
      f13=epK;
      f13cent=epKexp;
      sigf13=errepKexp;

      #valor do desvio de unit da ckm
      f14=abs(VcL.item((3,0)))
      f14cent=dev_unit
      sigf14=0.001

      f15=abs(VcL.item((3,1))*np.conj(VcL.item((3,0))))*10**(4)
      f15cent=1.22*10**(-4)*10**(4)
      sigf15=0.01

      summ_exp_1=((f0-f0cent)/sigf0)**2+((f1-f1cent)/sigf1)**2+((f2-f2cent)/sigf2)**2+((f3-f3cent)/sigf3)**2+((f4-f4cent)/sigf4)**2+((f5-f5cent)/sigf5)**2+((f6-f6cent)/sigf6)**2+((f7-f7cent)/sigf7)**2+((f8-f8cent)/sigf8)**2+((f9-f9cent)/sigf9)**2
      summ_exp_2=((f10-f10cent)/sigf10)**2+((f11-f11cent)/sigf11)**2+((f12-f12cent)/sigf12)**2+((f13-f13cent)/sigf13)**2
      summ_bound=((f14-f14cent)/sigf14*10)**2+((f15-f15cent)/sigf15)**2

      #max(0,f14-f14cent)*100 truque forçar coisas a um valor

      return (summ_exp_1)

def S(x):
      return (4*x-11*x*x+x*x*x)/(4*(1-x)*(1-x))-3/2*(x*x*x*math.log(x))/((1-x)*(1-x)*(1-x))
def S2(x,y):
      return x*y*(math.log(y)/(y-x)*(1/4+3/2*1/(1-y)-3/4*1/((1-y)*(1-y)))+math.log(x)/(x-y)*(1/4+3/2*1/(1-x)-3/4*1/((1-x)*(1-x)))-3/4*1/((1-x)*(1-y)))


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

def calc2(plist2):
      MT=plist2[0]
      xT=(MT/mW)**2
      t12=plist2[1]
      t13=plist2[2]
      t23=plist2[3]
      t14=plist2[4]
      t24=plist2[5]
      t34=plist2[6]
      delta=plist2[7]
      delta14=plist2[8]
      delta24=plist2[9]

      VcLH=np.dot(np.dot(np.dot(U34(t34),U24(t24,delta24)),U14(t14,delta14)),Um(t12,t23,t13,delta))
      VcL=VcLH.H
      #print("aa")
      #print(abs(helpp))
      V=VcLH[0:4,0:3]
      #print("bb")
      #print(abs(V))


      d= np.matrix([[mu,0],[0,mc]])
      D= np.matrix([[mt,0],[0,MT]])
      #print(VcL)
      KL=np.matrix([[VcL.item((0,0)),VcL.item((0,1))],[VcL.item((1,0)),VcL.item((1,1))]])
      RL=np.matrix([[VcL.item((0,2)),VcL.item((0,3))],[VcL.item((1,2)),VcL.item((1,3))]])
      ZL=np.matrix([[VcL.item((2,2)),VcL.item((2,3))],[VcL.item((3,2)),VcL.item((3,3))]])
   
      XL=np.dot(RL.H,np.linalg.inv(KL.H))
      SL=-np.dot(ZL,XL)
      #print(XL)
      XR=-np.dot(np.dot(np.linalg.inv(D),np.linalg.inv(XL.H)),d)

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

      

      VKR=O(0)
      UKR = np.dot(VKR, UR)
      KR=np.dot(np.dot(UKR,np.linalg.inv(SdxR)),UR.H)
 

      VZR=O(0)
      WZR = np.dot(VZR, WR)
      ZR=np.dot(np.dot(WZR,np.linalg.inv(Sdx2R)),WR.H)
   
      RL=np.dot(KL,XL.H)
      RR=np.dot(KR,XR.H)
      #print R

      SR=-np.dot(ZR,XR)

      #VcL=np.matrix([[KL.item((0,0)),KL.item((0,1)),RL.item((0,0)),RL.item((0,1))],[KL.item((1,0)),KL.item((1,1)),RL.item((1,0)),RL.item((1,1))],[SL.item((0,0)),SL.item((0,1)),ZL.item((0,0)),ZL.item((0,1))],[SL.item((1,0)),SL.item((1,1)),ZL.item((1,0)),ZL.item((1,1))]])
      VcR=np.matrix([[KR.item((0,0)),KR.item((0,1)),RR.item((0,0)),RR.item((0,1))],[KR.item((1,0)),KR.item((1,1)),RR.item((1,0)),RR.item((1,1))],[SR.item((0,0)),SR.item((0,1)),ZR.item((0,0)),ZR.item((0,1))],[SR.item((1,0)),SR.item((1,1)),ZR.item((1,0)),ZR.item((1,1))]])

      #AQUI
      omegatil=np.dot(np.dot(np.dot(KL,XL.H),D),np.dot(np.identity(2) +np.dot(XR,XR.H),ZR.H))
      Omegatil=np.dot(np.dot(np.dot(ZL,np.identity(2) +np.dot(XL,XL.H)),D),np.dot(XR,KR.H))
      aux=D+np.dot(np.dot(XL,d),XR.H)
      Omega=np.dot(np.dot(ZL,aux),ZR.H)
      #V= np.matrix([[np.conj(KL.item((0,0))),np.conj(KL.item((1,0))),np.conj(SL.item((0,0)))],[np.conj(KL.item((0,1))),np.conj(KL.item((1,1))),np.conj(SL.item((0,1)))],[np.conj(RL.item((0,0))),np.conj(RL.item((1,0))),np.conj(ZL.item((0,0)))],[np.conj(RL.item((0,1))),np.conj(RL.item((1,1))),np.conj(ZL.item((0,1)))]])
      m=np.matrix([[0,0,omegatil.item((0,0))],[0,0,omegatil.item((1,0))],[Omegatil.item((0,0)),Omegatil.item((0,1)),Omega.item((0,0))]])
      mtil=np.matrix([[omegatil.item((0,1))],[omegatil.item((1,1))],[Omega.item((0,1))]])
      Mtil=np.matrix([[Omegatil.item((1,0)),Omegatil.item((1,1)),Omega.item((1,0))]])
      M=Omega.item((1,1))
      Wu=np.dot(V,V.H)
      eta2=0.5*abs(abs(Wu)-np.identity(4))
      eta=np.matrix([[eta2.item((0,0)),eta2.item((0,1)),eta2.item((0,2))],[eta2.item((1,0)),eta2.item((1,1)),eta2.item((1,2))],[eta2.item((2,0)),eta2.item((2,1)),eta2.item((2,2))]])
      J=np.matrix([[abs((V.item((0,0))*V.item((1,1))*np.conj(V.item((1,0))*V.item((0,1)))).imag),abs((V.item((0,1))*V.item((1,2))*np.conj(V.item((1,1))*V.item((0,2)))).imag),abs((V.item((0,2))*V.item((1,0))*np.conj(V.item((0,0))*V.item((1,2)))).imag)],[abs((V.item((1,0))*V.item((2,1))*np.conj(V.item((2,0))*V.item((1,1)))).imag),abs((V.item((1,1))*V.item((2,2))*np.conj(V.item((2,1))*V.item((1,2)))).imag),abs((V.item((1,2))*V.item((2,0))*np.conj(V.item((1,0))*V.item((2,2)))).imag)],[abs((V.item((2,0))*V.item((0,1))*np.conj(V.item((0,0))*V.item((2,1)))).imag),abs((V.item((2,1))*V.item((0,2))*np.conj(V.item((0,1))*V.item((2,2)))).imag),abs((V.item((2,2))*V.item((0,0))*np.conj(V.item((2,0))*V.item((0,2)))).imag)]])

      deltamK=(GF*GF*mW*mW*mK*BK*fK*fK)/(6*pi*pi)*abs(np.conj(V.item((3,0)))*V.item((3,1))*np.conj(V.item((3,0)))*V.item((3,1))*S(xT)*etaTT+2*np.conj(V.item((3,0)))*V.item((3,1))*np.conj(V.item((1,0)))*V.item((1,1))*S2(xc,xT)*etacT+2*np.conj(V.item((3,0)))*V.item((3,1))*np.conj(V.item((2,0)))*V.item((2,1))*S2(xt,xT)*etatT);
      deltamB=(GF*GF*mW*mW*mB*fBsqBB*fBsqBB)/(6*pi*pi)*abs(np.conj(V.item((3,0)))*V.item((3,2))*np.conj(V.item((3,0)))*V.item((3,2))*S(xT)*etaTT+2*np.conj(V.item((3,0)))*V.item((3,2))*np.conj(V.item((1,0)))*V.item((1,2))*S2(xc,xT)*etacT+2*np.conj(V.item((3,0)))*V.item((3,2))*np.conj(V.item((2,0)))*V.item((2,2))*S2(xt,xT)*etatT);
      deltamBs=(GF*GF*mW*mW*mBs*fBssqBBs*fBssqBBs)/(6*pi*pi)*abs(np.conj(V.item((3,1)))*V.item((3,2))*np.conj(V.item((3,1)))*V.item((3,2))*S(xT)*etaTT+2*np.conj(V.item((3,1)))*V.item((3,2))*np.conj(V.item((1,1)))*V.item((1,2))*S2(xc,xT)*etacT+2*np.conj(V.item((3,1)))*V.item((3,2))*np.conj(V.item((2,1)))*V.item((2,2))*S2(xt,xT)*etatT);
      qq=np.conj(V.item((3,0)))*V.item((3,1))*np.conj(V.item((3,0)))*V.item((3,1))*S(xT)*etaTT+2*np.conj(V.item((3,0)))*V.item((3,1))*np.conj(V.item((1,0)))*V.item((1,1))*S2(xc,xT)*etacT+2*np.conj(V.item((3,0)))*V.item((3,1))*np.conj(V.item((2,0)))*V.item((2,1))*S2(xt,xT)*etatT
      epK=(kep*GF*GF*mW*mW*mK*BK*fK*fK)/(12*pi*pi*math.sqrt(2)*deltamKexp)*abs(qq.imag);
      gamma=np.angle(-(V.item((0,0))*np.conj(V.item((0,2))))/(V.item((1,0))*np.conj(V.item((1,2)))))
      gamma=gamma%(2*pi)
      return  m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta;



      
      

def calc(plist):
      MT=plist[0];
      xf=plist[1];
      gz=plist[2];
      gk=plist[3];
      tk=plist[4];
      tz=plist[5];
      xr1=plist[6];
      xr2=plist[7];
      xr3=plist[8];
      xr4=plist[9];

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
            eta2=0.5*abs(abs(Wu)-np.identity(4))
            eta=np.matrix([[eta2.item((0,0)),eta2.item((0,1)),eta2.item((0,2))],[eta2.item((1,0)),eta2.item((1,1)),eta2.item((1,2))],[eta2.item((2,0)),eta2.item((2,1)),eta2.item((2,2))]])
            
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
            deltamK=(GF*GF*mW*mW*mK*BK*fK*fK)/(6*pi*pi)*abs(np.conj(V.item((3,0)))*V.item((3,1))*np.conj(V.item((3,0)))*V.item((3,1))*S(xT)*etaTT+2*np.conj(V.item((3,0)))*V.item((3,1))*np.conj(V.item((1,0)))*V.item((1,1))*S2(xc,xT)*etacT+2*np.conj(V.item((3,0)))*V.item((3,1))*np.conj(V.item((2,0)))*V.item((2,1))*S2(xt,xT)*etatT);
            deltamB=(GF*GF*mW*mW*mB*fBsqBB*fBsqBB)/(6*pi*pi)*abs(np.conj(V.item((3,0)))*V.item((3,2))*np.conj(V.item((3,0)))*V.item((3,2))*S(xT)*etaTT+2*np.conj(V.item((3,0)))*V.item((3,2))*np.conj(V.item((1,0)))*V.item((1,2))*S2(xc,xT)*etacT+2*np.conj(V.item((3,0)))*V.item((3,2))*np.conj(V.item((2,0)))*V.item((2,2))*S2(xt,xT)*etatT);
            deltamBs=(GF*GF*mW*mW*mBs*fBssqBBs*fBssqBBs)/(6*pi*pi)*abs(np.conj(V.item((3,1)))*V.item((3,2))*np.conj(V.item((3,1)))*V.item((3,2))*S(xT)*etaTT+2*np.conj(V.item((3,1)))*V.item((3,2))*np.conj(V.item((1,1)))*V.item((1,2))*S2(xc,xT)*etacT+2*np.conj(V.item((3,1)))*V.item((3,2))*np.conj(V.item((2,1)))*V.item((2,2))*S2(xt,xT)*etatT);
            qq=np.conj(V.item((3,0)))*V.item((3,1))*np.conj(V.item((3,0)))*V.item((3,1))*S(xT)*etaTT+2*np.conj(V.item((3,0)))*V.item((3,1))*np.conj(V.item((1,0)))*V.item((1,1))*S2(xc,xT)*etacT+2*np.conj(V.item((3,0)))*V.item((3,1))*np.conj(V.item((2,0)))*V.item((2,1))*S2(xt,xT)*etatT
            epK=(kep*GF*GF*mW*mW*mK*BK*fK*fK)/(12*pi*pi*math.sqrt(2)*deltamKexp)*abs(qq.imag);
            gamma=np.angle(-(V.item((0,0))*np.conj(V.item((0,2))))/(V.item((1,0))*np.conj(V.item((1,2)))))
            gamma=gamma%(2*pi)
            '''
            print("deltamK")
            print(deltamK)
            print(deltamKexp)
            print("deltamB")
            print(deltamB)
            print(deltamBexp)
            print("deltamBs")
            print(deltamBs)
            print(deltamBsexp)
            print("epK")
            print(epK)
            print(epKexp)
            print(abs(VcL.item((3,1))*np.conj(VcL.item((3,0)))))
            print(float(1.22*10**(-4)))
            '''
            
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
                  KL=0
                  ZL=0
                  RL=0
                  AL=0
                  BL=0
      

      return m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta;


def O(ang):
    return np.matrix([[math.cos(ang),math.sin(ang)],[-math.sin(ang),math.cos(ang)]])


##param x
#file = open("a2.txt","a")
#param angles
file = open("b2.txt","a")



#values at mz from 0712.1419
mu = 0.00127;
ermu=0.5*10**(-3);
ermc=0.084
ermt=3
mc = 0.619;
mt = 171.7;
#source: PDG March 2020, https://pdg.lbl.gov/2020/reviews/rpp2020-rev-ckm-matrix.pdf do pdg
V11=0.97370
errV11=0.00014
V12=0.2245
errV12=0.0008
V13=3.82*10**(-3)
errV13=0.24*10**(-3)

V21=0.221
errV21=0.004
V22=0.987
errV22=0.011
V23=41.0*10**(-3)
errV23=1.4*10**(-3)

V31=8.0*10**(-3)
errV31=0.3*10**(-3)
V32=38.8*10**(-3)
errV32=1.1*10**(-3)
V33=1.013
errV33=0.030

#valor do desvio de unit da ckm
dev_unit=0.04

gammaexp=math.radians(72.1)
errgammaexp=math.radians(4.5)

#VALORES EXPERIMENTAIS FIXOS (all in GeV)
GF=1.166*10**(-5);
mW=80.379;
mZ=91.1876;

mD=1864.83*10**(-3);
errmD=0.05*10**(-3);
tauD=410.1*10**(-15);
secondtogevtotheminusone=1.517*10**(24)
errtauD=1.5*10**(-15);

rcZ=0.778;
BD=1.18;

fD=212*10**(-3);
errfD=0.7*10**(-3);
xD=0.39;
errxD=0.12;

mK=497.611*10**(-3);
errmK=0.013*10**(-3)

mB=5.27965;
errmB=0.12*10**(-3)
mBs=5.36688;
errmBs=0.14*10**(-3)

BK=0.717;
errBK=0.024;

BB=1.30
errBB=0.10;

BBs=1.35
errBBs=0.06;

fK=155.7*10**(-3);
errfK=0.3*10**(-3);

fB=190.0*10**(-3);
errfB=1.3*10**(-3);

fBs=230.3*10**(-3);
errfBs=1.3*10**(-3);

fBsqBB=fB*math.sqrt(BB);
fBssqBBs=fBs*math.sqrt(BBs);

kep=0.92;
errkep=0.02;

deltamKexp=3.484*10**(-15);
errdeltamKexp=0.006*10**(-15);

deltamBexp=3.334*10**(-13);
errdeltamBexp=0.013*10**(-13);

deltamBsexp=1.1683*10**(-11);
errdeltamBsexp=0.0013*10**(-11);

epKexp=2.228*10**(-3);
errepKexp=0.011*10**(-3);

etaTT=1;
etacT=1;
etatT=1;
xu=(mu/mW)**2;
xc=(mc/mW)**2;
xt=(mt/mW)**2;


MTmin=1;
MTmax=100;
xmin=-5
xmax=-1
tcabmin=0.22;
tcabmax=0.23;
zmax=-2;
zmin=-5;
xrdiv=10000;
it=1*10**(10);
j=0

ito=10**(4)
lr=10**(-8)
prec=0.000001
it_min=10;



i=0
##param X
#file = open("a2.txt","r")
##param angles
file = open("b2.txt","r")

for linesl in file:
      '''
      #param X
      plist=[]
      MT=lines[0]*mt
      xT=(MT/mW)**2
      xf=float(lines[1])
      gz=float(lines[2])
      gk=float(lines[3])
      tk=float(lines[4])
      tz=float(lines[5])
      xr1=float(lines[6])
      xr2=float(lines[7])
      xr3=float(lines[8])
      xr4=float(lines[9])
      plist.append(MT)
      plist.append(xf)
      plist.append(gz)
      plist.append(gk)
      plist.append(tk)
      plist.append(tz)
      plist.append(xr1)
      plist.append(xr2)
      plist.append(xr3)
      plist.append(xr4)
      m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta= calc(plist)
      '''

      
      #param angles
      plist=[]
      lines=linesl.split()
      MT=float(lines[0])*mt
      xT=(MT/mW)**2
      t12=float(lines[1])
      t13=float(lines[2])
      t23=float(lines[3])
      t14=float(lines[4])
      t24=float(lines[5])
      t34=float(lines[6])
      delta=float(lines[7])
      delta14=float(lines[8])
      delta24=float(lines[9])

      plist.append(MT)
      plist.append(t12)
      plist.append(t13)
      plist.append(t23)
      plist.append(t14)
      plist.append(t24)
      plist.append(t34)
      plist.append(delta)
      plist.append(delta14)
      plist.append(delta24)
      
      m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta= calc2(plist)

  

      if(L2V(plist)<10000):
            Btu=(abs(np.conj(VcL.item((3,0)))*VcL.item((3,2)))**2)/(2*abs(V.item((2,2))))*(1-mZ**2/mt**2)**2*(1+2*mZ**2/mt**2)*(1-3*mW**4/mt**4+2*mW**6/mt**6)**(-1)*10**(8);
            Btc=(abs(np.conj(VcL.item((3,1)))*VcL.item((3,2)))**2)/(2*abs(V.item((2,2))))*(1-mZ**2/mt**2)**2*(1+2*mZ**2/mt**2)*(1-3*mW**4/mt**4+2*mW**6/mt**6)**(-1)*10**(8);
            alpha=np.angle(-(V.item((2,0))*np.conj(V.item((2,2))))/(V.item((0,0))*np.conj(V.item((0,2)))))
            beta=np.angle(-(V.item((1,0))*np.conj(V.item((1,2))))/(V.item((2,0))*np.conj(V.item((2,2)))))
            alpha=alpha%(2*pi)
            beta=beta%(2*pi)

            xD=(math.sqrt(2)*tauD*mD)/(3)*GF*fD*fD*BD*rcZ*abs(np.conj(VcL.item((3,0)))*VcL.item((3,1)))*abs(np.conj(VcL.item((3,0)))*VcL.item((3,1)))*secondtogevtotheminusone*100

            Delta1=1-abs(Wu.item((0,0)))
            Delta2=1-abs(Wu.item((1,1)))
            Delta3=1-abs(Wu.item((2,2)))

            p=MT/mt*(Delta1+Delta2+Delta3)+1


            print("CASO")
            print(i)
            print("MT")
            print(MT)
            print("t12")
            print(t12)
            print("t13")
            print(t13)
            print("t23")
            print(t23)
            print("t14")
            print(t14)
            print("t24")
            print(t24)
            print("t34")
            print(t34)
            print("delta")
            print(delta)
            print("delta14")
            print(delta14)
            print("delta24")
            print(delta24)
            print("LOSS")
            print(L2V(plist))
            print("p-1")
            print(p-1)
            print("Delta1")
            print(math.sqrt(Delta1))
            print("Delta2")
            print(math.sqrt(Delta2))
            print("Delta3")
            print(math.sqrt(Delta3))

            print("xD em percent")
            print(xD)
            print("deltamK")
            print(deltamK)
            print("deltamB")
            print(deltamB)
            print("deltamBs")
            print(deltamBs)
            print("epK")
            print(epK)
            print("Btu")
            print(Btu)
            print("Btc")
            print(Btc)
            print("theta")
            print(np.angle(np.conj(V.item((3,1)))*V.item((3,0))))
            
            print("alpha")
            print(np.degrees(alpha))
            print("beta")
            print(np.degrees(beta))
            print("gamma")
            print(np.degrees(gamma))

            print("VLdagger")
            print(abs(VcL.H))
            print("Fu")
            print(abs(Wu))
            print("eta vezes mil")
            print(abs(eta)*10**(3))
            print("m")
            print(abs(m))
            print("mtil")
            print(abs(mtil))
            print("Mtil")
            print(abs(Mtil))
            print("M")
            print(abs(M))

            i=i+1;
 
                  
file.close()
