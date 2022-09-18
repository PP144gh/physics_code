#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Mar 29 23:00:58 2020

@exercise: GROUP 3: Objects
"""

from animal import Animal
from bird import Bird
from dog import Dog


piupiu = Bird(name="piupiu", age=3, gender="male", talk=True)
piupiu.add_favorite_words("what's up doc?")
piupiu.print_favorite_words()
print(piupiu)

galaro = Bird(name="galaro", age=6, gender="male", talk=False)
galaro.add_favorite_words("co-co-ro-co-co")
galaro.print_favorite_words()
print(galaro)

laika = Dog(name="laika", age=6, gender="female")
print(laika)


bobi = Dog(name="bobi", age=2, gender="male")
print(bobi)
