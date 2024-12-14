#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Dec 14 14:26:13 2024

@author: aidan
"""


f = open("Pi - Dec - Chudnovsky.txt", 'r')
fstr = f.read()
f.close()

pi_file_name = input("File to check: ")
pifile = open(pi_file_name, 'r')
pistr = pifile.read()
pifile.close()

i = 0
while (pistr[i] == fstr[i]):
    i += 1

print(i)












