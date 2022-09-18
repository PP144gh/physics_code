from neutrino_defs import *

file=open("na.txt","a")


for i in range(0,it):

      

      #geracao aleatoria
      plist=[]

      
      
      m1ev=random.uniform(1,9)*10**(random.uniform(-7,-2));
      plist.append(m1ev)
      d31=random.uniform(d31min*10**(3),d31max*10**(3))*10**(-3);
      plist.append(d31)
      d21= random.uniform(d21min*10**(5),d21max*10**(5))*10**(-5);
      plist.append(d21)
      #M generation
      #M1t=random.uniform(1,9)*10**random.uniform(Mmin,Mmax)
      #M2t=random.uniform(1,9)*10**random.uniform(Mmin,Mmax)
      #M3t=random.uniform(1,9)*10**random.uniform(Mmin,Mmax)
      M1t=10**18
      M2t=10**20
      M3t=10**22
      #print("bb")
      #print(sci_formatting(M1t))
      #print(sci_formatting(M2t))
      #print(sci_formatting(M3t))
      Mlist=[]
      Mlist.append(M1t)
      Mlist.append(M2t)
      Mlist.append(M3t)
      bubble_sort(Mlist)
      #print("aaaaa")
      #print(sci_formatting(Mlist[0]))
      #print(sci_formatting(Mlist[1]))
      #print(sci_formatting(Mlist[2]))
      M1=Mlist[0];
      plist.append(M1)
      M2=Mlist[1];
      plist.append(M2)
      M3=Mlist[2];
      plist.append(M3)
      t12=random.uniform(t12min,t12max);
      plist.append(t12)
      t13=random.uniform(t13min,t13max);
      plist.append(t13)
      t23=random.uniform(t23min,t23max);
      plist.append(t23)
      r12=random.uniform(1,9)**(random.uniform(-5,1))
      plist.append(r12)
      r13=random.uniform(1,9)**(random.uniform(-5,1))
      plist.append(r13)
      r23=random.uniform(1,9)**(random.uniform(-5,1))
      plist.append(r23)
      f13=random.uniform(0,2*pi);
      plist.append(f13)
      f12=random.uniform(0,2*pi);
      plist.append(f12)
      f23=random.uniform(0,2*pi);
      plist.append(f23)
      delta=random.uniform(deltamin,deltamax);
      delta=delta%(2*pi)
      plist.append(delta)
      dm1=random.uniform(0,2*pi);
      plist.append(dm1)
      dm2=random.uniform(0,2*pi);
      plist.append(dm2)

      sign=random.randint(0,1)
      if (sign==0):
            sign=-1.0;
      else:
            sign=float(1.0)

      plist.append(sign)
      

      #calculo de matrizes do modelo
      K, V, H, H2, X, m1, m2, m3, M1, M2, M3, m, M, D, d, etal, Kl, Xl, dl, Dl, Rl, Zl, R, Z, Oc, eta, deltaML, Mcaloop, VZ, ep, ep1, ep2, ep3, Nnu, zd, d31l, d21l, mdagm=calc(plist,v,mH,mZ)



      '''
      #minimizacao
      #print(abs(K))
      print("loss")
      print(L(plist))
      res=minimize(L,plist,method='Nelder-Mead', options={'disp': True})
      plist2=res["x"]
      K, V, H, H2, X, m1, m2, m3, M1, M2, M3, m, M, D, d, etal, Kl, Xl, dl, Dl, Rl, Zl=calc(plist2,v,mH,mZ)
      print("loss_min")
      print(L(plist2))
      '''



      if(14>10):
            #teste perturb
            print("teste pertub")
            if(abs(m[0,0])<=4*pi*mt):
                  if(abs(m[0,1])<=4*pi*mt):
                        if(abs(m[0,2])<=4*pi*mt):
                              if(abs(m[1,0])<=4*pi*mt):
                                    if(abs(m[1,1])<=4*pi*mt):
                                          if(abs(m[1,2])<=4*pi*mt):
                                                if(abs(m[2,0])<=4*pi*mt):
                                                      if(abs(m[2,1])<=4*pi*mt):
                                                            if(abs(m[2,2])<=4*pi*mt):
                                                                  #teste dev unit
                                                                  print("teste dev unit")
                                                                  if(abs(2*etal[0,0])<=2.5**(-3)):
                                                                        if(abs(2*etal[0,1])<=2.5**(-3)):
                                                                              if(abs(2*etal[0,0])<=2.4**(-3)):
                                                                                    if(abs(2*etal[0,2])<=2.7**(-3)):
                                                                                          if(abs(2*etal[1,0])<=2.4**(-3)):
                                                                                                if(abs(2*etal[1,1])<=4**(-4)):
                                                                                                      if(abs(2*etal[1,2])<=1.2**(-3)):
                                                                                                            if(abs(2*etal[2,0])<=2.7**(-3)):
                                                                                                                  if(abs(2*etal[2,1])<=1.2**(-3)):
                                                                                                                        if(abs(2*etal[2,2])<=5.6**(-3)):
                                                                                                                              #teste apos loop corrections respeita deltam's
                                                                                                                              print("teste dms")
                                                                                                                              if(d21l>d21min and d21l<d21max):
                                                                                                                                    if(d31l>d31min and d31l<d31max):
                                                                                                                                          print("PASSEIIIIIIIIIIIIIIII")
                                                                                                                                          file.write("%.10f" %m1ev + " ")
                                                                                                                                          file.write("%.10f" %d31 + " ")
                                                                                                                                          file.write("%.10f" %d21 + " ")
                                                                                                                                          file.write("%.10f" %M1 + " ")
                                                                                                                                          file.write("%.10f" %M2 + " ")
                                                                                                                                          file.write("%.10f" %M3 + " ")
                                                                                                                                          file.write("%.10f" %t12 + " ")
                                                                                                                                          file.write("%.10f" %t13 + " ")
                                                                                                                                          file.write("%.10f" %t23 + " ")
                                                                                                                                          file.write("%.10f" %r12 + " ")
                                                                                                                                          file.write("%.10f" %r13 + " ")
                                                                                                                                          file.write("%.10f" %r23 + " ")
                                                                                                                                          file.write("%.10f" %f13 + " ")
                                                                                                                                          file.write("%.10f" %f12 + " ")
                                                                                                                                          file.write("%.10f" %f23 + " ")
                                                                                                                                          file.write("%.10f" %delta + " ")
                                                                                                                                          file.write("%.10f" %dm1 + " ")
                                                                                                                                          file.write("%.10f" %dm2 + " ")
                                                                                                                                          file.write("%.10f" %sign + "\n")
                  
      


file.close()
      

  
