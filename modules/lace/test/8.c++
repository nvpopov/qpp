#include <lace/lace.hpp>
#include <iostream>
#include <boost/format.hpp>

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

  int n=5;
  dcomplex Ione(0,1);

  matrix<dcomplex,rectang> A(n);  

  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      A(i, j+i - ((j+i)>=n ? n:0) ) = j + Ione*i;

  prnmtr(A);
}

