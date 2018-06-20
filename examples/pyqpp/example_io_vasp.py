import sys
sys.path.append("../../build/modules")
import pyqpp 

file_vasp_poscar = open('../io/vasp_data/La44F148.POSCAR', 'r')
g1 = pyqpp.geometry_d(3)
pyqpp.read_vasp_poscar(file_vasp_poscar.fileno(), g1)

print("Number of atoms = {0}".format(g1.nat()))
print(" a = {0}, b = {1}, c = {2} ".format(g1.cell[0], g1.cell[1], g1.cell[2]))
print("Number of atom types = {0}".format(g1.n_types()))
for i in range(0, g1.nat()):
	print(g1[i])



 

