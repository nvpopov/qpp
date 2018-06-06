import sys
sys.path.append("../../build/modules")
import pyqpp

class CustomObserver(pyqpp.gobserver_d):
	
	def added (self,s,a,v):
		print("Observer::added",s,a,v)
		
	def inserted (self,at,s,a,v):
		print("Observer::inserted",at,s,a,v)
		
	def changed (self,at,s,a,v):
		print("Observer::changed",at,s,a,v)
		
	def erased (self,at,s):
		print("Observer::erased",at,s)
		
	def shaded (self,at,s,h):
		print("Observer::shaded",at,s,h)
		
	def reordered (self,ord_, s):
		print("Observer::reordered",ord_, s)					

v1 = pyqpp.vector3d(0.0,1.0,1.0)
print(v1)

g1 = pyqpp.geometry_d(0)
obs1 = CustomObserver()
g1.add_observer(obs1)
g1.add('C',1.0,1.0,1.0)
g1.add('C',2.0,1.0,1.0)
g1.add('C',3.0,1.0,1.0)
g1.add('H',1.0,1.0,1.0)
g1.erase(2)

print("Number of atoms is {0}".format(g1.nat()))
print("Number of atom types {0}".format(g1.n_types()))
