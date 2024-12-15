# -*- coding: utf-8 -*-
"""
Created on Sat Dec 14 01:51:23 2024

@author: Aidan
"""

import time
import decimal

t0 = time.time()
decimal.getcontext().prec = 100000
a = decimal.Decimal(545140134)
b = decimal.Decimal(13591409)
c = decimal.Decimal(640320)


def binary_split(a, b):
    if b == a + 1:
        Pab = -(6*a - 5)*(2*a - 1)*(6*a - 1)
        Qab = 10939058860032000 * a**3
        Rab = Pab * (545140134*a + 13591409)
    else:
        m = (a + b) // 2
        Pam, Qam, Ram = binary_split(a, m)
        Pmb, Qmb, Rmb = binary_split(m, b)
        
        Pab = Pam * Pmb
        Qab = Qam * Qmb
        Rab = Qmb * Ram + Pam * Rmb
    return Pab, Qab, Rab


def chudnovsky(n):
    P1n, Q1n, R1n = binary_split(1, n)
    return (426880 * decimal.Decimal(10005).sqrt() * Q1n) / (13591409*Q1n + R1n)

pi = chudnovsky(5000)

#print(pi)
print("Time: %.3f" %(time.time() - t0))
print("Checking digits")


f = open("Pi-Dec-100k.txt", 'r')
fstr = f.read()
f.close()


pistr = str(pi)
i = 0
while (pistr[i] == fstr[i]):
    i += 1

print(i)






























