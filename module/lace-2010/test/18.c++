#include <cassert>
#include <cstring>
// #include <lace/matrix.hpp>
// #include <lace/engine.hpp>
// #include <lace/wizard_instance.hpp>
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
  B(1,0) = -1/sqrt(2e0);

//   C(0,0) = C(1,1) = .5e0;
//   C(0,1) =  sqrt(3e0)/2;
//   C(1,0) = -sqrt(3e0)/2;

  C(0,0) = C(1,1) = C(0,1) = 1/sqrt(2e0);
  C(1,0) = -1/sqrt(2e0);

  C = 3.33333e0;
  
  for(int i=0; i<C.size(0); i++)
    for(int j=0; j<C.size(1); j++)
      C(i,j) = i + 0.1e0*j;

  std::cout << "MATRIX B\n";
  prnmtr(B);
  
  //  C = B;

  std::cout << "MATRIX C\n";
  prnmtr(C);

  B(sub(2,4,2),sub(2,4,2)) = B(sub(0,1),sub(0,1));

  std::cout << "MATRIX B\n";
  prnmtr(B);
  //  B(sub(0,1),sub(3,4)) = B(sub(0,1),sub(0,1));

  
//   A = (B( sub::full, 2|sub::full )*B( sub(1,4), sub(1,4) ) + C) + 0.1e0*A*B 
//     + C.T()*(B( sub(1,4), sub(1,4) )*B( sub(1,4), sub(1,4) ) + C);

//   prnmtr(B);
//   std::cout << "-------------\n";
//   B(sub(0,4),sub(0,1)) = B(sub(0,1),sub(0,4)).T();
//   prnmtr(B);
//   A = 1e0*C;

  //  B( sub(3,4), sub(3,4)) = C( sub(6,9,3), sub(0,3,2) ) + B( sub(0,1,1), sub(0,1,1)).T();
  //B( sub(3,4), sub(3,4)) = C + 4e0*B
  //A = ( A+B*C).T() + C*( A+B*C);
  //C =  A + 2e0*( B + 3e0*( C + 4e0*D) ) + 3.14*A + B + (10e0*(A+C.T())).T() + ( C + 4e0*D) ;

//   A = (B*B + 4e0*C( sub(0,4), sub(0,4) )) + (B + 4e0*C( sub(0,4), sub(0,4) )).T();

  //  B( sub(3,4), sub(3,4) ) = B( sub(0,1), sub(0,1) );
  
//   std::cout << "MATRIX B\n";
//   prnmtr(B); 

//  A = B*B + 0.1e0*(B*B).T();
//   prnmtr(A);
//   std::cout << "MATRIX B\n";
//   for(int i=0; i<B.size(0); i++)
//     {
//       for(int j=0; j<B.size(1); j++)
// 	std::cout << boost::format("%10.5f ") % B(i,j);
//       std::cout << "\n";
//     }

//   std::cout << "MATRIX A\n";
//   for(int i=0; i<A.size(0); i++)
//     {
//       for(int j=0; j<A.size(1); j++)
// 	std::cout << boost::format("%10.5f ") % A(i,j);
//       std::cout << "\n";
//     }

//   A = B*B.T() + B*C.T();

//   std::cout << "MATRIX A\n";
//   prnmtr(A);

//   std::cout << "MATRIX A\n";
//   for(int i=0; i<A.size(0); i++)
//     {
//       for(int j=0; j<A.size(1); j++)
// 	std::cout << boost::format("%10.5f ") % A(i,j);
//       std::cout << "\n";
//     }



}

