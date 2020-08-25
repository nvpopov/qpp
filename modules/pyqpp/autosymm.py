from qpp import *
from symm import abelian_sub, build_multab, complete_subgroup
from numpy.linalg import matrix_rank
from numpy.linalg import solve
from math import floor,sqrt

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
    for j in range(len(G)):
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
            y = y - self.n*y.dot(self.n)
            return y.norm() < self.c.tol_equiv
        elif self.dim == 2:
            y = x - self.c
            #print 'Yes I am'
            return abs(y.dot(self.n)) < self.c.tol_equiv
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
            elif abs((c2-c1).dot(n1.cross(n2))) < self.c.tol_equiv:
                s = n1.dot(n2)
                x1 = (n1 - s*n2).dot(c2-c1)/(1-s*s)
                return linear3d(0,c1+x1*n1)
            else:
                return linear3d(-1,vector3d(0,0,0))
        if d1==2 and d2==1:
            if abs(n1.dot(n2)) < self.c.tol_equiv:
                if abs(n1.dot(c2-c1)) < self.c.tol_equiv:
                    return linear3d(1,c2,n2)
                else:
                    return linear3d(-1,vector3d(0,0,0))
            else:
                return  linear3d(0,c2+n2*n1.dot(c1-c2)/n1.dot(n2))
        if d1==2 and d2==2:
            if (n1-n2).norm() < self.c.tol_equiv or (n1+n2).norm() < self.c.tol_equiv:
                if abs(n1.dot(c1-c2))<self.c.tol_equiv:
                    return self
                else:
                    return linear3d(-1,vector3d(0,0,0))
            else:
                s = n1.dot(n2)
                nn = n1.cross(n2)
                x1 = (c1.dot(n1)-s*c2.dot(n2))/(1-s*s)
                x2 = (c2.dot(n2)-s*c1.dot(n1))/(1-s*s)
                return linear3d(1,x1*n1+x2*n2,nn)
 
def vecreal(v):
    return vector3d(v[0].real,v[1].real,v[2].real)

def invariant_subspace_trash(R):
    lmb=vector3z()
    n = matrix3z()
    diagon3(lmb,n,R.R)
    T = vector3z(R.T[0],R.T[1],R.T[2])
    t = vector3z(n[0].dot(T), n[1].dot(T), n[2].dot(T))
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
        return linear3d(2,rc,vecreal(nn[0].cross(nn[1])))
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
            print(i,idx)
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
    for j in range(i[-1]+1,n):
        nss = ss & subspaces[j]
        if nss.dim in [1,2]:
            print('  '*len(i),i+[j],nss)
            recurs_add_subs(multab,subgroups,subspaces,complete_subgroup(subgroups[j] + sg,multab), nss, i+[j], n)
        elif nss.dim == 0:
            add_subs(multab,subgroups,subspaces,complete_subgroup(subgroups[j] + sg,multab),nss)
            print('  '*len(i),i+[j],nss,sg, len(subgroups[subspaces.index(nss)]))

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

def find_point_subgroups2(G):

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
    for i in range(n):
        if subspaces[i].dim==0:
            for j in range(n):
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

        for i in range(nnew,len(subspaces)):
            if subspaces[i].dim in (1,2):
                for j in range(n):
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

def rotrans_2frac(r):
    cl = r.cell
    a=matrix3d(cl[0],cl[1],cl[2]).tran()
    return rotrans_d(a.inv()*r.T, a.inv()*r.R*a)

def rotrans_2cart(r,cl):
    a=matrix3d(cl[0],cl[1],cl[2]).tran()
    return bound_rotrans_d(a*r.T, a*r.R*a.inv(), cl)

def rotrans_circle(r):
    F = rotrans_d(r.T,r.R)
    G=F
    circle = [F]
    while (G.R - matrix3d.identity()).norm() > rotrans_d.tol_rot:
        G = G*F
        circle.append(G)
    t = G.T
    n = len(circle)
    return circle

def LI_vecs(M, eps):
    dim = len(M)
    LI=[]
    I=[]
    for i in range(dim):
        tmp=[]
        for r in LI:
            tmp.append(r)
        MM = [x for x in M[i]]
        tmp.append(MM)                #set tmp=LI+[M[i]]
        if matrix_rank(tmp,tol=eps)>len(LI):    #test if M[i] is linearly independent from all (row) vectors in LI
            I.append(i)
            LI.append(MM)             #note that matrix_rank does not need to take in a square matrix
    return I                           #return set of linearly independent (row) vectors

def lincomb(y,x):
    n=len(x)
    A = [[x[i].dot(x[j]) for j in range(n)] for i in range(n)]
    b = [y.dot(x[i]) for i in range(n)]
    return solve(A,b)

def nullspace(a,eps):
    indep = LI_vecs(a,eps)
    dep = [i for i in range(len(a)) if not i in indep]
    if indep == []:
        return indep, dep, [[-1e0 if j==i else 0e0 for j in range(len(a))] for i in range(len(a))]
    if dep == []:
        return indep, dep, []
    basis = [a[i] for i in indep]
    ns = []
    for i in dep:
        x = lincomb(a[i],basis)
        coeffs = [0e0 for j in range(len(a))]
        for j in range(len(basis)):
            coeffs[indep[j]] = x[j]
        coeffs[i] = -1e0
        ns.append(coeffs)
    return indep, dep, ns

def round(x):
    return floor(x+.5)

def inspect_rotrans(r):
    eps = 1e-5
    cl = r.cell
    v = [vector3d(0), cl[0], cl[1], cl[2]]
    t=[]
    p=[]
    for i in range(4):
        c = rotrans_circle(rotrans_d(r.T+v[i], r.R))
        pp=vector3d(0,0,0)
        for g in c:
            pp = pp + g.T
        pp = pp/len(c)
        p.append(pp)
        t.append(c[-1].T)
    a = [t[1]-t[0],t[2]-t[0],t[3]-t[0],t[0]]
    b = [p[1]-p[0],p[2]-p[0],p[3]-p[0],p[0]]
    indep, dep, ns = nullspace(a,eps)
    if 3 in indep:
        # no way to make this rotrans a point symmetry
        return []
    print(ns)
    center = []
    for i in range(-1,len(ns)-1):
        v = vector3d(0e0)
        for j in range(4):
            v = v - ns[i][j]*b[j]
        center.append(v)
    idxx = []
    for j in range(3):
        if abs(ns[-1][j] - round(ns[-1][j])) < eps:
            idxx.append( -round(ns[-1][j]))
        else:
            return []
    idx = [index(idxx)]
    for i in range(len(ns)-1):
        idxx = []
        for j in range(3):
            if abs(ns[i][j] - round(ns[i][j])) < eps:
                idxx.append( -round(ns[i][j]))
        if len(idxx)==3:
            idx.append(index(idxx))
    return idx

def rotrans_grid(r,idx):
    d = len(idx)
    rf = rotrans_2frac(r)
    rf_shifted = [rotrans_2frac(shift_r(r,i)) for i in idx]
    pt_cntr = invariant_subspace(rf).point
    pt_shifted = [invariant_subspace(rfs).point for rfs in rf_shifted]
    cl = periodic_cell_d(3)
    for i in range(d):
        cl[i] = pt_shifted[i] - pt_cntr
    if (d)==1:
        n = [vector3d(1,0,0),vector3d(0,1,0),vector3d(0,0,1)]
        n1 = min(n, key = lambda x: abs(x.dot(cl[0])))
        cl[1] = n1
    if (d)<=2:
        cl[2] = cl[0].cross(cl[1])
    S = sphere_shape_d(.5*sqrt(3),-1e0*pt_cntr)
    fmin = S.fmin(cl)
    fmax = S.fmax(cl)
    grid0 = [ floor(fmin[i]) if i<d else 0 for i in range(3)] 
    grid1 = [ floor(fmax[i])+1 if i<d else 0 for i in range(3)]
    grd = []
    for g in index_range(grid0,grid1):
        I = index([0,0,0])
        for i in range(d):
            I = I + idx[i]*g[i]
        S = invariant_subspace(rotrans_2frac(shift_r(r,I)))
        print(S.dim,I,S.point, S.point.norm() < .5*sqrt(3))
        if ( S.point.norm() < .5*sqrt(3) ):
            grd.append(I)
    return grd

def relevant_subspaces(r):
    I = inspect_rotrans(r)
    if I==[]:
        return [],[]
    rr = shift_r(r,I[0])
    grd=rotrans_grid(rr,I[1:])
    return [invariant_subspace(shift_r(rr,g)) for g in grd],[shift_r(rr,g) for g in grd]
        
def check_symm_point(GC,uc,pt):
    eps = 1e-5
    res = []
    for g in GC:
        f = uc.cell.cart2frac(g*pt - pt)
        n = round(f[0])
        m = round(f[1])
        l = round(f[2])
        if (f - vector3d(n,l,m)).norm()<eps:
            res.append(rotrans_d(g.T+n*uc.cell[0]+m*uc.cell[1]+l*uc.cell[2], g.R))
    return res

        

def find_point_subgroups2(GC,uc):
    eps = 1e-5
    images = [[] for i in range(len(uc))]
    already = [False for i in range(len(uc))]
    for at in range(len(uc)):
        if not already[at]:
            atom = uc.atom[at]
            r0 = uc.pos(at)
            for j in range(len(GC)):
                r = GC[j]*r0
                r = uc.cell.reduce(r)
                found = False
                for at1 in range(len(uc)):
                    if uc.atom[at1]==atom:
                        for I in index_range([-1,-1,-1],[1,1,1]):
                            if (r - uc.pos(at1,I)).norm()<eps:
                                if not at1 in images[at]:
                                    images[at].append(at1)
                                    already[at1] = True
                                found = True
                                break
                if not found:
                    print(at,j,r0,r)
    #return images, already
    at=0
    for i in range(len(uc)):
        if len(images[i])>0:
            if len(images[at]) == 0 or  len(images[at]) < len(images[i]):
                at = i
    #print(at,images[at])
    #candidate points:
    r0 = uc.pos(at)
    pt_groups = []
    for at1 in images[at]:
        for I in index_range([-1,-1,-1],[1,1,1]):
            r1 = uc.pos(at1,I)
            pt = (r0 + r1)/2
            print(pt)
            if uc.cell.within(pt):
                cand_group = check_symm_point(GC,uc,pt)
                if len(cand_group) > 1:
                    pt_groups.append((cand_group,pt))
    return pt_groups
                
#-----------------------------------------------------------------------

def shift_r(r,I):
    cl = r.cell
    return bound_rotrans_d(r.T + cl[0]*I[0] + cl[1]*I[1] + cl[2]*I[2], r.R, r.cell)

def order_r(r):
    eps = 1e-5
    I = matrix3d.identity();
    n=1
    M = r.R
    while (M-I).norm() > eps:
        M = M*r.R
        n += 1
    return n

def abelian_division(G):
    A = group_analyzer_cgd(G)
    grps = []
    gen = []
    for i in range(len(G)):
        a = set(A.abelian_sub(i))
        if not a in grps:
            grps.append(a)
            gen.append(i)
    return gen

#---------------------------------------------

def subs_merge(subs,groups,sucessors,i,grp,pred):
    for g in grp:
        if not g in groups[i]:
            groups[i].append(g)
    for p in pred:
        if not i in sucessors[p]:
            sucessors[p].append(i)

def subs_new(subs,groups,sucessors,s,grp,pred):
    i = len(subs)
    subs.append(s)
    newg = []
    for g in grp:
        if not g in newg:
            newg.append(g)
    groups.append(newg)
    sucessors.append([])
    for p in pred:
        sucessors[p].append(i)

def subs_check(subs,groups,sucessors,i,j):
    if subs[i].within(subs[j]):
        subs_merge(subs,groups,sucessors,j,groups[i],[i])

def subs_is_relevant(S,cell):
    if S.dim == -1 or S.dim == 3:
        return False
    elif S.dim == 0:
        return cell.within_centered(S.point)
    else:
        return cell.cart2frac(S.point).norm() < .5*sqrt(3)


    
def find_point_subgroups(GC):
    geners = abelian_division(GC)
    subs = []
    groups = []
    sucessors = []
    for g in geners:
        r1 = relevant_subspaces(GC[g])
        print(r1)
        ss, rr = relevant_subspaces(GC[g])
        for i in range(len(ss)):
            if not ss[i] in subs:
                subs_new(subs,groups,sucessors,ss[i],[rr[i]],[])
            else:
                subs_merge(subs,groups,sucessors,subs.index(ss[i]),[rr[i]],[])
    for i in range(len(subs)):
        for j in range(len(subs)):
            if i!=j:
                subs_check(subs,groups,sucessors,i,j)
    inew = 0
    while inew < len(subs):
        inewest = len(subs)
        for ig1 in range(inewest):
            for ig2 in range(inew, inewest):
                if ig1!=ig2:
                    s = subs[ig1] & subs[ig2]
                    if not subs_is_relevant(s,GC[0].cell):
                        continue
                    found = False
                    ifound = -1
                    pred = []
                    if s == subs[ig1]:
                        found = True
                        ifound = ig1
                        pred = [ig2]
                    elif s == subs[ig2]:
                        found = True
                        ifound = ig2
                        pred = [ig1]
                    else:
                        for i in range(len(subs)):
                            if i!=ig1 and i!=ig2 and s == subs[i]:
                                found = True
                                ifound = i
                                pred = [ig1,ig2]
                                break
                    if found:
                        subs_merge(subs,groups,sucessors,ifound,groups[ig1] + groups[ig2], pred)
                    else:
                        subs_new(subs,groups,sucessors,s,groups[ig1] + groups[ig2], [ig1,ig2])
                        print(len(subs),subs[-1].dim, subs[-1].point, subs[-1].axis)
        inew = inewest
    S=[]
    G=[]
    for i in range(len(subs)):
        if sucessors[i]==[]:
            S.append(subs[i])
            GG=[]
            for g in groups[i]:
                symm_add(GG,g)
            G.append(GG)                            
    return S,G


