#include<lace/blas_mtr.hpp>
#include<lace/blas_vtr.hpp>
#include<lace/blas_mv.hpp>
#include<iostream>
#include<boost/format.hpp>
#include<cmath>

using namespace _lace_storage;
using _lace_expressions::sub;

int main()
{
  int N=10, M=9, L=8;
  matrix_storage<double,rectang> A(N,L), B(N,M+1), C(M,L);

  fill_mtr(B,0e0);
  for (int i=0; i<B.size(0) && i<B.size(1)+1; i++)
    B(i,i+1) = 1e0;

  std::cout << "-------------- B ------------ \n";
  for (int i=0; i<B.size(0); i++)
    {
      for (int j=0; j<B.size(1); j++)
	std::cout << boost::format("%8.3f")%B(i,j) << " ";
      std::cout << "\n"; 
    }

  for (int i=0; i<C.size(0); i++)
    for (int j=0; j<C.size(1); j++)
      C(i,j) = std::log(i+1) + 2*std::log(j+1);

  std::cout << "-------------- C ------------ \n";
  for (int i=0; i<C.size(0); i++)
    {
      for (int j=0; j<C.size(1); j++)
	std::cout << boost::format("%8.3f")%C(i,j) << " ";
      std::cout << "\n"; 
    }

  fill_mtr(A,0e0);
  mul_mtr(A,B,C,1e0,1e0, 0, 0);

  std::cout << "-------------- B*C ------------ \n";
  for (int i=0; i<A.size(0); i++)
    {
      for (int j=0; j<A.size(1); j++)
	std::cout << boost::format("%8.3f")%A(i,j) << " ";
      std::cout << "\n"; 
    }
}
