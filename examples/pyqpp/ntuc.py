#!/usr/bin/python3
import sys
sys.path.append("../../build/modules")
sys.path.append("../../modules/pyqpp")

from qpp import *
from sys import stdin,stdout
from math import pi


''' -----------------  ntuc -------------------
ntuc - an utility to NeuTralize Unite Cell, i.e. rearrange
a unite cell in such a way that it becomes symmetric and its
lowest electrostatic multipole moments are zero.
This utility is a part of QPP libraries
--------------------------------------------
'''

line = input('Provide the name of .xyz file: ')
f = open(line)
#uc = xgeometry('double',periodic_cell_d(3),charge='real')
uc = xgeometry_d(periodic_cell_d(3),[('charge','real')])
io.read_xyzq(f.fileno(),uc)
f.close()

line = input('Use fractional coordinates(y/n)? ')
uc.frac = ( line.lower()[0]=='y' )
eps = 0.001

io.write_xyzq(1,uc)

CG=array_fincryst_group_d()
print(type(CG))
print(type(uc))
print(type(eps))
find_cryst_symm(CG,uc,eps)

# Double the group
cell = CG[0].cell
cell_x8 = periodic_cell_d(cell[0]*2,cell[1]*2,cell[2]*2)
CG_x8 = array_fincryst_group_d(bound_rotrans_d(vector3d(0,0,0),cell_x8))
for C in CG:
    CG_x8.add(bound_rotrans_d(C.T,C.R,cell_x8))

T=[bound_rotrans_d(v,cell_x8) for v in cell]
for t in T:
    CG_x8.add(t)

s=[]
p=[]
d=[]
find_point_subgroups(s,p,d,CG_x8)

print('High symmetry sites in the unit cell:')
for i in xrange(len(p)):
    if d[i]>0:
        break
    f = uc.cell.cart2frac(p[i])
    print('site #{:d} cartesian= {:10.5f} {:10.5f} {:10.5f} fractional= {:10.5f} {:10.5f} {:10.5f} '.format(i,p[i][0],p[i][1],p[i][2],f[0],f[1],f[2]))
    for X in s[i]:
        a = analyze_transform(X)
        print('    axis= ',a[0],' angle(deg)= ', a[1]*180/pi, ' inversion= ', a[2])
    print

line = raw_input('Please select which of these sites should be the centre of UC: ')
i = int(line)
cntr = p[i]
PG = s[i]

line = raw_input('Please enter the radius of resulting unit cell: ')
R = float(line)
#if uc.frac:
#    uc.frac = False
#    for j in xrange(len(uc)):
#        uc.coord[j] = uc.cell.frac2cart(uc.coord[j])
#fill(nuc,uc,shp,8+1)

subl=[]
for i in xrange(len(uc)):
    if i in [k for k in s for s in subl]:
        continue
    s = []
    for j in xrange(len(uc)):
        already = False
        for op in CG:
            if already: break
            for I in index_range((-1,-1,-1),(1,1,1)):
                if (op*uc.pos(i)-uc.pos(j,I)).norm() < eps and uc.atom[i]==uc.atom[j]:
                    s.append(j)
                    already = True
                    break
    subl.append(s)

Q=[0e0]*len(subl)
for i in xrange(len(subl)):
    Q[i] = uc.charge[subl[i][0]]*len(subl[i])
    

#for i in xrange(len(uc)): print i,uc[i]
print('Found ',len(subl),' sublattices')
for i in xrange(len(subl)):
    print('sublattice #',i,' tot charge= ',Q[i],' atoms are ',subl[i])
    
nuc = xgeometry('double',periodic_cell_d(3),charge='real')
nuc.cell = uc.cell
shp = shape_sphere_d(R)
fidx = shp.fmax(uc.cell)
idx = index([0,0,0])
idx[0] = int(fidx[0])+1                
idx[1] = int(fidx[1])+1                
idx[2] = int(fidx[2])+1                

supshells = []
for s in xrange(len(subl)):
    shell = []
    for j in subl[s]:
        for I in index_range(index([0,0,0])-idx,idx):
            r = uc.pos(j,I) - cntr
            if r.norm() < R:
                shell.append(nuc.nat())
                nuc.add([uc.atom[j],r[0],r[1],r[2],uc.charge[j]])
    supshells.append(shell)

#print supshells

shells = []
for ss in supshells:
    s = []
    for at in ss:
        if not at in [at1 for sub in s for at1 in sub]:
            newsh = [at]
            for g in PG:
                r = g*nuc.pos(at)
                for at1 in xrange(len(nuc)):
                    if not at1 in newsh and (r-nuc.pos(at1)).norm()<eps and nuc.atom[at] == nuc.atom[at1]:
                        newsh.append(at1)
            s.append(newsh)
    shells.append(s)

print(shells)
f = open('ntuc.xyz','w')
atoms = [x[0].replace('_shl','').replace('_cor','') for x in nuc]
nuc.cell = periodic_cell_d(0)
for ss in shells:
    for s in ss:
        for at in range(len(nuc)):
            nuc.atom[at] = atoms[at]
        for at in s:
            nuc.atom[at] = 'Cl'
        write_xyz(f.fileno(),nuc)
f.close()
