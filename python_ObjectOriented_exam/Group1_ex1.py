# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
#Exercise 1

def temperature_converter(temperature_C, units):
    if temperature_C.replace('.','',1).isdigit(): 
        if (units == "F" or units == "f"):
            answer = (float(temperature_C)*9/5)+32
            print("The temperature is: ", float(answer), "F")
        elif (units == "K" or units == "k"):
            answer = float(temperature_C)+273.15
            print("The temperature is: ", float(answer), "K")
        else:
            print("Invalid Unit")
    else:
        print("Temperature is not a number")
        
     
temperature_value = input("Insert the temperature you want to convert: ")
temperature_units = input("What are the units?")

temperature_converter(temperature_value, temperature_units)

