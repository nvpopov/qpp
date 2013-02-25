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

  //  globals::preserv_matrix = false;

  dcomplex Ione(0,1);

  int n = 5;
  matrix<dcomplex,rectang> A(n), B(n), C(n);

  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      A(i, j+i - ((j+i)>=n ? n:0) ) = j+ Ione*i;

  prnmtr(A);

//   C=0;
//   for (int i=0; i<n; i++)
//     C(i,i)=1;
  
//   solve_lu(A,C,B);

  invert(A,B);

  std::cout << "The inverse matrix:\n";

  prnmtr(B);

  std::cout << "------- Check A --------\n";
  prnmtr(A);

  C=A*B;
  std::cout << "------- Check --------\n";
  prnmtr(C);

//   vector<double> x(n), y(n);

//   x=0;
//   x(2)=1;

//   y = A*x;

//   std::cout << " ------ x: ----------\n";
//   prnvtr(x);
//   std::cout << " ------ y: ----------\n";
//   prnvtr(y);

//   solve_lu(A,y,x);
//   std::cout << " ------ solve_lu: ----------\n";
//   prnvtr(x);

}
