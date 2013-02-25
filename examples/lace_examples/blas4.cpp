#include<lace/blas_mtr.hpp>
#include<lace/blas_vtr.hpp>
#include<lace/blas_mv.hpp>
#include<iostream>
#include<boost/format.hpp>

using namespace _lace_storage;
using _lace_expressions::sub;

int main()
{
  int N=10, M=10;
  matrix_storage<double,rectang> A(N,M);
  
  for (int i=0; i<N; i++)
    for( int j = 0; j<M; j++)
      A(i,j) = i + .1*j;

  std::cout << " -------------------- A -------------------\n";
  for (int i=0; i<N; i++)
    {
      for( int j = 0; j<M; j++)
	std::cout << boost::format("%8.3f")%A(i,j);
      std::cout << "\n";
    }

  vector_storage<double> v(N);

  fill_vtr(v,0e0);
  mtr_row(v,sub(0,10,3),A,4,sub(0,6,2),1e0);

  std::cout << " -------------------- v -------------------\n";
  for (int i=0; i<v.size(); i++)
    std::cout << boost::format("%8.3f")%v(i);
  std::cout << "\n";
}
