
def overloader(funlist,args,kwds,msg="Invalid arguments"):
    for f in funlist:
        try:
            res = f(*args,**kwds)
            return res
        except TypeError:
            pass
    raise TypeError(msg)

def boolify(s):
    if s.lower() in ['true','yes']:
        return True
    if s.lower() in ['false', 'no']:
        return False
    raise ValueError("huh?")

def autotype(s):
    for fn in (boolify, int, float):
        try:
            return fn(s)
        except ValueError:
            pass
    return s

def tbl2clms(s):
    res=[]
    for line in s.splitlines():
        fld = line.split()
        if fld[0].startswith('#'):
            continue
        for i in xrange(len(fld)):
            if len(res)<=i:
                res.append([])
            res[i].append(autotype(fld[i]))
    return res

        
def tbl2raws(s):
    res = []
    for line in s.splitlines():
        fld = line.split()
        if fld[0].startswith('#'):
            continue
        res.append([autotype(f) for f in fld])
    return res
