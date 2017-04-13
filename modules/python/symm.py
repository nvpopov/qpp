from nice import overloader

#---------------------------------------------------------

def symm_add(group,op):
    if op in group:
        return
    newelems = [op]
    while newelems != []:
        newnewelems = []
        #print "new ", newelems
        for g1 in newelems:
            for g2 in group+newelems:
                h = g1*g2
                if (not h in group) and (not h in newelems) and (not h in newnewelems):
                    newnewelems.append(h)
                h = g2*g1
                if (not h in group) and (not h in newelems) and (not h in newnewelems):
                    newnewelems.append(h)
        #print group, newelems, newnewelems
        group.extend(newelems)
        newelems = newnewelems

#---------------------------------------------------------

def build_multab(group):
    N = len(group)
    tab = []
    for i in xrange(N): tab.append(list([0]*N))
    #print tab
    for i in xrange(N):
        for j in xrange(N):
            #print i,j,group.index(group[i]*group[j])
            tab[i][j] = group.index(group[i]*group[j])
    return tab

#---------------------------------------------------------

def symm_order_by_multab(multab,i):
    #print "by multab call"
    if (type(multab) is list) and (type(multab[0]) is list) and (type(multab[0][0]) is int):
        n=0;
        j=i
        while j!=0:
            j = multab[j][i]
            n = n + 1
        return n + 1
    else:
        #print "by multab TE"
        raise TypeError()

def symm_order_by_element(A):
    #print "by element"
    n=0
    B=A*A
    while B!=A:
        B = B*A
        n = n + 1
    return n + 1

def symm_order_by_index(group,i):
    return symm_order_by_element(group[i])

def symm_order(*args,**kwds):
    return overloader([symm_order_by_multab,symm_order_by_element,symm_order_by_index],args,kwds, \
                      "qpp: invalid arguments in symm_order call"+str(args)+str(kwds))

#---------------------------------------------------------

def symm_invert_by_multab(multab,i):
    if (type(multab) is list) and (type(multab[0]) is list) and (type(multab[0][0]) is int):
        for j in xrange(len(multab)):
            if (multab[i][j]==0):
                return j
    else:
        raise TypeError()

def symm_invert_by_element(A):
    n=symm_order(A)   
    B = A
    for i in xrange(n-2):
        B = B*A
    return B

def symm_invert_by_index(group,i):
    e = group[0]
    g = group[i]
    a=g
    b=g*g
    while b!=e:
        a=b
        b=b*g
    return e

def symm_invert(*args,**kwds):
    return overloader([symm_invert_by_multab, symm_invert_by_element, symm_invert_by_index],args,kwds, \
                      "qpp: invalid arguments in symm_invert call"+str(args)+str(kwds))

#---------------------------------------------------------

def is_symm_group(G):
    for a in G:
        for b in G:
            #print G.index(a),G.index(b)
            if not a*b in G: return False
    return True

#---------------------------------------------------------

def is_normal_subgroup_by_multab(multab,H):
    if (not type(multab) is list) or (not type(multab[0]) is list) or (not type(multab[0][0]) is int):
        raise TypeError()
    if (not type(H) is list) or (not type(H[0]) is int):
        raise TypeError()
    for g in xrange(len(multab)):
        for h in H:
            gh = multab[g][h]
            ghg = multab[gh][symm_invert(multab,g)]
            if not ghg in H:
                return False
    return True
    
def is_normal_subgroup_by_groups(G,H):
    for g in G:
        for h in H:
            if not symm_invert(G,G.index(g))*h*g in H:
                return False
    return True

def is_normal_subgroup(*args,**kwds):
    return overloader([is_normal_subgroup_by_multab,is_normal_subgroup_by_groups],args,kwds, \
                      "qpp: invalid arguments in is_normal_subgroup call"+str(args)+str(kwds))


#---------------------------------------------------------

def mul_groups_groups(G,H):
    res=[]
    for g in G:
        for h in H:
            if not g*h in res:
                res.append(g*h)
    return res

def mul_groups_multab(multab,G,H):
    res=[]
    for g in G:
        for h in H:
            c = multab[g][h]
            if not c in res:
                res.append(c)
    return res

def mul_groups(*args,**kwds):
    return overloader([mul_groups_groups,mul_groups_multab],args,kwds, \
                      "qpp: invalid arguments in mul_groups call"+str(args)+str(kwds))


#---------------------------------------------------------

def idx2grp(G,I):
    return [G[i] for i in I]

#---------------------------------------------------------

def grp2idx(G,H):
    return [G.index(h) for h in H]

#---------------------------------------------------------

def abelian_sub_by_multab(multab,i):
    #print type(multab)
    #print multab[0], type(multab[0])
    #print multab[0][0],type(multab[0][0])
    if (not type(multab) is list) or (not type(multab[0]) is list) or (not type(multab[0][0]) is int):
        raise TypeError()
    sub=[0]
    j=i
    while j!=0:
        sub.append(j)
        j = multab[i][j]
    return sub

def abelian_sub_by_element(A):
    sub = [A]
    B=A*A
    while B!=A:
        sub.append(B)
        B = B*A
    sub.insert(0,sub[-1])
    del sub[-1]
    return sub
    
def abelian_sub_by_index(group,i):
    return abelian_sub_by_element(group[i])

def abelian_sub(*args,**kwds):
    return overloader([abelian_sub_by_multab,abelian_sub_by_element],args,kwds, \
                      "qpp: invalid arguments in abelian_sub call"+str(args)+str(kwds))

#---------------------------------------------------------

def find_generators_by_multab(multab,H):
    if (type(multab) is list) and (type(multab[0]) is list) and (type(multab[0][0]) is int):
        N = len(multab)
        if len(H) == N:
            return []
        #print 'fg by multab'
        for g in sorted(range(N), key = lambda x: -symm_order(multab,x)):
            if (not g in H) and N % (len(H)*symm_order(multab,g)) == 0:
                print 'trying ',g
                H1 = mul_groups(multab, H, abelian_sub(multab,g))
                if len(H1) == len(H)*symm_order(multab,g):
                    gg = find_generators_by_multab(multab,H1)
                    if type(gg) is list:
                        return [g]+gg
    else:
        raise TypeError()

def find_generators_by_groups(G,H):
    if len(G)==len(H):
        return []
    print len(H)
    for g in sorted(G, key=lambda x: -symm_order(x)):
        if (not g in H) and len(G) % (len(H)*symm_order(g))==0:
            H1=mul_groups(H, abelian_sub(g))
            if len(H1) == len(H)*symm_order(g):
                gg = find_generators_by_groups(G,H1)
                if type(gg) is list:
                    return [g]+gg


def find_generators(*args,**kwds):
    return overloader([find_generators_by_multab,find_generators_by_groups],args,kwds, \
                      "qpp: invalid arguments in find_generators call"+str(args)+str(kwds))

#---------------------------------------------------------

def class_left(G,H):
    classes = [H]
    used = H
    for g in G:
        if not g in used:
            newclass = []
            for h in H:
                newclass.append(g*h)
            classes.append(newclass)
            used = used + newclass
#    return classes
    return [[G.index(g) for g in c] for c in classes]

#---------------------------------------------------------

def class_right(G,H):
    classes = [H]
    used = H
    for g in G:
        if not g in used:
            newclass = []
            for h in H:
                newclass.append(h*g)
            classes.append(newclass)
            used = used + newclass
    return [[G.index(g) for g in c] for c in classes]

#---------------------------------------------------------

def build_subgroups(G):
    subs=[frozenset([0])]
    for i in xrange(1,len(G)):
        A = frozenset(abelian_sub(G,i))
        if not A in subs:
            subs.append(A)
    contin=True
    while contin:
        contin=False
        for A in subs:
            for B in subs:
                C = [G[0]]
                for x in list(A)+list(B):
                    add_symmetry(C,G[x])
                CC = frozenset(group2idx(G,C))
                if not CC in subs:
                    contin=True
                    subs.append(CC)
                    print A,B, len(subs), is_group(C)
                    print list(CC)
    return subs
    
