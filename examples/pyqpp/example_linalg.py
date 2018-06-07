import sys
sys.path.append("../../build/modules")
import pyqpp

print('\n=============Test matrix __str__ :===========')
m1 = pyqpp.matrix3d(1.0)
print(m1)
print('=============================================\n')

print('\n=============Test matrix add  :==============')
m1 = pyqpp.matrix3d(1.0)
m1.xy = 3.2
m1.xz = 2.1
m2 = pyqpp.matrix3d(2.0)
m2.yz = 1.2
m3 = m1+m2
print(m3)
print('=============================================\n')

print('\n=============Test matrix det  :==============')
m1 = pyqpp.matrix3d(1.0)
m1.xy = 4.2
m1.xz = 12.1
m2 = pyqpp.matrix3d(2.0)
m2.yz = 1.2
m2.xz = 7.2
m3 = pyqpp.matrix3d(4)
m3 = m1+m2
print(m3)
print(m3.det())
print('=============================================\n')

