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
    for i in range(N): tab.append(list([0]*N))
    #print tab
    for i in range(N):
        for j in range(N):
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
        for j in range(len(multab)):
            if (multab[i][j]==0):
                return j
    else:
        raise TypeError()

def symm_invert_by_element(A):
    n=symm_order(A)   
    B = A
    for i in range(n-2):
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
    for g in range(len(multab)):
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
    return overloader([abelian_sub_by_multab,abelian_sub_by_element,abelian_sub_by_index],args,kwds, \
                      "qpp: invalid arguments in abelian_sub call"+str(args)+str(kwds))

#---------------------------------------------------------

def find_generators_by_multab(multab,H):
    if (type(multab) is list) and (type(multab[0]) is list) and (type(multab[0][0]) is int):
        N = len(multab)
        if len(H) == N:
            return []
        #print('fg by multab H= ',H)
        for g in sorted(range(N), key = lambda x: -symm_order(multab,x)):
            if (not g in H) and N % (len(H)*symm_order(multab,g)) == 0:
                #print('trying ',g, ' ord= ', symm_order(multab,g))
                H1 = mul_groups(multab, H, abelian_sub(multab,g))
                #H2 = [multab[i][j] for i in H for j in abelian_sub(multab,g)]
                #print(sorted(H2))                
                if len(H1) == len(H)*symm_order(multab,g):
                    gg = find_generators_by_multab(multab,H1)
                    if type(gg) is list:
                        return [g]+gg
    else:
        raise TypeError()

def find_all_generators_by_multab(multab,H):
    if (type(multab) is list) and (type(multab[0]) is list) and (type(multab[0][0]) is int):
        N = len(multab)
        if len(H) == N:
            return [[]]
        #print('fg by multab H= ',H)
        res = []
        for g in sorted(range(N), key = lambda x: -symm_order(multab,x)):
            if (not g in H) and N % (len(H)*symm_order(multab,g)) == 0:
                #print('trying ',g, ' ord= ', symm_order(multab,g))
                H1 = mul_groups(multab, H, abelian_sub(multab,g))
                #H2 = [multab[i][j] for i in H for j in abelian_sub(multab,g)]
                #print(sorted(H2))                
                if len(H1) == len(H)*symm_order(multab,g):
                    gg = find_all_generators_by_multab(multab,H1)
                    #if type(gg) is list:
                    res = res + [[g]+x for x in gg]
        return res
    else:
        raise TypeError()

def find_generators_by_groups(G,H):
    if len(G)==len(H):
        return []
    #print len(H)
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

def class_left_by_multab(multab,H):
    if (type(multab) is list) and (type(multab[0]) is list) and (type(multab[0][0]) is int) \
       and (type(H) is list) and (type(H[0]) is int):
        N = len(multab)
        classes=[H]
        used = H
        for g in range(N):
            if not g in used:
                newclass = []
                for h in H:
                    newclass.append(multab[g][h])
                classes.append(newclass)
                used = used + newclass
        return classes
    else:
        raise TypeError()

def class_left_by_group(G,H):
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

def class_left(*args,**kwds):
    return overloader([class_left_by_multab,class_left_by_group],args,kwds, \
                      "qpp: invalid arguments in class_left call"+str(args)+str(kwds))


#---------------------------------------------------------

def class_right_by_multab(multab,H):
    if (type(multab) is list) and (type(multab[0]) is list) and (type(multab[0][0]) is int) \
       and (type(H) is list) and (type(H[0]) is int):
        N = len(multab)
        classes=[H]
        used = H
        for g in range(N):
            if not g in used:
                newclass = []
                for h in H:
                    newclass.append(multab[h][g])
                classes.append(newclass)
                used = used + newclass
        return classes
    else:
        raise TypeError()

def class_right_by_group(G,H):
    classes = [H]
    used = H
    for g in G:
        if not g in used:
            newclass = []
            for h in H:
                newclass.append(h*g)
            classes.append(newclass)
            used = used + newclass
#    return classes
    return [[G.index(g) for g in c] for c in classes]

def class_right(*args,**kwds):
    return overloader([class_right_by_multab,class_right_by_group],args,kwds, \
                      "qpp: invalid arguments in class_left call"+str(args)+str(kwds))

#---------------------------------------------------------

def complete_subgroup_by_multab(s,multab):
    if (type(multab) is list) and (type(multab[0]) is list) and (type(multab[0][0]) is int)\
       and (type(s) is list):        
        newelems = s
        res = [0]
        while newelems != []:
            newnewelems = []
            #print "new ", newelems
            for g1 in newelems:
                for g2 in res+newelems:
                    h = multab[g1][g2]
                    if not (h in res) and not (h in newelems) and not (h in newnewelems):
                        newnewelems.append(h)
                    h = multab[g2][g1]
                    if not (h in res) and not (h in newelems) and not (h in newnewelems):
                        newnewelems.append(h)
            res.extend(newelems)
            newelems = newnewelems
        return list(set(res))
    else:
        raise TypeError()

def complete_subgroup_by_group(S):
    G = []
    for g in S:
        symm_add(G,g)
    return G

def complete_subgroup(*args,**kwds):
    return overloader([complete_subgroup_by_multab,complete_subgroup_by_group],args,kwds, \
                      "qpp: invalid arguments in complete_subgroup call"+str(args)+str(kwds))

#---------------------------------------------------------

def orthogonal_subgroups_iter(multab,lcls,rcls,lidx,ridx,lused,rused,seed):
#    print "orth sub seed= ", seed
#    print "   lcls  = ", lcls
#    print "   rcls  = ", rcls
#    print "   lidx  = ", lidx
#    print "   ridx  = ", ridx
#    print "   lused = ", lused
#    print "   rused = ", rused    

    if not (False in lused) or not (False in lused):
        return [seed]

    res = []
    li = 0
    while lused[li]: li = li + 1
    for g in lcls[li]:
        if not rused[ridx[g]]:
            newgroup = complete_subgroup(seed + [g],multab)
            ng = []
            for h in newgroup:
                if not (h in ng) and not (h in seed):
                    ng.append(h)

#            print " g = ", g, " ng = ", ng

            contin = True
            for h in ng:
                if lused[lidx[h]] or rused[ridx[h]]:
                    contin = False
                    break
            if contin:
                newlused = [b for b in lused]
                newrused = [b for b in rused]
                for h in ng:
                    newlused[lidx[h]] = True
                    newrused[ridx[h]] = True
                res = res + orthogonal_subgroups_iter(multab,lcls,rcls,lidx,ridx,newlused,newrused,seed+ng)
    return res
                        

def orthogonal_subgroups(multab,group):
    if group == [0]:
        return range(len(multab))

    lcls = class_left(multab,group)
    rcls = class_right(multab,group)
    lidx = [0]*len(multab)
    ridx = [0]*len(multab)
    n = len(lcls)
    for i in range(n):
        for g in lcls[i]: lidx[g] = i
        for g in rcls[i]: ridx[g] = i
    lused = [False]*n
    rused = [False]*n
    lused[0] = True
    rused[0] = True
    return orthogonal_subgroups_iter(multab,lcls,rcls,lidx,ridx,lused,rused,[0])
            

#---------------------------------------------------------

def maximal_subgroups_by_multab(multab):
    if (type(multab) is list) and (type(multab[0]) is list) and (type(multab[0][0]) is int):
        done = [False]*len(multab)
        done[0] = True
        res = set()
        for g in range(len(multab)):
            if not done[g]:
                a = abelian_sub(multab,g)
#                print " a= " , a
                for h in a: 
                    if  symm_order(multab,h) == len(a):
                        done[h] = True
                for G in orthogonal_subgroups(multab,a):
                    res.add(frozenset(G))
        return [list(G) for G in res]
    else:
        raise TypeError()


def maximal_subgroups_by_group(G):

    return subs
    
def maximal_subgroups(*args,**kwds):
    return overloader([maximal_subgroups_by_multab,maximal_subgroups_by_group],args,kwds, \
                      "qpp: invalid arguments in build_subgroups call"+str(args)+str(kwds))

#-----------------------------------------------------------

def submultab(multab,sub):
    N = len(sub)
    stab = []
    for i in range(N):
        stab.append(list([0]*N))
        for j in range(N):
            m = multab[sub[i]][sub[j]]
#            print i,j,sub[i],sub[j],multab[sub[i]][sub[j]]
            k=0
            while sub[k]!=m: k=k+1
            stab[i][j] = k
#            print i,j,sub[i],sub[j],multab[sub[i]][sub[j]],k
    return stab

#-----------------------------------------------------------

def build_subgroups_iter(multab):
    if len(multab)==1:
        return []
    res = [range(len(multab))]
    
    for G in maximal_subgroups(multab):
        #print G
        if len(G)>1:
            stab = submultab(multab,G)
            #print "stab= ",stab
            sres = build_subgroups_iter(stab)
            for SG in sres:
                res.append([G[i] for i in SG])
    return res

def build_subgroups(multab):
    X = set([frozenset(g) for g in build_subgroups_iter(multab)])
    return [list(g) for g in X]+[[0]]

