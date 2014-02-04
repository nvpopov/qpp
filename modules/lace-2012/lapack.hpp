#ifndef _LACE_LAPACK_H
#define _LACE_LAPACK_H

// #include <lace/matrix.hpp>
// #include <lace/vector.hpp>

#include <lace-2012/shape.hpp>
#include <lace-2012/complex.hpp>

namespace _lace_storage{

//   using _lace_expressions::matrix;
//   using _lace_expressions::vector;
//   using _lace_storage::rectang;
//   using _lace_storage::symmetric;
//   using _lace_storage::hermitian;  
//   using _lace_storage::banddiag;   
//   using _lace_storage::symmband;   
//   using _lace_storage::hermband;   
//   using _lace_storage::triang;
//   using _lace_storage::matrix_type;
//   using _lace_expressions::sub;
//   using _lace_storage::dense;
//   using _lace_storage::sparse;

  template <typename VALTYPE, matrix_type MTRTYPE>
  void _solve_lu(matrix_shape shpa, VALTYPE *A, VALTYPE *y, VALTYPE *x);
  // Solves the equation
  //   Ax = y

  template <typename VALTYPE, matrix_type MTRTYPE>
  void _solve_lu(matrix_shape shpa, matrix_shape shpx, VALTYPE *A, VALTYPE *y, VALTYPE *x);
  // Solves the equation
  //   Ax = y

  //-----------------------------------------------------------------
  template<typename VALTYPE, matrix_type MTP>
  struct eigvals_valtype
  {
    typedef VALTYPE type;
  };

  template<>
  struct eigvals_valtype<lace::fcomplex,hermitian>
  {
    typedef float type;
  };

  template<>
  struct eigvals_valtype<lace::dcomplex,hermitian>
  {
    typedef double type;
  };
  //----------------------------------------------------------------------

  template <typename VALTYPE, matrix_type MTRTYPE>
  void _diagon(matrix_shape shpa, vector_shape shpl, matrix_shape shpx, 
	       VALTYPE *A, typename eigvals_valtype<VALTYPE,MTRTYPE>::type *lambda, VALTYPE *X);
  // Solves the eigenvalue problem
  //
  // A*x(i) = lambda(i)*x(i)

  int lapack_info();

  // ------------------ Template specializaion ---------------------------

  template<>
  void _solve_lu<float,rectang>(matrix_shape shpa, float *A, float *y, float *x);

  template<>
  void _solve_lu<double,rectang>(matrix_shape shpa, double *A, double *y, double *x);

  template<>
  void _solve_lu<lace::fcomplex,rectang>(matrix_shape shpa, lace::fcomplex *A, 
					 lace::fcomplex *y, lace::fcomplex *x);

  template<>
  void _solve_lu<lace::dcomplex,rectang>(matrix_shape shpa, lace::dcomplex *A, 
					 lace::dcomplex *y, lace::dcomplex *x);

  // ---------------------------------------------------------------------

  template<>
  void _solve_lu<float,rectang>(matrix_shape shpa, matrix_shape shpx, float *A, float *y, float *x);

  template<>
  void _solve_lu<double,rectang>(matrix_shape shpa, matrix_shape shpx, double *A, double *y, double *x);

  template<>
  void _solve_lu<lace::fcomplex,rectang>(matrix_shape shpa, matrix_shape shpx, 
					 lace::fcomplex *A, lace::fcomplex *y, lace::fcomplex *x);

  template<>
  void _solve_lu<lace::dcomplex,rectang>(matrix_shape shpa, matrix_shape shpx, 
					 lace::dcomplex *A, lace::dcomplex *y, lace::dcomplex *x);

  // ---------------------------------------------------------------------

  template<>
  void _diagon<float,symmetric>(matrix_shape shpa, vector_shape shpl, matrix_shape shpx, 
					float *A, float *lambda, float *X);

  template<>
  void _diagon<double,symmetric>(matrix_shape shpa, vector_shape shpl, matrix_shape shpx, 
					double *A, double *lambda, double *X);

  template<>
  void _diagon<float,hermitian>(matrix_shape shpa, vector_shape shpl, matrix_shape shpx, 
					float *A, float *lambda, float *X);

  template<>
  void _diagon<double,hermitian>(matrix_shape shpa, vector_shape shpl, matrix_shape shpx, 
					double *A, double *lambda, double *X);
  template<>
  void _diagon<lace::fcomplex,hermitian>(matrix_shape shpa, vector_shape shpl, matrix_shape shpx, 
					 lace::fcomplex *A, float *lambda, lace::fcomplex *X);

  template<>
  void _diagon<lace::dcomplex,hermitian>(matrix_shape shpa, vector_shape shpl, matrix_shape shpx, 
					 lace::dcomplex *A, double *lambda, lace::dcomplex *X);

};

#endif
