
def overloader(funlist,args,kwds,msg="Invalid arguments"):
    for f in funlist:
        try:
            res = f(*args,**kwds)
            return res
        except TypeError:
            pass

    raise TypeError(msg)

