#!/usr/bin/python3
import sys
sys.path.append("../../build/modules")
sys.path.append("../../modules/pyqpp")

from qpp import *
from sys import stdin,stdout
from math import pi


def qmmm_unit_cell(uc,pg,cntr,R):

    quc = xgeometry('d',periodic_cell_d(0),[('charge','real')])
    for i in range(len(uc)):
        if uc.frac:
            uc.coord[i] -= uc.cell.cart2frac(cntr)
        else:
            uc.coord[i] -= cntr
    fill(quc,uc,sphere_shape_d(R))

    G = point_group_d([])
    generator_form(G,pg)
    quc_unq = geometry_pgd(G)
    nimage = []
    unique(nimage,quc_unq, quc)

    for x in quc_unq: print(x)
    print(nimage)
    
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

qmmm_uc = qmmm_unit_cell(uc,PG,cntr,R)

f=open('qmmm_uc.xyz','w')
io.write_xyzq(f.fileno(),qmmm_uc)
f.close()
