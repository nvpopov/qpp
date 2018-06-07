from qpp_cpp import *

c = periodic_cell_d(3)

g = geometry_d(c)

g.add("H",0,0,0);
g.add("C",2,0,0);
g.add("N",5,0,0);
g.add("P",7,0,0);


class O(gobserver_d):
    def added(self,s,a,v):
        print "O::added",s,a,v  
    def changed(self,at,s,a,v):
        print "O::changed",at,s,a,v
    def inserted(self,at,s,a,v):
        print "O::inserted",at,s,a,v
    def erased(self,at,s):
        print "O::erased",at,s
    def shaded(self,at,s,h):
        print "O::shaded",at,s,h

o=O()
g.add_observer(o)
