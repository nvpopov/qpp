#include <geom/lace3d.hpp>
#include <symm/symm.hpp>
#include <symm/group_theory.hpp>
#include <iostream>
#include <boost/format.hpp>
#include <iomanip> 

using namespace qpp;

int main()
{
  /*
  auto C3 = RotMtrx({0,0,1},2*pi/3);
  auto Sig = Sigma<double>({0,1,0});

  generated_group<matrix3d<double> > T;
  T.generator(C3);
  T.generator(Sig);
  */
  
  auto C4 = RotMtrx({1,0,0},pi/2);
  auto C3 = RotMtrx({1,1,1},2*pi/3);
  auto C31 = RotMtrx({1,-1,-1},2*pi/3);
  generated_group<matrix3d<double> > T;
  T.generator(C4);
  T.generator(C3);
  // T.generator(C31);

  std::cout << "Group size = " << T.size() << std::endl;

  std::cout << std::setprecision(6) << std::fixed;

  for (int g=0; g<T.size(); g++)
    std::cout << g << std::endl << T[g] << std::endl;

  group_analyzer<decltype(C3), decltype(T)> A(T);

  std::cout << "N classes = " << A.n_classes() << "\n";
  for (int c=0; c< A.n_classes(); c++)
    {
      for (int j=0; j<A.class_size(c); j++)
	std::cout << A.class_element(c,j) << " ";
      std::cout << std::endl;
    }

  group_characters<std::complex<double>,decltype(C3), decltype(T)> chi(T,A);
  //group_characters<double,decltype(C3), decltype(T)> chi(T,A);

  std::cout << "N IRREP = " << chi.nirrep << std::endl;

  /*
  for (int irrep = 0; irrep < chi.nirrep; irrep++)
    {
      
    }*/

  std::cout << chi.chi << std::endl;
}
