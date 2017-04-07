from qpp_cpp import *
from symm import symm_add, build_multab, symm_order, symm_invert, is_symm_group, \
    is_normal_subgroup, mul_groups, idx2grp, grp2idx, abelian_sub, find_generators

vector_types = [vector3f, vector3d]

cell_types = [periodic_cell_f, periodic_cell_d]

# ------------------------------------------

def real_type(s):
    if s.lower() in ["f","float","f32","float32"]:
        return 0
    elif s.lower() in ["d","double","f64","float64"]:
        return 1
    else:
        raise TypeError("qpp: unknown type name for real number: " + s)

# ------------------------------------------

def index_empty(d):
    if type(d) is int:
        return index([0]*d)
    else: raise TypeError()

#---------------------------------------------------------

def vector_copy(x):
    if type(x) in vector_types:
        return type(x)(x)
    else:
        raise TypeError()

def vector_from_list(x,real="d"):
    r = real_type(real)
    if type(x) is list:
        return vector_types[r](x)
    else:
        raise TypeError()

def vector_from_tuple(x,real="d"):
    r = real_type(real)
    if type(x) is tuple:
        return vector_types[r](list(x))
    else:
        raise TypeError()

def vector_from_xyz(x,y,z,real="d"):
    r = real_type(real)
    return vector_types[r](x,y,z)

def vector(*args,**kwds):
    return overloader([vector_copy,vector_from_list,vector_from_tuple,vector_from_xyz],args,kwds, \
                      "qpp: invalid arguments of qpp.vector call"+str(args)+str(kwds))

#---------------------------------------------------------

def cell_empty(dim,real="d"):
    if type(real) is str:
        r = real_type(real)
        return cell_types[r][dim]()
    else:
        raise TypeError()

def cell_copy(x):
    if type(x) in cell_types:
        return type(x)(x)
    else:
        raise TypeError()

def cell_from_1vectors(a):
    if type(a) in vector_types:
        r = vector_types.index(type(a))
        return cell_types[r](a)
    else:
        raise TypeError()

def cell_from_2vectors(a,b):
    if type(a) in vector_types and type(b) in vector_types:
        r = vector_types.index(type(a))
        return cell_types[r](a,b)
    else:
        raise TypeError()

def cell_from_3vectors(a,b,c):
    if type(a) in vector_types and type(b) in vector_types and type(c) in vector_types :
        r = vector_types.index(type(a))
        return cell_types[r](a,b,c)
    else:
        raise TypeError()

def periodic_cell(*args,**kwds):
    return overloader([cell_empty, cell_copy, cell_from_1vectors, cell_from_2vectors, cell_from_3vectors], \
                      args, kwds, \
                      "qpp: invalid arguments of qpp.cell call"+str(args)+str(kwds))

