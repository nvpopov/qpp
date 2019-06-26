
#include <symm/groups.hpp>
#include <symm/autosymm.hpp>
#include <symm/gen_cell.hpp>
#include <symm/group_theory.hpp>
#include <iostream>
#include <fmt/format.h>

using namespace qpp;

void prnmtr(const matrix3<double> & M){
  for (int i=0; i<3; i++)
    {
      for (int j=0; j<3; j++)
        std::cout << fmt::format("{} ", M(i,j));
      std::cout << std::endl;
    }
}

int main()
{
  matrix3<double> C4x = RotMtrx({1,0,0}, pi/2);
  matrix3<double> C4y = RotMtrx({0,1,0}, pi/2);
  matrix3<double> I = matrix3<double>::Identity()*-1;

  array_group<matrix3<double> > OH;

  OH.generate(C4x);
  OH.generate(C4y);
  OH.generate(I);

  //matrix3d<double>::tol_equiv = 1e-6;

  gen_cell<double,matrix3<double> > Oh;
  generator_form(Oh,OH);

  for (int d=0; d < Oh.DIM; d++)
    {
      std::cout << "generator " << d << "\n";
      prnmtr(Oh.generators[d]);
    }
  std::cout << "orders: " << Oh.begin() << Oh.end() << "\n";

  geometry<double, decltype(Oh) > UF6(0);
  UF6.add("U",0,0,0);
  UF6.add("F", 3, 0, 0);
  UF6.add("F",-3, 0, 0);
  UF6.add("F", 0, 3, 0);
  UF6.add("F", 0,-3, 0);
  UF6.add("F", 0, 0, 3);
  UF6.add("F", 0, 0,-3);

  UF6.add("F_shl", 3, 0, 0);
  UF6.add("F_shl",-3, 0, 0);
  UF6.add("F_shl", 0, 3, 0);
  UF6.add("F_shl", 0,-3, 0);
  UF6.add("F_shl", 0, 0, 3);
  UF6.add("F_shl", 0, 0,-3.0);

  std::cout << has_symmetry(UF6, Oh) << "\n";
}
