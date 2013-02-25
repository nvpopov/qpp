#ifndef _LACE_BLAS_H
#define _LACE_BLAS_H

#include<lace/complex.hpp>
#include<lace/shape.hpp>

namespace _lace_storage{

  /* Templated BLAS interface
   * 
   * The meaningful VALTYPES are
   *       float
   *       double
   *       fcomplex
   *       dcomplex
   */

  template<typename VALTYPE>
  void axpy(int n, VALTYPE a, VALTYPE *x, int incx, VALTYPE *y, int incy);
  // y = y + a*x

  template<typename VALTYPE>
  void copy(int n, VALTYPE *x, int incx, VALTYPE *y, int incy);
  // Copy x -> y

  template<typename VALTYPE>
  void scal(int n, VALTYPE alpha, VALTYPE *y, int incy);
  // y *= a

  template<typename COMPLEX>
  void conj(int n, COMPLEX *x, int incx);
  // x = conj(x)

  //   template<typename VALTYPE>
  //   void asum(int n, VALTYPE *x, int incx);


  template<typename VALTYPE, matrix_type MTPA, matrix_type MTPB, matrix_type MTPC>
  void mulmm(matrix_shape shpa, VALTYPE *A, matrix_shape shpb, VALTYPE *B, matrix_shape shpc, VALTYPE *C,
	     VALTYPE alpha, VALTYPE beta, int opa, int opb);
  //
  // C = alpha*op(A)*op(B) + beta*C
  //
  // This is defined not for all possible A,B,C types combinations bu only for those provided by BLAS
  // Other combinations are done with default_mmm_ternary engine (see engine.hpp)

  // --------- Template specialization for axpy ------------

  template<>
  void axpy<float>(int n, float a, float *x, int incx, float *y, int incy);

  template<>
  void axpy<double>(int n, double a, double *x, int incx, double *y, int incy);

  template<>
  void axpy<lace::fcomplex>(int n, lace::fcomplex a, lace::fcomplex *x, int incx, lace::fcomplex *y, int incy);

  template<>
  void axpy<lace::dcomplex>(int n, lace::dcomplex a, lace::dcomplex *x, int incx, lace::dcomplex *y, int incy);

  // ---------- Template specialization for copy -----------

  template<>
  void copy<float>(int n, float *x, int incx, float *y, int incy);

  template<>
  void copy<double>(int n, double *x, int incx, double *y, int incy);

  template<>
  void copy<lace::fcomplex>(int n, lace::fcomplex *x, int incx, lace::fcomplex *y, int incy);

  template<>
  void copy<lace::dcomplex>(int n, lace::dcomplex *x, int incx, lace::dcomplex *y, int incy);

  // ---------- Template specialization for scal -----------

  template<>
  void scal<float>(int n, float alpha, float *y, int incy);

  template<>
  void scal<double>(int n, double alpha, double *y, int incy);

  template<>
  void scal<lace::fcomplex>(int n, lace::fcomplex alpha, lace::fcomplex *y, int incy);

  template<>
  void scal<lace::dcomplex>(int n, lace::dcomplex alpha, lace::dcomplex *y, int incy);

  // ---------- Template specialization for conj -----------

  template<>
  void conj<float>(int n, float *y, int incy);

  template<>
  void conj<double>(int n, double *y, int incy);

  template<>
  void conj<lace::fcomplex>(int n, lace::fcomplex *x, int incx);

  template<>
  void conj<lace::dcomplex>(int n, lace::dcomplex *x, int incx);

  // ---------- Template specialization for mulmm ----------

  template<>
  void mulmm<float,rectang,rectang,rectang>(matrix_shape shpa, float *A, 
					    matrix_shape shpb, float *B, 
					    matrix_shape shpc, float *C,
					    float alpha, float beta, 
					    int opa, int opb);
  
  template<>
  void mulmm<double,rectang,rectang,rectang>(matrix_shape shpa, double *A, 
					     matrix_shape shpb, double *B, 
					     matrix_shape shpc, double *C,
					     double alpha, double beta,
					     int opa, int opb);
  
  template<>
  void mulmm<lace::fcomplex,rectang,rectang,rectang>(matrix_shape shpa, lace::fcomplex *A, 
						     matrix_shape shpb, lace::fcomplex *B, 
						     matrix_shape shpc, lace::fcomplex *C,
						     lace::fcomplex alpha, lace::fcomplex beta,
						     int opa, int opb);
  
  template<>
  void mulmm<lace::dcomplex,rectang,rectang,rectang>(matrix_shape shpa, lace::dcomplex *A, 
						     matrix_shape shpb, lace::dcomplex *B, 
						     matrix_shape shpc, lace::dcomplex *C,
						     lace::dcomplex alpha, lace::dcomplex beta,
						     int opa, int opb);
  
  template<>
  void mulmm<float,symmetric,rectang,rectang>(matrix_shape shpa, float *A, 
					      matrix_shape shpb, float *B, 
					      matrix_shape shpc, float *C,
					      float alpha, float beta, 
					      int opa, int opb);
  
  template<>
  void mulmm<double,symmetric,rectang,rectang>(matrix_shape shpa, double *A, 
					       matrix_shape shpb, double *B, 
					       matrix_shape shpc, double *C,
					       double alpha, double beta,
					       int opa, int opb);
  template<>
  void mulmm<float,rectang,symmetric,rectang>(matrix_shape shpa, float *A, 
					      matrix_shape shpb, float *B, 
					      matrix_shape shpc, float *C,
					      float alpha, float beta, 
					      int opa, int opb);
  
  template<>
  void mulmm<double,rectang,symmetric,rectang>(matrix_shape shpa, double *A, 
					       matrix_shape shpb, double *B, 
					       matrix_shape shpc, double *C,
					       double alpha, double beta,
					       int opa, int opb);
  
  template<>
  void mulmm<lace::fcomplex,hermitian,rectang,rectang>(matrix_shape shpa, lace::fcomplex *A, 
						       matrix_shape shpb, lace::fcomplex *B, 
						       matrix_shape shpc, lace::fcomplex *C,
						       lace::fcomplex alpha, lace::fcomplex beta,
						       int opa, int opb);
  
  template<>
  void mulmm<lace::dcomplex,hermitian,rectang,rectang>(matrix_shape shpa, lace::dcomplex *A, 
						       matrix_shape shpb, lace::dcomplex *B, 
						       matrix_shape shpc, lace::dcomplex *C,
						       lace::dcomplex alpha, lace::dcomplex beta,
						       int opa, int opb);

  template<>
  void mulmm<lace::fcomplex,rectang,hermitian,rectang>(matrix_shape shpa, lace::fcomplex *A, 
						       matrix_shape shpb, lace::fcomplex *B, 
						       matrix_shape shpc, lace::fcomplex *C,
						       lace::fcomplex alpha, lace::fcomplex beta,
						       int opa, int opb);
  
  template<>
  void mulmm<lace::dcomplex,rectang,hermitian,rectang>(matrix_shape shpa, lace::dcomplex *A, 
						       matrix_shape shpb, lace::dcomplex *B, 
						       matrix_shape shpc, lace::dcomplex *C,
						       lace::dcomplex alpha, lace::dcomplex beta,
						       int opa, int opb);
   
};

#endif
