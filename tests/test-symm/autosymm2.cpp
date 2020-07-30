#include <symm/groups.hpp>
#include <symm/autosymm.hpp>
#include <symm/gen_cell.hpp>
#include <symm/group_theory.hpp>
#include <iostream>
#include <optional>

using namespace qpp;

int main(){

  vector3<double> n,T;
  double phi;
  matrix3<double> R;
  int inv;

  std::cout << "axis= ";
  std::cin >> n.x() >> n.y() >> n.z();
  n = n / n.norm();

  std::cout << "phi= ";
  std::cin >> phi;

  std::cout << "T= ";
  std::cin >> T.x() >> T.y() >> T.z();

  std::cout << "inv= ";
  std::cin >> inv;
  inv /= std::abs(inv);

  R = RotMtrx(n,phi)*inv;

  std::cout << "R = " << R << " T= " << T << "\n";

  std::optional<subspace3<double> > L = invariant_subspace(rotrans<double>(T,R));

  if (L) std::cout << "dim= " << (*L).dim << " pt= " << (*L).point << " n= " << (*L).axis << "\n";
}

