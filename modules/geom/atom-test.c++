#include <iostream>
#include <atom.hpp>

int main()
{
  qpp::classical_atom a,b;
  qpp::polarisible_atom c,d;

  a.name="Li";
  a.number=3;
  a.mass=7;
  a.charge=0;

  b.name="Li_Cl";
  b.number=3;
  b.mass=7;
  b.charge=0;

  std::cout << (a==b) << "\n";
}
