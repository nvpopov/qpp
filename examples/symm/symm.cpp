#include <fmt/format.h>
#include <iostream>
#include <geom/lace3d.hpp>
#include <symm/symm.hpp>
#include <symm/group_theory.hpp>
//#include <boost/format.hpp>

using namespace qpp;

void prnmtr(const matrix3<double> & M){
  for (int i=0; i<3; i++)
    {
      for (int j=0; j<3; j++)
        std::cout << fmt::format("{10.6f }", M(i,j));
      std::cout << std::endl;
    }
}

int main(){
  auto C3 = RotMtrx({0,0,1},2*pi/3);
  auto Sig = Sigma<double>({0,1,0});

  std::cout << "C3 = " << C3 << " Sig= " << Sig << "\n";

  generators_pack<matrix3<double> > G({C3,Sig});
  std::vector<matrix3<double> > g;

  G.generate(g);

  for (auto t : g)
    std::cout << t << std::endl;

  std::cout << "--------------------------------" << std::endl;

  generated_group<matrix3<double> > T;

  T.add( RotMtrx({1,1,1}, 2*pi/3) );
  T.add( RotMtrx({1,-1,-1}, 2*pi/3) );
  T.add( RotMtrx({1,1,0}, pi) );

  for (int i=0; i<T.size(); i++){
      std::cout << i << std::endl;
      prnmtr(T[i]);
    }

  std::cout << T.size() << std::endl;

  //  analyse_group<matrix3d<double>, decltype(T) > A(T);
  //group_analyzer< matrix3d<double>, decltype(G) > A(G);
  group_analyzer< matrix3<double>, decltype(g) > A(g);

  std::cout << "Multiplication table:\n";

  for (int i=0; i<g.size(); i++){
      std::cout << fmt::format("{3i} |", i);
      for (int j=0; j<g.size(); j++)
        std::cout << fmt::format("{3i}  ", A.multab(i,j));
      std::cout << std::endl;
    }

  std::cout << "N classes = " << A.n_classes() << "\n";
  for (int c=0; c < A.n_classes(); c++){
      for (int j=0; j < A.class_size(c); j++)
	std::cout << A.class_element(c,j) << " ";
      std::cout << std::endl;
    }
}
