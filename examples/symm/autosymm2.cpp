#include <symm/symm.hpp>
#include <symm/autosymm.hpp>
#include <symm/gcell.hpp>
#include <symm/group_theory.hpp>
#include <iostream>

using namespace qpp;

int main()
{

  vector3d<double> n,T;
  double phi;
  matrix3d<double> R;
  int inv;

  std::cout << "axis= ";
  std::cin >> n.x() >> n.y() >> n.z();
  n = n/norm(n);

  std::cout << "phi= ";
  std::cin >> phi;

  std::cout << "T= ";
  std::cin >> T.x() >> T.y() >> T.z();

  std::cout << "inv= ";
  std::cin >> inv;
  inv /= std::abs(inv);
  
  R = RotMtrx(n,phi)*inv;

  std::cout << "R = " << R << " T= " << T << "\n";

  linear3d_subspace<double> L = invariant_subspace(rotrans<double>(T,R));

  std::cout << "dim= " << L.dim << " pt= " << L.pt << " n= " << L.n << "\n";
}

