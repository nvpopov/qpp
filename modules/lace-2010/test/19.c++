#include <lace/lace.hpp>
#include <iostream>
using namespace lace;


template <class VALTYPE,matrix_type MT >
void prnmtr(matrix<VALTYPE,MT> &A)
{
  for(int i=0; i<A.size(0); i++)
    {
      for(int j=0; j<A.size(1); j++)
	std::cout << boost::format("%10.5f ") % A(i,j);
      std::cout << "\n";
    }
}

template <class VALTYPE,vector_type VT >
void prnvtr(vector<VALTYPE,VT> &A)
{
  for(int i=0; i<A.size(); i++)
    std::cout << boost::format("%10.5f ") % A(i);
  std::cout << "\n";
}

int main()
{
  int N=10;
  matrix<double,symmetric> S(N);

  S = 0e0;
  for (int i=0; i<N; i++)
    {
      S(i,i)=3;
      S(i, i+1==N ? 0:i+1) = 2;
    }
  //  prnmtr(S);
  vector<double> E(N);
  matrix<double> X(N);

  diagon(S,E,X);

  prnvtr(E);
  std::cout<<"\n";
  prnmtr(X);
}
