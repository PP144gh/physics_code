import numpy as np
from numpy import linalg as LA
import math
from math import pi
from math import e
import matplotlib.pyplot as plt
from pylab import scatter
import pylab
import csv
from random import uniform
from mpmath import *
from matplotlib import ticker

mp.dps=200

                  


listx=[]

listy=[]

listx2=[]

listy2=[]



t=0
it=0
zlist=[]

with open('b2.txt','r') as csvfile:
        plots = csv.reader(csvfile, delimiter=' ')
        for row in plots:
                #MUDAR ROWS
                print(row[3])
                print(row[9])
                if(float(row[10])==0):
                        listx.append(float(row[3]))
                        listy.append(float(row[9]))
                if(float(row[10])==1):
                        listx2.append(float(row[3]))
                        listy2.append(float(row[9]))
                      
                      
        
                        

#print(listx)

fig = plt.figure()
fig, ax =plt.subplots()


#plt.yscale('log')
#plt.xscale('log')
plt.xlim([float(0.039), float(0.041)])
plt.ylim([float(0.0),float(2*pi)])
pl1=plt.scatter(listx, listy, s=10, c='r', marker="+")
pl2=plt.scatter(listx2, listy2, s=10, c='b', marker="+")
pl1.set_alpha(1)
pl2.set_alpha(1)
listpl=[]
#MUDAR NOME
plt.title((r'$Correlation~12$'))
#plt.axhline(y=-3.25, color='lawngreen', linestyle='-')
#MUDAR NOME
plt.xlabel(r'$\theta_{23}$')
plt.ylabel(r'$\delta_{24}$')
#plt.axis('tight')

lgnd=plt.legend(loc='upper right',prop={'size':10},framealpha=1,fancybox=True)
for handle in lgnd.legendHandles:
    handle.set_sizes([50.0])

#plt.text(10**(-57),10**(30),"Forbidden Zone",fontsize='30',color='yellow')
#plt.text(10**(-78),10**(0),r"Nearly Massless $m_1$",fontsize='30',color='royalblue')



#MUDAR NOME
fig.savefig("plot_12.jpg",quality=100)
plt.show()

