import numpy as np
from math import exp, sqrt, log, cos, sin, acos, atan2, pi
from qpp import *
import random

def mkcharges(m):
    return np.array([-1+2*random.random() for i in range(m)])

def mkpoints(nm,a,b):
    g=xgeometry('d',periodic_cell_d(0),[('charge','real')])
    while(g.nat()<nm):
        c = vector3d(-b+2*b*random.random(),-b+2*b*random.random(),-b+2*b*random.random())
        tooclose = False
        for i in range(g.nat()):
            if (c-g.pos(i)).norm()<a:
                tooclose = True
                break
        if not tooclose:
            g.add('A',c)
    return g

from scipy.special import ellipkinc as ellip_F

def enf(t,x):
    if t < 1e-10:
        return 1e0
    st = sqrt(t)
    return 0.5/sqrt(1-2*x*t+t**2) + 0.25*ellip_F(2*atan2(st,1),(x+1)/2)/st

def enf_check(t,x,L):
    p=[]
    Pl_legendre_d(x,L,p)
    s=0e0
    for l in range(L):
        s += t**l * p[l] * (l+1)/(2*l+1)
    return s
        
def mkF(g,lam):
    nm = g.nat()
    F=np.zeros(shape=(nm,nm))
    for i in range(nm):
        ri = g.pos(i)
        for j in range(nm):
            rj = g.pos(j)
            t = ri.norm()*rj.norm()
            if t<1e-10:
                x=0e0
            else:
                x = ri.dot(rj)/t
            t = t*lam                        
            #F[i,j] = 1./sqrt(1. - 2*ri.dot(rj)*lam + t**2 )
            F[i,j] = enf(t,x)
            #F[i,j] = (1.-t**2)/(1. - 2*ri.dot(rj)*lam + t**2 )**(1.5)
            #F[i,j] = ((i+j)+1./lam)**(-abs(i-j)*lam)/(i+j+1)
            #        A[i,j] = (i+j+1)**(-abs(i-j))+exp(-lam/(abs(i-j)+1))
    return F

        
def div_FGH(A,n,m):
    nm = n + m
    return A[0:n,0:n], A[0:n,n:nm], A[n:nm,n:nm]

def solF(A,y):
    m = y.shape[0]
    n = A.shape[0] - m
    f,g,h = div_FGH(A,n,m)
    gy = np.matmul(g,y)
    return np.matmul(np.linalg.inv(f),gy)

def valF(F,x,y):
    n = x.shape[0]
    m = y.shape[0]
    nm=n+m
    return x.dot(np.matmul(F[0:n,0:n],x)) + 2*x.dot(np.matmul(F[0:n,n:nm],y)) + y.dot(np.matmul(F[n:nm,n:nm],y))


def fcut(f,beta,mu):
    if f==0e0:
        return 0e0
    return 1./(f + exp((-beta+1)*log(abs(f)) + beta*mu))


maxit = 1000
beta = 3
mu = log(1e-6)
convg = 1e-6

def lampath(g,y,lam0,lamfact):
    m = y.shape[0]
    n = g.nat() - m    
    lam = lam0
    A0 = mkF(g,lam)
    F0,G0,H0 = div_FGH( A0,n,m)
    x0 = solF(A0,y)    
    iter=0
    while iter < maxit:
        lam = lam/lamfact
        A1 = mkF(g,lam)
        F1,G1,H1 = div_FGH( A1 ,n,m)
        dxy = np.matmul( F1, x0) + np.matmul( G1, y)
        dx = np.zeros(shape = (n))
        f,v = np.linalg.eig(F1)
        print('   Eigenvals=', f)        
        for i in range(n):
            ff = fcut(f[i],beta,mu)
            fdx = dxy.dot(v[:,i])
            dx = dx - ff*fdx*v[:,i]
        x1 = x0 + dx
        err = sqrt(dx.dot(dx))
        print('iter=', iter, ' lambda=', lam, ' value= ', valF(A1*lam,x1,y),' error= ', err)
        if err < convg:
            break
        x0 = x1
        F0,G0,H0 = F1,G1,H1
        iter += 1
    return [xx.real for xx in x1]

def dipole(g):
    d = vector3d(0e0)
    for i in range(len(g)):
        d = d + g.charge[i]*g.pos(i)
    return d

def quadruple(g):
    Q = matrix3d(0e0)
    for i in range(len(g)):
        r = g.pos(i)
        for a in [0,1,2]:
            for b in [0,1,2]:
                Q[a,b] = Q[a,b] + g.charge[i]*r[a]*r[b]
    tr = Q[0,0]+Q[1,1]+Q[2,2]
    for a in [0,1,2]:
        Q[a,a] -= tr/3
    return Q*3

def octuple(g):
    O = np.zeros(shape=(3,3,3))
    for i in range(len(g)):
        r = g.pos(i)
        rr = r.norm()**2
        for a in [0,1,2]:
            for b in [0,1,2]:
                for c in [0,1,2]:
                    rabc = r[a]*r[b]*r[c]
                    if a==b: rabc -= rr*r[c]/5
                    if b==c: rabc -= rr*r[a]/5
                    if c==a: rabc -= rr*r[b]/5
                    O[a,b,c] = O[a,b,c] + g.charge[i]*rabc
    return O*15

def setq(g,x,q):
    n=len(x)
    m=len(q)
    for i in range(n):
        g.charge[i] = x[i]
    for i in range(m):
        g.charge[i+n] = q[i]
        
def lin_cond_minimum(A,B,b):
    '''Find the minimum of quadratic form:
             x*B*x = min
       with additional conditions:
             A*x = b
       the dimension of A is NxM, that of B is MxM,
       and M > N'''
    Binv = np.linalg.inv(B)
    BA = np.matmul(Binv,A.transpose())
    ABA = np.linalg.inv(np.matmul(A,BA))
    return np.matmul(BA,np.matmul(ABA,b))

def lin_cond_min2(A,F,G,a,y):
    '''Find the minimum of quadratic form:
             <x|F|x> + <x|G|y> + <y|(G+)|x> = min
       with additional conditions:
             A|x> = |a>
       the dimension of A is NxM, that of B is MxM,
       and M > N'''
    Finv = np.linalg.inv(F)                 # (1/F)
    FA = np.matmul(Finv,A.transpose())      # (1/F)*(A+)
    AF = FA.transpose()                     # A*(1/F) 
    AFA = np.linalg.inv(np.matmul(A,FA))    # 1/(A*(1/F)*(A+))
    FGy = np.matmul(Finv,np.matmul(G,y))
    CFGy = np.matmul(FA,np.matmul(AFA,np.matmul(A,FGy)))
    return np.matmul(FA,np.matmul(AFA,a)) + CFGy - FGy

def chainsolve(g,y,lam,L):
    m = y.shape[0]
    n = g.nat() - m    
    N = len(lam)
    lam0 = lam[0]
    A = [mkF(g,l) for l in lam]
    F=[]
    G=[]
    H=[]
    for AA in A:
        FF, GG, HH = div_FGH(AA, n, m)
        F.append(FF)
        G.append(GG)
        H.append(HH)
    DF = [F[k] - (lam[k]/lam[0])**L*F[0] for k in range(N)]
    DG = [G[k] - (lam[k]/lam[0])**L*G[0] for k in range(N)]
    DH = [H[k] - (lam[k]/lam[0])**L*H[0] for k in range(N)]
    x0 = solF(A[0],y)
    iter = 0
    while iter < maxit:
        v = np.zeros(shape = (N-1,n))
        u = np.zeros(shape = (N-1))
        for k in range(1,N):
            v[k-1,:] = np.matmul(DF[k],x0) + np.matmul(DG[k],y)
            norm = sqrt(v[k-1,:].dot(v[k-1,:]))
            v[k-1,:] = v[k-1,:]/norm
            u[k-1] = - 0.5*x0.dot(np.matmul(DF[k],x0)) - 0.5*y.dot(np.matmul(DH[k],y)) \
                     - y.dot(np.matmul(DG[k],x0))
            u[k-1] = u[k-1]/norm
        B = np.matmul(v.transpose(),v)
        b, bv = np.linalg.eig(B)
        #print(b,bv)
        Binv = np.zeros(shape = (n,n))
        for i in range(n):
            Binv = Binv + fcut(b[i],beta,mu)*np.outer(bv[:,i],bv[:,i])        
        dx = np.matmul(Binv,np.matmul(v.transpose(),u))
        err = sqrt(dx.dot(dx))
        print('it= ', iter, ' error= ', err, ' values= ', [valF(AA,x0+dx,y).real for AA in A])
        np.linalg.eigvals(B)
        x0 = x0 + dx
        iter = iter + 1
        if err < convg:
            break
    return x0

def plm_triangle(L,teta):
    res = []
    for m in range(L+1):
        y=[]
        Ylm_spherical_d(L,m,teta,y)
        res.append(y)
    return res

def ylm_triangle(L, teta, phi):
    P = plm_triangle(L,teta)
    Y = [np.array(P[0])]
    for m in range(1,L+1):
        pm = np.array(P[m])
        Y.append(pm*cos(m*phi))
        Y.append(pm*sin(m*phi))
    return Y

eps = 1e-6

def tet_phi(r):
    if r.norm() > eps:
        tet_cos = r[2]/r.norm()
    else:
        tet_cos = 0e0                
    if tet_cos > 1e0:
        tet_cos = 1e0
    if tet_cos < -1e0:
        tet_cos = -1e0                
    tet = acos(tet_cos)
    phi = atan2(r[1],r[0])
    return tet, phi

def mkA(g,L):
    A = np.zeros(shape=((L+1)**2, g.nat()))
    for i in range(g.nat()):
        r = g.pos(i)
        rr = r.norm()
        teta, phi = tet_phi(r)
        Y = plm_triangle(L,teta)
        j=0
        for l in range(L+1):
            pref = sqrt((4*pi)/(2*l+1))*(rr**l)
            for m in range(l+1):
                if m==0:
                    A[j,i] = pref*Y[0][l]
                    j = j + 1
                else:
                    A[j,i]   = pref*Y[m][l-m]*cos(m*phi)
                    A[j+1,i] = pref*Y[m][l-m]*sin(m*phi)
                    j = j + 2
                print(l,m,j)
    return A


def momsolve(g,y,lam,L):
    m = y.shape[0]
    n = g.nat() - m
    FGH = mkF(g,lam)
    F,G,H = div_FGH(FGH,n,m)
    AA = mkA(g,L)
    A = AA[:,:n]
    Q = - np.matmul(AA[:,n:],y)
    return lin_cond_min2(A,F,G,Q,y)

def glueA(A,shells,supershells=[]):
    na = A.shape[0]
    ma = len(shells)
    AA = np.zeros(shape=(na + len(supershells),ma))
    for i in range(na):
        for j in range(ma):
            elem = 0e0
            for k in shells[j]:
                elem += A[i,k]
            AA[i,j] = elem
    for i in range(len(supershells)):
        for j in supershells[i]:
            AA[na+i,j] = 1e0*len(shells[j])
    return AA


def glueF(F,shells):
    na = len(shells)
    FF = np.zeros(shape = (na,na) )
    for i in range(na):
        for j in range(na):
            elem = 0e0
            for i1 in shells[i]:
                for j1 in shells[j]:
                    elem += F[i1,j1]
            FF[i,j] = elem
    return FF


def shellsolve(g,y,lam,L,shells,supershells=[]):
    m = y.shape[0]
    n = g.nat() - m
    FGH = mkF(g,lam)
    F,G,H = div_FGH(FGH,n,m)
    AA = mkA(g,L)
    A = AA[:,:n]
    Q = - np.matmul(AA[:,n:],y)
    return lin_cond_min2(A,F,G,Q,y)


#chainsolve(g,q,lam,L)         
#for i in range(50):
#  print(lam,valF(FF(lam,n+m),x,y))
#  lam=lam/lamf

