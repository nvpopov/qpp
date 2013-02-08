#include "lapack.hpp"

#include <mkl_blas.h>
#include <mkl_lapack.h>

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

	char jobz = 'a';
	int lwork = -1;
	int *iwork = new int [8*std::min(m,n)];
	double *work = NULL;

	dgesdd(&jobz, &m, &n, &a(0,0), &m, &sigma(0), &u(0,0), &m, 
	       &vt(0,0), &n, work, &lwork, iwork, &info);

	work = new double [lwork];

	dgesdd(&jobz, &m, &n, &a(0,0), &m, &sigma(0), &u(0,0), &m, 
	       &vt(0,0), &n, work, &lwork, iwork, &info);

	delete iwork;
	delete work;

	//gesdd( char *jobz, MKL_INT *m, MKL_INT *n, double *a, MKL_INT *lda, double *s, double *u, MKL_INT *ldu, double *vt, MKL_INT *ldvt, double *work, MKL_INT *lwork, MKL_INT *iwork, MKL_INT *info );

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
	//void    dgesv( MKL_INT *n, MKL_INT *nrhs, double *a, MKL_INT *lda, MKL_INT *ipiv, 
	//double *b, MKL_INT *ldb, MKL_INT *info );
	dgesv(&n, &m, &a(0,0), &n, ipiv, &x(0,0), &n, &info);

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

	dgesv(&n, &m, &a(0,0), &n, ipiv, &x(0), &n, &info);
	
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
	char jobz='N', uplo='U';
	double *work = new double[3*n];

	//void    dspev( char *jobz, char *uplo, MKL_INT *n, double *ap, double *w, 
	//double *z, MKL_INT *ldz, double *work, MKL_INT *info );

	dspev( &jobz, &uplo, &n, &a(0,0), &eig_vals(0), empty, &n, work, &info);
 
	delete work;
	last_info = info;
      };


      void diagon(symmatrix_double &a, vector<double> &eig_vals, matrix_double &eig_vecs)
      {
	int n = a.size1();
 
	assert( eig_vals.size() == n );
 
	assert( eig_vecs.size1() == n && eig_vecs.size2() == n );

  
	int info;

	double *empty;
	char jobz='V', uplo='U';
	double *work = new double[3*n];

	//void    dspev( char *jobz, char *uplo, MKL_INT *n, double *ap, double *w, 
	//double *z, MKL_INT *ldz, double *work, MKL_INT *info );

	dspev( &jobz, &uplo, &n, &a(0,0), &eig_vals(0), &eig_vecs(0,0), &n, work, &info);
 
	delete work;

	last_info = info;
      };

      void diagon(matrix_dcomplex &a, vector<double> &eig_vals,matrix_dcomplex &eig_vecs)
      {
	int n = a.size1();
	assert( eig_vals.size() == n );
	assert( eig_vecs.size1() == n && eig_vecs.size2() == n );

	int info;
	//  double *empty;
	
	int sz=n*(n+1)/2;

	std::complex<double> aray[sz];

	// fixme!!! - this is not efficient
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

	// void    zhpev( char *jobz, char *uplo, MKL_INT *n, MKL_Complex16 *ap, double *w, 
	//MKL_Complex16 *z, MKL_INT *ldz, MKL_Complex16 *work, double *rwork, MKL_INT *info );
  
	char jobz='V',uplo='U';
	MKL_Complex16 *work = new MKL_Complex16[std::max(1,2*n-1)];
	double *rwork = new double[std::max(1,3*n-2)];

	zhpev(&jobz, &uplo, &n,(MKL_Complex16*)&aray[0], &eig_vals(0), 
	      (MKL_Complex16*)&eig_vecs(0,0), &n, work, rwork, &info);
	
	//  delete []aray;
 
	delete work;
	delete rwork;
	last_info = info;
      };

      void diagon(hermmatrix_dcomplex &a, vector<double> &eig_vals, matrix_dcomplex &eig_vecs)
      {
	int n = a.size1();
	assert( eig_vals.size() == n );
	assert( eig_vecs.size1() == n && eig_vecs.size2() == n );

	int info;  
	char jobz='V',uplo='U';
	MKL_Complex16 *work = new MKL_Complex16[std::max(1,2*n-1)];
	double *rwork = new double[std::max(1,3*n-2)];

	zhpev(&jobz, 
	      &uplo, 
	      &n,
	      (MKL_Complex16*)&a.at_element(0,0), 
	      &eig_vals(0), 
	      (MKL_Complex16*)&eig_vecs(0,0), &n, work, rwork, &info);
	
	//  delete []aray;
 
	delete work;
	delete rwork;

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

	char uplo='U';
	int incx = 1;

	for (int k=0; k<m; k++)
	  {
	    //std::cout << k << "\n";
	    //      dsyr( 'U', n, lambda(k), &vec(0,k), 1, &a(0,0),n);
	    dspr( &uplo, &n, &lambda(k), &vec(0,k), &incx, &a(0,0) );
	  };
      };

      //--------------------------------------------------------------------------------//

      void projectors(symmatrix_double &a, double lambda, vector<double> &vec)
      {
	int n = a.size1();
	assert( vec.size() == n );

	char uplo='U';
	int incx = 1;
	dspr( &uplo, &n, &lambda, &vec(0), &incx, &a(0,0) );
      };

      //--------------------------------------------------------------------------------//

      void projectors(hermmatrix_dcomplex &a, vector<double> &lambda, matrix_dcomplex &vec)
      {
	int n = a.size1();
	assert( vec.size1() == n );

	int m = lambda.size();
	assert( vec.size2() == m );
	//void zhpr(const char *uplo, const MKL_INT *n, const double *alpha, 
	//const MKL_Complex16 *x, const MKL_INT *incx, MKL_Complex16 *ap);

	char uplo='U';
	int incx = 1;
	for (int k=0; k<m; k++)
	  {
	    zhpr( &uplo, &n, &lambda(k), (MKL_Complex16*)&vec(0,k), &incx, 
		  (MKL_Complex16*)&a.at_element(0,0) );
	  };
      };

      //--------------------------------------------------------------------------------//
      //                            Matrix multiplication                               //
      //--------------------------------------------------------------------------------//

//       void mulmtr(matrix_double &a, symmatrix_double &b, matrix_double &c)
//       {
// 	int m = a.size1();
// 	int n = a.size2();

// 	assert( b.size1() == n );
// 	assert( c.size1() == m && c.size2() == n );

// 	matrix_double bb(b);
// 	char side = 'R', uplo = 'U';
// 	double alpha = 1e0;

// 	dsymm( &side, &uplo, &m, &n, &alpha, &bb(0,0), &n, &a(0,0), &m, &alpha, &c(0,0), &m);
//       };

//       void mulmtr(matrix_dcomplex &a, matrix_double &b, matrix_dcomplex &c)
//       {
// 	int m = a.size1();
// 	int n = b.size2();
// 	int k = a.size2();

// 	assert( b.size1() == k );
// 	assert( c.size1() == m && c.size2() == n );

// 	matrix_dcomplex bb(b);

// 	std::complex<double> I(0.0e0,1.0e0);
// 	//void zgemm(const char *transa, const char *transb, const MKL_INT *m, 
// 	//const MKL_INT *n, const MKL_INT *k,
// 	//const MKL_Complex16 *alpha, const MKL_Complex16 *a, const MKL_INT *lda,
// 	//const MKL_Complex16 *b, const MKL_INT *ldb, const MKL_Complex16 *beta,
// 	//MKL_Complex16 *c, const MKL_INT *ldc);
// 	char trans = 'N';

// 	zgemm( &trans, &trans, &m, &n, &k ,(MKL_Complex16*) &I,(MKL_Complex16*)&a(0,0) , 
// 	       m, (MKL_Complex16*)&bb(0,0), 
// 	       b.size1(), (doublecomplex*)&I, (doublecomplex*)&c(0,0), c.size1());

//       }
//       void mulmtr(matrix_double &a, matrix_dcomplex &b, matrix_dcomplex &c)
//       {
// 	int m = a.size1();
// 	int n = b.size2();
// 	int k = a.size2();

// 	assert( b.size1() == k );
// 	assert( c.size1() == m && c.size2() == n );

// 	matrix_dcomplex aa(a);
// 	matrix_dcomplex bb(b);

// 	std::complex<double> I(0.0e0,1.0e0);
// 	zgemm( 'N', 'N', m, n, k ,(doublecomplex*) &I,(doublecomplex*)&aa(0,0) , 
// 	       m, (doublecomplex*)&bb(0,0), 
// 	       b.size1(), (doublecomplex*)&I, (doublecomplex*)&c(0,0), c.size1());
//       }

//       void mulmtr(matrix_dcomplex &a, matrix_dcomplex &b, matrix_dcomplex &c)
//       {
// 	int m = a.size1();
// 	int n = b.size2();
// 	int k = a.size2();
  

// 	std::cout << "size::  a = " << a.size1() << "  " << a.size2() << "  b = " << b.size1() << "  " << b.size2() << "  c = " << c.size1() << " " << c.size2() << "\n" ; 
// 	assert( b.size1() == k );
// 	assert( c.size1() == m );
// 	assert( c.size2() == n );

// 	matrix_dcomplex bb(b);

// 	std::complex<double> I(0.0e0,1.0e0);
// 	zgemm( 'N', 'N', m, n, k ,(doublecomplex*) &I,(doublecomplex*)&a(0,0) , 
// 	       m, (doublecomplex*)&bb(0,0), 
// 	       b.size1(), (doublecomplex*)&I, (doublecomplex*)&c(0,0), c.size1());

//       }

//       void mulmtr(matrix_double &a, matrix_double &b, matrix_double &c)
//       {
// 	int m = a.size1();
// 	int n = b.size2();
// 	int k = a.size2();

// 	assert( b.size1() == n );
// 	assert( c.size1() == m && c.size2() == n );

// 	matrix_double bb(b);

// 	dgemm( 'N', 'N', m, n, k , 1e0, &a(0,0) ,  m, &bb(0,0), b.size1(), 1e0, &c(0,0), c.size1());
//       };


      int lapack_info()
      {
	return last_info;
      };

    };
  };
};
