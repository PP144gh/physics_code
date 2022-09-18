# -*- coding: utf-8 -*-
"""
Created on Wed Apr  1 20:29:05 2020

@author: lara-
"""

from animal import Animal

#isto e' um tipo de class inheritance. o bird vai herdar os argumentos e metodos da classe animal. para isso o construtor do animal tem de ser chamado no construtor do bird
class Dog(Animal):
    #o * antes de um argumento indica que ele é iteravel. por exemplo, se tivessemos *arg significaria que a funciam recebia uma lista arg e se podia iterar nela.
    #o ** antes indica que o argumento é uma lista keyworded. podemos iterar nele mas so podemos aceder aos seus valores atraves da keyword
    #melhor explicaçao: https://www.geeksforgeeks.org/args-kwargs-python/
    def __init__(self,**kwargs):
        #construtor do animal a ser chamado
        Animal.__init__(self,**kwargs)

    def human_years_dog(self):
        return self.human_years(5)
    
    def number_meals_dog(self):
        age=self.get_age()
        if (age <=3):
            return 5
        elif (age >3 and age<=6):
            return 4
        else:
            return 3

        
    def __str__(self):
        #como a variavel name de Animal e' privada, temos de usar a funcao get name para obter o nome
        name=self.get_name()
        food=self.number_meals_dog()
        human_age=self.human_years_dog()
        return Animal.__str__(self)+", but in human years it has " + str(human_age) +"\n"+name+" also needs to eat "+str(food)+" times per day!"
        
