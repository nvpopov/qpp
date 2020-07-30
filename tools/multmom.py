#!/usr/bin/python3

from qpp import *
import elpot

line = input('Provide the name of .xyz file: ')
f = open(line)
uc = xgeometry('d',periodic_cell_d(3),[('charge','real')])
io.read_xyzq(f.fileno(),uc)
f.close()

line = input('Use fractional coordinates(y/n)? ')
uc.frac = ( line.lower()[0]=='y' )

line = input('Please enter the maximum L for multipole moments calculation ')
L = int(line)

A = elpot.mkA(uc,L)
Q = [[] for i in range(L+1)]
i=0
for l in range(L+1):
    for m in range(2*l+1):
        q = 0e0
        for j in range(len(uc)):
            q += A[i,j]*uc.charge[j]
        Q[l].append(q)
        i += 1
        
for l in range(L+1):
    print(l)
    print(Q[l])
