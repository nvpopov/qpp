#include <cassert>
#include <cstring>
#include <lace/matrix.hpp>
#include <lace/engine.hpp>
#include <lace/wizard_instance.hpp>
#include <string>
#include <sstream>
#include <boost/format.hpp>
#include <lace/lace.hpp>

template<class Z>
std::string zfmt(Z z, int dig = 10 , int prec = 5)
{
  std::basic_ostringstream<char> _fmt;
  _fmt << "%" << dig << "." << prec << "f";

  std::basic_ostringstream<char> _ifmt;
  _ifmt << "%-" << dig << "." << prec << "f";

  std::basic_ostringstream<char> __s;
  if ( z.im() >= 0e0 )
    __s << (boost::format(_fmt.str()) % z.re()) << "+i*" << (boost::format(_ifmt.str()) % z.im());
  else
    __s << (boost::format(_fmt.str()) % z.re()) << "-i*" << (boost::format(_ifmt.str()) % (-z.im()));
  return  __s.str();
}

template <class VALTYPE,lace::matrix_type MT >
void prnmtr(lace::matrix<VALTYPE,MT> &A)
{
  for(int i=0; i<A.size(0); i++)
    {
      for(int j=0; j<A.size(1); j++)
	std::cout << boost::format("%10.5f ") % A(i,j);
      std::cout << "\n";
    }
}

int main()
{

	using lace::sub;
	lace::matrix<double,lace::rectang> A(5,5), B(5,5), C(5,5), D(2,2);

	B(0,0) = B(1,1) = B(0,1) = 1/sqrt(2e0);
	A(0,0) = A(0,1) = A(3,3) = A(4,4) = 2;
	C = B+A;
	prnmtr(C);
}

