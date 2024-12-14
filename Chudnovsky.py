# -*- coding: utf-8 -*-
"""
Created on Sat Dec 14 01:51:23 2024

@author: Aidan
"""

import time
import decimal as dec

dec.getcontext().prec = 1000
a = 545140134
b = 13591409
c = 640320

def factorial(n):
    output = dec.Decimal(1)
    for k in range(2, n + 1):
        output *= k
        
    return output


def compute_term(k):
    sign = (k % 2) * -2 + 1
    
    #For the time being, just calculate each factorial separately
    k_fact = factorial(k)
    three_k_fact = factorial(3*k)
    six_k_fact = factorial(6*k)

    linear_term = dec.Decimal(a) * k + b
    m = dec.Decimal(c)**dec.Decimal(3*k + 1.5)
    
    
    output = six_k_fact / three_k_fact
    output = output * linear_term / (k_fact**3)
    output = sign * output / m
    return output


t0 = time.time()
series = 0
N = 80

zeroth_term = compute_term(0)



for k in range(N):
    series += compute_term(k)

series *= 12
pi = dec.Decimal(1) / series

print(pi)
print("Time: %.3f" %(time.time() - t0))

print("Checking digits")


f = open("Pi-reference.txt", 'r')
fstr = f.read()
f.close()


pistr = str(pi)
i = 0
while (pistr[i] == fstr[i]):
    i += 1

print(i)






























