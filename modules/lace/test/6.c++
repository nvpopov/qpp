#include <iostream>
#include <lace/lace.hpp>
#include <lace/complex.hpp>

using namespace lace;

const int N=5;

// template<typename VALTYPE>
// class mtr{
//   VALTYPE val[N*(N+1)/2];
// public:
  
//   inline typename _hermitian_element<VALTYPE>::type operator()(int i, int j)
//   {
//     if ( j >= i )
//       return _hermitian_element<VALTYPE>::newelem(val[ j*(j+1)/2 + i ],false);
//     else
//       return _hermitian_element<VALTYPE>::newelem(val[ i*(i+1)/2 + j ],true);
//   }
// };

int main()
{
  lace::dcomplex I(0,1);

  lace::matrix<lace::dcomplex,hermitian> A(N);

  for (int i=0; i<N; i++)
    for (int j=0; j<=i; j++)
      A(i,j) = .2*i + j*I*.3;

  std::cout << "-----------------\n";
  for (int i=0; i<N; i++)
    {
      for (int j=0; j<N; j++)
	std::cout << " " << A(i,j);
      std::cout << "\n";
    }

  lace::matrix<double,symmetric> B(N);
  for (int i=0; i<N; i++)
    for (int j=0; j<=i; j++)
      B(i,j) = 0.1*i + j;
  std::cout << "-----------------\n";
  for (int i=0; i<N; i++)
    {
      for (int j=0; j<N; j++)
	std::cout << " " << B(i,j);
      std::cout << "\n";
    }

  lace::matrix<double,rectang> C(N,N+2);
  for (int i=0; i<N; i++)
    for (int j=0; j<N+2; j++)
      C(i,j) = i*j;
  std::cout << "-----------------\n";
  for (int i=0; i<N; i++)
    {
      for (int j=0; j<N+2; j++)
	std::cout << " " << C(i,j);
      std::cout << "\n";
    }
  //  _complex_reference<lace::dcomplex>(I,true) = 1.0;

}
