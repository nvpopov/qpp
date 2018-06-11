import sys
sys.path.append("../../build/modules")
import pyqpp.ptable as pt

print(pt.get_atom_name_by_number(22))
print(pt.get_atom_symbol_by_number(21))
print(pt.get_atom_number_by_name("Silicon"))
print(pt.get_atom_number_by_symbol("Si"))
print(pt.get_atom_symbol_by_number(14))
print(pt.get_atom_mass_by_number(14))


