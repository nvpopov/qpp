import qpp_cpp

index_t = [qpp_cpp.index_0, qpp_cpp.index_1, qpp_cpp.index_2, qpp_cpp.index_3, 
           qpp_cpp.index_4, qpp_cpp.index_5]

class index(object):
    
    def __init__(self,x):        
        if type(x) is index:
            self.D = x.D
            self.I = index_t[self.D](x.I)
            return

        elif type(x) is int:
            self.D = x
            lst = [0]*self.D

        elif type(x) is list:
            self.D = len(x)
            lst = x
        elif  type(x) is tuple:
            self.D = len(x)
            lst = list(x)
            
        else:
            raise TypeError("qpp.index: wrong argument type in constructor")

        if self.D >= 0 and self.D <=5:
            self.I = index_t[self.D](lst)
        else:
            raise IndexError("qpp.index: the dimension can be only from 0 to 5")
            
    def __str__(self):
        return self.I.__str__()

    def __getitem__(self,i):
        return self.I.__getitem__(i)

    def __setitem__(self,i,x):
        return self.I.__setitem__(i,x)

    def __add__(self,other):
        res = index(self.D)
        res.I = self.I + other.I
        return res

    def __sub__(self,other):
        res = index(self.D)
        res.I = self.I - other.I
        return res

    def __eq__(self,other):
        return self.D == other.D and self.I == other.I

    def __ne__(self,other):
        return self.D != other.D or self.I != other.I


class vector3(object):

