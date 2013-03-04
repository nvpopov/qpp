#include<iostream>
#include<boost/format.hpp>
#include<cmath>
#include<lace/lace.hpp>
#include<lace/shape.hpp>

using namespace lace;

void prnmtr( matrix<double,rectang> &C)
{
  for (int i=0; i<C.size(0); i++)
    {
      for (int j=0; j<C.size(1); j++)
	std::cout << boost::format("%8.3f")%C(i,j);
      std::cout << "\n";
    }
}


int main()
{
  int N = 6, M = 5;
  matrix<double,rectang> A(N,M), B(N,M), C;

  A = 1e0;

  for (int i=0; i<B.size(0); i++)
    for (int j=0; j<B.size(1); j++)
      B(i,j) = i+j*.1;

  prnmtr(B);
  std::cout << "\n\n";

  //lace::globals::debug = true;
  //  A = A + B;

  lace::globals::debug = true;

  C = B(sub(0,M-1),sub(0,M-1,2)).T();
  //A(sub(0,M-1,2),sub(0,M-1)) 

  prnmtr(C);
}
