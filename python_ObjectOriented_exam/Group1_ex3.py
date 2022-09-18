# -*- coding: utf-8 -*-
"""
Created on Wed Apr  1 18:54:23 2020

@author: lara-
"""

def square(side_size):
    if side_size < 2:
        print("Minimal square size is 2.")
    else:
        for i in range (0,side_size):
            if i>0:
                print()
            for a in range(0,side_size):
                print("*", end='')
                if (i==side_size-1 and a==i):
                    print()
            
            
side = int(input("insert the square size: "))
square(side)

