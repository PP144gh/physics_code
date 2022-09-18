# -*- coding: utf-8 -*-
"""
Created on Wed Apr  1 17:54:36 2020

@author: lara-
"""

#Exercise 2
import keyword
def postal_code_validator(postal):
    if len(postal) == 8:
        i=0
        control = 0
        while (i < len(postal)):
            if i < 4:
                if postal[i].isnumeric() == False:
                    #print("a")
                    #print(postal[i])
                    #print(postal[i].isnumeric())
                    print("Postal Code must have a hyphen separating the number in the fifth position") 
                    print("The first four elements in postal code must be digits.")
                    print("The last 3 elements in postal code must be digits.")
                    control = 1
                    break
                    
            elif i == 4:
                if postal[i] != "-":
                    #print("b")
                    print("Postal Code must have a hyphen separating the number in the fifth position") 
                    print("The first four elements in postal code must be digits.")
                    print("The last 3 elements in postal code must be digits.")
                    control = 1
                    break
            else:
                if postal[i].isnumeric() == False:
                    #print("c")
                    print("Postal Code must have a hyphen separating the number in the fifth position") 
                    print("The first four elements in postal code must be digits.")
                    print("The last 3 elements in postal code must be digits.")
                    control = 1
                    break
            i += 1    
        if control == 0:
            print("Postal Code", postal, "is ok")
            
    else:
        print("Postal Code length is wrong.")  
                                      
               

zip_code = input("Postal Code: ")
postal_code_validator(zip_code)