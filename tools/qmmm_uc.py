#!/usr/bin/python3
import sys
sys.path.append("../build/modules")
sys.path.append("../modules/pyqpp")

from qpp import *
from sys import stdin,stdout
from math import pi,sqrt,floor,atan2,cos,sin,acos
import numpy as np
import elpot
import autosymm

eps = 1e-3


def frac_dev(x):
    return x - floor(x)

# --------------------------------------------------------------

def transl_equiv(geom,cell,i,j):
    if geom.atom[i] != geom.atom[j]:
        return False
    f = cell.cart2frac(geom.pos(i)-geom.pos(j))
    return abs(frac_dev(f[0])) < eps and abs(frac_dev(f[1])) < eps and abs(frac_dev(f[2])) < eps

# --------------------------------------------------------------

def transl_equiv_shells(geom,cell,I,J):
    for i in I:
        for j in J:
            if transl_equiv(geom,cell,i,j):
                return True
    return False
# --------------------------------------------------------------

def euc_charges(uc, pg, R):
    # rule out cores
    cr_sh = .05
    cores = []
    for i in range(len(uc)):
        if uc.charge[i] > 0e0:
            for j in range(len(uc)):
                if uc.charge[j] < 0e0 and (uc.pos(i)-uc.pos(j)).norm() < cr_sh:
                    cores.append(i)
                    break
    for i in sorted(cores, reverse = True):
        uc.erase(i)
    # fill the sphere with points
    euc = xgeometry('d',periodic_cell_d(0),[('charge','real')])
    fill(euc,uc,sphere_shape_d(R))
    euc.sort(lambda g,i : g.pos(i).norm() )
    shells = []
    atnums = set(range(len(euc)))
    while len(atnums) > 0:
        i = atnums.pop()
        newshell = {i}
        for j in atnums:
            found = False
            for g in pg:
                if (euc.pos(j) - g*euc.pos(i)).norm()<eps:
                    found = True
                    break
            if found:
                newshell.add(j)
        for j in newshell:
            try:
                atnums.remove(j)
            except KeyError:
                pass
        shells.append(newshell)
    tshells = []
    shnums = set(range(len(shells)))
    while len(shnums)>0:
        i = shnums.pop()
        newtshell = {i}
        for j in shnums:
            if transl_equiv_shells(euc,uc.cell, shells[i], shells[j] ):
                newtshell.add(j)
        for j in newtshell:
            try:
                shnums.remove(j)
            except KeyError:
                pass
        tshells.append(newtshell)     
    return euc, shells, tshells

        
# --------------------------------------------------------------

def lattice_charges(uc,pg, R):
    pass

# --------------------------------------------------------------

def qmmm_unit_cell(uc, pg, cntr, R, Lmax, algo = 1):
    ''' uc (IN)   - unit cell
        pg (IN)   - point group
        cntr (IN) - the point selected as the center of extended unit cell
        R (IN)    - maximum radius of extended UC
        Lmax (IN) - maximum l to nullify multipole moments
        algo (IN) - the way to choose fictitious charges:
                    algo = 1 (default) - fictitious charges placed in the position of atoms (excluding cores)
                    algo = 2 - these charges are placed as points of periodic lattice
    '''

    # Symmetryze the unit cell with respect to given center and symmetry group
    
    quc = xgeometry('d',periodic_cell_d(0),[('charge','real')])
    for i in range(len(uc)):
        if uc.frac:
            uc.coord[i] -= uc.cell.cart2frac(cntr)
        else:
            uc.coord[i] -= cntr

    print("centered uc:")
    for i in range(len(uc)):
        print(uc[i])
            
    for i in range(uc.nat()):
        for j in range(len(pg)):
            r = pg[j]*uc.pos(i)
            quc.add([uc.atom[i], r[0], r[1], r[2], uc.charge[i]/len(pg)])

    # Merge coinciding atoms            
    treat_crowd(quc,4)

    print(uc.tol_geom)
    
    print('Symmetrized uc:\n')

    for i in range(3):
        print(uc.cell[i])
    
    for i in range(len(quc)):
        print(quc[i])
    
    # Select fictitious charges
    if algo == 1:
        fchrg, shells, sumzeros = euc_charges(uc,pg,R)
    elif algo == 2:
        fchrg, shells, sumzeros = lattice_charges(uc,pg,R)

    print('Shells:')
    print(shells)
    print(sumzeros)

    y = np.array([quc.charge[i] for i in range(len(quc))])
        
    for i in range(len(fchrg)):
        quc.insert(i,fchrg.atom[i],fchrg.coord[i])

    lam = 1./R**2

    s1 = [list(ss) for ss in shells]
    s2 = [list(ss) for ss in sumzeros]

    qshl = elpot.shellsolve(quc,y,lam,Lmax,s1,s2)

    qext = elpot.unroll(qshl,s1)

    for i in range(len(qext)):
        quc.charge[i] = qext[i]

    treat_crowd(quc,4)
        
    return quc

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
uc1 = xgeometry('d',periodic_cell_d(3),[('charge','real')])
uc1.cell = uc.cell
uc1.frac = uc.frac
for i in range(len(uc)):
    uc1.add(uc[i])

CG=array_fincryst_group_d()
#print(type(CG))
#print(type(uc))
#print(type(eps))
find_cryst_symm(CG,uc1,eps)

# Double the group
cell = CG[0].cell
cell_x8 = periodic_cell_d(cell[0]*2,cell[1]*2,cell[2]*2)
CG_x8 = array_fincryst_group_d("cellx8", bound_rotrans_d(vector3d(0,0,0),cell_x8))
for C in CG:
    CG_x8.add(bound_rotrans_d(C.T,C.R,cell_x8))

T=[bound_rotrans_d(v,cell_x8) for v in cell]
for t in T:
    CG_x8.add(t)

io.write_xyzq(1,uc)
input('Press enter')
    
S=[]
G=[]
#find_point_subgroups(G,S,CG_x8)
#find_point_subgroups(G,S,CG)
S,G = autosymm.find_point_subgroups(CG)

print('High symmetry sites in the unit cell:')
for i in range(len(S)):
<<<<<<< HEAD
    #p = S[i].point
    p = S[i].c
    f = uc.cell.cart2frac(p)
    #n = S[i].axis
    n = S[i].n
    print('\n{:d}) {} symmetry  center=({:10.5f},{:10.5f},{:10.5f}) '.format(i,point_group_symbol(G[i]),f[0],f[1],f[2]))
=======
    p = S[i].point
    #p = S[i].c
    f = uc.cell.cart2frac(p)
    n = S[i].axis
    #n = S[i].n
    Gi = array_point_group_d()
    for g in G[i]:
        Gi.add(g.R)
    print('\n{:d}) {} symmetry  center=({:10.5f},{:10.5f},{:10.5f}) '.format(i,point_group_symbol(Gi),f[0],f[1],f[2]))
>>>>>>> asm_uc2
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

L = Lmax
print("Final multipole moments:")
A = elpot.mkA(qmmm_uc,L)
Q = [[] for i in range(L+1)]
i=0
for l in range(L+1):
    for m in range(2*l+1):
        q = 0e0
        for j in range(len(qmmm_uc)):
            q += A[i,j]*qmmm_uc.charge[j]
        Q[l].append(q)
        i += 1
        
for l in range(L+1):
    print(l)
    print(Q[l])
