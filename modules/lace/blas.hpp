#ifndef _LACE_BLAS1_H
#define _LACE_BLAS1_H

#include<lace/complex.hpp>
#include<lace/shape.hpp>
#include<lace/storage.hpp>
#include<lace/range.hpp>

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
   
};

#endif
