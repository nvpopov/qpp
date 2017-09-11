#include <symm/symm.hpp>
#include <symm/autosymm.hpp>
#include <symm/gcell.hpp>
#include <symm/group_theory.hpp>
#include <iostream>

using namespace qpp;

int main()
{

  vector3d<double> a1,a2,b1,b2,n;
  double phi;
  matrix3d<double> R;

  std::cout << "a1= ";
  std::cin >> a1.x() >> a1.y() >> a1.z();

  std::cout << "b1= ";
  std::cin >> b1.x() >> b1.y() >> b1.z();

  std::cout << "a2= ";
  std::cin >> a2.x() >> a2.y() >> a2.z();

  std::cout << "b2= ";
  std::cin >> b2.x() >> b2.y() >> b2.z();
  
  rotate_pair(R,a1,a2,b1,b2);

  std::cout << " n= " << n << " phi= " << phi*180/pi << "\n";
  std::cout << "R= " << R << "\n";
  std::cout << "Should be:\n";
  std::cout << " b1= " << R*a1 << " b2= "  << R*a2 << "\n";

}

