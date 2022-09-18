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

def trigcircfind(plist3):
      lcode=[]
      for k in range(len(plist3)):
            if(k>0):
                  while(plist3[k]<0):
                        plist3[k]+=2*pi;
                  plist3[k]=plist3[k]%(2*pi)
                  if(k<7):
                        if(plist3[k]<=pi/2):
                              lcode.append(1)
                        elif(plist3[k]>pi/2 and plist3[k]<=pi):
                              lcode.append(2)
                        elif(plist3[k]>pi and plist3[k]<=1.5*pi):
                              lcode.append(3)
                        else:
                              lcode.append(4)
      return lcode
      

def converter(plist3):
        #0 mT, 1 t12, 2 t13, 3 t23, 4 t14, 5 t24, 6 t34, 7 d13, 8 d14, 9 d24

      lcode=trigcircfind(plist3)
      
      print(lcode)
      #t12 fora do 1Q.
      if(lcode[0]!=1):
            if(lcode[0]==2):
                  #print(math.cos(plist3[1]))
                  #faz c para -c
                  plist3[1]=pi-plist3[1]
                  #print(math.cos(plist3[1]))
                  #plist3[1]=plist3[1]-pi/2;

                  #d13
                  plist3[7]=(plist3[7]+pi)%(2*pi);
                  #d14
                  plist3[8]=(plist3[8]+pi)%(2*pi);
            if(lcode[0]==3):
                  #faz c para -c e s para -s
                  plist3[1]=plist3[1]-pi
            if(lcode[0]==4):
                  plist3[1]=2*pi-plist3[1]
                  #d13
                  plist3[7]=(plist3[7]+pi)%(2*pi);
                  #d14
                  plist3[8]=(plist3[8]+pi)%(2*pi);
      #t13 fora do 1Q.
      if(lcode[1]!=1):
            if(lcode[1]==2):
                  plist3[2]=pi-plist3[2]
                  #d14
                  plist3[8]=(plist3[8]+pi)%(2*pi);
            if(lcode[1]==3):
                  plist3[2]=plist3[2]-pi
                  #d13
                  plist3[7]=(plist3[7]+pi)%(2*pi);
                  #d14
                  plist3[8]=(plist3[8]+pi)%(2*pi);
            if(lcode[1]==4):
                  plist3[2]=2*pi-plist3[2]
                  #d13
                  plist3[7]=(plist3[7]+pi)%(2*pi);
      #t23 fora do 1Q.
      if(lcode[2]!=1):
            if(lcode[2]==2):
                  plist3[3]=pi-plist3[3];
                  #d13
                  plist3[7]=(plist3[7]+pi)%(2*pi);
                  #d24
                  plist3[9]=(plist3[9]+pi)%(2*pi);
            if(lcode[2]==3):
                  plist3[3]=plist3[3]-pi;
                  #d14
                  plist3[8]=(plist3[8]+pi)%(2*pi);
            if(lcode[2]==4):
                  plist3[3]=2*pi-plist3[3]
                  #d13
                  plist3[7]=(plist3[7]+pi)%(2*pi);
                  #d14
                  plist3[8]=(plist3[8]+pi)%(2*pi);
                  #d24
                  plist3[9]=(plist3[9]+pi)%(2*pi);
      #t14 fora do 1Q.
      if(lcode[3]!=1):
            if(lcode[3]==2):
                  plist3[4]=pi-plist3[4]
            if(lcode[3]==3):
                  plist3[4]=plist3[4]-pi
                  #d14
                  plist3[8]=(plist3[8]+pi)%(2*pi);
            if(lcode[3]==4):
                  plist3[4]=2*pi-plist3[4]
                  #d14
                  plist3[8]=(plist3[8]+pi)%(2*pi);
           
      #t24 fora do 1Q.
      if(lcode[4]!=1):
            if(lcode[4]==2):
                  plist3[5]=pi-plist3[5]
                  #d14
                  plist3[8]=(plist3[8]+pi)%(2*pi);
            if(lcode[4]==3):
                  plist3[5]=plist3[5]-pi
                  #d14
                  plist3[8]=(plist3[8]+pi)%(2*pi);
                  #d24
                  plist3[9]=(plist3[9]+pi)%(2*pi);
            if(lcode[4]==4):
                  plist3[5]=2*pi-plist3[5]
                  #d24
                  plist3[9]=(plist3[9]+pi)%(2*pi);
      #t34 fora do 1Q.
      if(lcode[5]!=1):
            if(lcode[5]==2):
                  plist3[6]=pi-plist3[6]
                  #d14
                  plist3[8]=(plist3[8]+pi)%(2*pi);
                  #d24
                  plist3[9]=(plist3[9]+pi)%(2*pi);
            if(lcode[5]==3):
                  plist3[6]=plist3[6]-pi
            if(lcode[5]==4):
                  plist3[6]=2*pi-plist3[6]
                  #d14
                  plist3[8]=(plist3[8]+pi)%(2*pi);
                  #d24
                  plist3[9]=(plist3[9]+pi)%(2*pi);

      lcode=trigcircfind(plist3)

      print(lcode)

      
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

      #mT>bounds experimentais
      f16=plist[0]
      f16cent=1000
      sigf16=0.00001

      

      summ_exp_1=((f0-f0cent)/sigf0)**2+((f1-f1cent)/sigf1)**2+((f2-f2cent)/sigf2)**2+((f3-f3cent)/sigf3)**2+((f4-f4cent)/sigf4)**2+((f5-f5cent)/sigf5)**2+((f6-f6cent)/sigf6)**2+((f7-f7cent)/sigf7)**2+((f8-f8cent)/sigf8)**2+((f9-f9cent)/sigf9)**2+((f14-f14cent)/sigf14)**2
      summ_infbound=((f10-f10cent)/sigf10)*max(0,((f10-f10cent)/sigf10))+((f11-f11cent)/sigf11)*max(0,((f11-f11cent)/sigf11))+((f12-f12cent)/sigf12)*max(0,((f12-f12cent)/sigf12))+((f13-f13cent)/sigf13)*max(0,((f13-f13cent)/sigf13))+((f15-f15cent)/sigf15)*max(0,((f15-f15cent)/sigf15))
      summ_supbound=((f16-f16cent)/sigf16)*min(0,((f16-f16cent)/sigf16))

  

      
      return (summ_exp_1+summ_infbound+summ_supbound)
      #return (summ_exp_1)+

def L2(plist):

      ###calc para L, calc2 para L2
      m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta, MT, xT, t12, t13, t23, t14, t24, t34, delta, delta14, delta24= calc2(plist)
      
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

      #mT>bounds experimentais. meti 1500 para o nosso benchmark. valor correto seria ~1000
      f16=plist[0]
      f16cent=1500
      sigf16=0.00001

      

      summ_exp_1=((f0-f0cent)/sigf0)**2+((f1-f1cent)/sigf1)**2+((f2-f2cent)/sigf2)**2+((f3-f3cent)/sigf3)**2+((f4-f4cent)/sigf4)**2+((f5-f5cent)/sigf5)**2+((f6-f6cent)/sigf6)**2+((f7-f7cent)/sigf7)**2+((f8-f8cent)/sigf8)**2+((f9-f9cent)/sigf9)**2
      #+((f14-f14cent)/sigf14)**2
      summ_infbound=((f10-f10cent)/sigf10)*max(0,((f10-f10cent)/sigf10))+((f11-f11cent)/sigf11)*max(0,((f11-f11cent)/sigf11))+((f12-f12cent)/sigf12)*max(0,((f12-f12cent)/sigf12))+((f13-f13cent)/sigf13)*max(0,((f13-f13cent)/sigf13))+((f15-f15cent)/sigf15)*max(0,((f15-f15cent)/sigf15))
      summ_supbound=((f16-f16cent)/sigf16)*min(0,((f16-f16cent)/sigf16))

  

      
      return (summ_exp_1+summ_infbound+summ_supbound)
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
      m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta, MT, xT, t12, t13, t23, t14, t24, t34, delta, delta14, delta24= calc2(plist)
      
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
      c12 = math.cos(t12)
      c13 = math.cos(t13)
      c23 = math.cos(t23)
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
      #print("matrizes")
      #print(Um(t12,t23,t13,delta))
      #print(U14(t14,delta14))
      #print(U24(t24,delta24))
      #print(U34(t34))
      
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


      try:

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
            
           
            
            
      except np.linalg.LinAlgError as err:
            if 'Singular matrix' in str(err):
                  #print("sing")
                  m=0
                  mtil=0
                  Mtil=0
                  M=0
                  V= np.matrix([[-1,-1,-1],[1,-1,-1],[1,-1,-1],[1,-1,-1]])
                  Wu=0
                  #VcL=0
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
                  deltamK=0
                  deltamB=0
                  deltamBs=0
                  epK=0
                  gamma=0
                  eta=0


      return  m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta, MT, xT, t12, t13, t23, t14, t24, t34, delta, delta14, delta24;

  

def calc(plist):
      MT=plist[0];
      xT=(MT/mW)**2
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
                  
      

      return m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta, MT, xT, xf, xr1, xr2, xr3, xr4, tk, tz, gk, gz;


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

mD=1864.83*10**(-3);
errmD=0.05*10**(-3);
tauD=410.1*10**(-15);
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

for i in range(0,it):


      
      '''
      ########################################
      ####################PARAM X############
      #######################################
 
      ##parameter region where minimum lies. comment if searching for region
      plist=[]
      MT=random.uniform(MTmin,MTmax)*mt
      plist.append(MT)
      xT=(MT/mW)**2;
      flip=random.randint(0, 1)
      #flip=1
      if(flip==1):
            xf=random.uniform(1,1.5)
            plist.append(xf)
      if(flip==0):
            xf=random.uniform(4,5)
            plist.append(xf)
      if(flip==1):
            gz=random.uniform(1.5,4.3)
            plist.append(gz)
      if(flip==0):
            gz=random.uniform(-1.57,1.57)
            if(gz<0):
                  gz=gz+2*pi;
            plist.append(gz)
      gk=random.uniform(4,5)
      plist.append(gk)
      tk=random.uniform(tcabmin,tcabmax)
      plist.append(tk)
      if(flip==1):
            tz=random.uniform(0.005,0.03)
            plist.append(tz)
      if(flip==0):
            tz=random.uniform(0.006,0.008)
            plist.append(tz)
      xr1=random.uniform(0.0030,0.005)
      plist.append(xr1)
      xr2=random.uniform(0.035,0.05)
      plist.append(xr2)
      xr3=random.uniform(0.038,0.042)
      plist.append(xr3)
      xr4=random.uniform(0.0025,0.006)
      plist.append(xr4)
      
      
      
      ##broad parameter search for minimun search. comment after minimum found
      
      plist=[]
      MT=random.uniform(MTmin,MTmax)*mt
      plist.append(MT)
      xT=(MT/mW)**2;
      xf=random.uniform(-pi/2,-0.4)
      plist.append(xf)
      gz=random.uniform(-pi/2,0)
      #if(gz<0):
            #gz=gz+2*pi;
      plist.append(gz)
      gk=random.uniform(-pi/2,0)
      plist.append(gk)
      tk=random.uniform(tcabmin,tcabmax)
      plist.append(tk)
      tz=random.uniform(0.02,0.03)
      plist.append(tz)
      xr1=random.uniform(0.002,0.004)
      plist.append(xr1)
      xr2=random.uniform(0.038,0.041)
      plist.append(xr2)
      xr3=random.uniform(0.035,0.045)
      plist.append(xr3)
      xr4=random.uniform(0.003,0.005)
      plist.append(xr4)
      #end broad parameter search

      #calculations
      m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta= calc(plist)

      
      ##minimization. comment after parameter region found. edit above
      #print("loss")
      end=0
      for i2 in range(0,it_min):
            print(i2)
            if(end==1):
                  plist=[]
                  plist=plist3
            print(L(plist))
            res=minimize(L,plist,method='Nelder-Mead', options={'disp': True})
            plist3=res["x"]
 
            m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta= calc(plist3)
            if (xf<0):
                  xf=xf+2*pi;
            if(xf>2*pi):
                  xf=xf%(2*pi)
                  
            if (gz<0):
                  gz=gz+2*pi;
            if(gz>2*pi):
                  gz=gz%(2*pi)
            if (gk<0):
                  gk=gk+2*pi;
            if(gk>2*pi):
                  gk=gk%(2*pi)


      
            MT=plist3[0];
            xT=(MT/mW)**2;
            xf=plist3[1];
            gz=plist3[2];
            gk=plist3[3];
            tk=plist3[4];
            tz=plist3[5];
            xr1=plist3[6];
            xr2=plist3[7];
            xr3=plist3[8];
            xr4=plist3[9];
            print("after min loss")
            print(L(plist3))
            end=1
            if(L(plist3)<10000):
                  print("aaaaaaaaaaaaa")
                  break
                  ##end minimization procedure
                  
      print(abs(VcL.H))
      #print(abs(V))
      
      
      
      ########################################
      ####################end PARAM X########
      #######################################
      '''
      
      
   
      ########################################
      ####################PARAM ANGLES############
      #######################################


      
      ##parameter region where minimum lies. comment if searching for region
      plist=[]
      MT=1500
      plist.append(MT)
      xT=(MT/mW)**2
      t12=random.uniform(0.22,0.23)
      plist.append(t12)
      t13=random.uniform(0.0035,0.0040)
      plist.append(t13)
      t23=random.uniform(0.035,0.040)
      plist.append(t23)
      t14=random.uniform(0,pi/2)
      plist.append(t14)
      t24=random.uniform(0,pi/2)
      plist.append(t24)
      t34=random.uniform(0,pi/2)
      plist.append(t34)
      delta=random.uniform(0,2*pi)
      plist.append(delta)
      delta14=random.uniform(0,2*pi)
      plist.append(delta14)
      delta24=random.uniform(0,2*pi)
      plist.append(delta24)

      
      
      
      ##broad parameter search for minimun search. comment after minimum found
      '''
      plist=[]
      
      MT=random.uniform(MTmin,MTmax)*mt
      plist.append(MT)
      xT=(MT/mW)**2
      t12=random.uniform(0,pi/2);
      plist.append(t12)
      t13=random.uniform(0,pi/2);
      plist.append(t13)
      t23=random.uniform(0,pi/2);
      plist.append(t23)
      t14=random.uniform(0,pi/2);
      plist.append(t14)
      t24=random.uniform(0,pi/2);
      plist.append(t24)
      t34=random.uniform(0,2*pi);
      plist.append(t34)
      delta=random.uniform(0,2*pi);
      plist.append(delta)
      delta14=random.uniform(0,2*pi);
      plist.append(delta14)
      delta24=random.uniform(0,2*pi);
      plist.append(delta24)
      '''

   



      #end broad parameter search

      #calculations
      m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta, MT, xT, t12, t13, t23, t14, t24, t34, delta, delta14, delta24= calc2(plist)

      
           
      ##minimization. comment after parameter region found. edit above
      #print("loss")
      end=0

      ##minimiza it_min vezes, so para antes de it_min se tiver loss<100. Possivel melhoria: funçao que deteta convergencia - casos em que ta preso em regioes de loss gigantes, fazer break de forma a nao ter que fazer as it_min vezes. cuidado para nao eliminar os casos em que começa mal mas dá um grande salto para regioes boas.
      for i2 in range(0,it_min):
            #print(i2)
            if(end==1):
                  plist=[]
                  plist=plist3
            print("inicio")
            print(plist)
            print(abs(VcL.H))
            print(L2(plist))
            print(L2V(plist))
            #plist3=[]
            #plist3=plist
            if(L2(plist)>100):
                  plist3=[]
                  res=minimize(L2,plist,method='Nelder-Mead', options={'disp': True})
                  plist3=res["x"]


                  
                  ##script onde se mete os angulos e fases todos na convencao ate pi/2. dps da minimizaçao alguns ficam negativos.
                  print("After min")
                  print(plist3)
                  print(L2(plist3))
                  
                  m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta, MT, xT, t12, t13, t23, t14, t24, t34, delta, delta14, delta24= calc2(plist3)


                  print("after min loss")
                  print(L2(plist3))
                  end=1
            else:
                  print("sai da minimizacao")
                  break
                  ##end minimization procedure
      
                  
      #print("saido do loop")
      #print(plist3)
      
      ##tirar apos testes!!!
      #plist3=plist
   
      #print(plist3)
      #print("TESTEEEEE")
      #m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta, MT, xT, t12, t13, t23, t14, t24, t34, delta, delta14, delta24= calc2(plist3)
      #print(VcL)
      #print(plist3)
      #print(abs(VcL.H))
      #loss=L2V(plist3)
      #print(loss)

         
      #poe todos os angulos entre 0 e 2pi
      #loss inicial é menor que threshold, acertou na regiao aleatoriamente.
      if(end==0):
            plist3=plist
      uselesslist=trigcircfind(plist3)

      #poe angulos entre 0 e pi/2 e ajusta as fases accordingly (convencao da ckm pdg)
      converter(plist3)
      m, mtil, Mtil, M, V, Wu, VcL, omegatil, Omegatil, Omega, J, XL, KL, ZL, RL, AL, BL, deltamK, deltamB, deltamBs, epK, gamma, eta, MT, xT, t12, t13, t23, t14, t24, t34, delta, delta14, delta24= calc2(plist3)
      print(plist3)
      print(abs(VcL.H))
      loss=L2V(plist3)
      print(loss)
                  
    


      ########################################
      #############end PARAM ANGLES##########
      #######################################
      
 
      #print(abs(VcL.H))
      #if(L(plist3)<10000):
      if(14<1000):
            print("bbbb")
            #print(L(VcL,V))
            #print(abs(VcL.H))
            if ((V.item((0,0))!=-1)): #when X is not singular
                  #dev from unitarity 
                  if(abs(VcL.item((3,0)))>dev_unit/(40) and abs(VcL.item((3,0)))<dev_unit*3):
                        print("B")
                        ##mij perturbativity bound
                        if(abs(m.item((0,0)))<=4*pi*mt):
                              print("C")
                              if(abs(m.item((0,1)))<=4*pi*mt):
                                    print("D")
                                    if(abs(m.item((0,2)))<=4*pi*mt):
                                          print("E")
                                          if(abs(m.item((1,0)))<=4*pi*mt):
                                                print("F")
                                                if(abs(m.item((1,1)))<=4*pi*mt):
                                                      print("G")
                                                      if(abs(m.item((1,2)))<=4*pi*mt):
                                                            print("H")
                                                            if(abs(m.item((2,0)))<=4*pi*mt):
                                                                  print("I")
                                                                  if(abs(m.item((2,1)))<=4*pi*mt):
                                                                        print("J")
                                                                        if(abs(m.item((2,2)))<=4*pi*mt):
                                                                              print("K")
                                                                              if(abs(mtil.item((0,0)))<=4*pi*mt ):
                                                                                    print("L")
                                                                                    if(abs(mtil.item((1,0)))<=4*pi*mt ):
                                                                                          print("M")
                                                                                          if(abs(mtil.item((2,0)))<=4*pi*mt):
                                                                                                print("N")
                                                                                               
                                                                                                if(deltamK<=deltamKexp):
                                                                                                      print("A2")
                                                                                                      if(deltamB<=deltamBexp):
                                                                                                            print("B2")
                                                                                                            if(deltamBs<=deltamBsexp):
                                                                                                                  print("C2")
                                                                                                                  if(epK<=epKexp):
                                                                                                                        print("D2")
                                                                                                                        ##DDbar mixing
                                                                                                                        if(abs(VcL.item((3,1))*np.conj(VcL.item((3,0))))<1.22*10**(-4)):
                                                                                                                              print("E2")
                                                                                                                              print("passei")
                                                                                                                              j=j+1;
                                                                                                                              
                                                                                                                              '''
                                                                                                                              ###param X

                                                                                                                              file.write("%f" %(MT/mt) + " ")
                                                                                                                              file.write("%f" %xf + " ")
                                                                                                                              file.write("%f" %gz + " ")
                                                                                                                              file.write("%f" %gk + " ")
                                                                                                                              file.write("%f" %tk + " ")
                                                                                                                              file.write("%f" %tz + " ")
                                                                                                                              file.write("%f" %xr1 + " ")
                                                                                                                              file.write("%f" %xr2 + " ")
                                                                                                                              file.write("%f" %xr3 + " ")
                                                                                                                              file.write("%f" %xr4 + "\n")
                                                                                                                              '''
                                                                                                                              ##param angles
                                                                                                                              file.write("%f" %(MT/mt) + " ")
                                                                                                                              file.write("%f" %t12 + " ")
                                                                                                                              file.write("%f" %t13 + " ")
                                                                                                                              file.write("%f" %t23 + " ")
                                                                                                                              file.write("%f" %t14 + " ")
                                                                                                                              file.write("%f" %t24 + " ")
                                                                                                                              file.write("%f" %t34 + " ")
                                                                                                                              file.write("%f" %delta + " ")
                                                                                                                              file.write("%f" %delta14 + " ")
                                                                                                                              file.write("%f" %delta24 + " ")
                                                                                                                              file.write("%f" %loss + "\n")
                                                                                                                              
                                          
                        
                            
file.close()


'''

 ##Vckm bounds
                                                                                                if(abs(V.item((2,1)))>(V32-errV32) and abs(V.item((2,1)))<(V32+errV32)  ):
                                                                                                      print("O")
                                                                                                      if(abs(V.item((2,2)))>(V33-errV33) and abs(V.item((2,2)))<(V33+errV33)):
                                                                                                            print("P")
                                                                                                            if((abs(V.item((0,1)))>(V12-errV12)) and (abs(V.item((0,1)))<(V12+errV12))):
                                                                                                                  print("Q")
                                                                                                                  if(abs(V.item((1,0)))>(V21-errV21) and abs(V.item((1,0)))<(V21+errV21)):
                                                                                                                        print("R")
                                                                                                                        print(abs(V.item((1,1))))
                                                                                                                        print((V22-errV22))
                                                                                                                        print((V22+errV22))
                                                                                                                        if(abs(V.item((1,1)))>(V22-errV22) and abs(V.item((1,1)))<(V22+errV22)):
                                                                                                                              print("S")
                                                                                                                              #print(abs(VcL.H))
                                                                                                                              #print(abs(V.item((1,2))))
                                                                                                                              if(abs(V.item((1,2)))>(V23-errV23) and abs(V.item((1,2)))<(V23+errV23) ):
                                                                                                                                    print("T")
                                                                                                                                    #print(abs(ZL))
                                                                                                                                    #print(abs(XL))
                                                                                                                                    
                                                                                                                                    if(abs(V.item((0,2)))>(V13-errV13) and abs(V.item((0,2)))<(V13+errV13)):
                                                                                                                                          print("U")
                                                                                                                                      
                                                                                                                                          
                                                                                     
                                                                                                                                          #print(abs(V.item((2,0))))
                                                                                                                                          if(abs(V.item((2,0)))>(V31-errV31) and abs(V.item((2,0)))<(V31+errV31)):
                                                                                                                                                print("V")
                                                                                                                                                ##pheno bounds
                                                                                                                                              
                                                                                                                                                #print(gamma)
                                                                                                                                                #gamma=1.2
                                                                                                                                                #print(gamma)
                                                                                                                                                if ((gamma>=(gammaexp-errgammaexp)) and (gamma<=(gammaexp+errgammaexp))):
                                                                                                                                                      print("X")
                                                                                                                                                      #print(abs(VcL.H))
'''
