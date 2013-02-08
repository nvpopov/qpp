#include <cassert>
#include <cstring>
#include <lace/lace.hpp>
#include <string>
#include <sstream>
#include <boost/format.hpp>
#include <lace/matrix_expressions.hpp>

using _lace_expressions::matrix_expression;
using lace::sub;

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

template <class VALTYPE,_lace_storage::matrix_type MT >
void prnmtr(_lace_expressions::matrix<VALTYPE,MT> &A)
{
  for(int i=0; i<A.size(0); i++)
    {
      for(int j=0; j<A.size(1); j++)
	std::cout << boost::format("%10.5f ") % A(i,j);
      std::cout << "\n";
    }
}

template <class VALTYPE,_lace_storage::vector_type VT >
void prnvtr(_lace_expressions::vector<VALTYPE,VT> &A)
{
  for(int i=0; i<A.size(); i++)
    std::cout << boost::format("%10.5f ") % A(i);
  std::cout << "\n";
}

int main()
{
  lace::matrix<double,lace::rectang> A(2,3),B(3,4),C(2,4), AT(3,2), BT(4,3), A1(6), B1(10), C1(10);

  //  lace::matrix<double,lace::symmetric> S(3);

  //  lace::vector<double> v(3),u(3),w(3),u1(10);


  //  std::cout << S.xpr_total_number << "\n";

//   A=0e0;
//   A(0,0)=A(1,1)=A(2,2)=2;

//   B=0e0;
//   B(0,1)=B(1,2)=1;

//   C=0e0;

//   S=0e0;
//   S(0,1) = S(1,2) = 1;
//   S(0,2) = 2;

// //   v(0)=v(1)=v(2)=1./sqrt(3.);

// //   u = 0.1e0;


//   C = 2.*(A*B*A+B) + (S*B+B)*A.T() + u%(v+A*v);


  for (int i=0; i<3; i++)
    {
      A(0,i)=i+1;
      A(1,i)=i+4;
    }

  B(0,0)=B(1,1)=B(2,2)=B(0,3)=B(1,3)=B(2,3)=1;

  BT = B.T();
  AT = A.T();

  C = A*BT.T();

  std::cout << "A\n";
  prnmtr(A);
  std::cout << "B\n";
  prnmtr(B);
  std::cout << "C\n";
  prnmtr(C);

  lace::vector<double> v(10);

  v=0e0;
  v(sub(2,6,2)) = 1e0;
  v(sub(1,7,3)) *= 2;

  prnvtr(v);

  lace::matrix<double,lace::triang> T(6,6,lace::matrix_shape::lower);
  double *x = &T(0,0);
  int n = T.size(0);
  for (int i = 0; i<n*(n+1)/2; i++)
    *(x+i) = i;

  std::cout << " -------- T: ----------\n";
  prnmtr(T);

  lace::matrix<double> R(n);
  v.resize(n);
  for (int i = 0; i<v.size(); i++)
    v(i) = i;

  R = v%v;

  std::cout << " -------- R: ----------\n";
  prnmtr(R);

  R = R + T;
  
  std::cout << " -------- R+T: ----------\n";
  prnmtr(R);

//   A1(sub(0,5,2), sub(1,4,3)) = A.T();
//   B1(sub(4,7),sub(3,9,3)) = B.T();

//   C1(sub(1,3,2),sub(2,8,2))=A1(sub(0,5,2), sub(1,4,3)).T()*B1(sub(4,7),sub(3,9,3)).T();

//   std::cout << "A\n";
//   prnmtr(A1);
//   std::cout << "B\n";
//   prnmtr(B1);
//   std::cout << "C\n";
//   prnmtr(C1);

//   std::cout << "C\n";
//   prnmtr(C);
  

//   u = 0e0;
//   u(0)= 1e0;

//   v = B*u;

//   std::cout << "v\n";
//   prnvtr(v);

//   C = A*B + B;
//   std::cout << "A*B+B\n";
//   prnmtr(C);

//   std::cout << "C=2.*(A*B+B) + (A*B+B).T()\n";
//   C = 2.*(A*B+B) + (A*B+B).T();
//   prnmtr(C);

//   std::cout << "C=2.*(A*B+B) + (A*B+B).T()+S\n";
//   C = 2.*(A*B+B) + (A*B+B).T() + S.T();
//   prnmtr(C);

//   std::cout << "v\n";
//   prnvtr(v);
//   std::cout << "u\n";
//   prnvtr(u);

//   u=0e0;
//   v=0e0;

//   u(1)=1;
//   v(2)=1;
//   for (int i=0; i<10; i++)
//     u1(i) = i+1;
//   //  v(sub(0,1)) = 2.*u(sub(1,2)) + 3.*u(sub(0,1));//+A*u+B*(A*u);
//   v = 2.*v + u1(sub(0,4,2));
  
  
//   lace::matrix<double,lace::rectang> A(3);
//   double s2 = std::sqrt(.5);

//   A(0,0) = s2;  A(0,1) = -s2; A(0,2) = 0e0;
//   A(1,0) = s2;  A(1,1) =  s2; A(1,2) = 0e0;
//   A(2,0) = 0e0; A(2,1) = 0e0; A(2,2) = 1e0;

//   lace::vector<double,lace::dense> u(3), v(3), w(4);
//   u(0) = 1e0; u(1) = 0e0; u(2) = 1e0;
//   w=0e0;
//   w(3) = 3.3;


//   v = 2.*(u+w(sub(1,3)) +(u+w(sub(1,3)).T ;


//   std::cout << "result:\n";
//   prnvtr(v);

  std::cout << A.xpr_total_number << "\n";
}
