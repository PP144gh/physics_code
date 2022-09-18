# -*- coding: utf-8 -*-
"""
Created on Wed Apr  1 20:38:39 2020

@author: lara-
"""


class Animal:
      #o * antes de um argumento indica que ele é iteravel. por exemplo, se tivessemos *arg significaria que a funciam recebia uma lista arg e se podia iterar nela.
    #o ** antes indica que o argumento é uma lista keyworded. podemos iterar nele mas so podemos aceder aos seus valores atraves da keyword
    #melhor explicaçao: https://www.geeksforgeeks.org/args-kwargs-python/
    def __init__(self, **kwargs):
        if 'name' in kwargs:
            self.__name = kwargs['name']
        if 'age' in kwargs:
            self.__age = kwargs['age']
        if 'gender' in kwargs:
            self.__gender = kwargs['gender']
         
    def get_name(self):
        return self.__name
    def get_age(self):
        return self.__age
    def get_gender(self):
        return self.__gender
    
    def number_meals(self):
       return 3

    def human_years(self,conv):
        age=self.get_age()
        return age*conv

    def __str__(self):
        #como a variavel name de Animal e' privada, temos de usar a funcao get name para obter o nome
        name=self.get_name()
        age=self.get_age()
        gender=self.get_gender()
        text=name + " is "+str(age)+ " years old"
        return text

        

