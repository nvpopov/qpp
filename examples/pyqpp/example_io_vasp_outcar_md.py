import sys
sys.path.append("../../build/modules")
import pyqpp 

outcar = open('/home/nvpopov/work/python-playground/potfit_md/mddata/laf3_v1.OUTCAR', 'r')

g_l, v_l, en_l, t_l = pyqpp.io.read_vasp_outcar_md(outcar.fileno())

print("len of g_l = {}".format(len(g_l)))
print("len of v_l = {}".format(len(v_l)))
print("len of en_l = {}".format(len(en_l)))
print("len of t_l = {}".format(len(t_l)))



 

