from qpp import *

# ----------------------------------------------------------

def read_xyz(geom,filename):
    f = open(filename,"r")
    nat = int(f.readline().split()[0])
    s=f.readline().split()
    if geom.dim == 3:
        if len(s) == 9:
            for i in range(3):
                for j in range(3):
                    geom.cell[i,j] = float(s[3*i+j])
        elif len(s) == 6:
            geom.cell = type(geom.cell)(float(s[0]),float(s[1]),float(s[2]),float(s[3]),float(s[4]),float(s[5]))
        
    for i in xrange(nat):
        s=f.readline().split()
        geom.add(s[0],float(s[1]),float(s[2]),float(s[3]))

# ----------------------------------------------------------

def read_xyz(geom,filename):
    f = open(filename,"r")
    nat = int(f.readline().split()[0])
    s=f.readline().split()
    if geom.dim == 3:
        if len(s) == 9:
            for i in range(3):
                for j in range(3):
                    geom.cell[i,j] = float(s[3*i+j])
        elif len(s) == 6:
            geom.cell = type(geom.cell)(float(s[0]),float(s[1]),float(s[2]),float(s[3]),float(s[4]),float(s[5]))
        
    for i in xrange(nat):
        s=f.readline().split()
        geom.add(s[0],float(s[1]),float(s[2]),float(s[3]))
        geom.charge[-1] = float(s[4])
    
# ----------------------------------------------------------

def write_xyz(geom,filename):    
    f = open(filename,"w")
    f.write("{0:d}\n\n".format(geom.nat()))
    for i in xrange(geom.nat()):
        
        f.write("{0:5s}{1:15.8f}{2:15.8f}{3:15.8f}\n".format(geom.atom[i],geom.coord[i,0],geom.coord[i,1],geom.coord[i,2]))
    f.close()


# ----------------------------------------------------------

def write_xyzq(geom,filename):    
    f = open(filename,"w")
    f.write("{0:d}\n\n".format(geom.nat()))
    for i in xrange(geom.nat()):
        
        f.write("{0:5s}{1:15.8f}{2:15.8f}{3:15.8f}{3:15.8f}\n".format(geom.atom[i],geom.coord[i,0],geom.coord[i,1],geom.coord[i,2],geom.charge[i]))
    f.close()

 
