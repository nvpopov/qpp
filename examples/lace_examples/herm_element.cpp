//#define SMART_HERMITIAN

#include <lace/storage.hpp>
//#include <lace/prnmv.hpp>
#include <iostream>

using namespace _lace_storage;

int main()
{
  int N = 5;
  matrix_storage<lace::dcomplex,hermitian> A(matrix_shape(hermitian,N,N));

  A.setval(0e0);

  lace::dcomplex I(0,1);
  A(1,2) = 2+I;

  A(3,2) = 2+3*I;

  for (int i=0; i < N; i++)
    {
      for (int j=0; j<N; j++)
	std::cout << A(i,j) << "   ";
      std::cout << "\n";
    }
}
