import numpy as np
import os
import sys
from decimal import *
from numpy import linalg as LA
import math
from math import radians
from math import pi
from math import e
import time
import random
from scipy.optimize import minimize

#from mpmath import*
import mpmath as mp

from scipy import linalg
np.set_printoptions(suppress=True)
from cmath import sqrt


#definitions of functions and parameter limits setting


'''
def L(plist):

      ###calc para L, calc2 para L2
      K, V, H, H2, X, m1, m2, m3, M1, M2, M3, m, M, D, d, etal, Kl, Xl, dl, Dl, Rl, Zl=calc(plist,v,mH,mZ)
      
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
def LV(plist):

      ###calc para L, calc2 para L2
      K, V, H, H2, X, m1, m2, m3, M1, M2, M3, m, M, D, d, etal, Kl, Xl, dl, Dl, Rl, Zl=calc(plist,v,mH,mZ)
      
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

'''
###TAKAGI FACT FUNCTIONS
EPS = 1e-10


def approx_eq(a, b):
    return EPS > a - b > -EPS


def symmetric_svd(a):
    # Here we implicitly assume a is symmetric.
    A = mp.matrix(a)

    reA = A.apply(mp.re)
    imA = A.apply(mp.im)
    n = len(a)
    
    #forma de declarar matrix 2n x 2n
    Bmat = [[0 for _ in range(2 * n)] for _ in range(2 * n)]
    #preenche matrix em blocos, up left block é re(A), up right block e down left block é im(A), down right block é -re(A). B é simetrica e tem traço 0
    for i in range(n):
        for j in range(n):
            Bmat[i][j] = reA[i, j]
            Bmat[i + n][j] = imA[i, j]
            Bmat[i][j + n] = imA[i, j]
            Bmat[i + n][j + n] = -reA[i, j]

    B = mp.matrix(Bmat)
    #mp.nprint(mp.chop(B),5)
    #Q.T * mp.diag(ev) * Q == B
    ev, Q = mp.eigsy(B)


    #only use this part uncommented if you are sure that A is symmetric!!! this is a fix for the case when there are two eigenvalues that are essentially zero (precision is e-p an they are smaller). when this is the case their signs might be wrong. and you can have cases where you have 5 positive eigenvalues and 7 negative, while their summ is essentially zero, because you have one extra negative that should be positive, i.e., they should be +0 -0 but they are -0 -0. when this happens the assert(len(vs)==n) will be false and cause an error.
    #this maps the first 6 values, that should be negative (if they are not i force it), to the last 6 in reverse order, that are positive due to the map being -1* the others.
    #print("AAA")
    nn=int(len(ev)/2)
    for i in range(0,nn):
        ev[i]=-abs(ev[i])
        ev[2*nn-1-i]=abs(ev[i])
    #print(ev)
    ####

    #Qmat =Q.T
    Qmat = [[Q[j, i] for j in range(2 * n)] for i in range(2 * n)]
    #def de Umat nxn matrix
    Umat = [[0 for _ in range(n)] for _ in range(n)]
    vs = [Qmat[i] for i, v in enumerate(ev) if v > 0]

    #print("test")
    #print(n)
    #print(vs)
    #print(len(vs))
    assert(len(vs) == n)

    for i in range(n):
        for j in range(n):
            Umat[i][j] = vs[j][i] - 1j * vs[j][i + n]

    Q = mp.matrix(Umat)

    # Accordingly, Q.T * A * Q is a diagonal matrix
    sing_mat = Q.T * A * Q
    sing_vs = [sing_mat[i, i] for i in range(len(sing_mat))]

    return sing_vs, Q


def takagi_fact(a):
    A = mp.matrix(a)
    sing_vs, Q = symmetric_svd(A)
    phase_mat = mp.diag([mp.exp(-1j * mp.arg(sing_v) / 2.0)
                         for sing_v in sing_vs])

    vs = [mp.fabs(sing_v) for sing_v in sing_vs]
    Qp = Q * phase_mat

    return vs, Qp


def set_dps(dps):
    mp.dps = dps




def calc(plist,v,mH,mZ):
      #set precision
      mp.mp.dps = 100
      mp.mp.pretty=True
      m1ev=plist[0]
      d31=plist[1]
      d21=plist[2]
      M1=plist[3]
      M2=plist[4]
      M3=plist[5]
      t12=plist[6]
      t13=plist[7]
      t23=plist[8]
      r12=plist[9]
      r13=plist[10]
      r23=plist[11]
      f13=plist[12]
      f12=plist[13]
      f23=plist[14]
      delta=plist[15]
      dm1=plist[16]
      dm2=plist[17]
      sign=plist[18]
      
      evtogev=1e-9
      z=m1ev*m1ev/d31

      ##matrizes singulares try except teste
      #print("START")
      
      m1=float(m1ev)
      #print(m1)
      m2=float(math.sqrt(d31*(z+d21/d31)))
      m3=float(math.sqrt(d31*(z+1)))
      dlist=[]
      Dlist=[]
      dlist.append(m1)
      dlist.append(m2)
      dlist.append(m3)
      Dlist.append(M1)
      Dlist.append(M2)
      Dlist.append(M3)

      dlistsq=[]
      dlistsq.append(mp.sqrt(m1))
      dlistsq.append(mp.sqrt(m2))
      dlistsq.append(mp.sqrt(m3))

      Dlistinv=[]
      Dlistinv.append(1/M1)
      Dlistinv.append(1/M2)
      Dlistinv.append(1/M3)

      Dlistinvsq=[]
      Dlistinvsq.append(mp.sqrt(1/M1))
      Dlistinvsq.append(mp.sqrt(1/M2))
      Dlistinvsq.append(mp.sqrt(1/M3))


      
      #d=np.diag(dlist)
      d=mp.diag(dlist)
      dsq=mp.diag(dlistsq)
      #print(m1)
      #print(m2)
      #print(m3)
      D=mp.diag(Dlist)
      Dinv=mp.diag(Dlistinv)
      Dinvsq=mp.diag(Dlistinvsq)
      #print(d)
      #print("d")
      #mp.nprint(mp.chop(d),25)
      #print("D")
      #mp.nprint(mp.chop(D),5)
      #mp.nprint(Dinv,25)
      #mp.nprint(Dinvsq,25)
      #mp.nprint(dsq,20)
      
      #Oc=np.dot(Oc23(r23*e**(1j*f23)),np.dot(Oc13(r13*e**(1j*f13)),Oc12(r12*e**(1j*f12))))
      #print(Oc)
      Oc=sign*Oc23(r23*e**(1j*f23))*Oc13(r13*e**(1j*f13))*Oc12(r12*e**(1j*f12))
      #print("Oc")
      #mp.nprint(mp.chop(Oc),5)
      #X = np.dot(np.dot(1j*np.sqrt(np.linalg.inv(D)),Oc),np.sqrt(d))
      #print(X)
      #mp.nprint(mp.sqrtm(d),20)
      X=-1j*Dinvsq*Oc*dsq
      #print("X")
      #mp.nprint(mp.chop(X),5)


      '''
      #A = np.dot(X.H,X)
      A=X.H*X
      #A= X.transpose_conj()
      #mp.nprint(mp.chop(A),5)
      #eigsy real sym, eighe complex hermitian, eig standard matrix
      dx, U= mp.eighe(A)
      dxsq=mp.diag(dx)
      #mp.eye(x) xtimesx identity matrix
      Sdx = mp.sqrtm(mp.eye(3) +dxsq)
      B =  X*X.H
      dx2, W= mp.eighe(B)
      dxsq2= mp.diag(dx2)
      Sdx2= mp.sqrtm(mp.eye(3) +dxsq2)
      '''
      
      V=Um(t12,t23,t13,delta,dm1,dm2);
      #UPMNS = Um(math.sqrt(0.307),math.sqrt(0.417), math.sqrt(0.0212),1.40*pi,2*pi/rangefinal*p1,2*pi/rangefinal*p2)
      #UK = np.dot(V, U)
      #UK=V*U
      #K=np.dot(np.dot(UK,np.linalg.inv(Sdx)),U.H)
      #K=UK*Sdx**(-1)*U.H
      #mp.nprint(mp.chop(X.H*X),5)
      HRaux=mp.sqrtm(mp.eye(3) +X.H*X)
      #mp.nprint(mp.chop(HRaux),5)
      HR=HRaux**(-1)
      K=V*HR
      #print("K")
      #mp.nprint(mp.chop(K),5)
      H=HR
      HL=V*HR*V.H

      eta=0.5*V*X.H*X*V.H
      #H=np.dot(np.dot(U,np.linalg.inv(Sdx)),U.H)
      #H=U*Sdx**(-1)*U.H
      #H2=np.dot(np.dot(W,np.linalg.inv(Sdx2)),W.H)
      #H2=W*Sdx2**(-1)
      #dev = np.absolute(np.identity(3) - np.dot(K,K.H))
      #dev=mabs(mp.eye(3)-K*K.H)
      #eta=mabs(0.5*(mp.eye(3)-K*K.H))
      #mp.nprint(mp.chop(dev),5)
      #print("eta")
      #mp.nprint(mp.chop(eta),5)

      #K2=np.dot(V,H)
      #K2=V*H
      R=K*X.H
      #print("R")
      #mp.nprint(mp.chop(R),5)      
      #R=np.dot(K,X.H)
      
      #escolher VZ tal que M seja diagonal, base da leptogenesis. na maioria dos casos isto correspondete a VZ=ident
      VZ=mp.eye(3)
      HRauxZ=mp.sqrtm(mp.eye(3) +X*X.H)
      HRZ=HRauxZ**(-1)
      aux=D+X*d*X.T
      
      for k in range(0,2):
            #mp.nprint(mp.chop(VZ),5)
           
            Z=VZ*HRZ
            H2=HRZ
            #print("Z")
            #mp.nprint(mp.chop(Z),5)
      
    
          
            M=Z*aux*Z.T
            #print("M")
            #mp.nprint(mp.chop(M),5)

            
            if(k==0):
                  
                  #print("PA")
                  Dplist, VZ0 =takagi_fact(M)
                  #Dp=mp.diag(Dplist)
                  #mp.nprint(mp.chop(Dp),5)
                  #mp.nprint(mp.chop(VZ0),5)
                  #cc tem que dar M
                  #cc=(VZ0.H).T*Dp*VZ0.H
                  #mp.nprint(mp.chop(cc),5)
                  #mp.nprint(mp.chop(M),5)
                  VZ=VZ0.T


      #mp.nprint(mp.chop(M))
      #mp.nprint(mp.chop(VZ))
      
            
            
      


      
      #m=np.dot(np.dot(np.dot(K,X.H),D),np.linalg.inv((T.H).T))
      m=K*X.H*D*((Z.H)**(-1)).T
      #to use in the numerical calculation of mdagm, since V cancels. yields better results in edge cases.
      msenzaV=H*X.H*D*((Z.H)**(-1)).T
      #print("m")
      #mp.nprint(mp.chop(m),5)

      S=-Z*X
    
      UL=cbmat(K,R)
      #mp.nprint(mp.chop(UL),5)
      
      #print(abs(R))
      #print(abs(UL))
      dDlist=[]
      dDlist.append(d[0,0])
      dDlist.append(d[1,1])
      dDlist.append(d[2,2])
      dDlist.append(D[0,0])
      dDlist.append(D[1,1])
      dDlist.append(D[2,2])
      dD=mp.diag(dDlist)
      ldD=[]

      #caso em que m1 é zero. (funçao tende pra zero em zero mas numericamente da infinito)
      if(d[0,0]==0):
            ldD.append(0.0)
      else:
            ldD.append(d[0,0]*d[0,0]*d[0,0]*(3*(mp.log((d[0,0]/mZ)*(d[0,0]/mZ)))/((d[0,0]*d[0,0])/((mZ*mZ))-1)+(mp.log((d[0,0]/mH)*(d[0,0]/mH)))/((d[0,0]*d[0,0])/((mH*mH))-1)))
            
      ldD.append(d[1,1]*d[1,1]*d[1,1]*(3*(mp.log((d[1,1]/mZ)*(d[1,1]/mZ)))/((d[1,1]*d[1,1])/((mZ*mZ))-1)+(mp.log((d[1,1]/mH)*(d[1,1]/mH)))/((d[1,1]*d[1,1])/((mH*mH))-1)))
      ldD.append(d[2,2]*d[2,2]*d[2,2]*(3*(mp.log((d[2,2]/mZ)*(d[2,2]/mZ)))/((d[2,2]*d[2,2])/((mZ*mZ))-1)+(mp.log((d[2,2]/mH)*(d[2,2]/mH)))/((d[2,2]*d[2,2])/((mH*mH))-1)))
      ldD.append(D[0,0]*D[0,0]*D[0,0]*(3*(mp.log((D[0,0]/mZ)*(D[0,0]/mZ)))/((D[0,0]*D[0,0])/((mZ*mZ))-1)+(mp.log((D[0,0]/mH)*(D[0,0]/mH)))/((D[0,0]*D[0,0])/((mH*mH))-1)))
      ldD.append(D[1,1]*D[1,1]*D[1,1]*(3*(mp.log((D[1,1]/mZ)*(D[1,1]/mZ)))/((D[1,1]*D[1,1])/((mZ*mZ))-1)+(mp.log((D[1,1]/mH)*(D[1,1]/mH)))/((D[1,1]*D[1,1])/((mH*mH))-1)))
      ldD.append(D[2,2]*D[2,2]*D[2,2]*(3*(mp.log((D[2,2]/mZ)*(D[2,2]/mZ)))/((D[2,2]*D[2,2])/((mZ*mZ))-1)+(mp.log((D[2,2]/mH)*(D[2,2]/mH)))/((D[2,2]*D[2,2])/((mH*mH))-1)))
      fdD=1/((4*pi*v)*(4*pi*v))*mp.diag(ldD)
      #fdD=mp.diag(ldD)
      #mp.nprint(mp.chop(fdD),5)
      #print("fdD")
      #print(abs(fdD))
      #deltaML=np.dot(np.dot(UL,fdD),UL.T)
      deltaML=UL*fdD*UL.T
      #3x3 matrix with zeros
      #deltaML=mp.matrix(3,3)
      #print("inicio SVD")
      #print("deltaML")
      #mp.nprint(mp.chop(deltaML),5)
      

      #print("Mcaloop")
      Mcaloop=crbmat(deltaML,m,m.T,M)
      #mp.nprint(mp.chop(Mcaloop),5)




      ##takagi fact done using mpmath lib, more precision
      #faz a takagi decomp de A com uma unit U e diaginal D: U.T A U = D
      #print("PB")
      s, u =takagi_fact(Mcaloop)
      ss=mp.diag(s)
      #mp.nprint(mp.chop(ss),5)
      #mp.nprint(mp.chop(u),5)
      #cc tem que dar Mcaloop
      #cc=(u.H).T*s*u.H
      #mp.nprint(mp.chop(cc),5)
      #mp.nprint(mp.chop(Mcaloop),5)
      #ubom=u
    

      '''
      #mp.nprint(mp.chop(Mcaloop),5)
      #u,s, vh =LA.svd(Mcaloop)
    
      s, u = symmetric_svd(Mcaloop)
      #print("AAA")
      #mp.pretty=True
      #mp.nprint(mp.chop(u),5)
      ss=mp.diag(s)
      #mp.nprint(mp.chop(ss),5)
      #print("AAA")
      #tem q dar Mcaloop
      aa= (u.H).T*ss*u.H
      #mp.nprint(mp.chop(aa),5)
      #aid=np.dot(np.dot(u.H,Mcaloop),np.conj(u))
      #tem q dar ss
      aid=u.T*Mcaloop*u
      #print("aid")
      #print(aid)
      #mp.nprint(mp.chop(aid),5)
      ik=0
      phlist=[]
      while(ik<aid.rows):
            phlist.append(e**(1j*(mp.arg(aid[ik,ik])/2)))
            ik+=1
                          
      diagf=mp.diag(phlist)
      #print(diagf)
      #inv = np.matrix('0 0 0 0 0 1; 0 0 0 0 1 0; 0 0 0 1 0 0; 0 0 1 0 0 0; 0 1 0 0 0 0; 1 0 0 0 0 0')
      #inv=mp.matrix(6,6)
      #inv[0,5]=1;inv[1,4]=1;inv[2,3]=1;inv[3,2]=1;inv[4,1]=1;inv[5,0]=1;
      #mp.nprint(mp.chop(inv),5)
      #ubom=np.dot(np.dot(u,diagf),inv)
      ubom=u*diagf
      #aid2=np.dot(np.dot(ubom.H,Mcaloop),np.conj(ubom))
      aid2=ubom.T*Mcaloop*ubom
      #print("aid2")
      #mp.nprint(mp.chop(aid2),5)
      '''

      dlist=[]
      Dlist=[]
      dlist.append(mp.re(s[0]))
      dlist.append(mp.re(s[1]))
      dlist.append(mp.re(s[2]))
      Dlist.append(mp.re(s[3]))
      Dlist.append(mp.re(s[4]))
      Dlist.append(mp.re(s[5]))

      dl=mp.diag(dlist)
      Dl=mp.diag(Dlist)

      #print("dl")
      #mp.nprint(mp.chop(d),5)
      #mp.nprint(mp.chop(dl),5)
      #print("Dl")
      #mp.nprint(mp.chop(D),5)
      #mp.nprint(mp.chop(Dl),5)
      

      Kl=mp.matrix([[u[0,0],u[0,1],u[0,2]],[u[1,0],u[1,1],u[1,2]],[u[2,0],u[2,1],u[2,2]]])
      Rl=mp.matrix([[u[0,3],u[0,4],u[0,5]],[u[1,3],u[1,4],u[1,5]],[u[2,3],u[2,4],u[2,5]]])
      Zl=mp.matrix([[u[3,3],u[3,4],u[3,5]],[u[4,3],u[4,4],u[4,5]],[u[5,3],u[5,4],u[5,5]]])

      #Xl=np.dot(Rl.H,np.linalg.inv(Kl.H))
      Xl=Rl.H*(Kl.H)**(-1)
      #print("Xl")
      #mp.nprint(mp.chop(Xl),5)

      

      #Sl=-np.dot(Zl,Xl)
      Sl=-Zl*Xl

      
      d31l=mp.re(dl[2,2]*dl[2,2]-dl[0,0]*dl[0,0])
      #print(d31l)
      d21l=mp.re(dl[1,1]*dl[1,1]-dl[0,0]*dl[0,0])
      #print(d21l)

      #print("K")
      #mp.nprint(mp.chop(K),5)
      #mp.nprint(mp.chop(Kl),5)

      #Rc=np.conjugate(R)
      #Kc=np.conjugate(K)
      #Theta=np.matrix([[K[0,0],K[0,1],K[0,2],R[0,0],R[0,1]],[K[1,0],K[1,1],K[1,2],R[1,0],R[1,1]],[K[2,0],K[2,1],K[2,2],R[2,0],R[2,1]]])
      #KK=np.dot(Theta,Theta.H)
      #realshit=np.real((Rc[1,0]*R[0,0])*(K[1,0]*Kc[0,0] + K[1,1]*Kc[0,1] +  K[1,2]*Kc[0,2]))
      #print realshit
      #realshit2=-4/(KK[0,0]*KK[1,1])
      #print realshit2
      #val=float(np.real(realshit2*realshit))
      #print val
      #M3c=M3
      #test2=max(dx)
      etal=0.5*(mp.eye(3)-Kl*Kl.H)
      #print("etal")
     

      #calcular outputs experimentais

  

      #leptogenesis
      
      l1=(msenzaV.H)*msenzaV;l3=mimg(l1);
      #print("m")
      #mp.nprint(mp.chop(m*evtogev),5)
      #print("mdagm")
      #mp.nprint(mp.chop(l1*evtogev**2),5)

      #l4=D*X*X.H*D;l5=mimg(l4);


      ep=mp.matrix(3,3)
      mdag=m.H;
      for i in range(0,3):
            for a in range(0,3):
                  #i=1
                  if(i==0):
                        #j=2
                        j1=mp.im(mdag[i,a]*l1[i,1]*m[a,1])*(f(M1,M2)+g(M1,M2,l1,2))+mp.im(mdag[i,a]*l1[1,i]*m[a,1])*(gp(M1,M2,l1,2))
                        #j1=mp.im(mdag[i,a]*l1[i,1]*m[a,1])
                        #j=3
                        j2=mp.im(mdag[i,a]*l1[i,2]*m[a,2])*(f(M1,M3)+g(M1,M3,l1,3))+mp.im(mdag[i,a]*l1[2,i]*m[a,2])*(gp(M1,M3,l1,3))
                        ep[i,a]=mp.re(2/(v*v)*1/(8*pi)*1/(l1[i,i])*(j1+j2))
                        '''
                        print("j1")
                        mp.nprint(mp.chop(j1),5)
                        print("j2")
                        mp.nprint(mp.chop(j2),5)
                        print("f12")
                        mp.nprint(mp.chop((f(M1,M2))),5)
                        print("g12")
                        mp.nprint(mp.chop(g(M1,M2,l1,2)),5)
                        print("gp12")
                        mp.nprint(mp.chop((gp(M1,M2,l1,2))),5)
                        print("f13")
                        mp.nprint(f(M1,M3))
                        print("g13")
                        mp.nprint(mp.chop(g(M1,M3,l1,3)),5)
                        print("gp13")
                        mp.nprint(mp.chop((gp(M1,M3,l1,3))),5)
                        '''
                    
                  #i=2
                  if(i==1):
                        #j=1
                        j0=mp.im(mdag[i,a]*l1[i,0]*m[a,0])*(f(M2,M1)+g(M2,M1,l1,1))+mp.im(mdag[i,a]*l1[0,i]*m[a,0])*(gp(M2,M1,l1,1))
                        #j=3
                        j2=mp.im(mdag[i,a]*l1[i,2]*m[a,2])*(f(M2,M3)+g(M2,M3,l1,3))+mp.im(mdag[i,a]*l1[2,i]*m[a,2])*(gp(M2,M3,l1,3))
                        ep[i,a]=mp.re(2/(v*v)*1/(8*pi)*1/(l1[i,i])*(j0+j2))
                        #print(v*v)
                      
                  #i=3
                  if(i==2):
                        #j=1
                        j0=mp.im(mdag[i,a]*l1[i,0]*m[a,0])*(f(M3,M1)+g(M3,M1,l1,1))+mp.im(mdag[i,a]*l1[0,i]*m[a,0])*(gp(M3,M1,l1,1))
                        #j=2
                        j1=mp.im(mdag[i,a]*l1[i,1]*m[a,1])*(f(M3,M2)+g(M3,M2,l1,2))+mp.im(mdag[i,a]*l1[1,i]*m[a,1])*(gp(M3,M2,l1,2))
                        ep[i,a]=mp.re(2/(v*v)*1/(8*pi)*1/(l1[i,i])*(j0+j1))
                
                        


            
      ep1e=ep[0,0]
      ep1mu=ep[0,1]
      ep1tau=ep[0,2]
      #ep1=ep1e+ep1mu+ep1tau

            
      ep2e=ep[1,0]
      ep2mu=ep[1,1]
      ep2tau=ep[1,2]
      #ep2=ep2e+ep2mu+ep2tau

            
      ep3e=ep[2,0]
      ep3mu=ep[2,1]
      ep3tau=ep[2,2]
      #ep3=ep3e+ep3mu+ep3tau


      ep1=mp.re(2/(v*v)*1/(8*pi)*1/(l1[0,0])*(mp.im(l1[0,1]*l1[0,1])*(f(M1,M2)+g(M1,M2,l1,2))+mp.im(l1[0,2]*l1[0,2])*(f(M1,M3)+g(M1,M3,l1,3))))
      ep2=mp.re(2/(v*v)*1/(8*pi)*1/(l1[1,1])*(mp.im(l1[1,0]*l1[1,0])*(f(M2,M1)+g(M2,M1,l1,1))+mp.im(l1[1,2]*l1[1,2])*(f(M2,M3)+g(M2,M3,l1,3))))
      ep3=mp.re(2/(v*v)*1/(8*pi)*1/(l1[2,2])*(mp.im(l1[2,1]*l1[2,1])*(f(M3,M2)+g(M3,M2,l1,2))+mp.im(l1[2,0]*l1[2,0])*(f(M3,M1)+g(M3,M1,l1,1))))
      #print(ep1t)
      #print(ep2t)
      #print(ep3t)


      
      #calcular Nnu
      Nnu=0
      counter=0
      KHK=Kl.H*Kl
      KHR=Kl.H*Rl
      RHK=Rl.H*Kl
      RHR=Rl.H*Rl
      if(M1<mZ):
            counter+=1
      if(M2<mZ):
            counter+=1
      if(M3<mZ):
            counter+=1

      #print(counter)

      #counter=0
      #print(counter)
      
      for i in range(0,3):
            for j in range(0,3):
                  Nnu+=abs(KHK[i,j])**2

      for i in range(0,3):
            for k in range(0,counter):
                  Nnu+=abs(KHR[i,j])**2


      for k in range(0,counter):
            for j in range(0,3):
                  Nnu+=abs(RHK[i,j])**2


      for k in range(0,counter):
            for l in range(0,counter):
                  Nnu+=abs(RHR[i,j])**2


   
   

      
      #zero-distance
      KKH=Kl*Kl.H

      zd=mp.matrix(3,3)
      for i in range(0,3):
            for j in range(0,3):
                  if(i==j):
                        zd[i,j]=0
                  else:
                        zd[i,j]=1/(KKH[i,i]*KKH[j,j])*abs(KKH[i,j])**2
      
                        
      '''
      zdemu=zd[0,1]
      zdmue=zd[1,0]
      
      zdetau=zd[0,2]
      zdtaue=zd[2,0]
      
      zdmutau=zd[1,2]
      zdtaumu=zd[2,1]
      '''

      

      mdagm=l1;
            
      return K, V, H, H2, X, m1, m2, m3, M1, M2, M3, m, M, D, d, etal, Kl, Xl, dl, Dl, Rl, Zl, R, Z, Oc, eta, deltaML, Mcaloop, VZ, ep, ep1, ep2, ep3, Nnu, zd, d31l, d21l, mdagm;


def mabs(A):
      B=mp.matrix(A.rows,A.cols)
      for i in range(0,A.rows):
            for j in range(0,A.cols):
                  B[i,j]=mp.fabs(A[i,j])
      return B


def mimg(A):
      B=mp.matrix(A.rows,A.cols)
      for i in range(0,A.rows):
            for j in range(0,A.cols):
                  B[i,j]=mp.im(A[i,j])
      return B

##matrix (A B) for A and B with same nr of rows and columns
def cbmat(A,B):
      ma=mp.matrix(A.rows,A.cols+B.cols)
      for i in range(0,A.rows):
            for j in range(0,A.cols+B.cols):
                  if(j<A.cols):
                        ma[i,j]=A[i,j]
                  else:
                        ma[i,j]=B[i,j-A.cols]
      return ma

#untested
##matrix (A) for A and B with same nr of rows and columns
#        (B)
def rbmat(A,B):
      ma=mp.matrix(A.rows,A.cols+B.cols)
      for i in range(0,A.cols):
            for j in range(0,A.rows+B.rows):
                  if(j<A.rows):
                        ma[j,i]=A[j,i]
                  else:
                        ma[i,j]=B[j-A.rows,i]
      return ma

##matrix (A B) for A,B,C,D with same nr of rows and columns
#        (C D)
def crbmat(A,B,C,D):
      ma=mp.matrix(A.rows+B.rows,A.cols+B.cols)
      for i in range(0,A.rows+B.rows):
            for j in range(0,A.cols+B.cols):
                  if(i<A.rows):
                        if(j<A.cols):
                              ma[i,j]=A[i,j]
                        else:
                              ma[i,j]=B[i,j-A.cols]
                  else:
                        if(j<A.cols):
                              ma[i,j]=C[i-A.rows,j]
                        else:
                              ma[i,j]=D[i-A.rows,j-A.cols]
                        
      return ma
      
def bubble_sort(nums):
    # We set swapped to True so the loop looks runs at least once
    swapped = True
    while swapped:
        swapped = False
        for i in range(len(nums) - 1):
            if nums[i] > nums[i + 1]:
                # Swap the elements
                nums[i], nums[i + 1] = nums[i + 1], nums[i]
                # Set the flag to True so we'll loop again
                swapped = True

def sci_formatting(number):
    a, b = '{:.4E}'.format(number).split('E')
    return '{:.5f}E{:+03d}'.format(float(a), int(b))



def Um(t12,t23,t13,delta,f1,f2):
      
      s12=math.sin(t12);
      s13=math.sin(t13)
      s23=math.sin(t23)
      c12 = math.sqrt(1-s12**2)
      c13 = math.sqrt(1-s13**2)
      c23 = math.sqrt(1-s23**2) 
      #return np.dot(np.matrix([[c12*c13, s12*c13,s13*e**(-1j*delta)],[-s12*c23-c12*s23*s13*e**(1j*delta), c12*c23-s12*s23*s13*e**(1j*delta),s23*c13],[s12*s23-c12*c23*s13*e**(1j*delta),-c12*s23-s12*c23*s13*e**(1j*delta),c23*c13]]),np.diag([1,e**(1j*f1),e**(1j*f2)]))
      return mp.matrix([[c12*c13, s12*c13,s13*e**(-1j*delta)],[-s12*c23-c12*s23*s13*e**(1j*delta), c12*c23-s12*s23*s13*e**(1j*delta),s23*c13],[s12*s23-c12*c23*s13*e**(1j*delta),-c12*s23-s12*c23*s13*e**(1j*delta),c23*c13]])*mp.diag([1,e**(1j*f1),e**(1j*f2)])

def Oc13(w13):
    return mp.matrix([[mp.cos(w13),0,mp.sin(w13)],[0,1,0],[-1*mp.sin(w13),0,mp.cos(w13)]])

def Oc12(w12):
    return mp.matrix([[mp.cos(w12),mp.sin(w12),0],[-1*mp.sin(w12),mp.cos(w12),0],[0,0,1]])

def Oc23(w23):
    return mp.matrix([[1,0,0],[0,mp.cos(w23),mp.sin(w23)],[0,-1*mp.sin(w23),mp.cos(w23)]])

def f(Mi,Mj):
      mp.dps=100
      x=(Mj*Mj)/(Mi*Mi)
      
      #mp.nprint(mp.chop(x),5)
      #mp.nprint(mp.chop(-1/(2*mp.sqrt(x))),5)
      #for very large x function goes to zero but numerically this log gives 0 and the computers numerical value of the function is wrong
      if(mp.log(1+1/x)==0.0):
          #function for very large x
          return (-1/(2*mp.sqrt(x)))
      else:
          return (mp.sqrt(x)*(1-(1+x)*mp.log(1+1/x)))

def g(Mi,Mj,l1,j):
      mp.dps=100
      x=(Mj*Mj)/(Mi*Mi)
      Gamma=(Mj*l1[j-1,j-1])/(8*pi)
      a=Gamma/Mi
      return((mp.sqrt(x)*(1-x))/((x-1)**2+a**2))

def gp(Mi,Mj,l1,j):
      mp.dps=100
      x=(Mj*Mj)/(Mi*Mi)        
      return(1/(mp.sqrt(x))*g(Mi,Mj,l1,j))



#VALORES EXPERIMENTAIS FIXOS
#em ev
evtogev=1e-9
v=246.202*1/evtogev
mH=125.10*1/evtogev
mZ=91.1876*1/evtogev
mt=173.8*1/evtogev


#from nufit v5 2020
t12min=radians(31.27)
t12max=radians(35.86)

t23min=radians(39.6)
t23max=radians(51.8)

t13min=radians(8.20)
t13max=radians(8.97)

d31min=2.431*10**(-3)
d31max=2.598*10**(-3)

d21min=6.82*10**(-5)
d21max=8.04*10**(-5)

deltamin=radians(107)
deltamax=radians(403)

Mmin=0
Mmax=25


it=10**(10);

