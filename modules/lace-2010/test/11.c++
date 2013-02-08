#include <cassert>
#include <cstring>
#include <lace/lace.hpp>
#include <string>
#include <sstream>
#include <boost/format.hpp>
#include <lace/lace3d.hpp>
#include <cmath>

using namespace lace;

template <class VALTYPE,_lace_storage::matrix_type MT >
void prnmtr(_lace_expressions::matrix<VALTYPE,MT> &A)
{
  for(int i=0; i<A.size(0); i++)
    {
      for(int j=0; j<A.size(1); j++)
	std::cout << boost::format("%10.5f ") % A(i,j);
      std::cout << "\n";
    }
}

template <class VALTYPE,_lace_storage::vector_type VT >
void prnvtr(_lace_expressions::vector<VALTYPE,VT> &A)
{
  for(int i=0; i<A.size(); i++)
    std::cout << boost::format("%10.5f ") % A(i);
  std::cout << "\n";
}


int main()
{
  double pi = 4.*std::atan(1.0);
  std::cout << "pi= " << pi << "\n";
  matrix3d<double> a = RotMtrx( vector3d<double>(1,1,1), pi/4);

  matrix<double> A(3);

  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      A(i,j) = a(i,j);

  prnmtr(A);

  vector<double> u(3), v(3);

  u=0;
  u(0)=1e0;

  v = A.T()*u;

  std::cout << "v:\n";
  prnvtr(v);
}
