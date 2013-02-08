#ifndef _LAPACK_H
#define _LAPACK_H

#include <boost/numeric/ublas/hermitian.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/symmetric.hpp>
#include <complex>

namespace boost { 
  namespace numeric { 
    namespace ublas {
      
      // BLAS compatible matrix types
      
      typedef std::complex<double> dcomplex;

      typedef matrix<double,column_major> matrix_double;
      typedef matrix<float,column_major>  matrix_float;
      typedef matrix<std::complex<double>,column_major> matrix_dcomplex;
      //typedef matrix<complex<float>,column_major>  matrix_complex;

      typedef symmetric_matrix<double,upper,column_major>  symmatrix_double;
      typedef hermitian_matrix<std::complex<double>,upper,column_major>  hermmatrix_dcomplex;

      typedef symmetric_matrix<float,lower,column_major>   symmatrix_float;
      
      void sv_decompose( matrix_double &a, vector<double> &sigma, matrix_double &u, matrix_double &vt);
      // Singular value decomposition of matrix a
      //
      // LAPACK : DGESDD
  
      void solve_lu(matrix_double &a, matrix_double &b, matrix_double &x);
      // Returns the solution of lin equations a*x = b
      //
      // LAPACK : DGESV

      void solve_lu(matrix_double &a, vector<double> &b, vector<double> &x);
      // Returns the solution of lin equations a*x = b
      //
      // LAPACK : DGESV

      void inverse_mat(matrix_double &A);
      // returns inverse matrix_double
      // 
      //

      void inverse_mat(matrix_dcomplex &A);
      // returns inverse matrix_dcomplex
      // 
      //

      void eigen_right(matrix_double &a, vector<double> &eig); //?
      // Right eigenvalues of non-symmetric matrix
      //
      // LAPACK : DGEEV

      void diagon(symmatrix_double &a, vector<double> &eig_vals);
      void diagon(symmatrix_double &a, vector<double> &eig_vals, matrix_double &eig_vecs);
      void diagon(matrix_dcomplex &a, vector<double> &eig_vals, matrix_dcomplex &eig_vecs);
      void diagon(hermmatrix_dcomplex &a, vector<double> &eig_vals, matrix_dcomplex &eig_vecs);
      // Diagonalization of symmetric matrix
      //
      // LAPACK : DSPEV, DSPEVD , ZHPEV

      void projectors(symmatrix_double &a, vector<double> &lambda, matrix_double &vec);
      //
      //  Building a += SUM lambda(k)* outer_prod( vec(:,k), vec(:,k) )
      //                 k
      //
      // Using BLAS : DSPR

      void projectors(symmatrix_double &a, double lambda, vector<double> &vec);
      //
      //  Performing a += SUM lambda* outer_prod( vec, vec)
      //                   k
      //
      // BLAS : DSPR
      
      void projectors(hermmatrix_dcomplex &a, vector<double> &lambda, matrix_dcomplex &vec);
      //
      //  Building a += SUM lambda(k)* outer_prod( conj(vec(:,k)), vec(:,k) )
      //                 k
      //
      // Using BLAS : ZHPR

      void mulmtr(matrix_double &a, matrix_double &b, matrix_double &c);
      //
      // c = a*b
      //
      // BLAS : DGEMM

      void mulmtr(matrix_double &a, matrix_dcomplex &b, matrix_dcomplex &c);
      void mulmtr(matrix_dcomplex &a, matrix_double &b, matrix_dcomplex &c);
      //
      // c = a*b
      //
      // BLAS : ZGEMM

      void mulmtr(matrix_dcomplex &a, matrix_dcomplex &b, matrix_dcomplex &c);
      //
      // c = a*b
      //
      // BLAS : ZGEMM

      void mulmtr(matrix_double &a, symmatrix_double &b, matrix_double &c);
      //
      // c += a*b
      //
      // BLAS : DSYMM

      int lapack_info();
      
    };
  };
};

#endif
