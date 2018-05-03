from qpp import *
from symm import abelian_sub, build_multab, complete_subgroup

def is_pure_translation(A):
    return A.R.norm() < A.tol_rot and A.T.norm() < A.tol_transl

def has_pure_translation(G):
    E = type(G[0].R)(1)
    for g1 in G:
        for g2 in G:
            if (g1.R*g2.R-E).norm() <= g1.tol_rot and \
               (g1.R*g2.T+g1.T).norm() > g1.tol_trans:
                return True
    return False

def reduce_translations(G):
    for j in xrange(len(G)):
        f = G[j].cell.cart2frac(G[j].T)
        for i in range(3):
            if (f[i] > 1.0-G[j].tol_trans):
                f[i] = f[i] - 1
        G[j].T = G[j].cell.frac2cart(f)
 
# ----------------------------------------------------------

class linear3d:
    dim = 0

    def __init__(self,dim1,c1,n1=vector3d(0,0,1)):
        self.dim = dim1
        self.c = c1
        self.n = n1/n1.norm()

    def __str__(self):
        if self.dim==0:
            return 'point '+str(self.c)
        elif self.dim==1:
            return 'line '+str(self.c)+str(self.n)
        elif self.dim==2:
            return 'plane'+str(self.c)+str(self.n)
        elif self.dim==-1:
            return 'empty set'
        elif self.dim==3:
            return 'entire space'

    def __contains__(self,x):
        if self.dim == -1:
            return False
        elif self.dim == 0:
            return (self.c-x).norm() < self.c.tol_equiv
        elif self.dim == 1:
            y = x - self.c
            y = y - self.n*scal(y,self.n)
            return y.norm() < self.c.tol_equiv
        elif self.dim == 2:
            y = x - self.c
            #print 'Yes I am'
            return abs(scal(y,self.n)) < self.c.tol_equiv
        elif self.dim == 3:
            return True

    def __eq__(self,x):
        if self.dim != x.dim:
            return False
        if self.dim == 0:
            return (self.c-x.c).norm() < self.c.tol_equiv
        elif self.dim in [1,2]:
            return ( (self.n-x.n).norm() < self.c.tol_equiv) and (x.c in self)
        elif self.dim in [-1,3]:
            return True

    def __and__(self,x):
        if self.dim>x.dim:
            d1 = self.dim
            d2 = x.dim
            c1 = self.c
            c2 = x.c
            n1 = self.n
            n2 = x.n
        else:            
            d2 = self.dim
            d1 = x.dim
            c2 = self.c
            c1 = x.c
            n2 = self.n
            n1 = x.n
        if (d1==3):
            return linear3d(d2,c2,n2)
        if (d2==-1):
            return linear3d(-1,vector3d(0,0,0))
        if  d2 == 0:
            if c2 in linear3d(d1,c1,n1):
                return linear3d(0,c2)
            else:
                return linear3d(-1,vector3d(0,0,0))
        if d1==1 and d2==1:
            if  (n1-n2).norm() < self.c.tol_equiv or (n1+n2).norm() < self.c.tol_equiv:
                if c2 in linear3d(d1,c1,n1):
                    return self
                else:
                    return linear3d(-1,vector3d(0,0,0))
            elif abs(scal(c2-c1,n1%n2)) < self.c.tol_equiv:
                s = scal(n1,n2)
                x1 = scal(n1 - s*n2, c2-c1)/(1-s*s)
                return linear3d(0,c1+x1*n1)
            else:
                return linear3d(-1,vector3d(0,0,0))
        if d1==2 and d2==1:
            if abs(scal(n1,n2)) < self.c.tol_equiv:
                if abs(scal(n1,c2-c1)) < self.c.tol_equiv:
                    return linear3d(1,c2,n2)
                else:
                    return linear3d(-1,vector3d(0,0,0))
            else:
                return  linear3d(0,c2+n2*scal(n1,c1-c2)/scal(n1,n2))
        if d1==2 and d2==2:
            if (n1-n2).norm() < self.c.tol_equiv or (n1+n2).norm() < self.c.tol_equiv:
                if abs(scal(n1,c1-c2))<self.c.tol_equiv:
                    return self
                else:
                    return linear3d(-1,vector3d(0,0,0))
            else:
                s = scal(n1,n2)
                nn = n1%n2
                x1 = (scal(c1,n1)-s*scal(c2,n2))/(1-s*s)
                x2 = (scal(c2,n2)-s*scal(c1,n1))/(1-s*s)
                return linear3d(1,x1*n1+x2*n2,nn)
 
def vecreal(v):
    return vector3d(v[0].real,v[1].real,v[2].real)

def invariant_subspace(R):
    lmb=vector3z()
    n = matrix3z()
    diagon3(lmb,n,R.R)
    T = vector3z(R.T[0],R.T[1],R.T[2])
    t = vector3z(scal(n[0],T), scal(n[1],T), scal(n[2],T))
    x = vector3z(0,0,0)
    nn=[]
    for i in range(3):
        if abs(lmb[i]-1)<R.T.tol_equiv:
            if abs(t[i])<R.T.tol_equiv:
                nn.append(n[i])
            else:
                return linear3d(-1,vector3d(0,0,0))
        else:
            x[i] = t[i]/(1-lmb[i])
    c = x[0]*n[0]+x[1]*n[1]+x[2]*n[2]
    rc = vecreal(c)
    d = len(nn)
    if d==0:
        return linear3d(0,rc)
    elif d==1:
        return linear3d(1,rc,vecreal(nn[0]))
    elif d==2:
        return linear3d(2,rc,vecreal(nn[0]%nn[1]))
    elif d==3:
        return linear3d(3,rc)
   
def merge_equiv_subs(subspaces,subgroups,multab):
    i=0
    newss=[]
    newsg=[]
    already = [False]*len(subspaces)
    while i<len(subspaces):
        if not already[i] and subspaces[i].dim != -1:
            idx = [j for j,l in enumerate(subspaces) if l==subspaces[i] ]
            print i,idx
            g = []
            for j in idx:
                g = g + subgroups[j]
                already[j] = True
            newss.append(subspaces[i])
            newsg.append(complete_subgroup(g,multab))            
        i = i + 1
    return [newsg,newss]


def add_subs(multab,subgroups,subspaces,sg,ss):
    try:
        i = subspaces.index(ss)
        subgroups[i] = complete_subgroup(subgroups[i] + sg, multab)
    except ValueError: 
        subspaces.append(ss)
        subgroups.append(sg)

def recurs_add_subs(multab,subgroups,subspaces,sg,ss,i,n):
    for j in xrange(i[-1]+1,n):
        nss = ss & subspaces[j]
        if nss.dim in [1,2]:
            print '  '*len(i),i+[j],nss
            recurs_add_subs(multab,subgroups,subspaces,complete_subgroup(subgroups[j] + sg,multab), nss, i+[j], n)
        elif nss.dim == 0:
            add_subs(multab,subgroups,subspaces,complete_subgroup(subgroups[j] + sg,multab),nss)
            print '  '*len(i),i+[j],nss,sg, len(subgroups[subspaces.index(nss)])

def add_subspace(subspaces,elements,s,g):
    try:
        i = subspaces.index(s)
        #elements[i] = complete_subgroup( elements[i] | set(g))
        elements[i] = elements[i] | set(g)
    except ValueError:
        if s.dim > -1:
            subspaces.append(s)
            elements.append(set(g))
            #elements.append(complete_subgroup(g))

def find_point_subgroups(G):

    # unbind
    GG = [rotrans_d(g.T,g.R) for g in G]
    '''GG = []
    eps = G[0].tol_trans
    for g in G:
        f = g.cell.cart2frac(g.T)
        for i in [-1,0,1]:
            for j in [-1,0,1]:
                for k in [-1,0,1]:
                    f1 = f + vector3d(i,j,k)
                    if f1[0] > -eps and f1[0] < 1+eps and f1[1] > -eps and f1[1] < 1+eps \
                       and f1[2] > -eps and f1[2] < 1+eps:
                        GG.append(rotrans_d(g.cell.frac2cart(f1),g.R))'''
    subspaces = []
    elements = []

    for g in GG:
        s = invariant_subspace(g)
        if s.dim == -1: continue
        add_subspace(subspaces,elements,s,[g])

    n = len(subspaces)
    '''
    for  i in xrange(n):
        print i, subspaces[i], len(elements[i])
    '''
    for i in xrange(n):
        if subspaces[i].dim==0:
            for j in xrange(n):
                if subspaces[i].c in subspaces[j]:
                    #elements[i] = complete_subgroup(elements[i] + elements[j])
                    elements[i] = elements[i] | elements[j]
                    #add_subspace(subspaces,elements,s,[g])
    '''
    print
    for  i in xrange(n):
        print i, subspaces[i], len(elements[i])
    '''
    nnew = 0
    contin = True
    while contin:
        nnewnew = len(subspaces)
        #print nnew,nnewnew

        for i in xrange(nnew,len(subspaces)):
            if subspaces[i].dim in (1,2):
                for j in xrange(n):
                    if subspaces[j].dim in (1,2):
                        add_subspace(subspaces,elements, subspaces[i] & subspaces[j], \
                                     #elements[i] + elements[j])
                                     elements[i] | elements[j])
        contin = nnewnew < len(subspaces)
        nnew = nnewnew

    return subspaces,[complete_subgroup(e) for e in elements]


def find_point_subgroups1(G):
    M = build_multab(G)
    # form initial set of abelian subgroups & their invariant subspaces
    gabels = []
    sabels = []

    for g in sorted(range(len(G)), key = lambda i: -symm_order(M,i)):
#        if not g in [j for i in gabels for j in i]:
            add_subs(M,gabels,sabels,abelian_sub(M,g),invariant_subspace(G[g]))
            #gabels.append(abelian_sub(M,g))
            #sabels.append(invariant_subspace(G[g]))

    #recurs_add_subs(M,gabels,sabels,[0],linear3d(3,vector3d(0,0,0)),[-1],len(gabels))

    subspaces = [s for s in sabels]
    subgroups = [g for g in gabels]
    sidx = [[i] for i in range(len(sabels))]
    bidx = [[] for i in range(len(sabels))]
    for i in range(len(sabels)):
        for j in range(len(sabels)):
            if i!=j and ( subspaces[i] & subspaces[j] == subspaces[i]):
                sidx[i].append(j)
            if subspaces[i] & subspaces[j] == linear3d(-1,vector3d(0,0,0)):
                bidx[i].append(j)

    newss = subspaces

    return [gabels,sabels,sidx,bidx]



def find_cryst_symm(geom,R):
    B = array_point_group_d()
    bravais_point_group(B,geom.cell,R)
