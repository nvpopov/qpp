#!/usr/bin/python3
import sys
sys.path.append("../../build/modules")
sys.path.append("../../modules/pyqpp")

from qpp import *
from sys import stdin,stdout
from math import pi,sqrt,floor,atan2,cos,sin,acos
import numpy as np

eps = 1e-3

def frac_dev(x):
    return x - floor(x+.5)


def transl_equiv(geom,cell,i,j):
    if geom.atom[i] != geom.atom[j]:
        return False
    f = cell.cart2frac(geom.pos(i)-geom.pos(j))
    return abs(frac_dev(f[0])) < eps and abs(frac_dev(f[1])) < eps and abs(frac_dev(f[2])) < eps


def transl_equiv_shells(geom,cell,I,J):
    for i in I:
        for j in J:
            if transl_equiv(geom,cell,i,j):
                return True
    return False

def lin_cond_minimum(A,B,b):
    '''Find the minimum of quadratic form:
             x*B*x = min
       with additional conditions:
             A*x = b
       the dimension of A is NxM, that of B is MxM,
       and M > N'''
    Binv = np.linalg.inv(B)
    BA = np.matmul(Binv,A.transpose())
    ABA = np.linalg.inv(np.matmul(A,BA))
    return np.matmul(BA,np.matmul(ABA,b))

def qmmm_unit_cell(uc,pg,cntr,R,Lmax):
    pass


''' -----------------  qmmm_uc -------------------
qmmm_uc - an utility to build Unit Cell for QMMM calculation, 
i.e. rearrange a unit cell in such a way that it becomes 
symmetric and its lowest electrostatic multipole moments are zero.
This utility is a part of QPP libraries
--------------------------------------------
'''

line = input('Provide the name of .xyz file: ')
f = open(line)
#uc = xgeometry('double',periodic_cell_d(3),charge='real')
uc = xgeometry('d',periodic_cell_d(3),[('charge','real')])
io.read_xyzq(f.fileno(),uc)
f.close()

line = input('Use fractional coordinates(y/n)? ')
uc.frac = ( line.lower()[0]=='y' )
eps = 0.001

bound_rotrans_d.tol_trans=1e-8
bound_rotrans_d.tol_rot=1e-8

io.write_xyzq(1,uc)

CG=array_fincryst_group_d()
print(type(CG))
print(type(uc))
print(type(eps))
find_cryst_symm(CG,uc,eps)

# Double the group
cell = CG[0].cell
cell_x8 = periodic_cell_d(cell[0]*2,cell[1]*2,cell[2]*2)
CG_x8 = array_fincryst_group_d("cellx8", bound_rotrans_d(vector3d(0,0,0),cell_x8))
for C in CG:
    CG_x8.add(bound_rotrans_d(C.T,C.R,cell_x8))

T=[bound_rotrans_d(v,cell_x8) for v in cell]
for t in T:
    CG_x8.add(t)

S=[]
G=[]
find_point_subgroups(G,S,CG_x8)

print('High symmetry sites in the unit cell:')
for i in range(len(S)):
    p = S[i].point
    f = uc.cell.cart2frac(p)
    n = S[i].axis
    print('\n{:d}) {} symmetry  center=({:10.5f},{:10.5f},{:10.5f}) '.format(i,point_group_symbol(G[i]),f[0],f[1],f[2]))
#    print('\nsite #{:d} symmetry= {} cartesian= {:10.5f} {:10.5f} {:10.5f} fractional= {:10.5f} {:10.5f} {:10.5f} '.format(i,point_group_symbol(G[i]), p[0],p[1],p[2],f[0],f[1],f[2]))
    print(' dim = {:d} axis=({:10.5f},{:10.5f},{:10.5f})'.format(S[i].dim, n[0], n[1], n[2]))
#    for X in G[i]:
#        a = analyze_transform(X)
#        print('    axis= ',a[0],' angle(deg)= ', a[1]*180/pi, ' inversion= ', a[2])
    print

line = input('Please select which of these sites should be the centre of UC: ')
i = int(line)
cntr = S[i].point
PG = G[i]

line = input('Please enter the radius of resulting unit cell: ')
R = float(line)

line = input('Please enter the maximum L for multipole moments to nullify: ')
Lmax = int(line)

qmmm_uc = qmmm_unit_cell(uc,PG,cntr,R,Lmax)

f=open('qmmm_uc.xyz','w')
io.write_xyzq(f.fileno(),qmmm_uc)
f.close()
