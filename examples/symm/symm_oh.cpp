#include <symm/symm.hpp>
#include <symm/group_theory.hpp>
#include <iostream>

using namespace qpp;

void prnmtr(const matrix3d<double> & M)
{
  for (int i=0; i<3; i++)
    {
      for (int j=0; j<3; j++)
        //Migrate to fmt
        //std::cout << boost::format("%10.6f ") % M(i,j);
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
  
  for (int i=0; i<OH.size(); i++)
    {
      std::cout << i << std::endl;
      prnmtr(OH[i]);
    }
  std::cout << OH.size() << std::endl;

  int i1 = OH.index(C4x),
    i2 = OH.index(C4y);

  std::cout <<"C4x index is " << i1 << " C4y index is " << i2 << std::endl;

  group_analyzer< matrix3d<double>, decltype(OH) > AOH(OH);

  std::cout << "Abelian subgroup of C4x: ";
  for (int g : AOH.abelian_sub(i1))
    std::cout << g << " ";
  std::cout << "\n";

  std::cout << " Two subgroup product: ";
  for (int g : AOH.mul_subs(AOH.abelian_sub(i1),AOH.abelian_sub(i2)))
    std::cout << g << " ";
  std::cout << "\n";
  
  std::vector<int> ee = {0}, gg = AOH.find_generators(ee);

  std::cout << "generators ";
  for (int g : gg)
    std::cout << g << " ";
  std::cout << "\n";

}
