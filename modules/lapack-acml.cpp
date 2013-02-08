#include "lapack.hpp"

#include <acml.h>

#include <boost/numeric/ublas/fwd.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/blas.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/detail/matrix_assign.hpp>
#include <boost/numeric/ublas/symmetric.hpp>
#include <boost/numeric/ublas/hermitian.hpp>

#include <boost/numeric/ublas/io.hpp>
#include <boost/format.hpp> 

#include <boost/progress.hpp>
//#include <iostream>

namespace boost{
  namespace numeric{
    namespace ublas  {

      int last_info;

      void sv_decompose( matrix_double &a, vector<double> &sigma, matrix_double &u, matrix_double &vt)
      {
	// call the BLAS SVD and return
	// a = u * singl * v^T

	int m = a.size1();
	int n = a.size2();
	int info;

	assert( u.size1() == m && u.size2() == m );
	assert( vt.size1() == n && vt.size2() == n );
	assert( sigma.size() >= n || sigma.size() >= m );

	dgesdd('a', m, n, &a(0,0), m, &sigma(0), &u(0,0), m, &vt(0,0), n, &info);

	assert( info==0 && "SVD decomposition failed"!=NULL );

	last_info = info;
  
	//std::cout<<"info= "<<info<<"\n";

      };

      void solve_lu(matrix_double &a, matrix_double &b, matrix_double &x)
      {
	int n = a.size1();
	int m = b.size2();

	assert( a.size2() == n );
	assert( b.size1() == n );

	assert( x.size1() == n && x.size2() == m );

	int info;
	int *ipiv = new int [n];
  
	x = b;

	dgesv(n, m, &a(0,0), n, ipiv, &x(0,0), n, &info);

	last_info = info;

	delete ipiv;

      };

      void solve_lu(matrix_double &a, vector<double> &b, vector<double> &x)
      {
	int n = a.size1();
	int m = 1;
	
	assert( a.size2() == n );
	assert( b.size() == n );
	assert( x.size() == n );

	int info;
	int *ipiv = new int [n];
	
	x = b;

	dgesv(n, m, &a(0,0), n, ipiv, &x(0), n, &info);
	
	last_info = info;

	delete ipiv;
	
      };
      
      void inverse_mat(matrix_double &A)
      {
  
	int n = A.size1();
  
	matrix_double A_(n,n),I(n,n);
	I  = identity_matrix<double>(n,n);

	solve_lu(A,A_,I);

	A=A_;

	return;

      }
      void inverse_mat(matrix_dcomplex &A)
      {
  
	int n = A.size1();
  
	matrix_dcomplex A_(n,n),I(n,n);
	I  = identity_matrix<std::complex<double> >(n,n);

	permutation_matrix<int> P(n);

	int res= lu_factorize(A,P);

	if(res!=0) return;
	swap_rows(P,I);
  
	A_ = solve(A, I, unit_lower_tag());
  
	I = A_;

	A_ = solve(A, I, upper_tag()); 

	A=A_;

	return;

      }


      void eigen_right(matrix_double &a, vector<double> &eig){};

      void diagon(symmatrix_double &a, vector<double> &eig_vals)
      {
	int n = a.size1();
	assert( eig_vals.size() == n );
  
	int info;
	double *empty;

	dspev( 'N', 'U', n, &a(0,0), &eig_vals(0), empty, n, &info);
 
	last_info = info;
      };


      void diagon(matrix_dcomplex &a, vector<double> &eig_vals,matrix_dcomplex &eig_vecs)
      {
	int n = a.size1();
	assert( eig_vals.size() == n );
	assert( eig_vecs.size1() == n && eig_vecs.size2() == n );

	int info;
	//  double *empty;
	{
	  int sz=n*(n+1)/2;

	  std::complex<double> aray[sz];

	  sz=0;

	  for(int i = 0; i < n; i++)
	    for(int j = 0; j <= i; j++)
	      {
		aray[sz] = a(j,i);
		sz++;
	      }

	  sz=0;

	  //   std::cout << "aray\n";
	  //   for(int i = 0; i < n; i++)
	  //     {
	  //       for(int j = 0; j <= i; j++)
	  // 	std::cout<<aray[sz]<<"   ", sz++;
	  //       std::cout<<"\n";
	  //     };

  
	  zhpev('V', 'U', n,(doublecomplex*)&aray[0], &eig_vals(0), (doublecomplex*)&eig_vecs(0,0), n, &info);
	};
	//  delete []aray;
 
	last_info = info;
      };

      void diagon(hermmatrix_dcomplex &a, vector<double> &eig_vals, matrix_dcomplex &eig_vecs)
      {
	int n = a.size1();
	assert( eig_vals.size() == n );
	assert( eig_vecs.size1() == n && eig_vecs.size2() == n );

	int info;  

	zhpev('V', 'U', n,(doublecomplex*)&a.at_element(0,0), &eig_vals(0), (doublecomplex*)&eig_vecs(0,0), n, &info);

	last_info = info;
      };

      void diagon(symmatrix_double &a, vector<double> &eig_vals, matrix_double &eig_vecs)
      {
	int n = a.size1();
 
	assert( eig_vals.size() == n );
 
	assert( eig_vecs.size1() == n && eig_vecs.size2() == n );

  
	int info;

	dspev( 'V', 'U', n, &a(0,0), &eig_vals(0), &eig_vecs(0,0), n, &info); /// it's fucking fuction
 
	last_info = info;
      };

      //--------------------------------------------------------------------------------//
      //                                Projectors                                      //
      //--------------------------------------------------------------------------------//

      void projectors(symmatrix_double &a, vector<double> &lambda, matrix_double &vec)
      {
	int n = a.size1();
	assert( vec.size1() == n );

	int m = lambda.size();
	assert( vec.size2() == m );

	for (int k=0; k<m; k++)
	  {
	    //std::cout << k << "\n";
	    //      dsyr( 'U', n, lambda(k), &vec(0,k), 1, &a(0,0),n);
	    dspr( 'U', n, lambda(k), &vec(0,k), 1, &a(0,0) );
	  };
      };

      //--------------------------------------------------------------------------------//

      void projectors(symmatrix_double &a, double lambda, vector<double> &vec)
      {
	int n = a.size1();
	assert( vec.size() == n );

	dspr( 'U', n, lambda, &vec(0), 1, &a(0,0) );
      };

      //--------------------------------------------------------------------------------//

      void projectors(hermmatrix_dcomplex &a, vector<double> &lambda, matrix_dcomplex &vec)
      {
	int n = a.size1();
	assert( vec.size1() == n );

	int m = lambda.size();
	assert( vec.size2() == m );

	for (int k=0; k<m; k++)
	  {
	    zhpr( 'U', n, lambda(k), (doublecomplex*)&vec(0,k), 1, (doublecomplex*)&a.at_element(0,0) );
	  };
      };

      //--------------------------------------------------------------------------------//
      //                            Matrix multiplication                               //
      //--------------------------------------------------------------------------------//

      void mulmtr(matrix_double &a, symmatrix_double &b, matrix_double &c)
      {
	int m = a.size1();
	int n = a.size2();

	assert( b.size1() == n );
	assert( c.size1() == m && c.size2() == n );

	matrix_double bb(b);

	dsymm( 'R', 'U', m, n, 1e0, &bb(0,0), n, &a(0,0), m, 1e0, &c(0,0), m);
      };

      void mulmtr(matrix_dcomplex &a, matrix_double &b, matrix_dcomplex &c)
      {
	int m = a.size1();
	int n = b.size2();
	int k = a.size2();

	assert( b.size1() == k );
	assert( c.size1() == m && c.size2() == n );

	matrix_dcomplex bb(b);

	std::complex<double> I(0.0e0,1.0e0);
	zgemm( 'N', 'N', m, n, k ,(doublecomplex*) &I,(doublecomplex*)&a(0,0) , 
	       m, (doublecomplex*)&bb(0,0), 
	       b.size1(), (doublecomplex*)&I, (doublecomplex*)&c(0,0), c.size1());

      }
      void mulmtr(matrix_double &a, matrix_dcomplex &b, matrix_dcomplex &c)
      {
	int m = a.size1();
	int n = b.size2();
	int k = a.size2();

	assert( b.size1() == k );
	assert( c.size1() == m && c.size2() == n );

	matrix_dcomplex aa(a);
	matrix_dcomplex bb(b);

	std::complex<double> I(0.0e0,1.0e0);
	zgemm( 'N', 'N', m, n, k ,(doublecomplex*) &I,(doublecomplex*)&aa(0,0) , 
	       m, (doublecomplex*)&bb(0,0), 
	       b.size1(), (doublecomplex*)&I, (doublecomplex*)&c(0,0), c.size1());
      }

      void mulmtr(matrix_dcomplex &a, matrix_dcomplex &b, matrix_dcomplex &c)
      {
	int m = a.size1();
	int n = b.size2();
	int k = a.size2();
  

	std::cout << "size::  a = " << a.size1() << "  " << a.size2() << "  b = " << b.size1() << "  " << b.size2() << "  c = " << c.size1() << " " << c.size2() << "\n" ; 
	assert( b.size1() == k );
	assert( c.size1() == m );
	assert( c.size2() == n );

	matrix_dcomplex bb(b);

	std::complex<double> I(0.0e0,1.0e0);
	zgemm( 'N', 'N', m, n, k ,(doublecomplex*) &I,(doublecomplex*)&a(0,0) , 
	       m, (doublecomplex*)&bb(0,0), 
	       b.size1(), (doublecomplex*)&I, (doublecomplex*)&c(0,0), c.size1());

      }

      void mulmtr(matrix_double &a, matrix_double &b, matrix_double &c)
      {
	int m = a.size1();
	int n = b.size2();
	int k = a.size2();

	assert( b.size1() == n );
	assert( c.size1() == m && c.size2() == n );

	matrix_double bb(b);

	dgemm( 'N', 'N', m, n, k , 1e0, &a(0,0) ,  m, &bb(0,0), b.size1(), 1e0, &c(0,0), c.size1());
      };


      int lapack_info()
      {
	return last_info;
      };

    };
  };
};
