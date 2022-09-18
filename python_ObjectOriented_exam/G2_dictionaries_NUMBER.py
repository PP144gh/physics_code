#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Mar 29 09:51:13 2020

@author: Pedro Garcia
@exercise: GROUP 2: Lists and Dictionaries 
"""
import random 
character_list = [
                {
                "name":"Thanos",
                "avenger":False,
                "powers":{
                            "strength":100,
                            "intelligence": 80,
                            "magic":100,
                            "humor": 10
                        }
                
                },
                {
                "name":"Iron Man",
                "avenger":True,
                "powers":{
                            "strength":80,
                            "intelligence": 100,
                            "magic":0,
                            "humor": 90
                        }
                
                },
                {
                "name":"Captain America",
                "avenger":True,
                "powers":{
                            "strength":80,
                            "intelligence": 90,
                            "magic":0,
                            "humor": 50
                        }
                
                },
                {
                "name":"Hulk",
                "avenger":True,
                "powers":{
                            "strength":95,
                            "intelligence": 10,
                            "magic":10,
                            "humor": 70,
                        }
                
                },
                {
                "name":"Loki",
                "avenger":False,
                "powers":{
                            "strength":70,
                            "intelligence": 90,
                            "magic":90,
                            "humor": 80
                        }
                },
        ]

    
def print_character(char):
   if char["avenger"] == True:
       print("Avenger",char["name"])
   else: 
       print("Villain", char["name"])
   print("strength",char["powers"]["strength"])
   print("intelligence",char["powers"]["intelligence"])
   print("magic",char["powers"]["magic"])
   print("humor",char["powers"]["humor"])
   
     
           
#TEST
#print_character(character_list[1])


def print_characters(filt):
    for char in character_list:
        if filt=="all":
            print_character(char)
        elif filt =="avengers":
            if char["avenger"]==True:
                print_character(char)
        elif filt =="villains":
            if char["avenger"]==False:
                print_character(char)
        else:
            print ("Wrong argument")
            
        
#TEST           
#print_characters("avengers")

 
def add_character(name,bol):
    control=0
    for char in character_list:
        if char["name"]==name:
            control=1 
    if control==0:
            character_list.append({
                "name":name,
                "avenger":bol,
                "powers":{
                            "strength":random.randint(1,100),
                            "intelligence": random.randint(1,100),
                            "magic":random.randint(1,100),
                            "humor": random.randint(1,100)
                        }
                
                })
            print("Character",name, "created with sucess")
    else:
        print ("Character", name, "already exists")
    
 
#demo data to add new characters to your list   
add_character("Ant-man", True)
add_character("Ant-man", True)
add_character("Hawkeye", True)
add_character("Red Skull", False)
add_character("Ultron", False)
#TEST
print_characters("all")


def remove_not_funny(humor_d):
    for char in character_list:
        if char["powers"]["humor"]<=humor_d:
            character_list.remove(char)
#TEST
#remove_not_funny(65)
#print_characters("all")

def battle():
    leng=len(character_list)
    r1=random.randint(0,leng-1)
    r2=random.randint(0,leng-1)
    while (r2==r1):
        r2=random.randint(0,leng-1)
    
    print("A new battle is about to begin between...")
    print("player 1:",character_list[r1]["name"])
    print("Vs")
    print("player 2:",character_list[r2]["name"])
    list_powers=["strength","intelligence","magic","humor"]
    print("The selected power is...")
    choice=random.choice(list_powers)
    print(choice)
    print(character_list[r1]["name"], "is", character_list[r1]["powers"][choice])
    print(character_list[r2]["name"], "is", character_list[r2]["powers"][choice])
    print("THE WINNER IS...")
    if ((character_list[r1]["powers"][choice])/(character_list[r2]["powers"][choice])>1):
        print (character_list[r1]["name"],"!!!")
    elif((character_list[r1]["powers"][choice])/(character_list[r2]["powers"][choice])<1):
       print (character_list[r2]["name"],"!!!")
    else:
        print ("It's a tie!!")



#TEST
battle()
    
#print(character_list[2]["powers"][0])
    
