#include <symm/symm.hpp>
#include <lace/lace3d.hpp>
#include <iostream>
#include <cmath>

int main()
{
  lace::matrix3d<double> E(1e0);
  qpp::symmetry<lace::matrix3d<double> > G(E);

  double s = 1e0/sqrt(2e0);
  lace::matrix3d<double> A( s,    -s,  0e0,
			    s,     s,  0e0,
			    0e0, 0e0,  1e0);
  
  G.generator(A);

  for (int i=0; i<G.size(); i++)
    std::cout << G(i) << "\n";

//   lace::matrix3d<double> B = A*A, C = B*B;

//   bool eq =  (E==C*C);

//   std::cout << A << B << B*A << C << C*C << eq << "\n";

}
