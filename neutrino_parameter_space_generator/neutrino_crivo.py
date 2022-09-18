from neutrino_defs import *



#filters parameter space 

file = open("na.txt","r")
file2 = open("nac.txt","a")

ct=0
for linesl in file:
      plist=[]
      lines=linesl.split()
      m1ev=float(lines[0])
      d31=float(lines[1])
      d21=float(lines[2])
      M1=float(lines[3])
      M2=float(lines[4])
      M3=float(lines[5])
      t12=float(lines[6])
      t13=float(lines[7])
      t23=float(lines[8])
      r12=float(lines[9])
      r13=float(lines[10])
      r23=float(lines[11])
      f13=float(lines[12])
      f12=float(lines[13])
      f23=float(lines[14])
      delta=float(lines[15])
      dm1=float(lines[16])
      dm2=float(lines[17])
      sign=float(lines[18])
      plist.append(m1ev)
      plist.append(d31)
      plist.append(d21)
      plist.append(M1)
      plist.append(M2)
      plist.append(M3)
      plist.append(t12)
      plist.append(t13)
      plist.append(t23)
      plist.append(r12)
      plist.append(r13)
      plist.append(r23)
      plist.append(f13)
      plist.append(f12)
      plist.append(f23)
      plist.append(delta)
      plist.append(dm1)
      plist.append(dm2)
      plist.append(sign)
      #print(plist)


      #calculo de matrizes do modelo
      K, V, H, H2, X, m1, m2, m3, M1, M2, M3, m, M, D, d, etal, Kl, Xl, dl, Dl, Rl, Zl, R, Z, Oc, eta, deltaML, Mcaloop, VZ, ep, ep1, ep2, ep3, Nnu, zd, d31l, d21l, mdagm=calc(plist,v,mH,mZ)
      #testes do gerador
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
                                                                                                                                          file.write("%.10f" %dm2 + "\n")
      '''
      if (14>10):
            print("teste dms")
            if(d21l>d21min and d21l<d21max):
                  if(d31l>d31min and d31l<d31max):
                        print("PASSEIIIIIIIIIIIIIIII")
                        file2.write("%.10f" %m1ev + " ")
                        file2.write("%.10f" %d31 + " ")
                        file2.write("%.10f" %d21 + " ")
                        file2.write("%.10f" %M1 + " ")
                        file2.write("%.10f" %M2 + " ")
                        file2.write("%.10f" %M3 + " ")
                        file2.write("%.10f" %t12 + " ")
                        file2.write("%.10f" %t13 + " ")
                        file2.write("%.10f" %t23 + " ")
                        file2.write("%.10f" %r12 + " ")
                        file2.write("%.10f" %r13 + " ")
                        file2.write("%.10f" %r23 + " ")
                        file2.write("%.10f" %f13 + " ")
                        file2.write("%.10f" %f12 + " ")
                        file2.write("%.10f" %f23 + " ")
                        file2.write("%.10f" %delta + " ")
                        file2.write("%.10f" %dm1 + " ")
                        file2.write("%.10f" %dm2 + " ")
                        file2.write("%.10f" %sign + "\n")
                  
            
      

file.close()
file2.close()
  
