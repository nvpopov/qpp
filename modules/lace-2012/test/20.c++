#include <lace/lace.hpp>
#include <iostream>
using namespace lace;

template<class VALTYPE>
class fmt
{
public:
  static std::string fm(VALTYPE x)
  { 
    std::stringstream ss;
    ss << boost::format("%10.5f ") % x;
    return ss.str();
  }
};

template<>
class fmt<lace::dcomplex>
{
public:
  static std::string fm(lace::dcomplex x)
  {
    std::stringstream ss;
    ss << x << " ";
    return ss.str();
  }
};

template <matrix_type MT , class VALTYPE>
void prnmtr(lace::matrix<VALTYPE,MT> &A)
{
  for(int i=0; i<A.size(0); i++)
    {
      for(int j=0; j<A.size(1); j++)
	std::cout <<  fmt<VALTYPE>::fm(A(i,j));
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
  int N=6, M=3, MXRND=123671253;

  matrix<lace::dcomplex> n(N,M);
  lace::dcomplex I(0,1);

  for (int i=0; i<N; i++)
    for (int j=0; j<M; j++)
      n(i,j) = 1e0*(rand()%MXRND)/MXRND - .5e0 + I*(1e0*(rand()%MXRND)/MXRND - .5e0);

  for (int j=0; j<M; j++)
    {
      double s=0e0;
      for (int i=0; i<N; i++)
	s += lace::norm2(n(i,j));
      n(sub::full,sub(j,j)) = n(sub::full,sub(j,j))/std::sqrt(s);
    }

  prnmtr(n);

  vector<lace::dcomplex> nn(N);
  nn = n(sub::full,0);
  
  std::cout << "\n";
  prnvtr(nn);

  matrix<lace::dcomplex> A(N);

  A = n(sub::full,0)*n(sub::full,0).H();
  std::cout << "Outer product\n";

  matrix<lace::dcomplex,hermitian> AA(N);

  for (int i=0; i<N; i++)
    for(int j=0; j<=i; j++)
      AA(i,j) = A(i,j);
  prnmtr(AA);

  n.resize(N,N);

  lace::vector<double> eig(N);
  diagon(AA,eig,n);

  std::cout << "Eig\n";
  prnvtr(eig);

  std::cout << "Eigv:\n";
  prnmtr(n);

}
