from qpp import *

def read_contcar(filename):
    f = open(filename,'r')
    f.next()
    scale = float(f.next())
    cl = periodic_cell_d(3)
    for i in xrange(3):
       cl[i] = vector3d([ float(c) for c in  f.next().split() ])

    elems = f.next().split()
    natoms = [int(c) for c in f.next().split()]
    line = f.next()
    dynamic_flag = False
    if 'Selective' in line:
        dynamic_flag = True
        line = f.next()
    geom = geometry_d(cl)
    
    if 'Kart' in line or 'Cart' in line or 'kart' in line or 'cart' in line:
        for (i,n) in enumerate(natoms):
            for j in xrange(n):
                if not dynamic_flag:
                    geom.add ( elems[i], *[ float(c) for c in  f.next().split()[0:3] ] )
    if 'direct' in line or 'Direct' in line:
        geom.frac= True
        for (i,n) in enumerate(natoms):
            for j in range(n):
                if not dynamic_flag:
                    geom.add ( elems[i], *[ float(c) for c in  f.next().split()[0:3] ] )

    return geom

