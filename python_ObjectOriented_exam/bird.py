# -*- coding: utf-8 -*-
"""
Created on Wed Apr  1 20:28:53 2020

@author: lara-
"""
from animal import Animal

#isto e' um tipo de class inheritance. o bird vai herdar os argumentos e metodos da classe animal. para isso o construtor do animal tem de ser chamado no construtor do bird
class Bird(Animal):
    #o * antes de um argumento indica que ele é iteravel. por exemplo, se tivessemos *arg significaria que a funciam recebia uma lista arg e se podia iterar nela.
    #o ** antes indica que o argumento é uma lista keyworded. podemos iterar nele mas so podemos aceder aos seus valores atraves da keyword
    #melhor explicaçao: https://www.geeksforgeeks.org/args-kwargs-python/
    def __init__(self,**kwargs):
        #construtor do animal a ser chamado
        Animal.__init__(self,**kwargs)
        if 'talk' in kwargs:
            self.talk = kwargs['talk']
        self.favorite_words=[]

    def add_favorite_words(self,word):
        if self.talk==True:
            self.favorite_words.append(word)
        else:
            name=self.get_name()
            print(name+" does not talk")

    def print_favorite_words(self):
        name=self.get_name()
        if (len(self.favorite_words)>0):
            print(name+"'s favorite words are:")
            for word in self.favorite_words:
                print(word)
        else:
            print(name+" has no favorite words yet")

    def human_years_bird(self):
        return self.human_years(8)
    
        
    def __str__(self):
        human_age=self.human_years_bird()
        return Animal.__str__(self)+", but in human years it has " + str(human_age)
        
