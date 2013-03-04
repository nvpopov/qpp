#include<iostream>
#include<boost/format.hpp>
#include<cmath>
#include<lace/lace.hpp>
#include<lace/shape.hpp>

using namespace lace;

int main()
{
  int N = 6, M = 5;
  matrix<double,rectang> A(N,M), B(N,M);

  A = 1e0;

  for (int i=0; i<B.size(0); i++)
    for (int j=0; j<B.size(1); j++)
      B(i,j) = i+j*.1;

  //  A = A + B;

  A(sub(0,M-1,2),sub(0,M-1)) = B(sub(0,M-1),sub(0,M-1,2)).T();

  for (int i=0; i<A.size(0); i++)
    {
      for (int j=0; j<A.size(1); j++)
	std::cout << boost::format("%8.3f")%A(i,j);
      std::cout << "\n";
    }
}
