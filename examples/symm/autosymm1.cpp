
#include <symm/symm.hpp>
#include <symm/autosymm.hpp>
#include <symm/gcell.hpp>
#include <symm/group_theory.hpp>
#include <iostream>
#include <fmt/format.h>

using namespace qpp;

void prnmtr(const matrix3d<double> & M)
{
  for (int i=0; i<3; i++)
    {
      for (int j=0; j<3; j++)
        std::cout << fmt::format("{10.6} ", M(i,j));
      std::cout << std::endl;
    }
}

int main()
{
  matrix3d<double> C4x = RotMtrx({1,0,0},pi/2);
  matrix3d<double> C4y = RotMtrx({0,1,0},pi/2);
  matrix3d<double> I(-1);

  generated_group<matrix3d<double> > OH;

  OH.add(C4x);
  OH.add(C4y);
  OH.add(I);

  //matrix3d<double>::tol_equiv = 1e-6;

  generalized_cell<double,matrix3d<double> > Oh = generator_form<matrix3d<double>, decltype(OH)>(OH);

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
  UF6.add("F_shl", 0, 0,-3.01);

  std::cout << has_symmetry(UF6, Oh) << "\n";
}
