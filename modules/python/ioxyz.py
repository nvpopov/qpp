from qpp import *

def read_xyz(geom,filename):
    f = open(filename,"r")
    nat = int(f.readline().split()[0])
    s=f.readline().split()
    if geom.dim == 3:
        if len(s) == 9:
            for i in range(3):
                for j in range(3):
                    geom.cell[i,j] = float(s[3*i+j])
    

def write_xyz(geom,filename):
    
    f = open(filename,"w")
    
